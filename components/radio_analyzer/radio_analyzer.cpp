#include "radio_analyzer.h"

namespace esphome {
namespace radio_analyzer {


void RadioAnalyzer::setup() {

  ESP_LOGI("radio_analyzer", "Radio Analyzer démarrage");

}


void RadioAnalyzer::loop() {

  if (millis() - last_update_ > 1000) {

    last_update_ = millis();

    float rssi = -100;

    if (rssi_sensor_ != nullptr) {
      rssi_sensor_->publish_state(rssi);
    }

  }

}


}
}
