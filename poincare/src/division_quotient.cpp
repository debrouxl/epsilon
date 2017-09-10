#include <poincare/division_quotient.h>

extern "C" {
#include <assert.h>
}
#include <cmath>

namespace Poincare {

DivisionQuotient::DivisionQuotient() :
  Function("quo", 2)
{
}

Expression::Type DivisionQuotient::type() const {
  return Type::DivisionQuotient;
}

Expression * DivisionQuotient::cloneWithDifferentOperands(Expression** newOperands,
        int numberOfOperands, bool cloneOperands) const {
  assert(newOperands != nullptr);
  DivisionQuotient * dq = new DivisionQuotient();
  dq->setArgument(newOperands, numberOfOperands, cloneOperands);
  return dq;
}

template<typename T>
Evaluation<T> * DivisionQuotient::templatedEvaluate(Context& context, AngleUnit angleUnit) const {
  T f1 = m_args[0]->approximate<T>(context, angleUnit);
  T f2 = m_args[1]->approximate<T>(context, angleUnit);
  if (isnan(f1) || isnan(f2) || f1 != (int)f1 || f2 != (int)f2) {
    return Complex<T>::NewFNAN();
  }
  return Complex<T>::NFloat(std::floor(f1/f2));
}

}

