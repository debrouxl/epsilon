#include <poincare/undefined.h>
#include <poincare/layout_engine.h>

extern "C" {
#include <math.h>
#include <string.h>
}

namespace Poincare {

Expression::Type Undefined::type() const {
  return Type::Undefined;
}

int Undefined::polynomialDegree(char symbolName) const {
  return -1;
}

ExpressionLayout * Undefined::privateCreateLayout(PrintFloat::Mode floatDisplayMode, ComplexFormat complexFormat) const {
  char buffer[16];
  int numberOfChars = PrintFloat::convertFloatToText<float>(NAN, buffer, 16, 1, floatDisplayMode);
  return LayoutEngine::createStringLayout(buffer, numberOfChars);
}

int Undefined::writeTextInBuffer(char * buffer, int bufferSize, int numberOfSignificantDigits) const {
  if (bufferSize == 0) {
    return -1;
  }
  return strlcpy(buffer, "undef", bufferSize);
}

}

