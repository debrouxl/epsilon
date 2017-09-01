#include <poincare/complex.h>
extern "C" {
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
}
#include <cmath>
#include <math.h>
#include <poincare/complex_matrix.h>
#include "layout/string_layout.h"
#include "layout/baseline_relative_layout.h"
#include <ion.h>

namespace Poincare {

void PrintFloat::printBase10IntegerWithDecimalMarker(char * buffer, int bufferSize, int bufferLength, Integer i, int decimalMarkerPosition) {
  /* The decimal marker position is always preceded by a char, thus, it is never
   * in first position. When called by convertFloatToText, the buffer length is
   * always > 0 as we asserted a minimal number of available chars. */
  assert(bufferSize > 0 && decimalMarkerPosition != 0);
  char tempBuffer[PrintFloat::k_storedFloatBufferLength];
  int intLength = i.convertToText(tempBuffer, PrintFloat::k_storedFloatBufferLength);
  for (int k = bufferLength-1; k >= 0; k--) {
    if (k == decimalMarkerPosition) {
      buffer[k] = '.';
      continue;
    }
    if (intLength > 0) {
      buffer[k] = tempBuffer[--intLength];
      continue;
    }
    buffer[k] = '0';
  }
}

template<typename T>
Complex<T> Complex<T>::Float(T x) {
  return Complex(x,0);
}

template<typename T>
Complex<T> Complex<T>::Cartesian(T a, T b) {
  return Complex(a,b);
}

template<typename T>
Complex<T> Complex<T>::Polar(T r, T th)  {
  T c = std::cos(th);
  T s = std::sin(th);
  /* Cheat: see comment on cosine.cpp.
   * Sine and cosine openbsd immplementationd are numerical approximation.
   * We though want to avoid evaluating e^(i*pi) to -1+1E-17i. We thus round
   * cosine and sine results to 0 if they are negligible compared to the
   * argument th. */
  c = th != 0 && std::fabs(c/th) <= Expression::epsilon<T>() ? 0 : c;
  s = th != 0 && std::fabs(s/th) <= Expression::epsilon<T>() ? 0 : s;
  return Complex(r*c,r*s);
}

template<typename T>
static inline T setSign(T f, bool negative) {
  if (negative) {
    return -f;
  }
  return f;
}

template<typename T>
T digitsToFloat(const char * digits, int length) {
  if (digits == nullptr) {
    return 0;
  }
  T result = 0;
  const char * digit = digits;
  for (int i = 0; i < length; i++) {
    result = 10 * result;
    result += *digit-'0';
    digit++;
  }
  return result;
}

template<typename T>
Complex<T>::Complex(const char * integralPart, int integralPartLength, bool integralNegative,
    const char * fractionalPart, int fractionalPartLength,
    const char * exponent, int exponentLength, bool exponentNegative) {
  T i = digitsToFloat<T>(integralPart, integralPartLength);
  T j = digitsToFloat<T>(fractionalPart, fractionalPartLength);
  T l = setSign<T>(digitsToFloat<T>(exponent, exponentLength), exponentNegative);

  m_a = setSign((i + j*std::pow(10, -std::ceil((T)fractionalPartLength)))* std::pow(10, l), integralNegative);
  m_b = 0;
}

template<typename T>
T Complex<T>::toScalar() const {
  if (m_b != 0) {
    return NAN;
  }
  return m_a;
}

template<typename T>
int Complex<T>::numberOfRows() const {
  return 1;
}

template<typename T>
int Complex<T>::numberOfColumns() const {
  return 1;
}

template<typename T>
Expression::Type Complex<T>::type() const {
  return Expression::Type::Complex;
}

template <class T>
Complex<T> * Complex<T>::clone() const {
  return new Complex<T>(*this);
}

template <class T>
Evaluation<T> * Complex<T>::cloneWithDifferentOperands(Expression** newOperands,
    int numberOfOperands, bool cloneOperands) const {
  return this->clone();
}

template <class T>
int Complex<T>::writeTextInBuffer(char * buffer, int bufferSize, int numberOfSignificantDigits) const {
  return convertComplexToText(buffer, bufferSize, Preferences::sharedPreferences()->displayMode(), Preferences::sharedPreferences()->complexFormat(), numberOfSignificantDigits);
}

template <class T>
Evaluation<T> * Complex<T>::createInverse() const {
  return new Complex<T>(Cartesian(1/m_a, -1/m_b));
}

template <class T>
T Complex<T>::a() const {
  return m_a;
}

template <class T>
T Complex<T>::b() const {
  return m_b;
}

template <class T>
T Complex<T>::r() const {
  if (m_b == 0) {
    return std::fabs(m_a);
  }
  return std::sqrt(m_a*m_a + m_b*m_b);
}

template <class T>
T Complex<T>::th() const {
  T result = std::atan(m_b/m_a) + M_PI;
  if (m_a >= 0) {
    T a = m_a == 0 ? 0 : m_a;
    result = std::atan(m_b/a);
  }
  if (result > M_PI + FLT_EPSILON) {
    result = result - 2*M_PI;
  }
  return result;
}

template <class T>
Complex<T> Complex<T>::conjugate() const {
  return Cartesian(m_a, -m_b);
}

template <class T>
int Complex<T>::convertFloatToText(T f, char * buffer, int bufferSize,
    int numberOfSignificantDigits, Expression::FloatDisplayMode mode) {
  assert(numberOfSignificantDigits > 0);
  if (mode == Expression::FloatDisplayMode::Default) {
    return convertFloatToText(f, buffer, bufferSize, numberOfSignificantDigits, Preferences::sharedPreferences()->displayMode());
  }
  char tempBuffer[PrintFloat::k_storedFloatBufferLength];
  int requiredLength = convertFloatToTextPrivate(f, tempBuffer, numberOfSignificantDigits, mode);
  /* if the required buffer size overflows the buffer size, we first force the
   * display mode to scientific and decrease the number of significant digits to
   * fit the buffer size. If the buffer size is still to small, we only write
   * the beginning of the float and truncate it (which can result in a non sense
   * text) */
  if (mode == Expression::FloatDisplayMode::Decimal && requiredLength >= bufferSize) {
    requiredLength = convertFloatToTextPrivate(f, tempBuffer, numberOfSignificantDigits, Expression::FloatDisplayMode::Scientific);
  }
  if (requiredLength >= bufferSize) {
    int adjustedNumberOfSignificantDigits = numberOfSignificantDigits - requiredLength + bufferSize - 1;
    adjustedNumberOfSignificantDigits = adjustedNumberOfSignificantDigits < 1 ? 1 : adjustedNumberOfSignificantDigits;
    requiredLength = convertFloatToTextPrivate(f, tempBuffer, adjustedNumberOfSignificantDigits, Expression::FloatDisplayMode::Scientific);
  }
  requiredLength = requiredLength < bufferSize ? requiredLength : bufferSize;
  strlcpy(buffer, tempBuffer, bufferSize);
  return requiredLength;
}

template <class T>
Complex<T>::Complex(T a, T b) :
  m_a(a),
  m_b(b)
{
}

template <class T>
const Complex<T> * Complex<T>::complexOperand(int i) const {
  return this;
}

template <class T>
ExpressionLayout * Complex<T>::privateCreateLayout(Expression::FloatDisplayMode floatDisplayMode, Expression::ComplexFormat complexFormat) const {
  assert(floatDisplayMode != Expression::FloatDisplayMode::Default);
  if (complexFormat == Expression::ComplexFormat::Polar) {
    return createPolarLayout(floatDisplayMode);
  }
  return createCartesianLayout(floatDisplayMode);
}

template<typename T>
template<typename U>
Evaluation<U> * Complex<T>::templatedEvaluate(Context& context, Expression::AngleUnit angleUnit) const {
  return new Complex<U>(Complex<U>::Cartesian((U)m_a, (U)m_b));
}

template <class T>
int Complex<T>::convertComplexToText(char * buffer, int bufferSize, Expression::FloatDisplayMode displayMode, Expression::ComplexFormat complexFormat, int numberOfSignificantDigits) const {
  assert(displayMode != Expression::FloatDisplayMode::Default);
  int numberOfChars = 0;
  if (isnan(m_a) || isnan(m_b)) {
    return convertFloatToText(NAN, buffer, bufferSize, numberOfSignificantDigits, displayMode);
  }
  if (complexFormat == Expression::ComplexFormat::Polar) {
    if (r() != 1 || th() == 0) {
      numberOfChars = convertFloatToText(r(), buffer, bufferSize, numberOfSignificantDigits, displayMode);
      if (r() != 0 && th() != 0 && bufferSize > numberOfChars+1) {
        buffer[numberOfChars++] = '*';
        // Ensure that the string is null terminated even if buffer size is to small
        buffer[numberOfChars] = 0;
      }
    }
    if (r() != 0 && th() != 0) {
      if (bufferSize > numberOfChars+3) {
        buffer[numberOfChars++] = Ion::Charset::Exponential;
        buffer[numberOfChars++] = '^';
        buffer[numberOfChars++] = '(';
        // Ensure that the string is null terminated even if buffer size is to small
        buffer[numberOfChars] = 0;
      }
      numberOfChars += convertFloatToText(th(), buffer+numberOfChars, bufferSize-numberOfChars, numberOfSignificantDigits, displayMode);
      if (bufferSize > numberOfChars+3) {
        buffer[numberOfChars++] = '*';
        buffer[numberOfChars++] = Ion::Charset::IComplex;
        buffer[numberOfChars++] = ')';
        buffer[numberOfChars] = 0;
      }
    }
    return numberOfChars;
  }

  if (m_a != 0 || m_b == 0) {
    numberOfChars = convertFloatToText(m_a, buffer, bufferSize, numberOfSignificantDigits, displayMode);
    if (m_b > 0 && !isnan(m_b) && bufferSize > numberOfChars+1) {
      buffer[numberOfChars++] = '+';
      // Ensure that the string is null terminated even if buffer size is to small
      buffer[numberOfChars] = 0;
    }
  }
  if (m_b != 1 && m_b != -1 && m_b != 0) {
    numberOfChars += convertFloatToText(m_b, buffer+numberOfChars, bufferSize-numberOfChars, numberOfSignificantDigits, displayMode);
    buffer[numberOfChars++] = '*';
  }
  if (m_b == -1 && bufferSize > numberOfChars+1) {
    buffer[numberOfChars++] = '-';
  }
  if (m_b != 0 && bufferSize > numberOfChars+1) {
    buffer[numberOfChars++] = Ion::Charset::IComplex;
    buffer[numberOfChars] = 0;
  }
  return numberOfChars;
}

template <class T>
int Complex<T>::convertFloatToTextPrivate(T f, char * buffer, int numberOfSignificantDigits, Expression::FloatDisplayMode mode) {
  assert(mode != Expression::FloatDisplayMode::Default);
  assert(numberOfSignificantDigits > 0);
  if (isinf(f)) {
    int currentChar = 0;
    if (f < 0) {
      buffer[currentChar++] = '-';
    }
    buffer[currentChar++] = 'i';
    buffer[currentChar++] = 'n';
    buffer[currentChar++] = 'f';
    buffer[currentChar] = 0;
    return currentChar;
  }

  if (isnan(f)) {
    int currentChar = 0;
    buffer[currentChar++] = 'u';
    buffer[currentChar++] = 'n';
    buffer[currentChar++] = 'd';
    buffer[currentChar++] = 'e';
    buffer[currentChar++] = 'f';
    buffer[currentChar] = 0;
    return currentChar;
  }

  T logBase10 = f != 0 ? std::log10(std::fabs(f)) : 0;
  int exponentInBase10 = std::floor(logBase10);
  /* Correct the exponent in base 10: sometines the exact log10 of f is 6.999999
   * but is stored as 7 in hardware. We catch these cases here. */
  if (f != 0 && logBase10 == (int)logBase10 && std::fabs(f) < std::pow(10, logBase10)) {
    exponentInBase10--;
  }

  Expression::FloatDisplayMode displayMode = mode;
  if ((exponentInBase10 >= numberOfSignificantDigits || exponentInBase10 <= -numberOfSignificantDigits) && mode == Expression::FloatDisplayMode::Decimal) {
    displayMode = Expression::FloatDisplayMode::Scientific;
  }

  // Number of char available for the mantissa
  int availableCharsForMantissaWithoutSign = numberOfSignificantDigits + 1;
  int availableCharsForMantissaWithSign = f >= 0 ? availableCharsForMantissaWithoutSign : availableCharsForMantissaWithoutSign + 1;

  // Compute mantissa
  /* The number of digits in an int64_t is capped because the maximal integer is
   * 2^63 - 1. As our mantissa is an integer, we assert that we stay beyond this
   * threshold during computation. */
  assert(availableCharsForMantissaWithoutSign - 1 < std::log10(std::pow(2.0f, 63.0f)));

  int numberOfDigitBeforeDecimal = exponentInBase10 >= 0 || displayMode == Expression::FloatDisplayMode::Scientific ?
                                   exponentInBase10 + 1 : 1;
  T unroundedMantissa = f * std::pow(10, (T)availableCharsForMantissaWithoutSign - 1 - numberOfDigitBeforeDecimal);
  T mantissa = std::round(unroundedMantissa);
  /* if availableCharsForMantissaWithoutSign - 1 - numberOfDigitBeforeDecimal
   * is too big (or too small), mantissa is now inf. We handle this case by
   * using logarithm function. */
  if (isnan(mantissa) || isinf(mantissa)) {
    mantissa = std::round(std::pow(10, std::log10(std::fabs(f))+(T)(availableCharsForMantissaWithoutSign - 1 - numberOfDigitBeforeDecimal)));
    mantissa = std::copysign(mantissa, f);
  }
  /* We update the exponent in base 10 (if 0.99999999 was rounded to 1 for
   * instance) */
  T truncatedMantissa = unroundedMantissa > 0 ? std::floor(unroundedMantissa) : std::ceil(unroundedMantissa);
  if (isinf(truncatedMantissa) || isnan(truncatedMantissa)) {
    T unroundedMantissaLogExp = std::pow(10, std::log10(std::fabs(f))+(T)(availableCharsForMantissaWithoutSign - 1 - numberOfDigitBeforeDecimal));
    truncatedMantissa = unroundedMantissaLogExp > 0 ? std::floor(unroundedMantissaLogExp) : std::ceil(unroundedMantissaLogExp);
    truncatedMantissa = std::copysign(truncatedMantissa, f);
  }
  if (mantissa != truncatedMantissa) {
    T newLogBase10 = mantissa != 0 ? std::log10(std::fabs(mantissa/std::pow((T)10, (T)(availableCharsForMantissaWithoutSign - 1 - numberOfDigitBeforeDecimal)))) : 0;
    if (isnan(newLogBase10) || isinf(newLogBase10)) {
      newLogBase10 = std::log10(std::fabs((T)mantissa)) - (T)(availableCharsForMantissaWithoutSign - 1 - numberOfDigitBeforeDecimal);
    }
    exponentInBase10 = std::floor(newLogBase10);
  }
  int decimalMarkerPosition = exponentInBase10 < 0 || displayMode == Expression::FloatDisplayMode::Scientific ?
    1 : exponentInBase10+1;
  decimalMarkerPosition = f < 0 ? decimalMarkerPosition+1 : decimalMarkerPosition;

  // Correct the number of digits in mantissa after rounding
  int mantissaExponentInBase10 = exponentInBase10 > 0 || displayMode == Expression::FloatDisplayMode::Scientific ? availableCharsForMantissaWithoutSign - 1 : availableCharsForMantissaWithoutSign + exponentInBase10;
  if (std::floor(std::fabs((T)mantissa) * std::pow((T)10, - mantissaExponentInBase10)) > 0) {
    mantissa = mantissa/10;
  }

  int numberOfCharExponent = exponentInBase10 != 0 ? std::log10(std::fabs((T)exponentInBase10)) + 1 : 1;
  if (exponentInBase10 < 0){
    // If the exponent is < 0, we need a additional char for the sign
    numberOfCharExponent++;
  }

  // Supress the 0 on the right side of the mantissa
  Integer dividend = Integer((int64_t)std::fabs(mantissa));
  Integer quotien = dividend.divide_by(Integer(10));
  Integer digit = dividend.subtract(quotien.multiply_by(10));
  int minimumNumberOfCharsInMantissa = 1;
  while (digit == Integer(0) && availableCharsForMantissaWithoutSign > minimumNumberOfCharsInMantissa &&
      (availableCharsForMantissaWithoutSign > exponentInBase10+2 || displayMode == Expression::FloatDisplayMode::Scientific)) {
    mantissa = mantissa/10;
    availableCharsForMantissaWithoutSign--;
    availableCharsForMantissaWithSign--;
    dividend = (Integer&&)quotien;
    quotien = dividend.divide_by(10);
    digit = dividend.subtract(quotien.multiply_by(10));
  }

  // Suppress the decimal marker if no fractional part
  if ((displayMode == Expression::FloatDisplayMode::Decimal && availableCharsForMantissaWithoutSign == exponentInBase10+2)
      || (displayMode == Expression::FloatDisplayMode::Scientific && availableCharsForMantissaWithoutSign == 2)) {
    availableCharsForMantissaWithSign--;
  }

  // Print mantissa
  assert(availableCharsForMantissaWithSign < PrintFloat::k_storedFloatBufferLength);
  PrintFloat::printBase10IntegerWithDecimalMarker(buffer, PrintFloat::k_storedFloatBufferLength, availableCharsForMantissaWithSign, Integer((int64_t)mantissa), decimalMarkerPosition);
  if (displayMode == Expression::FloatDisplayMode::Decimal || exponentInBase10 == 0) {
    buffer[availableCharsForMantissaWithSign] = 0;
    return availableCharsForMantissaWithSign;
  }
  // Print exponent
  assert(availableCharsForMantissaWithSign < PrintFloat::k_storedFloatBufferLength);
  buffer[availableCharsForMantissaWithSign] = Ion::Charset::Exponent;
  assert(numberOfCharExponent+availableCharsForMantissaWithSign+1 < PrintFloat::k_storedFloatBufferLength);
  PrintFloat::printBase10IntegerWithDecimalMarker(buffer+availableCharsForMantissaWithSign+1, PrintFloat::k_storedFloatBufferLength, numberOfCharExponent, Integer(exponentInBase10), -1);
  buffer[availableCharsForMantissaWithSign+1+numberOfCharExponent] = 0;
  return (availableCharsForMantissaWithSign+1+numberOfCharExponent);
}

template <class T>
ExpressionLayout * Complex<T>::createPolarLayout(Expression::FloatDisplayMode floatDisplayMode) const {
  char bufferBase[PrintFloat::k_printedFloatBufferLength+2];
  int numberOfCharInBase = 0;
  char bufferSuperscript[PrintFloat::k_printedComplexBufferLength+2];
  int numberOfCharInSuperscript = 0;

  if (r() != 1 || th() == 0) {
    numberOfCharInBase = convertFloatToText(r(), bufferBase, PrintFloat::k_printedComplexBufferLength, Expression::k_numberOfPrintedSignificantDigits, floatDisplayMode);
    if (r() != 0 && th() != 0) {
      bufferBase[numberOfCharInBase++] = '*';
    }
  }
  if (r() != 0 && th() != 0) {
    bufferBase[numberOfCharInBase++] = Ion::Charset::Exponential;
    bufferBase[numberOfCharInBase] = 0;
  }

  if (r() != 0 && th() != 0) {
    numberOfCharInSuperscript = convertFloatToText(th(), bufferSuperscript, PrintFloat::k_printedComplexBufferLength, Expression::k_numberOfPrintedSignificantDigits, floatDisplayMode);
    bufferSuperscript[numberOfCharInSuperscript++] = '*';
    bufferSuperscript[numberOfCharInSuperscript++] = Ion::Charset::IComplex;
    bufferSuperscript[numberOfCharInSuperscript] = 0;
  }
  if (numberOfCharInSuperscript == 0) {
    return new StringLayout(bufferBase, numberOfCharInBase);
  }
  return new BaselineRelativeLayout(new StringLayout(bufferBase, numberOfCharInBase), new StringLayout(bufferSuperscript, numberOfCharInSuperscript), BaselineRelativeLayout::Type::Superscript);
}

template <class T>
ExpressionLayout * Complex<T>::createCartesianLayout(Expression::FloatDisplayMode floatDisplayMode) const {
  char buffer[PrintFloat::k_printedComplexBufferLength];
  int numberOfChars = convertComplexToText(buffer, PrintFloat::k_printedComplexBufferLength, floatDisplayMode, Expression::ComplexFormat::Cartesian, Expression::k_numberOfPrintedSignificantDigits);
  return new StringLayout(buffer, numberOfChars);
}

template class Poincare::Complex<float>;
template class Poincare::Complex<double>;
template Poincare::Evaluation<double>* Poincare::Complex<double>::templatedEvaluate<double>(Poincare::Context&, Poincare::Expression::AngleUnit) const;
template Poincare::Evaluation<float>* Poincare::Complex<double>::templatedEvaluate<float>(Poincare::Context&, Poincare::Expression::AngleUnit) const;
template Poincare::Evaluation<double>* Poincare::Complex<float>::templatedEvaluate<double>(Poincare::Context&, Poincare::Expression::AngleUnit) const;
template Poincare::Evaluation<float>* Poincare::Complex<float>::templatedEvaluate<float>(Poincare::Context&, Poincare::Expression::AngleUnit) const;

}

