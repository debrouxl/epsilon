#ifndef HARDWARE_TEST_USB_TEST_CONTROLLER_H
#define HARDWARE_TEST_USB_TEST_CONTROLLER_H

#include <escher.h>
#include "reset_controller.h"
#include "arrow_view.h"

namespace HardwareTest {

class USBTestController final : public ViewController, public Timer {
public:
  USBTestController(Responder * parentResponder);
  View * view() override {
    return &m_view;
  }
  void viewWillAppear() override;
  bool handleEvent(Ion::Events::Event e) override;
private:
  bool fire() override;
  class ContentView final : public SolidColorView {
  public:
    ContentView() : SolidColorView(KDColorWhite), m_USBTextView(KDText::FontSize::Large), m_USBView(), m_arrowView() {}
    BufferTextView * USBTextView() {
      return &m_USBTextView;
    }
    ArrowView * arrowView() {
      return &m_arrowView;
    }
  private:
    class USBView : public View {
    public:
      void drawRect(KDContext * ctx, KDRect rect) const override;
      constexpr static KDCoordinate k_USBHoleWidth = 40;
      constexpr static KDCoordinate k_USBHoleHeight = 20;
      constexpr static KDCoordinate k_marginHeight = 50;
    };
    constexpr static KDCoordinate k_textHeight = 50;
    void layoutSubviews() override;
    int numberOfSubviews() const override;
    View * subviewAtIndex(int index) override;
    BufferTextView m_USBTextView;
    USBView m_USBView;
    ArrowView m_arrowView;
  };
  constexpr static const char * k_USBPlugText = "PLUG USB";
  constexpr static const char * k_USBUnplugText = "OK, UNPLUG USB";
  ContentView m_view;
  bool m_shouldPlugUSB;
  ResetController m_resetController;
};

}

#endif

