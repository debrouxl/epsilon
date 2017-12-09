#ifndef HARDWARE_TEST_LED_TEST_CONTROLLER_H
#define HARDWARE_TEST_LED_TEST_CONTROLLER_H

#include <escher.h>
#include "battery_test_controller.h"
#include "arrow_view.h"

namespace HardwareTest {

class LEDTestController final : public ViewController {
public:
  LEDTestController(Responder * parentResponder) :
    ViewController(parentResponder),
    m_view(),
    m_LEDColorIndex(0),
    m_batteryTestController(this) {}
  View * view() override {
    return &m_view;
  }
  bool handleEvent(Ion::Events::Event event) override;
  void viewWillAppear() override;
private:
  class ContentView final : public SolidColorView {
  public:
    ContentView() :
      SolidColorView(KDColorWhite),
      m_ledColorIndicatorView(KDColorBlack),
      m_ledColorOutlineView(KDColorBlack),
      m_ledView(KDText::FontSize::Large),
      m_arrowView() {
      m_ledView.setText("LED");
    }
    SolidColorView * LEDColorIndicatorView() {
      return &m_ledColorIndicatorView;
    }
  private:
    void layoutSubviews() override;
    int numberOfSubviews() const override;
    View * subviewAtIndex(int index) override;
    SolidColorView m_ledColorIndicatorView;
    SolidColorView m_ledColorOutlineView;
    BufferTextView m_ledView;
    ArrowView m_arrowView;
  };
  void setLEDColor(KDColor color);
  constexpr static KDCoordinate k_arrowLength = 100;
  constexpr static KDCoordinate k_arrowMargin = 20;
  constexpr static KDCoordinate k_indicatorSize = 20;
  constexpr static KDCoordinate k_indicatorMargin = 8;
  constexpr static int k_numberOfColors = 5;
  constexpr static KDColor k_LEDColors[k_numberOfColors] = {KDColorWhite, KDColorRed, KDColorBlue, KDColorGreen, KDColorBlack};
  static KDColor LEDColorAtIndex(int i);
  ContentView m_view;
  int m_LEDColorIndex;
  BatteryTestController m_batteryTestController;
};

}

#endif

