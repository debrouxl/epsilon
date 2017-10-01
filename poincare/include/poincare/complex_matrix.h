#ifndef POINCARE_COMPLEX_MATRIX_H
#define POINCARE_COMPLEX_MATRIX_H

#include <poincare/evaluation.h>

namespace Poincare {

template<typename T>
class ComplexMatrix final : public Evaluation<T> {
public:
  ComplexMatrix(const Complex<T> * complexes, int numberOfRows, int numberOfColumns) :
    m_values(new Complex<T>[numberOfRows*numberOfColumns]),
    m_numberOfRows(numberOfRows),
    m_numberOfColumns(numberOfColumns) {
    for (int i = 0; i < numberOfRows*numberOfColumns; i++) {
      m_values[i] = complexes[i];
    }
  }
  ComplexMatrix(const Complex<T> * complexes, int numberOfRows, int numberOfColumns, bool borrow) :
    m_values(const_cast<Complex<T> *>(complexes)),
    m_numberOfRows(numberOfRows),
    m_numberOfColumns(numberOfColumns) {}
  ~ComplexMatrix() {
    delete[] m_values;
    m_values = nullptr;
  }
  ComplexMatrix(const ComplexMatrix& other) = delete;
  ComplexMatrix(ComplexMatrix&& other) = delete;
  ComplexMatrix& operator=(const ComplexMatrix& other) = delete;
  ComplexMatrix& operator=(ComplexMatrix&& other) = delete;
  T toScalar() const override;
  const Complex<T> * complexOperand(int i) const override;
  int numberOfRows() const override;
  int numberOfColumns() const override;
  ComplexMatrix<T> * clone() const override;
  ComplexMatrix<T> * cloneWithDifferentOperands(Expression** newOperands,
    int numberOfOperands, bool cloneOperands = true) const override;
  static Evaluation<T> * createIdentity(int dim);
private:
  Evaluation<float> * privateEvaluate(Expression::SinglePrecision p, Context& context, Expression::AngleUnit angleUnit) const override { return templatedEvaluate<float>(context, angleUnit); }
  Evaluation<double> * privateEvaluate(Expression::DoublePrecision p, Context& context, Expression::AngleUnit angleUnit) const override { return templatedEvaluate<double>(context, angleUnit); }
 template<typename U> Evaluation<U> * templatedEvaluate(Context& context, Expression::AngleUnit angleUnit) const;
  Complex<T> * m_values;
  int m_numberOfRows;
  int m_numberOfColumns;
};

}

#endif

