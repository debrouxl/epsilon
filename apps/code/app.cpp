#include "app.h"
#include "../apps_container.h"
#include <assert.h>

namespace Code {

App::Descriptor App::Snapshot::s_descriptor;

I18n::Message App::sCodeMessages[] = {I18n::Message::BetaVersion, I18n::Message::BetaVersionMessage1, I18n::Message::BetaVersionMessage2, I18n::Message::BetaVersionMessage3, I18n::Message::BetaVersionMessage4};

KDColor App::sCodeColors[] = {KDColorBlack, KDColorBlack, KDColorBlack, KDColorBlack, KDColorBlack};

void App::didBecomeActive(Window * window) {
  ::App::didBecomeActive(window);
  displayModalViewController(&m_betaVersionController, 0.5f, 0.5f);
}

}
