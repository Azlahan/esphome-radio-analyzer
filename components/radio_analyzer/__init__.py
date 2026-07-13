import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import sensor

from esphome.const import CONF_ID


DEPENDENCIES = ["sensor"]


radio_analyzer_ns = cg.esphome_ns.namespace("radio_analyzer")

RadioAnalyzer = radio_analyzer_ns.class_(
    "RadioAnalyzer",
    cg.Component
)


CONF_RSSI = "rssi"


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RadioAnalyzer),

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

    if CONF_RSSI in config:
        sens = await sensor.new_sensor(config[CONF_RSSI])
        cg.add(
            var.set_rssi_sensor(sens)
        )
