#include <poincare/undefined.h>
extern "C" {
#include <math.h>
}
#include "layout/string_layout.h"

namespace Poincare {

Expression::Type Undefined::type() const {
  return Type::Undefined;
}

ExpressionLayout * Undefined::privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const {
  char buffer[16];
  int numberOfChars = Complex<float>::convertFloatToText(NAN, buffer, 16, 1, floatDisplayMode);
  return new StringLayout(buffer, numberOfChars);
}

int Undefined::writeTextInBuffer(char * buffer, int bufferSize) const {
  if (bufferSize == 0) {
    return -1;
  }
  return strlcpy(buffer, "undef", bufferSize);
}

}

