import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, sx127x
from esphome.const import CONF_ID

# Déclaration du namespace C++
radio_analyzer_ns = cg.esphome_ns.namespace("radio_analyzer")
RadioAnalyzer = radio_analyzer_ns.class_("RadioAnalyzer", cg.Component)

# On ne garde que sx127x en dépendance stricte
DEPENDENCIES = ["sx127x"]

CONF_RADIO_ID = "radio_id"
CONF_RSSI = "rssi"
CONF_SNR = "snr"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(RadioAnalyzer),
        cv.Required(CONF_RADIO_ID): cv.use_id(cg.Component),
        cv.Optional(CONF_RSSI): sensor.sensor_schema(
            accuracy_decimals=0,
            device_class="signal_strength",
            state_class="measurement",
        ),
        cv.Optional(CONF_SNR): sensor.sensor_schema(
            accuracy_decimals=1,
            state_class="measurement",
        ),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    # Liaison avec le module radio
    radio = await cg.get_variable(config[CONF_RADIO_ID])
    cg.add(var.set_rx_device(radio))
    
    # Enregistrement du capteur RSSI s'il est configuré
    if CONF_RSSI in config:
        sens = await sensor.new_sensor(config[CONF_RSSI])
        cg.add(var.set_rssi_sensor(sens))
        
    # Enregistrement du capteur SNR s'il est configuré
    if CONF_SNR in config:
        sens = await sensor.new_sensor(config[CONF_SNR])
        cg.add(var.set_snr_sensor(sens))
