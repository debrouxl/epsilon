#include <poincare/addition.h>
#include <poincare/complex_matrix.h>
extern "C" {
#include <assert.h>
#include <stdlib.h>
}
#include "layout/horizontal_layout.h"
#include "layout/string_layout.h"
#include "layout/parenthesis_layout.h"

namespace Poincare {

const Addition Addition::staticAdd;

Expression::Type Addition::type() const {
  return Type::Addition;
}

ExpressionLayout * Addition::privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const {
  assert(floatDisplayMode != FloatDisplayMode::Default);
  assert(complexFormat != ComplexFormat::Default);
  ExpressionLayout* children_layouts[3] = {
    m_operands[0]->createLayout(floatDisplayMode, complexFormat),
    new StringLayout("+", 1),
    m_operands[1]->type() == Type::Opposite ? new ParenthesisLayout(m_operands[1]->createLayout(floatDisplayMode, complexFormat)) : m_operands[1]->createLayout(floatDisplayMode, complexFormat)
  };
  ExpressionLayout * layout = new HorizontalLayout(children_layouts, 3, false);
  return layout;
}

template<typename T>
Complex<T> Addition::compute(const Complex<T> & c, const Complex<T> & d) {
  return Complex<T>::Cartesian(c.a()+d.a(), c.b()+d.b());
}

Expression * Addition::cloneWithDifferentOperands(Expression** newOperands,
    int numberOfOperands, bool cloneOperands) const {
  return new Addition(newOperands, cloneOperands);
}

bool Addition::isCommutative() const {
  return true;
}

template Poincare::Complex<float> Poincare::Addition::compute<float>(const Poincare::Complex<float> &, const Poincare::Complex<float> &);
template Poincare::Complex<double> Poincare::Addition::compute<double>(const Poincare::Complex<double> &, const Poincare::Complex<double> &);

template Poincare::Evaluation<float>* Poincare::Addition::computeOnMatrices<float>(Poincare::Evaluation<float>*, Poincare::Evaluation<float>*);
template Poincare::Evaluation<double>* Poincare::Addition::computeOnMatrices<double>(Poincare::Evaluation<double>*, Poincare::Evaluation<double>*);

template Poincare::Evaluation<float>* Poincare::Addition::computeOnComplexAndMatrix<float>(Poincare::Complex<float> const*, Poincare::Evaluation<float>*);
template Poincare::Evaluation<double>* Poincare::Addition::computeOnComplexAndMatrix<double>(Poincare::Complex<double> const*, Poincare::Evaluation<double>*);

}
