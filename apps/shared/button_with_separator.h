#ifndef SHARED_BUTTON_WITH_SEPARATOR_H
#define SHARED_BUTTON_WITH_SEPARATOR_H

#include <escher.h>

class ButtonWithSeparator final : public Button {
public:
  ButtonWithSeparator(Responder * parentResponder, I18n::Message textBody, Invocation invocation) :
    Button(parentResponder, textBody, invocation, KDText::FontSize::Large, KDColorBlack) {}
  void drawRect(KDContext * ctx, KDRect rect) const override;
private:
  constexpr static KDCoordinate k_margin = 5;
  constexpr static KDCoordinate k_lineThickness = 1;
  void layoutSubviews() override;
};

#endif
