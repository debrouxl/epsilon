#ifndef POINCARE_REAL_PART_H
#define POINCARE_REAL_PART_H

#include <poincare/function.h>

namespace Poincare {

class RealPart final : public Function {
public:
  RealPart();
  Type type() const override;
  Expression * cloneWithDifferentOperands(Expression ** newOperands,
    int numberOfOperands, bool cloneOperands = true) const override;
private:
  Complex<float> computeComplex(const Complex<float> & c, AngleUnit angleUnit) const override {
    return templatedComputeComplex(c);
  }
  Complex<double> computeComplex(const Complex<double> & c, AngleUnit angleUnit) const override {
    return templatedComputeComplex(c);
  }
  template<typename T> Complex<T> templatedComputeComplex(const Complex<T> & c) const {
    return Complex<T>::Float(c.a());
  }
};

}

#endif


