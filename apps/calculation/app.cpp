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

}
