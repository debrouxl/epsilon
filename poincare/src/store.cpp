extern "C" {
#include <assert.h>
#include <stdlib.h>
#include <math.h>
}
#include <poincare/store.h>
#include <ion.h>
#include <poincare/complex.h>
#include <poincare/context.h>
#include "layout/horizontal_layout.h"
#include "layout/string_layout.h"

namespace Poincare {

Expression::Type Store::type() const {
  return Type::Store;
}

static_assert('\x8F' == Ion::Charset::Sto, "Incorrect");
int Store::writeTextInBuffer(char * buffer, int bufferSize, int numberOfSignificantDigits) const {
  return LayoutEngine::writeInfixExpressionTextInBuffer(this, buffer, bufferSize, numberOfSignificantDigits, "\x8F");
}

Expression * Store::shallowReduce(Context& context, AngleUnit angleUnit) {
  context.setExpressionForSymbolName(value(), symbol(), context);
  return replaceWith(editableOperand(1), true)->shallowReduce(context, angleUnit);
}

ExpressionLayout * Store::privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const {
  static const char stoSymbol[2] = {Ion::Charset::Sto, 0};
  assert(floatDisplayMode != FloatDisplayMode::Default);
  assert(complexFormat != ComplexFormat::Default);
  ExpressionLayout * childrenLayouts[3] = {
    value()->createLayout(floatDisplayMode, complexFormat),
    new StringLayout(stoSymbol, 1),
    symbol()->createLayout(floatDisplayMode, complexFormat)
  };
  return new HorizontalLayout(childrenLayouts, 3, false);
}

template<typename T>
Expression * Store::templatedApproximate(Context& context, AngleUnit angleUnit) const {
  context.setExpressionForSymbolName(value(), symbol(), context);
  if (context.expressionForSymbol(symbol()) != nullptr) {
    return context.expressionForSymbol(symbol())->approximate<T>(context, angleUnit);
  }
  return Complex<T>::NewFNAN();
}

}
