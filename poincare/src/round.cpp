#include <poincare/round.h>

extern "C" {
#include <assert.h>
}
#include <cmath>

namespace Poincare {

Round::Round() :
  Function("round", 2)
{
}

Expression::Type Round::type() const {
  return Type::Round;
}

Expression * Round::cloneWithDifferentOperands(Expression** newOperands,
        int numberOfOperands, bool cloneOperands) const {
  assert(newOperands != nullptr);
  Round * r = new Round();
  r->setArgument(newOperands, numberOfOperands, cloneOperands);
  return r;
}

template<typename T>
Evaluation<T> * Round::templatedEvaluate(Context& context, AngleUnit angleUnit) const {
  T f1 = m_args[0]->approximate<T>(context, angleUnit);
  T f2 = m_args[1]->approximate<T>(context, angleUnit);
  if (isnan(f2) || f2 != (int)f2) {
    return Complex<T>::NewFNAN();
  }
  T err = std::pow(10, std::floor(f2));
  return Complex<T>::NFloat(std::round(f1*err)/err);
}

}


