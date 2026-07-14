#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/sx127x/sx127x.h"

namespace esphome {
namespace radio_analyzer {

class RadioAnalyzer : public Component,
                      public sx127x::SX127xListener {
 public:

  void setup() override;
  void loop() override;

  void set_rssi_sensor(sensor::Sensor *sensor) {
    this->rssi_sensor_ = sensor;
  }

  void set_radio(sx127x::SX127x *radio) {
    this->radio_ = radio;
  }

  void on_packet(
      const std::vector<uint8_t> &packet,
      float rssi,
      float snr
  ) override;


 protected:

  sx127x::SX127x *radio_{nullptr};

  sensor::Sensor *rssi_sensor_{nullptr};

};

}  // namespace radio_analyzer
}  // namespace esphome
