import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.const import CONF_ID


radio_analyzer_ns = cg.esphome_ns.namespace("radio_analyzer")

RadioAnalyzer = radio_analyzer_ns.class_(
    "RadioAnalyzer",
    cg.Component
)


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RadioAnalyzer),
})
