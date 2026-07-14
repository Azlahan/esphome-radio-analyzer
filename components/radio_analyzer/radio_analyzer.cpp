#include "radio_analyzer.h"
#include "esphome/core/log.h"

namespace esphome {
namespace radio_analyzer {

static const char *const TAG = "radio_analyzer";


void RadioAnalyzer::setup() {
  ESP_LOGI(TAG, "Radio Analyzer initialisé");
}


void RadioAnalyzer::dump_config() {
  ESP_LOGCONFIG(TAG, "Radio Analyzer");
}


void RadioAnalyzer::on_packet(
    const std::vector<uint8_t> &packet,
    float rssi,
    float snr) {

  this->packet_count_++;

  ESP_LOGI(TAG, "==============================");
  ESP_LOGI(TAG, "Packet #%u", this->packet_count_);
  ESP_LOGI(TAG, "Length : %d bytes", packet.size());
  ESP_LOGI(TAG, "RSSI   : %.1f dBm", rssi);
  ESP_LOGI(TAG, "SNR    : %.1f dB", snr);


  std::string payload;

  char buffer[4];

  for (auto byte : packet) {
    snprintf(buffer, sizeof(buffer), "%02X ", byte);
    payload += buffer;
  }

  ESP_LOGI(TAG, "Payload: %s", payload.c_str());
  ESP_LOGI(TAG, "==============================");


  if (this->rssi_sensor_ != nullptr) {
    this->rssi_sensor_->publish_state(rssi);
  }
}

}  // namespace radio_analyzer
}  // namespace esphome
