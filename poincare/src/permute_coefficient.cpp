#include <poincare/permute_coefficient.h>
#include <poincare/complex.h>

extern "C" {
#include <assert.h>
}
#include <cmath>

namespace Poincare {

PermuteCoefficient::PermuteCoefficient() :
  Function("permute", 2)
{
}

Expression::Type PermuteCoefficient::type() const {
  return Type::PermuteCoefficient;
}

Expression * PermuteCoefficient::cloneWithDifferentOperands(Expression** newOperands,
        int numberOfOperands, bool cloneOperands) const {
  assert(newOperands != nullptr);
  PermuteCoefficient * pc = new PermuteCoefficient();
  pc->setArgument(newOperands, numberOfOperands, cloneOperands);
  return pc;
}

template<typename T>
Evaluation<T> * PermuteCoefficient::templatedEvaluate(Context& context, AngleUnit angleUnit) const {
  T n = m_args[0]->approximate<T>(context, angleUnit);
  T k = m_args[1]->approximate<T>(context, angleUnit);
  if (std::isnan(n) || std::isnan(k) || n != (int)n || k != (int)k || n < 0.0f || k < 0.0f) {
    return Complex<T>::NewFNAN();
  }
  if (k > n) {
    return new Complex<T>();
  }
  T result = 1;
  for (int i = (int)n-(int)k+1; i <= (int)n; i++) {
    result *= i;
  }
  return Complex<T>::NFloat(std::round(result));
}

}

