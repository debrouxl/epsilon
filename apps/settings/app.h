#ifndef SETTINGS_APP_H
#define SETTINGS_APP_H

#include <escher.h>
#include "main_controller.h"
#include "settings_icon.h"
#include "../i18n.h"

namespace Settings {

class App final : public ::App {
public:
  class Descriptor final : public ::App::Descriptor {
  public:
    I18n::Message name() override {
      return I18n::Message::SettingsApp;
    }
    I18n::Message upperName() override {
      return I18n::Message::SettingsAppCapital;
    }
    const Image * icon() override {
      return ImageStore::SettingsIcon;
    }
  };
  class Snapshot final : public ::App::Snapshot {
  public:
    App * unpack(Container * container) override {
      return new App(container, this);
    }
    Descriptor * descriptor() override {
      return &s_descriptor;
    }
  private:
    static Descriptor s_descriptor;
  };
private:
  App(Container * container, Snapshot * snapshot) :
    ::App(container, snapshot, &m_stackViewController, I18n::Message::Warning),
    m_mainController(&m_stackViewController),
    m_stackViewController(&m_modalViewController, &m_mainController) {}
  MainController m_mainController;
  StackViewController m_stackViewController;
};

}

#endif
