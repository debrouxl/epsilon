#ifndef POINCARE_AND_H
#define POINCARE_AND_H

#include <poincare/binary_operation.h>

namespace Poincare {

class And : public BinaryOperation {
  using BinaryOperation::BinaryOperation;
public:
  Type type() const override;
  Expression * cloneWithDifferentOperands(Expression** newOperands,
      int numnerOfOperands, bool cloneOperands = true) const override;
  bool isCommutative() const override;
  template<typename T> static Complex<T> compute(const Complex<T> & c, const Complex<T> & d);
private:
  Complex<float> privateCompute(const Complex<float> & c, const Complex<float> & d) const override {
    return compute(c, d);
  }
  Complex<double> privateCompute(const Complex<double> & c, const Complex<double> & d) const override {
    return compute(c, d);
  }
  ExpressionLayout * privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const override;
};

}

#endif
