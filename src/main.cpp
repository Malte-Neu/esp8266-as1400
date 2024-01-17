#include "credentials.h" //if this file is missing: rename credentials.h.tpl and fill in your wifi configuration

// Auto generated code by esphome
// ========== AUTO GENERATED INCLUDE BLOCK BEGIN ===========
#include "esphome.h"
#include "elsterAs1400.h"

using namespace esphome;
using std::isnan;
using std::min;
using std::max;
logger::Logger *logger_logger;
web_server_base::WebServerBase *web_server_base_webserverbase;
captive_portal::CaptivePortal *captive_portal_captiveportal;
wifi::WiFiComponent *wifi_wificomponent;
mdns::MDNSComponent *mdns_mdnscomponent;

mqtt::MQTTClientComponent *mqtt_mqttclientcomponent;
using namespace mqtt;
using namespace sensor;
using namespace json;
preferences::IntervalSyncer *preferences_intervalsyncer;
using namespace uart;
uart::ESP8266UartComponent *uart_bus;
esphome::esp8266::ESP8266GPIOPin *esphome_esp8266_esp8266gpiopin;
esphome::esp8266::ESP8266GPIOPin *esphome_esp8266_esp8266gpiopin_2;

mqtt::MQTTSensorComponent *mqtt_mqttsensorcomponent;

mqtt::MQTTSensorComponent *mqtt_mqttsensorcomponent_2;
const uint8_t ESPHOME_ESP8266_GPIO_INITIAL_MODE[16] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, INPUT, 255, OUTPUT, 255};
const uint8_t ESPHOME_ESP8266_GPIO_INITIAL_LEVEL[16] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255};
#define yield() esphome::yield()
#define millis() esphome::millis()
#define micros() esphome::micros()
#define delay(x) esphome::delay(x)
#define delayMicroseconds(x) esphome::delayMicroseconds(x)
// ========== AUTO GENERATED INCLUDE BLOCK END ==========="

void setup() {
  // ========== AUTO GENERATED CODE BEGIN ===========
  // esp8266:
  //   board: d1_mini
  //   framework:
  //     version: 3.0.2
  //     source: ~3.30002.0
  //     platform_version: platformio/espressif8266 @ 3.2.0
  //   restore_from_flash: false
  //   early_pin_init: true
  //   board_flash_mode: dout
  esphome::esp8266::setup_preferences();
  // async_tcp:
  //   {}
  // esphome:
  //   name: electricmeter
  //   build_path: .esphome/build/electricmeter
  //   platformio_options: {}
  //   includes: []
  //   libraries: []
  //   name_add_mac_suffix: false
  //   min_version: 2022.11.2
  App.pre_setup("electricmeter", __DATE__ ", " __TIME__, false);
  // logger:
  //   level: VERY_VERBOSE
  //   id: logger_logger
  //   baud_rate: 115200
  //   tx_buffer_size: 512
  //   deassert_rts_dtr: false
  //   hardware_uart: UART0
  //   logs: {}
  //   esp8266_store_log_strings_in_flash: true
  logger_logger = new logger::Logger(115200, 512);
  logger_logger->set_uart_selection(logger::UART_SELECTION_UART0);
  logger_logger->pre_setup();
  logger_logger->set_component_source("logger");
  App.register_component(logger_logger);
  // web_server_base:
  //   id: web_server_base_webserverbase
  web_server_base_webserverbase = new web_server_base::WebServerBase();
  web_server_base_webserverbase->set_component_source("web_server_base");
  App.register_component(web_server_base_webserverbase);
  // captive_portal:
  //   id: captive_portal_captiveportal
  //   web_server_base_id: web_server_base_webserverbase
  captive_portal_captiveportal = new captive_portal::CaptivePortal(web_server_base_webserverbase);
  captive_portal_captiveportal->set_component_source("captive_portal");
  App.register_component(captive_portal_captiveportal);
  // wifi:
  //   ap:
  //     ssid: Electricmeter Fallback Hotspot
  //     id: wifi_wifiap
  //     ap_timeout: 1min
  //   id: wifi_wificomponent
  //   domain: .local
  //   reboot_timeout: 15min
  //   power_save_mode: NONE
  //   fast_connect: false
  //   output_power: 20.0
  //   networks:
  //   - ssid: Luftkabel
  //     password: '0045762572566523437215'
  //     id: wifi_wifiap_2
  //     priority: 0.0
  //   use_address: electricmeter.local
  wifi_wificomponent = new wifi::WiFiComponent();
  wifi_wificomponent->set_use_address("electricmeter.local");
  {
  wifi::WiFiAP wifi_wifiap_2 = wifi::WiFiAP();
  wifi_wifiap_2.set_ssid(WIFI_SSID );
  wifi_wifiap_2.set_password(WIFI_PW );
  wifi_wifiap_2.set_priority(0.0f);
  wifi_wificomponent->add_sta(wifi_wifiap_2);
  }
  {
  wifi::WiFiAP wifi_wifiap = wifi::WiFiAP();
  wifi_wifiap.set_ssid("Electricmeter Fallback Hotspot");
  wifi_wificomponent->set_ap(wifi_wifiap);
  }
  wifi_wificomponent->set_ap_timeout(60000);
  wifi_wificomponent->set_reboot_timeout(900000);
  wifi_wificomponent->set_power_save_mode(wifi::WIFI_POWER_SAVE_NONE);
  wifi_wificomponent->set_fast_connect(false);
  wifi_wificomponent->set_output_power(20.0f);
  wifi_wificomponent->set_component_source("wifi");
  App.register_component(wifi_wificomponent);
  // mdns:
  //   id: mdns_mdnscomponent
  //   disabled: false
  mdns_mdnscomponent = new mdns::MDNSComponent();
  mdns_mdnscomponent->set_component_source("mdns");
  App.register_component(mdns_mdnscomponent);
  // mqtt:
  //   broker: openhabian
  //   keepalive: 180s
  //   id: mqtt_mqttclientcomponent
  //   port: 1883
  //   username: ''
  //   password: ''
  //   discovery: true
  //   discovery_retain: true
  //   discovery_prefix: homeassistant
  //   discovery_unique_id_generator: legacy
  //   discovery_object_id_generator: none
  //   use_abbreviations: true
  //   topic_prefix: electricmeter
  //   reboot_timeout: 15min
  //   birth_message:
  //     topic: electricmeter/status
  //     payload: online
  //     qos: 0
  //     retain: true
  //   will_message:
  //     topic: electricmeter/status
  //     payload: offline
  //     qos: 0
  //     retain: true
  //   shutdown_message:
  //     topic: electricmeter/status
  //     payload: offline
  //     qos: 0
  //     retain: true
  //   log_topic:
  //     topic: electricmeter/debug
  //     qos: 0
  //     retain: true
  mqtt_mqttclientcomponent = new mqtt::MQTTClientComponent();
  mqtt_mqttclientcomponent->set_component_source("mqtt");
  App.register_component(mqtt_mqttclientcomponent);
  mqtt_mqttclientcomponent->set_broker_address(MQTT_BROKER_IP);
  mqtt_mqttclientcomponent->set_broker_port(1883);
  mqtt_mqttclientcomponent->set_username("");
  mqtt_mqttclientcomponent->set_password("");
  mqtt_mqttclientcomponent->set_discovery_info("homeassistant", mqtt::MQTT_LEGACY_UNIQUE_ID_GENERATOR, mqtt::MQTT_NONE_OBJECT_ID_GENERATOR, true);
  mqtt_mqttclientcomponent->set_topic_prefix("electricmeter");
  mqtt_mqttclientcomponent->set_birth_message(mqtt::MQTTMessage{
      .topic = "electricmeter/status",
      .payload = "online",
      .qos = 0,
      .retain = true,
  });
  mqtt_mqttclientcomponent->set_last_will(mqtt::MQTTMessage{
      .topic = "electricmeter/status",
      .payload = "offline",
      .qos = 0,
      .retain = true,
  });
  mqtt_mqttclientcomponent->set_shutdown_message(mqtt::MQTTMessage{
      .topic = "electricmeter/status",
      .payload = "offline",
      .qos = 0,
      .retain = true,
  });
  mqtt_mqttclientcomponent->set_log_message_template(mqtt::MQTTMessage{
      .topic = "electricmeter/debug",
      .payload = "",
      .qos = 0,
      .retain = true,
  });
  mqtt_mqttclientcomponent->set_keep_alive(180);
  mqtt_mqttclientcomponent->set_reboot_timeout(900000);
  // sensor:
  // json:
  //   {}
  // preferences:
  //   id: preferences_intervalsyncer
  //   flash_write_interval: 60s
  preferences_intervalsyncer = new preferences::IntervalSyncer();
  preferences_intervalsyncer->set_write_interval(60000);
  preferences_intervalsyncer->set_component_source("preferences");
  App.register_component(preferences_intervalsyncer);
  // uart:
  //   id: uart_bus
  //   tx_pin:
  //     number: 14
  //     mode:
  //       output: true
  //       analog: false
  //       input: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     inverted: false
  //     id: esphome_esp8266_esp8266gpiopin
  //   rx_pin:
  //     number: 12
  //     mode:
  //       input: true
  //       analog: false
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     inverted: false
  //     id: esphome_esp8266_esp8266gpiopin_2
  //   baud_rate: 9600
  //   data_bits: 8
  //   parity: NONE
  //   stop_bits: 1
  //   debug:
  //     direction: BOTH
  //     sequence:
  //     - then:
  //       - lambda: !lambda |-
  //           UARTDebug::log_string(direction, bytes);
  //         type_id: lambdaaction
  //       trigger_id: trigger
  //       automation_id: automation
  //     trigger_id: uart_uartdebugger
  //     after:
  //       bytes: 150
  //       timeout: 100ms
  //     dummy_receiver: false
  //     dummy_receiver_id: uart_uartdummyreceiver
  //   rx_buffer_size: 256
  uart_bus = new uart::ESP8266UartComponent();
  uart_bus->set_component_source("uart");
  App.register_component(uart_bus);
  uart_bus->set_baud_rate(300);
  esphome_esp8266_esp8266gpiopin = new esphome::esp8266::ESP8266GPIOPin();
  esphome_esp8266_esp8266gpiopin->set_pin(14);
  esphome_esp8266_esp8266gpiopin->set_inverted(false);
  esphome_esp8266_esp8266gpiopin->set_flags(gpio::Flags::FLAG_OUTPUT);
  uart_bus->set_tx_pin(esphome_esp8266_esp8266gpiopin);
  esphome_esp8266_esp8266gpiopin_2 = new esphome::esp8266::ESP8266GPIOPin();
  esphome_esp8266_esp8266gpiopin_2->set_pin(12);
  esphome_esp8266_esp8266gpiopin_2->set_inverted(false);
  esphome_esp8266_esp8266gpiopin_2->set_flags(gpio::Flags::FLAG_INPUT);
  uart_bus->set_rx_pin(esphome_esp8266_esp8266gpiopin_2);
  uart_bus->set_rx_buffer_size(256);
  uart_bus->set_stop_bits(1);
  uart_bus->set_data_bits(7);
  uart_bus->set_parity(uart::UART_CONFIG_PARITY_EVEN);

  // =========== AUTO GENERATED CODE END ============

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  using namespace as1400;
  As1440Meter *as1440_meter;
  as1440_meter = new As1440Meter(60000);
  as1440_meter->set_uart_parent(uart_bus);
  as1440_meter->set_component_source("Elster AS1440");

  App.register_component(as1440_meter);


  As1400Sensor *sensor_1 = new As1400Sensor("Total kwh in", "1.8.1");
  App.register_sensor(sensor_1);
  sensor_1->set_disabled_by_default(false);
  sensor_1->set_device_class("energy");
  sensor_1->set_state_class(sensor::STATE_CLASS_TOTAL_INCREASING);
  sensor_1->set_unit_of_measurement("kWh");
  sensor_1->set_accuracy_decimals(4);
  sensor_1->set_force_update(false);
  mqtt_mqttsensorcomponent = new mqtt::MQTTSensorComponent(sensor_1);
  mqtt_mqttsensorcomponent->set_component_source("mqtt");
  App.register_component(mqtt_mqttsensorcomponent);
  as1440_meter->register_sensor(sensor_1);


  As1400Sensor *sensor_2 = new As1400Sensor("Current power in", "1.7.0");
  App.register_sensor(sensor_2);
  sensor_2->set_disabled_by_default(false);
  sensor_2->set_icon("mdi:lightning-bolt");
  sensor_2->set_device_class("power");
  sensor_2->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  sensor_2->set_unit_of_measurement("W");
  sensor_2->set_accuracy_decimals(0);
  sensor_2->set_multiplier(1000);
  sensor_2->set_force_update(false);
  mqtt_mqttsensorcomponent_2 = new mqtt::MQTTSensorComponent(sensor_2);
  mqtt_mqttsensorcomponent_2->set_component_source("mqtt");
  App.register_component(mqtt_mqttsensorcomponent_2);
  as1440_meter->register_sensor(sensor_2);


  App.setup();
}

void loop() {
  App.loop();
}
