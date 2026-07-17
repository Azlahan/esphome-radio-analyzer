import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import sensor, sx127x
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_SIGNAL_STRENGTH,
    UNIT_DECIBEL,
)

# On indique qu'on dépend de sx127x et du domaine sensor d'ESPHome
DEPENDENCIES = ["sensor", "sx127x"]

radio_analyzer_ns = cg.esphome_ns.namespace("radio_analyzer")

RadioAnalyzer = radio_analyzer_ns.class_(
    "RadioAnalyzer",
    cg.Component
)

CONF_RADIO_ID = "radio_id"
CONF_RSSI = "rssi"
CONF_SNR = "snr"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RadioAnalyzer),

    # Liaison avec le module radio
    cv.Required(CONF_RADIO_ID): cv.use_id(sx127x.SX127x),

    # Capteur RSSI optionnel
    cv.Optional(CONF_RSSI): sensor.sensor_schema(
        unit_of_measurement=UNIT_DECIBEL,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_SIGNAL_STRENGTH,
    ),

    # Capteur SNR optionnel (très utile pour le SX127x en LoRa)
    cv.Optional(CONF_SNR): sensor.sensor_schema(
        unit_of_measurement="dB",
        accuracy_decimals=1,
    ),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # Récupération et assignation du module radio
    radio = await cg.get_variable(config[CONF_RADIO_ID])
    cg.add(var.set_radio(radio))

    # Configuration des capteurs si présents dans le YAML
    if CONF_RSSI in config:
        sens_rssi = await sensor.new_sensor(config[CONF_RSSI])
        cg.add(var.set_rssi_sensor(sens_rssi))

    if CONF_SNR in config:
        sens_snr = await sensor.new_sensor(config[CONF_SNR])
        cg.add(var.set_snr_sensor(sens_snr))
