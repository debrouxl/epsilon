#include <poincare/great_common_divisor.h>
#include <poincare/complex.h>

extern "C" {
#include <assert.h>
}
#include <cmath>

namespace Poincare {

GreatCommonDivisor::GreatCommonDivisor() :
  Function("gcd", 2)
{
}

Expression::Type GreatCommonDivisor::type() const {
  return Type::GreatCommonDivisor;
}

Expression * GreatCommonDivisor::cloneWithDifferentOperands(Expression** newOperands,
        int numberOfOperands, bool cloneOperands) const {
  assert(newOperands != nullptr);
  GreatCommonDivisor * gcd = new GreatCommonDivisor();
  gcd->setArgument(newOperands, numberOfOperands, cloneOperands);
  return gcd;
}

template<typename T>
Evaluation<T> * GreatCommonDivisor::templatedEvaluate(Context& context, AngleUnit angleUnit) const {
  T f1 = m_args[0]->approximate<T>(context, angleUnit);
  T f2 = m_args[1]->approximate<T>(context, angleUnit);
  if (std::isnan(f1) || std::isnan(f2) || f1 != (int)f1 || f2 != (int)f2) {
    return Complex<T>::NewFNAN();
  }
  int a = (int)f2;
  int b = (int)f1;
  if (f1 > f2) {
    b = a;
    a = (int)f1;
  }
  int r = 0;
  while((int)b!=0){
    r = a - ((int)(a/b))*b;
    a = b;
    b = r;
  }
  return Complex<T>::NFloat(std::round((T)a));
}

}

