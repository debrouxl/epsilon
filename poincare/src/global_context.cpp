#include <poincare/global_context.h>
#include <poincare/matrix.h>
#include <poincare/matrix.h>
#include <assert.h>
#include <ion.h>

namespace Poincare {

Complex<double> * GlobalContext::defaultExpression() {
  static Complex<double> defaultExpression(Complex<double>::Float(0.0));
  return &defaultExpression;
}

int GlobalContext::symbolIndex(const Symbol * symbol) const {
  if (symbol->isMatrixSymbol()) {
    return symbol->name() - (char)Symbol::SpecialSymbols::M0;
  }
  if (symbol->isScalarSymbol()) {
    return symbol->name() - 'A';
  }
  return -1;
}

const Expression * GlobalContext::expressionForSymbol(const Symbol * symbol) {
  if (symbol->name() == Ion::Charset::SmallPi) {
    return &m_pi;
  }
  if (symbol->name() == Ion::Charset::Exponential) {
    return &m_e;
  }
  if (symbol->name() == Ion::Charset::IComplex) {
    return &m_i;
  }
  int index = symbolIndex(symbol);
  if (symbol->isMatrixSymbol()) {
    return m_matrixExpressions[index];
  }
  if (index < 0 || index >= k_maxNumberOfScalarExpressions) {
    return nullptr;
  }
  if (m_expressions[index] == nullptr) {
    return defaultExpression();
  }
  return m_expressions[index];
}

ExpressionLayout * GlobalContext::expressionLayoutForSymbol(const Symbol * symbol) {
  if (symbol->isMatrixSymbol()) {
    int index = symbolIndex(symbol);
    if (m_matrixLayout[index] == nullptr && m_matrixExpressions[index] != nullptr) {
      m_matrixLayout[index] = m_matrixExpressions[index]->createLayout();
    }
    return m_matrixLayout[index];
  }
  return nullptr;
}

void GlobalContext::setExpressionForSymbolName(const Expression * expression, const Symbol * symbol, Context & context) {
  int index = symbolIndex(symbol);
 if (symbol->isMatrixSymbol()) {
    int indexMatrix = symbol->name() - (char)Symbol::SpecialSymbols::M0;
    assert(indexMatrix >= 0 && indexMatrix < k_maxNumberOfMatrixExpressions);
    Expression * evaluation = expression ? expression->approximate<double>(context) : nullptr; // evaluate before deleting anything (to be able to evaluate M1+2->M1)
    if (m_matrixExpressions[indexMatrix] != nullptr) {
      delete m_matrixExpressions[indexMatrix];
      m_matrixExpressions[indexMatrix] = nullptr;
    }
    if (m_matrixLayout[indexMatrix] != nullptr) {
      delete m_matrixLayout[indexMatrix];
      m_matrixLayout[indexMatrix] = nullptr;
    }
    if (evaluation != nullptr) {
      if (evaluation->type() == Expression::Type::Complex) {
        m_matrixExpressions[indexMatrix] = new Matrix(&evaluation, 1, 1, false);
      } else {
        m_matrixExpressions[indexMatrix] = static_cast<Matrix *>(evaluation);
      }
    }
    return;
  }
  if (index < 0 || index >= k_maxNumberOfScalarExpressions) {
    return;
  }
  Expression * evaluation = expression ? expression->approximate<double>(context) : nullptr; // evaluate before deleting anything (to be able to evaluate A+2->A)
  delete m_expressions[index];
  m_expressions[index] = nullptr;
  if (evaluation == nullptr) {
    return;
  }
  if (evaluation->type() == Expression::Type::Complex) {
    m_expressions[index] = static_cast<Complex<double> *>(evaluation);
  } else {
    m_expressions[index] = Complex<double>::NewFNAN();
    delete evaluation;
  }
}

}
