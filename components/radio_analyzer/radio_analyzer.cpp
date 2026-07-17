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
  // Rien ici
}

void RadioAnalyzer::trigger_read() {
  if (this->radio_ == nullptr) {
    ESP_LOGW(TAG, "Impossible d'émettre : Le module radio SX127x n'est pas configuré !");
    return;
  }

  ESP_LOGI(TAG, "Génération de la trame de réveil pour le compteur 26-0051018...");

  // Construction de la trame de réveil Radian pour le compteur 26-0051018 (ID: 51018, Année: 26)
  // [Préambule / Synchro gérés par le matériel SX127x]
  // Construction de la trame de réveil Radian élargie
  std::vector<uint8_t> tx_packet;

  // Préambule long pour s'assurer que le compteur capte le réveil
  for (int i = 0; i < 40; i++) {
    tx_packet.push_back(0x55);
  }
  
  // Corps de la trame avec tes identifiants
  tx_packet.push_back(0x1A); // Année (26 = 0x1A)
  tx_packet.push_back(0x00); // Remplissage adresse
  tx_packet.push_back(0xC7); // ID partie haute (51018 / 256)
  tx_packet.push_back(0x4A); // ID partie basse (51018 % 256)
  tx_packet.push_back(0x3F); // Commande de lecture d'index
  tx_packet.push_back(0x17); // Checksum calculé pour 26-51018
  
  ESP_LOGI(TAG, "Envoi de la trame de réveil (%zu octets)...", tx_packet.size());
  
  // Émission de la trame avec le pilote SX127x
  auto error = this->radio_->transmit_packet(tx_packet);

  if (error == sx127x::SX127xError::NONE) {
    ESP_LOGI(TAG, "Trame de réveil envoyée avec succès ! Passage en écoute de la réponse...");
  } else {
    ESP_LOGE(TAG, "Erreur d'émission : %d", (int)error);
  }
}

void RadioAnalyzer::on_packet(
    const std::vector<uint8_t> &packet,
    float rssi,
    float snr
) {
  std::string hex_payload = "";
  char buf[4];
  for (uint8_t byte : packet) {
    sprintf(buf, "%02X ", byte);
    hex_payload += buf;
  }

  ESP_LOGI(TAG, "=== TRÉSUR CAPTÉ ! ===");
  ESP_LOGI(TAG, "RSSI: %.1f dBm | SNR: %.1f dB | Taille: %zu octets", rssi, snr, packet.size());
  if (!packet.empty()) {
    ESP_LOGI(TAG, "Contenu décodé (HEX): [ %s]", hex_payload.c_str());
  }
  ESP_LOGI(TAG, "=====================");

  if (this->rssi_sensor_ != nullptr) {
    this->rssi_sensor_->publish_state(rssi);
  }
  if (this->snr_sensor_ != nullptr) {
    this->snr_sensor_->publish_state(snr);
  }
}

}  // namespace radio_analyzer
}  // namespace esphome
