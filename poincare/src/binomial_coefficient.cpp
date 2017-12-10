#include <poincare/binomial_coefficient.h>
#include <poincare/undefined.h>
#include <poincare/complex.h>
#include <poincare/rational.h>
#include "layout/parenthesis_layout.h"
#include "layout/grid_layout.h"

extern "C" {
#include <stdlib.h>
#include <assert.h>
}
#include <cmath>

namespace Poincare {

Expression::Type BinomialCoefficient::type() const {
  return Type::BinomialCoefficient;
}

Expression * BinomialCoefficient::shallowReduce(Context& context, AngleUnit angleUnit) {
  Expression * e = Expression::shallowReduce(context, angleUnit);
  if (e != this) {
    return e;
  }
  Expression * op0 = editableOperand(0);
  Expression * op1 = editableOperand(1);
#if MATRIX_EXACT_REDUCING
  if (op0->type() == Type::Matrix || op1->type() == Type::Matrix) {
    return replaceWith(new Undefined(), true);
  }
#endif
  if (op0->type() == Type::Rational) {
    Rational * r0 = static_cast<Rational *>(op0);
    if (!r0->denominator().isOne() || r0->numerator().isNegative()) {
      return replaceWith(new Undefined(), true);
    }
  }
  if (op1->type() == Type::Rational) {
    Rational * r1 = static_cast<Rational *>(op1);
    if (!r1->denominator().isOne() || r1->numerator().isNegative()) {
      return replaceWith(new Undefined(), true);
    }
  }
  if (op0->type() != Type::Rational || op1->type() != Type::Rational) {
    return this;
  }
  Rational * r0 = static_cast<Rational *>(op0);
  Rational * r1 = static_cast<Rational *>(op1);

  Integer n = r0->numerator();
  Integer k = r1->numerator();
  if (n.isLowerThan(k)) {
    return replaceWith(new Undefined(), true);
  }
  /* if n is too big, we do not reduce to avoid too long computation.
   * The binomial coefficient will be evaluate approximatively later */
  if (Integer(k_maxNValue).isLowerThan(n)) {
    return this;
  }
  Rational result(1);
  Integer kBis = Integer::Subtraction(n, k);
  k = kBis.isLowerThan(k) ? kBis : k;
  int clippedK = k.extractedInt(); // Authorized because k < n < k_maxNValue
  for (int i = 0; i < clippedK; i++) {
    Rational factor = Rational(Integer::Subtraction(n, Integer(i)), Integer::Subtraction(k, Integer(i)));
    result = Rational::Multiplication(result, factor);
  }
  return replaceWith(new Rational(result), true);
}

ExpressionLayout * BinomialCoefficient::privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const {
  assert(floatDisplayMode != FloatDisplayMode::Default);
  assert(complexFormat != ComplexFormat::Default);
  ExpressionLayout * childrenLayouts[2] = {
    operand(0)->createLayout(floatDisplayMode, complexFormat),
    operand(1)->createLayout(floatDisplayMode, complexFormat)
  };
  return new ParenthesisLayout(new GridLayout(childrenLayouts, 2, 1, false));
}

template<typename T>
Expression * BinomialCoefficient::templatedApproximate(Context& context, AngleUnit angleUnit) const {
  T n = operand(0)->approximateToScalar<T>(context, angleUnit);
  T k = operand(1)->approximateToScalar<T>(context, angleUnit);
  k = k > (n-k) ? n-k : k;
  if (std::isnan(n) || std::isnan(k) || n != std::round(n) || k != std::round(k) || k > n || k < 0 || n < 0) {
    return Complex<T>::NewFNAN();
  }
  T result = 1;
  for (int i = 0; i < k; i++) {
    result *= (n-(T)i)/(k-(T)i);
    if (std::isinf(result) || std::isnan(result)) {
      return Complex<T>::NewFloat(result);
    }
  }
  return Complex<T>::NewFloat(std::round(result));
}

}
