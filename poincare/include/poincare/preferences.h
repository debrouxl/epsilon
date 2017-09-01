#ifndef POINCARE_PREFERENCES_H
#define POINCARE_PREFERENCES_H

#include <poincare/expression.h>

namespace Poincare {

class Preferences {
public:
  static Preferences * sharedPreferences() {
    return &s_preferences;
  };
  Expression::AngleUnit angleUnit() const {
    return m_angleUnit;
  }
  void setAngleUnit(Expression::AngleUnit angleUnit) {
    m_angleUnit = angleUnit;
  }
  Expression::FloatDisplayMode displayMode() const {
    return m_displayMode;
  }
  void setDisplayMode(Expression::FloatDisplayMode FloatDisplayMode) {
    m_displayMode = FloatDisplayMode;
  }
  Expression::ComplexFormat complexFormat() const {
    return m_complexFormat;
  }
  void setComplexFormat(Expression::ComplexFormat complexFormat) {
    m_complexFormat = complexFormat;
  }
private:
  Preferences() :
    m_angleUnit(Expression::AngleUnit::Degree),
    m_displayMode(Expression::FloatDisplayMode::Decimal),
    m_complexFormat(Expression::ComplexFormat::Cartesian) {
  }
  Expression::AngleUnit m_angleUnit;
  Expression::FloatDisplayMode m_displayMode;
  Expression::ComplexFormat m_complexFormat;
  static Preferences s_preferences;
};

}

#endif
