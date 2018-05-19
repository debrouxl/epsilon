#ifndef POINCARE_PREFERENCES_H
#define POINCARE_PREFERENCES_H

#include <poincare/expression.h>
#include <poincare/print_float.h>

namespace Poincare {

class Preferences final {
public:
  static Preferences * sharedPreferences() {
    return &s_preferences;
  }
  Expression::AngleUnit angleUnit() const {
    return m_angleUnit;
  }
  void setAngleUnit(Expression::AngleUnit angleUnit) {
    m_angleUnit = angleUnit;
  }
  PrintFloat::Mode displayMode() const {
    return m_displayMode;
  }
  void setDisplayMode(PrintFloat::Mode mode) {
    m_displayMode = mode;
  }
  Expression::ComplexFormat complexFormat() const {
    return m_complexFormat;
  }
  void setComplexFormat(Expression::ComplexFormat complexFormat) {
    m_complexFormat = complexFormat;
  }
  char numberOfSignificantDigits() const {
    return m_numberOfSignificantDigits;
  }
  void setNumberOfSignificantDigits(char numberOfSignificantDigits) {
    m_numberOfSignificantDigits = numberOfSignificantDigits;
  }
private:
  Preferences() :
    m_angleUnit(Expression::AngleUnit::Degree),
    m_displayMode(PrintFloat::Mode::Decimal),
    m_complexFormat(Expression::ComplexFormat::Cartesian),
    m_numberOfSignificantDigits(PrintFloat::k_numberOfPrintedSignificantDigits) {
  }
  Expression::AngleUnit m_angleUnit;
  PrintFloat::Mode m_displayMode;
  Expression::ComplexFormat m_complexFormat;
  char m_numberOfSignificantDigits;
  static Preferences s_preferences;
};

}

#endif
