extern "C" {
#include <assert.h>
#include <stdlib.h>
}

#include <poincare/subtraction.h>
#include <poincare/opposite.h>
#include "layout/horizontal_layout.h"
#include "layout/string_layout.h"
#include "layout/parenthesis_layout.h"

namespace Poincare {

Expression * Subtraction::cloneWithDifferentOperands(Expression** newOperands,
    int numberOfOperands, bool cloneOperands) const {
  assert(newOperands != nullptr);
  assert(numberOfOperands == 2);
  return new Subtraction(newOperands, cloneOperands);
}

Expression::Type Subtraction::type() const {
  return Expression::Type::Subtraction;
}

ExpressionLayout * Subtraction::privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const {
  assert(floatDisplayMode != FloatDisplayMode::Default);
  assert(complexFormat != ComplexFormat::Default);
  ExpressionLayout * children_layouts[3] = {
    m_operands[0]->createLayout(floatDisplayMode, complexFormat),
    new StringLayout("-", 1),
    m_operands[1]->type() == Type::Opposite ? new ParenthesisLayout(m_operands[1]->createLayout(floatDisplayMode, complexFormat)) : m_operands[1]->createLayout(floatDisplayMode, complexFormat)
  };
  return new HorizontalLayout(children_layouts, 3);
}

template<typename T>
Complex<T> Subtraction::compute(const Complex<T> & c, const Complex<T> & d) {
  return Complex<T>::Cartesian(c.a()-d.a(), c.b() - d.b());
}

template<typename T> Evaluation<T> * Subtraction::templatedComputeOnComplexAndComplexMatrix(const Complex<T> * c, Evaluation<T> * m) const {
  Evaluation<T> * operand = computeOnComplexMatrixAndComplex(m, c);
  Evaluation<T> * result = Opposite::computeOnMatrix(operand);
  delete operand;
  return result;
}

}

template Poincare::Complex<float> Poincare::Subtraction::compute<float>(const Poincare::Complex<float> &, const Poincare::Complex<float> &);
template Poincare::Complex<double> Poincare::Subtraction::compute<double>(const Poincare::Complex<double> &, const Poincare::Complex<double> &);
