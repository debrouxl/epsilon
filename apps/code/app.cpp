#include "app.h"
#include "../apps_container.h"
#include "helpers.h"

namespace Code {

App::Descriptor App::Snapshot::s_descriptor;

App::Snapshot::Snapshot() :
#if EPSILON_GETOPT
  m_lockOnConsole(false),
#endif
  m_scriptStore()
{
}

#if EPSILON_GETOPT
bool App::Snapshot::lockOnConsole() const {
  return m_lockOnConsole;
}

void App::Snapshot::setOpt(const char * name, char * value) {
  if (strcmp(name, "script") == 0) {
      m_scriptStore.deleteAllScripts();
      char * separator = strchr(value, ':');
      if (!separator) {
        return;
      }
      *separator = 0;
      const char * scriptName = value;
      const char * scriptContent = separator+1;
      Code::ScriptTemplate script(scriptName, scriptContent);
      m_scriptStore.addScriptFromTemplate(&script);
      return;
  }
  if (strcmp(name, "lock-on-console") == 0) {
    m_lockOnConsole = true;
    return;
  }
}
#endif

App::App(Container * container, Snapshot * snapshot) :
  ::App(container, snapshot, &m_codeStackViewController, I18n::Message::Warning),
  m_listFooter(&m_codeStackViewController, &m_menuController, &m_menuController, ButtonRowController::Position::Bottom, ButtonRowController::Style::EmbossedGrey, ButtonRowController::Size::Large),
  m_menuController(&m_listFooter, snapshot->scriptStore(), &m_listFooter
#if EPSILON_GETOPT
      , snapshot->lockOnConsole()
#endif
      ),
  m_codeStackViewController(&m_modalViewController, &m_listFooter),
  m_variableBoxController(&m_menuController, snapshot->scriptStore())
{
}

bool App::textInputDidReceiveEvent(TextInput * textInput, Ion::Events::Event event) {
  const char * pythonText = Helpers::PythonTextForEvent(event);
  if (pythonText != nullptr) {
    textInput->handleEventWithText(pythonText);
    return true;
  }
  if (event == Ion::Events::Var) {
    m_variableBoxController.setTextInputCaller(textInput);
    displayModalViewController(&m_variableBoxController, 0.f, 0.f, Metric::PopUpTopMargin, Metric::PopUpLeftMargin, 0, Metric::PopUpRightMargin);
    return true;
  }
  return false;
}

}
