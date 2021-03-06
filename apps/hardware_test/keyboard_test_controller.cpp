#include "keyboard_test_controller.h"
extern "C" {
#include <assert.h>
}
#include <poincare.h>

using namespace Poincare;

namespace HardwareTest {

KeyboardTestController::KeyboardTestController(Responder * parentResponder) :
  ViewController(parentResponder),
  m_keyboardView()
{
}

bool KeyboardTestController::handleEvent(Ion::Events::Event event) {
  Ion::Keyboard::State state = Ion::Keyboard::scan();
  Ion::Keyboard::State onlyKeyDown = Ion::Keyboard::State(Ion::Keyboard::ValidKeys[m_keyboardView.testedKeyIndex()]);
  if (state == onlyKeyDown) {
    m_keyboardView.setTestedKeyIndex(m_keyboardView.testedKeyIndex()+1);
    if (m_keyboardView.testedKeyIndex() == Ion::Keyboard::NumberOfValidKeys) {
      // Returning false will go to the next step in the WizardViewController
      return false;
    }
  }
  return true;
}

void KeyboardTestController::viewWillAppear() {
  m_keyboardView.setTestedKeyIndex(0);
}

}

