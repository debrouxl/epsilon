#include "app.h"
#include "../apps_container.h"

extern "C" {
#include <assert.h>
}

namespace HardwareTest {

App::Descriptor App::Snapshot::s_descriptor;

App * App::Snapshot::unpack(Container * container) {
  return new App(container, this);
}

int App::numberOfTimers() {
  return firstResponder() == &m_USBTestController;
}

Timer * App::timerAtIndex(int i) {
  assert(i == 0);
  return &m_USBTestController;
}

bool App::processEvent(Ion::Events::Event e) {
  ::App::processEvent(e);
  return true;
}

}
