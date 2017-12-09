#include "app.h"
#include "../apps_container.h"
#include "../i18n.h"

using namespace Poincare;

using namespace Shared;

namespace Calculation {

App::Descriptor App::Snapshot::s_descriptor;

App::App(Container * container, Snapshot * snapshot) :
  TextFieldDelegateApp(container, snapshot, &m_editExpressionController),
  m_localContext((GlobalContext *)((AppsContainer *)container)->globalContext(), snapshot->calculationStore()),
  m_historyController(&m_editExpressionController, snapshot->calculationStore()),
  m_editExpressionController(&m_modalViewController, &m_historyController, snapshot->calculationStore())
{
}

bool App::textFieldDidReceiveEvent(::TextField * textField, Ion::Events::Event event) {
  if ((event == Ion::Events::Var ||  event == Ion::Events::XNT) && TextFieldDelegateApp::textFieldDidReceiveEvent(textField, event)) {
    return true;
  }
  /* Here, we check that the expression entered by the user can be printed with
   * less than k_printedExpressionLength characters. Otherwise, we prevent the
   * user from adding this expression to the calculation store. */
  if (textField->isEditing() && textField->textFieldShouldFinishEditing(event)) {
    Expression * exp = Expression::parse(textField->text());
    if (exp == nullptr) {
      textField->app()->displayWarning(I18n::Message::SyntaxError);
      return true;
    }
    char buffer[Calculation::k_printedExpressionSize];
    int length = exp->writeTextInBuffer(buffer, sizeof(buffer));
    delete exp;
    /* if the buffer is totally full, it is VERY likely that writeTextInBuffer
     * escaped before printing utterly the expression. */
    if (length >= Calculation::k_printedExpressionSize-1) {
      displayWarning(I18n::Message::SyntaxError);
      return true;
    }
  }
  return false;
}

}
