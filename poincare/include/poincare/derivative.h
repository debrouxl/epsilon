#ifndef POINCARE_DERIVATIVE_H
#define POINCARE_DERIVATIVE_H

#include <poincare/layout_engine.h>
#include <poincare/static_hierarchy.h>
#include <poincare/variable_context.h>

namespace Poincare {

class Derivative final : public StaticHierarchy<2> {
  using StaticHierarchy<2>::StaticHierarchy;
public:
  Type type() const override;
  Expression * clone() const override {
    return new Derivative(m_operands, true);
  }
private:
  /* Layout */
  ExpressionLayout * privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const override {
    return LayoutEngine::createPrefixLayout(this, floatDisplayMode, complexFormat, name());
  }
  int writeTextInBuffer(char * buffer, int bufferSize) const override {
    return LayoutEngine::writePrefixExpressionTextInBuffer(this, buffer, bufferSize, name());
  }
  const char * name() const { return "diff"; }
  /* Simplification */
  Expression * shallowReduce(Context& context, AngleUnit angleUnit) override;
  /* Evaluation */
  Expression * privateApproximate(SinglePrecision p, Context& context, AngleUnit angleUnit) const override { return templatedApproximate<float>(context, angleUnit); }
  Expression * privateApproximate(DoublePrecision p, Context& context, AngleUnit angleUnit) const override { return templatedApproximate<double>(context, angleUnit); }
  template<typename T> Expression * templatedApproximate(Context& context, AngleUnit angleUnit) const;
  template<typename T> T growthRateAroundAbscissa(T x, T h, VariableContext<T> variableContext, AngleUnit angleUnit) const;
  template<typename T> T approximateDerivate2(T x, T h, VariableContext<T> xContext, AngleUnit angleUnit) const;
  // TODO: Change coefficients?
  constexpr static float k_maxErrorRateOnApproximation = 0.001;
  constexpr static float k_minInitialRate = 0.01;
  constexpr static float k_rateStepSize = 1.4;
};

}

#endif
