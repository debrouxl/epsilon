#ifndef HARDWARE_TEST_APP_H
#define HARDWARE_TEST_APP_H

#include <escher.h>
#include "usb_test_controller.h"
#include "keyboard_test_controller.h"

class AppsContainer;

namespace HardwareTest {

class App final : public ::App {
public:
  class Snapshot final : public ::App::Snapshot {
  public:
    App * unpack(Container * container) override;
    Descriptor * descriptor() override {
      return &s_descriptor;
    }
  private:
    static App::Descriptor s_descriptor;
  };
  ViewController * USBController() {
    return &m_USBTestController;
  }
  int numberOfTimers() override;
  Timer * timerAtIndex(int i) override;
  bool processEvent(Ion::Events::Event e) override;
private:
  App(Container * container, Snapshot * snapshot) :
    ::App(container, snapshot, &m_keyboardController),
    m_keyboardController(&m_modalViewController),
    m_USBTestController(nullptr) {}
  KeyboardTestController m_keyboardController;
  USBTestController m_USBTestController;
};

}

#endif

