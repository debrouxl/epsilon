#ifndef HARDWARE_TEST_RESET_CONTROLLER_H
#define HARDWARE_TEST_RESET_CONTROLLER_H

#include <escher.h>

namespace HardwareTest {

class ResetController final : public ViewController {
public:
  ResetController(Responder * parentResponder) : ViewController(parentResponder), m_view() {}
  View * view() override {
    return &m_view;
  }
  bool handleEvent(Ion::Events::Event event) override;
private:
  class ContentView final : public View {
  public:
    ContentView() : m_resetTextView() {
      m_resetTextView.setText("RESET");
    }
    BufferTextView * resetTextView();
  private:
    void layoutSubviews() override;
    int numberOfSubviews() const override;
    View * subviewAtIndex(int index) override;
    BufferTextView m_resetTextView;
  };
  ContentView m_view;
};

}

#endif

