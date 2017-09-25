#ifndef ESCHER_TOOLBOX_H
#define ESCHER_TOOLBOX_H

#include <escher/stack_view_controller.h>

class Toolbox : public StackViewController {
public:
  Toolbox(Responder * parentResponder, ViewController * rootViewController);
  void setSender(Responder * sender) {
    m_sender = sender;
  }
  using StackViewController::viewWillAppear;
  using StackViewController::viewDidDisappear;
protected:
  virtual Responder * sender();
private:
  Responder * m_sender;
};


#endif
