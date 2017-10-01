extern "C" {
#include <assert.h>
#include <stdlib.h>
}
#include <poincare/complex_matrix.h>
#include <poincare/complex.h>
#include "layout/grid_layout.h"
#include "layout/bracket_layout.h"
#include <cmath>
#include <float.h>
#include <string.h>

namespace Poincare {

template<typename T>
T ComplexMatrix<T>::toScalar() const {
  if (m_numberOfRows != 1 || m_numberOfColumns != 1) {
    return NAN;
  }
  if (m_values[0].b() != 0) {
    return NAN;
  }
  return m_values[0].a();
}

template<typename T>
int ComplexMatrix<T>::numberOfRows() const {
  return m_numberOfRows;
}

template<typename T>
int ComplexMatrix<T>::numberOfColumns() const {
  return m_numberOfColumns;
}

template<typename T>
const Complex<T> * ComplexMatrix<T>::complexOperand(int i) const {
  return &m_values[i];
}

template<typename T>
ComplexMatrix<T> * ComplexMatrix<T>::clone() const {
  return new ComplexMatrix<T>(m_values, m_numberOfRows, m_numberOfColumns, false);
}

template<typename T>
ComplexMatrix<T> * ComplexMatrix<T>::cloneWithDifferentOperands(Expression** newOperands,
    int numberOfOperands, bool cloneOperands) const {
  assert(newOperands != nullptr);
  return new ComplexMatrix((Complex<T> *)newOperands[0], m_numberOfRows, m_numberOfColumns, false);
}

template<typename T>
Evaluation<T> * ComplexMatrix<T>::createIdentity(int dim) {
  Complex<T> * operands = new Complex<T> [dim*dim];
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      if (i == j) {
        operands[i*dim+j] = Complex<T>::Float(1.0);
      } else {
        operands[i*dim+j] = Complex<T>::Float(0.0);
      }
    }
  }
  Evaluation<T> * matrix = new ComplexMatrix<T>(operands, dim, dim, true);
  return matrix;
}

template<typename T>
template <class U>
Evaluation<U> * ComplexMatrix<T>::templatedEvaluate(Context& context, Expression::AngleUnit angleUnit) const {
  Complex<U> * values = new Complex<U>[m_numberOfRows*m_numberOfColumns];
  for (int i = 0; i < m_numberOfRows*m_numberOfColumns; i++) {
    values[i] = Complex<U>::Cartesian(m_values[i].a(), m_values[i].b());
  }
  Evaluation<U> * result = new ComplexMatrix<U>(values, m_numberOfRows, m_numberOfColumns, true);
  return result;

}

template class Poincare::ComplexMatrix<float>;
template class Poincare::ComplexMatrix<double>;

template Poincare::Evaluation<double>* Poincare::ComplexMatrix<float>::templatedEvaluate<double>(Poincare::Context&, Poincare::Expression::AngleUnit) const;
template Poincare::Evaluation<float>* Poincare::ComplexMatrix<float>::templatedEvaluate<float>(Poincare::Context&, Poincare::Expression::AngleUnit) const;
template Poincare::Evaluation<double>* Poincare::ComplexMatrix<double>::templatedEvaluate<double>(Poincare::Context&, Poincare::Expression::AngleUnit) const;
template Poincare::Evaluation<float>* Poincare::ComplexMatrix<double>::templatedEvaluate<float>(Poincare::Context&, Poincare::Expression::AngleUnit) const;

}
