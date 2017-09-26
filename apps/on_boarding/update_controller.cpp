#include "update_controller.h"
#include "../apps_container.h"
#include <assert.h>

namespace OnBoarding {

I18n::Message UpdateController::sOnBoardingMessages[] = {I18n::Message::UpdateAvailable, I18n::Message::UpdateMessage1, I18n::Message::UpdateMessage2, I18n::Message::UpdateMessage3, I18n::Message::UpdateMessage4};

KDColor UpdateController::sOnBoardingColors[] = {KDColorBlack, KDColorBlack, KDColorBlack, KDColorBlack, Palette::YellowDark};

bool UpdateController::handleEvent(Ion::Events::Event event) {
  if (event != Ion::Events::Back && event != Ion::Events::OnOff) {
    app()->dismissModalViewController();
    AppsContainer * appsContainer = (AppsContainer *)app()->container();
    if (appsContainer->activeApp()->snapshot() == appsContainer->onBoardingAppSnapshot()) {
      appsContainer->refreshPreferences();
      appsContainer->switchTo(appsContainer->appSnapshotAtIndex(0));
    }
    return true;
  }
  return false;
}

}
