#ifndef APPS_CONTAINER_H
#define APPS_CONTAINER_H

#include "home/app.h"
#include "on_boarding/app.h"
#include "hardware_test/app.h"
#include "on_boarding/update_controller.h"
#include "usb/app.h"
#include "apps_window.h"
#include "empty_battery_window.h"
#include "math_toolbox.h"
#include "variable_box_controller.h"
#include "exam_pop_up_controller.h"
#include "exam_pop_up_controller_delegate.h"
#include "led_timer.h"
#include "battery_timer.h"
#include "suspend_timer.h"
#include "backlight_dimming_timer.h"

#define USE_PIC_VIEW_APP 0
#if USE_PIC_VIEW_APP
#include "picview/picview_app.h"
#endif

#include <ion/events.h>

class AppsContainer : public Container, ExamPopUpControllerDelegate {
public:
  AppsContainer();
  static bool poincareCircuitBreaker();
  virtual int numberOfApps() = 0;
  virtual App::Snapshot * appSnapshotAtIndex(int index) = 0;
  App::Snapshot * hardwareTestAppSnapshot() {
    return &m_hardwareTestSnapshot;
  }
  App::Snapshot * onBoardingAppSnapshot() {
    return &m_onBoardingSnapshot;
  }
  App::Snapshot * usbConnectedAppSnapshot() {
    return &m_usbConnectedSnapshot;
  }
  void reset();
  Poincare::Context * globalContext() {
    return &m_globalContext;
  }
  MathToolbox * mathToolbox() {
    return &m_mathToolbox;
  }
  VariableBoxController * variableBoxController() {
    return &m_variableBoxController;
  }
  void suspend(bool checkIfPowerKeyReleased = false);
  virtual bool dispatchEvent(Ion::Events::Event event) override;
  void switchTo(App::Snapshot * snapshot) override;
  void run() override;
  bool updateBatteryState();
  void refreshPreferences() {
    m_window.refreshPreferences();
  }
  void displayExamModePopUp(bool activate);
  void shutdownDueToLowBattery();
  void setShiftAlphaStatus(Ion::Events::ShiftAlphaStatus newStatus);
  OnBoarding::UpdateController * updatePopUpController() { return &m_updateController; }
  void redrawWindow();
  // Exam pop-up controller delegate
  void examDeactivatingPopUpIsDismissed() override;
protected:
  Home::App::Snapshot * homeAppSnapshot() { return &m_homeSnapshot; }
private:
  Window * window() override { return &m_window; }
  int numberOfContainerTimers() override;
  Timer * containerTimerAtIndex(int i) override;
  bool processEvent(Ion::Events::Event event);
  void resetShiftAlphaStatus();
  bool updateAlphaLock();
  AppsWindow m_window;
  EmptyBatteryWindow m_emptyBatteryWindow;
#if USE_PIC_VIEW_APP
  PicViewApp m_picViewApp;
#endif
  Poincare::GlobalContext m_globalContext;
  MathToolbox m_mathToolbox;
  VariableBoxController m_variableBoxController;
  ExamPopUpController m_examPopUpController;
  OnBoarding::UpdateController m_updateController;
  LedTimer m_ledTimer;
  BatteryTimer m_batteryTimer;
  SuspendTimer m_suspendTimer;
  BacklightDimmingTimer m_backlightDimmingTimer;
  Home::App::Snapshot m_homeSnapshot;
  OnBoarding::App::Snapshot m_onBoardingSnapshot;
  HardwareTest::App::Snapshot m_hardwareTestSnapshot;
  USB::App::Snapshot m_usbConnectedSnapshot;
};

#endif
