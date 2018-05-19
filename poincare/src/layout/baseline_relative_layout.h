#ifndef POINCARE_BASELINE_RELATIVE_LAYOUT_H
#define POINCARE_BASELINE_RELATIVE_LAYOUT_H

#include <poincare/expression.h>
#include <poincare/expression_layout.h>

namespace Poincare {

class BaselineRelativeLayout final : public ExpressionLayout {
public:
  enum class Type {
    Subscript,
    Superscript
  };
  BaselineRelativeLayout(ExpressionLayout * baseLayout, ExpressionLayout * indiceLayout, Type type);
  ~BaselineRelativeLayout() {
    delete m_baseLayout;
    delete m_indiceLayout;
  }
  BaselineRelativeLayout(const BaselineRelativeLayout& other) = delete;
  BaselineRelativeLayout(BaselineRelativeLayout&& other) = delete;
  BaselineRelativeLayout& operator=(const BaselineRelativeLayout& other) = delete;
  BaselineRelativeLayout& operator=(BaselineRelativeLayout&& other) = delete;
  ExpressionLayout * baseLayout() {
    return m_baseLayout;
  }
  ExpressionLayout * indiceLayout() {
    return m_indiceLayout;
  }
protected:
  void render(KDContext * ctx, KDPoint p, KDColor expressionColor, KDColor backgroundColor) override;
  KDSize computeSize() override;
  ExpressionLayout * child(uint16_t index) override;
  KDPoint positionOfChild(ExpressionLayout * child) override;
private:
  constexpr static KDCoordinate k_indiceHeight = 5;
  ExpressionLayout * m_baseLayout;
  ExpressionLayout * m_indiceLayout;
  Type m_type;
};

}

#endif
