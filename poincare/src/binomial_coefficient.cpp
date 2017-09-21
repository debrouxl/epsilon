#include <poincare/binomial_coefficient.h>
#include <poincare/evaluation.h>
#include <poincare/complex.h>
#include "layout/parenthesis_layout.h"
#include "layout/grid_layout.h"

extern "C" {
#include <stdlib.h>
#include <assert.h>
}
#include <cmath>

namespace Poincare {

BinomialCoefficient::BinomialCoefficient() :
  Function("binomial", 2)
{
}

Expression::Type BinomialCoefficient::type() const {
  return Type::BinomialCoefficient;
}

Expression * BinomialCoefficient::cloneWithDifferentOperands(Expression** newOperands,
        int numberOfOperands, bool cloneOperands) const {
  assert(newOperands != nullptr);
  BinomialCoefficient * bc = new BinomialCoefficient();
  bc->setArgument(newOperands, numberOfOperands, cloneOperands);
  return bc;
}

template<typename T>
Evaluation<T> * BinomialCoefficient::templatedEvaluate(Context& context, AngleUnit angleUnit) const {
  T n = m_args[0]->approximate<T>(context, angleUnit);
  T k = m_args[1]->approximate<T>(context, angleUnit);
  if (isnan(n) || isnan(k) || n != (int)n || k != (int)k || k > n || k < 0 || n < 0) {
    return Complex<T>::NewFNAN();
  }
  T result = 1;
  for (int i = 0; i < (int)k; i++) {
    result *= (n-(T)i)/(k-(T)i);
  }
  return Complex<T>::NFloat(std::round(result));
}

ExpressionLayout * BinomialCoefficient::privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const {
  assert(floatDisplayMode != FloatDisplayMode::Default);
  assert(complexFormat != ComplexFormat::Default);
  ExpressionLayout * childrenLayouts[2] = {
    m_args[0]->createLayout(floatDisplayMode, complexFormat),
    m_args[1]->createLayout(floatDisplayMode, complexFormat)
  };
  return new ParenthesisLayout(new GridLayout(childrenLayouts, 2, 1, false));
}

}
