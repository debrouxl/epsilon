#include "usb_timer.h"
#include "global_preferences.h"
#include "apps_container.h"

bool USBTimer::fire() {
  bool needRedrawing = false;
  if (Ion::USB::isPlugged()) {
    if (!m_previousPluggedState && GlobalPreferences::sharedGlobalPreferences()->examMode() == GlobalPreferences::ExamMode::Activate) {
      m_container->displayExamModePopUp(false);
      needRedrawing = true;
    }
#if LED_WHILE_CHARGING
    KDColor LEDColor = Ion::Battery::isCharging() ? KDColorYellow : KDColorGreen;
    Ion::LED::setColor(LEDColor);
#endif
    if (!m_previousPluggedState) {
      Ion::Backlight::setBrightness(Ion::Backlight::MaxBrightness);
    }
    m_previousPluggedState = true;
  } else {
    if (m_previousPluggedState) {
#if LED_WHILE_CHARGING
      Ion::LED::setColor(KDColorBlack);
#endif
      m_previousPluggedState = false;
    }
  }
  return needRedrawing;
}
