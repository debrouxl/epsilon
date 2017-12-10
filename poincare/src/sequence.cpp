#include <poincare/sequence.h>
#include <poincare/symbol.h>
#include <poincare/complex.h>
#include <poincare/variable_context.h>
#include <poincare/undefined.h>
#include "layout/string_layout.h"
#include "layout/horizontal_layout.h"
extern "C" {
#include <assert.h>
#include <stdlib.h>
}
#include <cmath>

namespace Poincare {

ExpressionLayout * Sequence::privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const {
  assert(floatDisplayMode != FloatDisplayMode::Default);
  assert(complexFormat != ComplexFormat::Default);
  ExpressionLayout * childrenLayouts[2] = {
    new StringLayout("n=", 2),
    operand(1)->createLayout(floatDisplayMode, complexFormat)
  };
  return createSequenceLayoutWithArgumentLayouts(new HorizontalLayout(childrenLayouts, 2), operand(2)->createLayout(floatDisplayMode, complexFormat), operand(0)->createLayout(floatDisplayMode, complexFormat));
}

template<typename T>
Expression * Sequence::templatedApproximate(Context& context, AngleUnit angleUnit) const {
  T start = operand(1)->approximateToScalar<T>(context, angleUnit);
  T end = operand(2)->approximateToScalar<T>(context, angleUnit);
  if (std::isnan(start) || std::isnan(end) || start != (int)start || end != (int)end || end - start > k_maxNumberOfSteps) {
    return Complex<T>::NewFNAN();
  }
  VariableContext<T> nContext = VariableContext<T>('n', &context);
  Symbol nSymbol('n');
  Expression * result = Complex<T>::NewFloat(emptySequenceValue());
  for (int i = (int)start; i <= (int)end; i++) {
    if (shouldStopProcessing()) {
      delete result;
      return Complex<T>::NewFNAN();
    }
    Complex<T> iExpression = Complex<T>::Float(i);
    nContext.setExpressionForSymbolName(&iExpression, &nSymbol, nContext);
    Expression * expression = operand(0)->approximate<T>(nContext, angleUnit);
    Expression * newResult = evaluateWithNextTerm(T(), result, expression);
    delete result;
    delete expression;
    result = newResult;
  }
  return result;
}

}
