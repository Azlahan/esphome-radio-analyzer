import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import sensor, sx127x

from esphome.const import CONF_ID


DEPENDENCIES = ["sensor", "sx127x"]


radio_analyzer_ns = cg.esphome_ns.namespace("radio_analyzer")

RadioAnalyzer = radio_analyzer_ns.class_(
    "RadioAnalyzer",
    cg.Component
)


CONF_RSSI = "rssi"
CONF_RADIO_ID = "radio_id"


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RadioAnalyzer),

    cv.Required(CONF_RADIO_ID): cv.use_id(sx127x.SX127x),

    cv.Optional(CONF_RSSI): sensor.sensor_schema(
        accuracy_decimals=0,
        unit_of_measurement="dBm",
    ),
})


async def to_code(config):

    var = cg.new_Pvariable(
        config[CONF_ID]
    )

    await cg.register_component(
        var,
        config
    )

    radio = await cg.get_variable(
        config[CONF_RADIO_ID]
    )

    cg.add(
        var.set_radio(radio)
    )


    if CONF_RSSI in config:
        sens = await sensor.new_sensor(config[CONF_RSSI])

        cg.add(
            var.set_rssi_sensor(sens)
        )