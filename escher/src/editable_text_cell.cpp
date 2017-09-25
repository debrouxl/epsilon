#include <escher/editable_text_cell.h>
#include <escher/app.h>
#include <escher/palette.h>
#include <assert.h>

EditableTextCell::EditableTextCell(Responder * parentResponder, TextFieldDelegate * delegate, char * draftTextBuffer,
   KDText::FontSize size, float horizontalAlignment, float verticalAlignment, KDColor textColor, KDColor backgroundColor) :
  HighlightCell(),
  Responder(parentResponder),
  m_textField(this, m_textBody, draftTextBuffer, TextField::maxBufferSize(), delegate, true, size, horizontalAlignment, verticalAlignment, textColor, backgroundColor)
{
}

void EditableTextCell::setHighlighted(bool highlight) {
  HighlightCell::setHighlighted(highlight);
  KDColor backgroundColor = highlight? Palette::Select : KDColorWhite;
  m_textField.setBackgroundColor(backgroundColor);
}

int EditableTextCell::numberOfSubviews() const {
  return 1;
}

View * EditableTextCell::subviewAtIndex(int index) {
  assert(index == 0);
  return &m_textField;
}

void EditableTextCell::layoutSubviews() {
  m_textField.setFrame(bounds());
}

void EditableTextCell::didBecomeFirstResponder() {
  app()->setFirstResponder(&m_textField);
}

KDSize EditableTextCell::minimalSizeForOptimalDisplay() const {
  return m_textField.minimalSizeForOptimalDisplay();
}
