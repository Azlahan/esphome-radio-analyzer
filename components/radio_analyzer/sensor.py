import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import sensor

from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_SIGNAL_STRENGTH,
    UNIT_DECIBEL,
)


radio_analyzer_ns = cg.esphome_ns.namespace("radio_analyzer")

RadioAnalyzer = radio_analyzer_ns.class_(
    "RadioAnalyzer",
    cg.Component
)


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RadioAnalyzer),

    cv.Optional("rssi"): sensor.sensor_schema(
        unit_of_measurement=UNIT_DECIBEL,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_SIGNAL_STRENGTH,
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
