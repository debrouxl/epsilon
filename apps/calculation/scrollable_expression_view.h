#ifndef CALCULATION_SCROLLABLE_EXPRESSION_VIEW_H
#define CALCULATION_SCROLLABLE_EXPRESSION_VIEW_H

#include <escher.h>

namespace Calculation {

class ScrollableExpressionView final : public ScrollableView, public ScrollViewDataSource {
public:
  ScrollableExpressionView(Responder * parentResponder) :
    ScrollableView(parentResponder, &m_expressionView, this),
    m_expressionView() {}
  void setExpression(Poincare::ExpressionLayout * expressionLayout){
  m_expressionView.setExpression(expressionLayout);
  layoutSubviews();
}

  void setBackgroundColor(KDColor backgroundColor) {
    m_expressionView.setBackgroundColor(backgroundColor);
  }
  KDSize minimalSizeForOptimalDisplay() const override {
    return m_expressionView.minimalSizeForOptimalDisplay();
  }
private:
  ExpressionView m_expressionView;
};

}

#endif
