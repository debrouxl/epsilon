#ifndef HARDWARE_TEST_KEYBOARD_CONTROLLER_H
#define HARDWARE_TEST_KEYBOARD_CONTROLLER_H

#include <escher.h>
#include "keyboard_view.h"
#include "screen_test_controller.h"

namespace HardwareTest {

class KeyboardTestController final : public ViewController {
public:
  KeyboardTestController(Responder * parentResponder);
  View * view() override {
    return &m_keyboardView;
  }
  bool handleEvent(Ion::Events::Event event) override;
  void viewWillAppear() override;
private:
  KeyboardView m_keyboardView;
  ScreenTestController m_screenTestController;
};

}

#endif

