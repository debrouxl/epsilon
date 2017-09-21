#include <poincare/confidence_interval.h>
#include <poincare/matrix.h>
#include <poincare/evaluation.h>
extern "C" {
#include <assert.h>
}
#include <cmath>

namespace Poincare {

ConfidenceInterval::ConfidenceInterval() :
  Function("confidence", 2)
{
}

Expression::Type ConfidenceInterval::type() const {
  return Type::ConfidenceInterval;
}

Expression * ConfidenceInterval::cloneWithDifferentOperands(Expression** newOperands,
        int numberOfOperands, bool cloneOperands) const {
  assert(newOperands != nullptr);
  ConfidenceInterval * ci = new ConfidenceInterval();
  ci->setArgument(newOperands, numberOfOperands, cloneOperands);
  return ci;
}

template<typename T>
Evaluation<T> * ConfidenceInterval::templatedEvaluate(Context& context, AngleUnit angleUnit) const {
  T f = m_args[0]->approximate<T>(context, angleUnit);
  T n = m_args[1]->approximate<T>(context, angleUnit);
  if (std::isnan(f) || std::isnan(n) || n != (int)n || n < 0 || f < 0 || f > 1) {
    return Complex<T>::NewFNAN();
  }
  Complex<T> operands[2] = {
    Complex<T>::Float(f - 1/std::sqrt(n)),
    Complex<T>::Float(f + 1/std::sqrt(n))
  };
  return new ComplexMatrix<T>(operands, 1, 2, false);
}

}
