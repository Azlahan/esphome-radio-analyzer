# ESPHome Radio Analyzer (433 MHz) 📻

Ce composant personnalisé pour **ESPHome** permet de transformer une carte de développement **LilyGO T3 LoRa32 (v1.6.1)** en un analyseur de spectre et récepteur de paquets radio bruts sur la fréquence **433.92 MHz**. 

Il est idéal pour intercepter, analyser et débugger les signaux de sondes météo, télécommandes sans fil ou autres objets connectés utilisant la modulation FSK/OOK dans cette bande de fréquences.

---

## 🚀 Fonctionnalités
- 🛰️ **Scan de paquets bruts** via le module radio SX1278.
- 📊 **Mesures en temps réel** de la force du signal (**RSSI**) et du rapport signal/bruit (**SNR**).
- 🖥️ **Affichage OLED intégré** (SSD1306) affichant le RSSI en dBm avec une jauge graphique dynamique.
- 💾 **Dump hexadécimal** complet des trames captées directement dans les logs ESPHome (niveau `INFO`).

---

## 🛠️ Schéma de câblage (LilyGO T3 v1.6.1)

Le module radio **SX1278** et l'écran **OLED** intégrés à la carte LilyGO utilisent les broches (GPIO) suivantes :

| Périphérique | Fonction | GPIO |
| :--- | :--- | :--- |
| **Écran OLED** (I2C) | SDA / SCL | `GPIO21` / `GPIO22` |
| **Module SX1278** (SPI) | CLK / MOSI / MISO | `GPIO5` / `GPIO27` / `GPIO19` |
| | CS / RST / DIO0 | `GPIO18` / `GPIO23` / `GPIO26` |

---

## 💻 Installation Rapide

Pour installer cet analyseur sur ta carte depuis Home Assistant :

1. Crée un nouvel appareil **ESPHome** (type ESP32).
2. Copie-colle la configuration présente dans le fichier [examples/lilygo_t3_v1_6_1.yaml](examples/lilygo_t3_v1_6_1.yaml).
3. Remplace les lignes Wi-Fi par tes identifiants personnels :
   ```yaml
   wifi:
     ssid: "TON_RESEAU_WIFI"
     password: "TON_MOT_DE_PASSE"
