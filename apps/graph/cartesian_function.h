#ifndef GRAPH_CARTESIAN_FUNCTION_H
#define GRAPH_CARTESIAN_FUNCTION_H

#include "../shared/function.h"

namespace Graph {

class CartesianFunction final : public Shared::Function {
public:
  using Shared::Function::Function;
  CartesianFunction(const char * text = nullptr, KDColor color = KDColorBlack);
  bool displayDerivative() {
    return m_displayDerivative;
  }
  void setDisplayDerivative(bool display) {
    m_displayDerivative = display;
  }
  double approximateDerivative(double x, Poincare::Context * context) const;
  char symbol() const override;
private:
  bool m_displayDerivative;
};

}

#endif
