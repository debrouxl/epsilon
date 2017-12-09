#ifndef CALCULATION_TEXT_FIELD_H
#define CALCULATION_TEXT_FIELD_H

#include <escher.h>

namespace Calculation {

class TextField final : public ::TextField {
public:
  TextField(Responder * parentResponder, char * textBuffer, size_t textBufferSize, TextFieldDelegate * delegate) :
    ::TextField(parentResponder, textBuffer, textBuffer, textBufferSize, delegate, false) {
    setEditing(true);
  }
  bool handleEvent(Ion::Events::Event event) override;
};

}

#endif
