#include "elsterAs1400.h"

namespace esphome {
namespace as1400 {

static const char END_TEXT = 0x03;
static const char LINE_END = '\n';
static const char *const REQUEST_SEQUENCE = "/?!\r\n";
static const uint32_t MAX_READ_TIME = 20;

As1440Meter::As1440Meter(uint32_t update_interval) : PollingComponent(update_interval) {
    is_in_read_mode = false;
    first_run = true;
    read_data_pattern = std::regex("^(\\d\\.\\d\\.\\d)\\((\\d+\\.\\d+).*");
}


void As1440Meter::loop() {
    if (is_in_read_mode ) {
        read_data_to_buffer();
        std::string data;
        do {
            data = readline();
            if (data != "") {
                update_sensor(data);
            }
        } while (data != "");

        check_eof();
    } else {
        read_data_to_bin();
    }
}

void As1440Meter::update_sensor(std::string data) {
    std::cmatch match;
    std::regex_match(data.c_str(), match, read_data_pattern);
    if (match.size() > 0) {
        std::string code = match[1].str();
        std::string value = match[2].str();
        ESP_LOGV(TAG, "measurement extracted: code \"%s\" value \"%s\" in inputdata \"%s\"", code.c_str(), value.c_str(), data.c_str());
        if (first_run) {
            ESP_LOGI(TAG, "Measurement found for code \"%s\" rawdata \"%s\"", code.c_str(), value.c_str());
        }

        bool sensor_found = false;
        for (As1400Sensor *sensor : sensor_list) {
            if (sensor->code == code) {
                digitalWrite(LED_BUILTIN, LOW);
                ESP_LOGD(TAG, "New data for sensor %s extracted from \"%s\": Code \"%s\" value \"%s\"", sensor->get_name().c_str(), data.c_str(), code.c_str(), value.c_str());

                char * pEnd = NULL;
                float dec_value = strtof(value.c_str(), &pEnd);
                if (*pEnd) { // error was detected
                    ESP_LOGW(TAG, "Error convert string (\"%s\") to floatvalue.", value.c_str());
                } else {
                    dec_value = dec_value * sensor->get_multiplier();
                    sensor->publish_state(dec_value);
                }
                sensor_found = true;
                digitalWrite(LED_BUILTIN, HIGH);
            }
        }

        if (! sensor_found) {
            ESP_LOGV(TAG, "No sensor registered for code \"%s\"", code.c_str());
        }
    } else {
        ESP_LOGV(TAG, "No measurementdata found in inputdata \"%s\"", data.c_str());
    }
}

void As1440Meter::check_eof() {
    if (incoming_data_buffer.size() > 1024) {
        ESP_LOGW(TAG, "Buffer to large, maybe wrong data received. Will delete all data. Size %d content\"%s\"", incoming_data_buffer.size(), incoming_data_buffer.data());
        is_in_read_mode = false;
        incoming_data_buffer.clear();
        incoming_data_buffer.shrink_to_fit();
        first_run = false;
    }

    for (char i : incoming_data_buffer) {
        if (i == LINE_END)
            break; //still line data available
        if (i == END_TEXT) {
            ESP_LOGV(TAG, "eof reached. exit readmode.");
            is_in_read_mode = false;
            incoming_data_buffer.clear();
            first_run = false;
        }
    }
}

void As1440Meter::register_sensor(As1400Sensor *sensor) {
    this->sensor_list.push_back(sensor);
}

bool As1440Meter::read_data_to_buffer() {
    size_t start_count = incoming_data_buffer.size();
    uint32_t read_timeout = millis() + MAX_READ_TIME;

    //read all available until timeout or \n
    char c = ' ';
    while (available() && (millis() < read_timeout)) {
        c = read();
        if (c == '\r')
            continue; // ignore \r, we only depend on \n
        incoming_data_buffer.emplace_back(c);
    }
    if (incoming_data_buffer.size() > start_count) {
        ESP_LOGVV(TAG, "read_data_to_buffer: new Data received (%d chars) current buffer \"%s\"", incoming_data_buffer.size() - start_count, incoming_data_buffer.data());
    }
    return incoming_data_buffer.size() > start_count;
}

void As1440Meter::read_data_to_bin() {
    uint32_t read_timeout = millis() + MAX_READ_TIME;
    while (available() && (millis() < read_timeout)) {
        read();
    }
}

std::string As1440Meter::readline() {
    int new_line_pos = -1;
    int i = 0;
    bool found = false;
    while (i < incoming_data_buffer.size()) {
        if (incoming_data_buffer[i] == LINE_END) {
            new_line_pos = i;
            break;
        }
        i++;
    }

    if (new_line_pos > -1) {
        std::string line_data(incoming_data_buffer.cbegin(), incoming_data_buffer.cbegin() + new_line_pos);
        incoming_data_buffer.erase(incoming_data_buffer.begin(), incoming_data_buffer.begin() + new_line_pos + 1);
        ESP_LOGV(TAG, "readline()  line_data: \"%s\" still in buffer: \"%s\" ", line_data.c_str(), incoming_data_buffer.data());
        return line_data;
    }
    return "";
}

void As1440Meter::update() {
    ESP_LOGD(TAG, "As1440Meter update");
    if (this->is_in_read_mode) {
        ESP_LOGW(TAG, "Still in read mode. Updateinterval to short or wrong data received. Will clear data and reset read mode. Data in buffer \"%s\"", incoming_data_buffer.data());
        incoming_data_buffer.clear();
        this->is_in_read_mode = false;
    } else {
        //enable read mode. Polling is executed in loop
        this->is_in_read_mode = true;
        write_str(REQUEST_SEQUENCE);
        incoming_data_buffer.clear();
    }
}

void As1440Meter::dump_config() {
    ESP_LOGCONFIG(TAG, "As1440Meter dump_config");
    ESP_LOGCONFIG(TAG, "Registered sensors:");
    for (As1400Sensor *sensor : sensor_list) {
        ESP_LOGCONFIG(TAG, " %s", sensor->get_name().data());
    }
    ESP_LOGCONFIG(TAG, "Total %d", sensor_list.size());
}


}} //namespace
