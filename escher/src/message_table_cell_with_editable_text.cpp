#include <escher/message_table_cell_with_editable_text.h>
#include <escher/palette.h>
#include <escher/app.h>

MessageTableCellWithEditableText::MessageTableCellWithEditableText(Responder * parentResponder, TextFieldDelegate * textFieldDelegate, char * draftTextBuffer, I18n::Message message) :
  Responder(parentResponder),
  MessageTableCell(message),
  m_textField(this, m_textBody, draftTextBuffer, TextField::maxBufferSize(), textFieldDelegate, true, KDText::FontSize::Large, 1.0f, 0.5f)
{
}

View * MessageTableCellWithEditableText::accessoryView() const {
  return (View *)&m_textField;
}

void MessageTableCellWithEditableText::didBecomeFirstResponder() {
  app()->setFirstResponder(&m_textField);
}

void MessageTableCellWithEditableText::setHighlighted(bool highlight) {
  MessageTableCell::setHighlighted(highlight);
  KDColor backgroundColor = highlight? Palette::Select : KDColorWhite;
  m_textField.setBackgroundColor(backgroundColor);
}

void MessageTableCellWithEditableText::setAccessoryText(const char * text) {
  m_textField.setText(text);
  layoutSubviews();
}

void MessageTableCellWithEditableText::setTextColor(KDColor color) {
  m_textField.setTextColor(color);
  MessageTableCell::setTextColor(color);
}
