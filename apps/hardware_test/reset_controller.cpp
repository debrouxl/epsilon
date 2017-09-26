#include "reset_controller.h"
extern "C" {
#include <assert.h>
}

namespace HardwareTest {

bool ResetController::handleEvent(Ion::Events::Event event) {
  return true;
}

void ResetController::ContentView::layoutSubviews() {
  m_resetTextView.setFrame(bounds());
}

int ResetController::ContentView::numberOfSubviews() const {
  return 1;
}

View * ResetController::ContentView::subviewAtIndex(int index) {
  return &m_resetTextView;
}

}

