#include <poincare/division_remainder.h>

extern "C" {
#include <assert.h>
}
#include <cmath>

namespace Poincare {

DivisionRemainder::DivisionRemainder() :
  Function("rem", 2)
{
}

Expression::Type DivisionRemainder::type() const {
  return Type::DivisionRemainder;
}

Expression * DivisionRemainder::cloneWithDifferentOperands(Expression** newOperands,
        int numberOfOperands, bool cloneOperands) const {
  assert(newOperands != nullptr);
  DivisionRemainder * dr = new DivisionRemainder();
  dr->setArgument(newOperands, numberOfOperands, cloneOperands);
  return dr;
}

template<typename T>
Evaluation<T> * DivisionRemainder::templatedEvaluate(Context& context, AngleUnit angleUnit) const {
  T f1 = m_args[0]->approximate<T>(context, angleUnit);
  T f2 = m_args[1]->approximate<T>(context, angleUnit);
  if (std::isnan(f1) || std::isnan(f2) || f1 != (int)f1 || f2 != (int)f2) {
    return Complex<T>::NewFNAN();
  }
  return Complex<T>::NFloat(std::round(f1-f2*std::floor(f1/f2)));
}

}

