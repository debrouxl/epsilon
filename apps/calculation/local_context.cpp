#include "local_context.h"
#include <string.h>
using namespace Poincare;

namespace Calculation {

Expression * LocalContext::ansValue() {
  if (m_calculationStore->numberOfCalculations() == 0) {
    return m_parentContext->defaultExpression();
  }
  Calculation * lastCalculation = m_calculationStore->calculationAtIndex(m_calculationStore->numberOfCalculations()-1);
  return lastCalculation->approximateOutput(m_parentContext);
}

void LocalContext::setExpressionForSymbolName(const Expression * expression, const Symbol * symbol, Context & context) {
  if (symbol->name() != Symbol::SpecialSymbols::Ans) {
    m_parentContext->setExpressionForSymbolName(expression, symbol, context);
  }
}

const Expression * LocalContext::expressionForSymbol(const Symbol * symbol) {
  if (symbol->name() == Symbol::SpecialSymbols::Ans) {
    return ansValue();
  } else {
    return m_parentContext->expressionForSymbol(symbol);
  }
}

}
