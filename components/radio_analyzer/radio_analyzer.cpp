#include "radio_analyzer.h"
#include "esphome/core/log.h"

namespace esphome {
namespace radio_analyzer {

static const char *const TAG = "radio_analyzer";

void RadioAnalyzer::setup() {
  if (this->radio_ != nullptr) {
    this->radio_->register_listener(this);
  }
}

void RadioAnalyzer::loop() {
  // Rien ici pour préserver les performances de l'ESP32
}

void RadioAnalyzer::on_packet(
    const std::vector<uint8_t> &packet,
    float rssi,
    float snr
) {
  // Conversion de la charge utile en hexadécimal lisible
  std::string hex_payload = "";
  char buf[4];
  for (uint8_t byte : packet) {
    sprintf(buf, "%02X ", byte);
    hex_payload += buf;
  }

  // Log des détails dans la console ESPHome
  ESP_LOGI(TAG, "Packet reçu ! RSSI: %.1f dBm | SNR: %.1f dB | Taille: %zu octets", rssi, snr, packet.size());
  if (!packet.empty()) {
    ESP_LOGI(TAG, "  Contenu (HEX): [ %s]", hex_payload.c_str());
  }

  // Publication vers Home Assistant
  if (this->rssi_sensor_ != nullptr) {
    this->rssi_sensor_->publish_state(rssi);
  }
  if (this->snr_sensor_ != nullptr) {
    this->snr_sensor_->publish_state(snr);
  }
}

}  // namespace radio_analyzer
}  // namespace esphome
