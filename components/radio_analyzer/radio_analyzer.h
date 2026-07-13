#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace radio_analyzer {

class RadioAnalyzer : public Component {

 public:

  void setup() override;
  void loop() override;

  void set_rssi_sensor(sensor::Sensor *sensor) {
    rssi_sensor_ = sensor;
  }

 protected:

  sensor::Sensor *rssi_sensor_{nullptr};

  unsigned long last_update_{0};

};


}
}
