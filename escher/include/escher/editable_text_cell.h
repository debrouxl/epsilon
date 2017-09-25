#ifndef ESCHER_EDITABLE_TEXT_CELL_H
#define ESCHER_EDITABLE_TEXT_CELL_H

#include <escher/responder.h>
#include <escher/highlight_cell.h>
#include <escher/text_field_delegate.h>
#include <escher/text_field.h>

class EditableTextCell final : public HighlightCell, public Responder {
public:
  EditableTextCell(Responder * parentResponder = nullptr, TextFieldDelegate * delegate = nullptr, char * draftTextBuffer = nullptr, KDText::FontSize size = KDText::FontSize::Large,
     float horizontalAlignment = 0.0f, float verticalAlignment = 0.5f, KDColor textColor = KDColorBlack, KDColor = KDColorWhite);
  void setTextFieldDelegate(TextFieldDelegate * delegate) {
    m_textField.setDelegate(delegate);
  }
  void setTextFieldDraftTextBuffer(char * draftTextBuffer) {
    m_textField.setDraftTextBuffer(draftTextBuffer);
  }
  TextField * textField() {
    return &m_textField;
  }
  void setHighlighted(bool highlight) override;
  const char * text() const {
    return m_textField.text();
  }
  void setText(const char * textContent) {
    m_textField.setText(textContent);
  }
  int numberOfSubviews() const override;
  View * subviewAtIndex(int index) override;
  void layoutSubviews() override;
  void didBecomeFirstResponder() override;
  bool isEditing() {
    return m_textField.isEditing();
  }
  void setEditing(bool isEditing) {
    m_textField.setEditing(isEditing);
  }
  KDSize minimalSizeForOptimalDisplay() const override;
private:
  constexpr static KDCoordinate k_separatorThickness = 1;
  TextField m_textField;
  char m_textBody[TextField::maxBufferSize()];
};

#endif
