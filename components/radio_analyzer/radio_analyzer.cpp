#include "radio_analyzer.h"

namespace esphome {
namespace radio_analyzer {


void RadioAnalyzer::setup() {

  if (this->radio_ != nullptr) {
    this->radio_->register_listener(this);
  }

}


void RadioAnalyzer::loop() {
}


void RadioAnalyzer::on_packet(
    const std::vector<uint8_t> &packet,
    float rssi,
    float snr
) {

  ESP_LOGD(
      "radio_analyzer",
      "Packet reçu RSSI %.1f SNR %.1f",
      rssi,
      snr
  );


  if (this->rssi_sensor_ != nullptr) {
    this->rssi_sensor_->publish_state(rssi);
  }

}


}  // namespace radio_analyzer
}  // namespace esphome
