#include "screen_test_controller.h"
extern "C" {
#include <assert.h>
}

namespace HardwareTest {

bool ScreenTestController::handleEvent(Ion::Events::Event event) {
  if (event != Ion::Events::OK) {
    return true;
  }
  if (m_patternIndex == Pattern::numberOfPatterns()) {
    ModalViewController * modal = (ModalViewController *)parentResponder();
    modal->displayModalViewController(&m_ledTestController, 0.0f, 0.0f);
  } else {
    showNextPattern();
  }
  return true;
}

void ScreenTestController::viewWillAppear() {
  m_patternIndex = 0;
  showNextPattern();
}

void ScreenTestController::showNextPattern() {
  m_view.setPattern(Pattern::patternAtIndex(m_patternIndex++));
}

}

