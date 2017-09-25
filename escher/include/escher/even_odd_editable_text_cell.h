#ifndef ESCHER_EVEN_ODD_EDITABLE_TEXT_CELL_H
#define ESCHER_EVEN_ODD_EDITABLE_TEXT_CELL_H

#include <escher/responder.h>
#include <escher/even_odd_cell.h>
#include <escher/editable_text_cell.h>

class EvenOddEditableTextCell final : public EvenOddCell, public Responder {
public:
  EvenOddEditableTextCell(Responder * parentResponder, TextFieldDelegate * delegate, char * draftTextBuffer, KDText::FontSize size = KDText::FontSize::Large);
  EditableTextCell * editableTextCell() {
    return &m_editableCell;
  }
  void setEven(bool even) override;
  void setHighlighted(bool highlight) override;
  const char * text() const {
    return m_editableCell.text();
  }
  void setText(const char * textContent) {
    m_editableCell.setText(textContent);
  }
  int numberOfSubviews() const override;
  View * subviewAtIndex(int index) override;
  void layoutSubviews() override;
  void didBecomeFirstResponder() override;
  bool isEditing() {
    return m_editableCell.isEditing();
  }
  void setEditing(bool isEditing) {
    m_editableCell.setEditing(isEditing);
  }
private:
  EditableTextCell m_editableCell;
};

#endif
