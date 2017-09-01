#ifndef POINCARE_ADDITION_H
#define POINCARE_ADDITION_H

#include <poincare/binary_operation.h>

namespace Poincare {

class Addition final : public BinaryOperation {
  using BinaryOperation::BinaryOperation;
public:
  Type type() const override;
  Expression * cloneWithDifferentOperands(Expression** newOperands,
      int numnerOfOperands, bool cloneOperands = true) const override;
  bool isCommutative() const override;
  template<typename T> static Complex<T> compute(const Complex<T> c, const Complex<T> d);
  template<typename T> static Evaluation<T> * computeOnMatrices(Evaluation<T> * m, Evaluation<T> * n) {
    return staticAdd.computeOnComplexMatrices(m,n);
  }
  template<typename T> static Evaluation<T> * computeOnComplexAndMatrix(const Complex<T> * c, Evaluation<T> * m) {
    return staticAdd.computeOnComplexAndComplexMatrix(c,m);
  }
private:
  Complex<float> privateCompute(const Complex<float> c, const Complex<float> d) const override {
    return compute(c, d);
  }
  Complex<double> privateCompute(const Complex<double> c, const Complex<double> d) const override {
    return compute(c, d);
  }
  ExpressionLayout * privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const override;
  static const Addition staticAdd;
};

}

#endif
