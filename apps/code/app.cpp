#include "app.h"
#include "../apps_container.h"

namespace Code {

App::Descriptor App::Snapshot::s_descriptor;

App::App(Container * container, Snapshot * snapshot) :
  ::App(container, snapshot, &m_codeStackViewController, I18n::Message::Warning),
  m_listFooter(&m_codeStackViewController, &m_menuController, &m_menuController, ButtonRowController::Position::Bottom, ButtonRowController::Style::EmbossedGrey, ButtonRowController::Size::Large),
  m_menuController(&m_listFooter, snapshot->scriptStore(), &m_listFooter),
  m_codeStackViewController(&m_modalViewController, &m_listFooter),
  m_toolboxActionForTextArea([](void * sender, const char * text) {
      TextArea * textArea = static_cast<TextArea *>(sender);
      int previousCursorLocation = textArea->cursorLocation();
      if (textArea->insertTextWithIndentation(text)) {
      // insertText() also moves the cursor. We need to re-move it to the
      // position we want (which is after the first parenthesis or before the
      // first point).
        int deltaCursorLocation = - textArea->cursorLocation() + previousCursorLocation + Shared::ToolboxHelpers::CursorIndexInCommand(text);
      // WARNING: This is a dirty and only works because the cursor location we
      // want is always on the first line of the text we insert. Because of the
      // auto indentation, it would be difficult to compute the wanted cursor
      // location on other lines of the text.
        textArea->moveCursor(deltaCursorLocation);
      }}),
  m_toolboxActionForTextField([](void * sender, const char * text) {
      TextField * textField = static_cast<TextField *>(sender);
      if (!textField->isEditing()) {
        textField->setEditing(true);
      }
      int newCursorLocation = textField->cursorLocation() + Shared::ToolboxHelpers::CursorIndexInCommand(text);
      if (textField->insertTextAtLocation(text, textField->cursorLocation())) {
        textField->setCursorLocation(newCursorLocation);
      }}),
  m_variableBoxController(&m_menuController, snapshot->scriptStore())
{
}

}
