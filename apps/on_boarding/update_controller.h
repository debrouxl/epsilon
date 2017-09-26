#ifndef ON_BOARDING_UPDATE_CONTROLLER_H
#define ON_BOARDING_UPDATE_CONTROLLER_H

#include "../shared/message_controller.h"

namespace OnBoarding {

class UpdateController final : public MessageController {
public:
  UpdateController() : MessageController(sOnBoardingMessages, sOnBoardingColors) {}
  bool handleEvent(Ion::Events::Event event) override;
private:
  static I18n::Message sOnBoardingMessages[];
  static KDColor sOnBoardingColors[];
};

}

#endif

