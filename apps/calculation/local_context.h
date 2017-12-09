#ifndef CALCULATION_LOCAL_CONTEXT_H
#define CALCULATION_LOCAL_CONTEXT_H

#include <poincare.h>
#include "calculation_store.h"

namespace Calculation {

class LocalContext final : public Poincare::Context {
public:
  LocalContext(Poincare::GlobalContext * parentContext, CalculationStore * calculationStore) :
    m_calculationStore(calculationStore),
    m_parentContext(parentContext) {}
  void setExpressionForSymbolName(const Poincare::Expression * expression, const Poincare::Symbol * symbol, Context & context) override;
  const Poincare::Expression * expressionForSymbol(const Poincare::Symbol * symbol) override;
private:
  Poincare::Expression * ansValue();
  CalculationStore * m_calculationStore;
  Poincare::GlobalContext * m_parentContext;
};

}

#endif
