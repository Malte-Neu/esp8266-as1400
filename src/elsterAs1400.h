#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/log.h"
#include <Arduino.h>
#include <regex>

using namespace esphome;
using namespace sensor;

namespace esphome {
namespace as1400 {

static const char *const TAG = "as1400";

class As1400Sensor : public Sensor {
    public:
        As1400Sensor(const std::string &name, const std::string &code) : Sensor(name) {this->code = code; this->multiplier = 1;}
        std::string code;
        void set_multiplier(int multiplier){ this->multiplier = multiplier;}
        int get_multiplier() { return this->multiplier; }
    private:
        int multiplier;
};


class As1440Meter : public PollingComponent, public uart::UARTDevice {
    public:
        As1440Meter(uint32_t update_interval);

        void loop() override;

        void update() override;

        void dump_config() override;

        void register_sensor(As1400Sensor *sensor);

    private:
        std::vector<As1400Sensor*> sensor_list;
        std::vector<char> incoming_data_buffer;
        std::regex read_data_pattern;
        bool is_in_read_mode;
        bool first_run;
        bool read_data_to_buffer();
        void read_data_to_bin();
        void check_eof();
        void update_sensor(std::string data);
        std::string readline();
};

}}//namespace