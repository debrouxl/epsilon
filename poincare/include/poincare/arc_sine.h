#ifndef POINCARE_ARC_SINE_H
#define POINCARE_ARC_SINE_H

#include <poincare/layout_engine.h>
#include <poincare/static_hierarchy.h>
#include <poincare/approximation_engine.h>

namespace Poincare {

class ArcSine final : public StaticHierarchy<1>  {
  using StaticHierarchy<1>::StaticHierarchy;
public:
  Type type() const override;
  Expression * clone() const override {
    return new ArcSine(m_operands, true);
  }
private:
  /* Layout */
  ExpressionLayout * privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const override {
    return LayoutEngine::createPrefixLayout(this, floatDisplayMode, complexFormat, name());
  }
  int writeTextInBuffer(char * buffer, int bufferSize) const override {
    return LayoutEngine::writePrefixExpressionTextInBuffer(this, buffer, bufferSize, name());
  }
  const char * name() const { return "asin"; }
  /* Simplification */
  Expression * shallowReduce(Context & context, AngleUnit angleUnit) override;
  /* Evaluation */
  template<typename T> static Complex<T> computeOnComplex(const Complex<T> & c, AngleUnit angleUnit);
  Expression * privateApproximate(SinglePrecision p, Context& context, AngleUnit angleUnit) const override {
    return ApproximationEngine::map<float>(this, context, angleUnit,computeOnComplex<float>);
  }
  Expression * privateApproximate(DoublePrecision p, Context& context, AngleUnit angleUnit) const override {
    return ApproximationEngine::map<double>(this, context, angleUnit, computeOnComplex<double>);
  }
};

}

#endif
