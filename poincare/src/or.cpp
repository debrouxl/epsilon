#include <poincare/or.h>
extern "C" {
#include <assert.h>
#include <stdlib.h>
}
#include "layout/horizontal_layout.h"
#include "layout/string_layout.h"
#include "layout/parenthesis_layout.h"

namespace Poincare {

Expression::Type Or::type() const {
  return Type::Or;
}

ExpressionLayout * Or::privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const {
  assert(floatDisplayMode != FloatDisplayMode::Default);
  assert(complexFormat != ComplexFormat::Default);
  ExpressionLayout* children_layouts[3] = {
    m_operands[0]->createLayout(floatDisplayMode, complexFormat),
    new StringLayout(" or ", 4),
    m_operands[1]->type() == Type::Opposite ? new ParenthesisLayout(m_operands[1]->createLayout(floatDisplayMode, complexFormat)) : m_operands[1]->createLayout(floatDisplayMode, complexFormat)
  };
  ExpressionLayout * layout = new HorizontalLayout(children_layouts, 3, false);
  return layout;
}

template<typename T>
Complex<T> Or::compute(const Complex<T> & c, const Complex<T> & d) {
  uint32_t result = ((uint32_t)c.a()) | ((uint32_t)d.a());
  return Complex<T>::Float((T)result);
}

Expression * Or::cloneWithDifferentOperands(Expression** newOperands,
    int numberOfOperands, bool cloneOperands) const {
  return new Or(newOperands, cloneOperands);
}

bool Or::isCommutative() const {
  return true;
}

}
