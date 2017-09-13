#ifndef APPS_USB_TIMER_H
#define APPS_USB_TIMER_H

#include <escher.h>

class AppsContainer;

class USBTimer final : public Timer {
public:
  constexpr USBTimer(AppsContainer * container) : Timer(1), m_container(container), m_previousPluggedState(false) {}
private:
  bool fire() override;
  AppsContainer * m_container;
  bool m_previousPluggedState;
};

#endif

