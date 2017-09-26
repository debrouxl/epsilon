#ifndef CODE_APP_H
#define CODE_APP_H

#include <escher/app.h>
#include "code_icon.h"
#include "../i18n.h"
#include "menu_controller.h"
#include "program.h"
#include "../shared/message_controller.h"

namespace Code {

class App final : public ::App {
public:
  class Descriptor final : public ::App::Descriptor {
  public:
    I18n::Message name() override {
      return I18n::Message::CodeApp;
    }
    I18n::Message upperName() override {
      return I18n::Message::CodeAppCapital;
    }
    const Image * icon() override {
      return ImageStore::CodeIcon;
    }
  };
  class Snapshot final : public ::App::Snapshot {
  public:
    Snapshot() : m_program() {}
    App * unpack(Container * container) override {
      return new App(container, this);
    }
    void reset() override {
      m_program.setContent("");
    }
    Descriptor * descriptor() override {
      return &s_descriptor;
    }
    Program * program() {
      return &m_program;
    }
  private:
    Program m_program;
    static Descriptor s_descriptor;
  };
  void didBecomeActive(Window * window) override;
private:
  App(Container * container, Snapshot * snapshot) :
    ::App(container, snapshot, &m_menuController, I18n::Message::Warning),
    m_betaVersionController(sCodeMessages, sCodeColors),
    m_menuController(this, snapshot->program()) {}
  MessageController m_betaVersionController;
  MenuController m_menuController;
  static I18n::Message sCodeMessages[];
  static KDColor sCodeColors[];
};

}

#endif
