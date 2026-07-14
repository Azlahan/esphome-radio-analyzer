#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/sx127x/sx127x.h"

namespace esphome {
namespace radio_analyzer {

class RadioAnalyzer : public Component, public sx127x::SX127xListener {
 public:
  void setup() override;
  void dump_config() override;

  void set_rssi_sensor(sensor::Sensor *sensor) {
    this->rssi_sensor_ = sensor;
  }

  void on_packet(const std::vector<uint8_t> &packet, float rssi, float snr) override;

 protected:
  sensor::Sensor *rssi_sensor_{nullptr};
  uint32_t packet_count_{0};
};

}  // namespace radio_analyzer
}  // namespace esphome
