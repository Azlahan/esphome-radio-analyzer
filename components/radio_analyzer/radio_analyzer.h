#pragma once

#include "esphome/core/component.h"

namespace esphome {
namespace radio_analyzer {


class RadioAnalyzer : public Component {

 public:

  void setup() override;
  void loop() override;

};


}
}
