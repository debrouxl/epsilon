#include <escher/toolbox.h>

Toolbox::Toolbox(Responder * parentResponder, ViewController * rootViewController) :
  StackViewController(parentResponder, rootViewController, true, KDColorWhite, Palette::PurpleBright, Palette::PurpleDark),
  m_sender(nullptr)
{
}

Responder * Toolbox::sender() {
  return m_sender;
}
