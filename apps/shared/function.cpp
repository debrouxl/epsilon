#include "function.h"
#include <string.h>
#include <cmath>
#include <assert.h>

using namespace Poincare;

namespace Shared {

Function::Function(const char * name, KDColor color) :
  m_expression(nullptr),
  m_text{0},
  m_name(name),
  m_color(color),
  m_layout(nullptr),
  m_active(true)
{
}

Function& Function::operator=(const Function& other) {
  // Self-assignment is benign
  m_color = other.m_color;
  m_name = other.m_name;
  m_active = other.m_active;
  setContent(other.m_text);
  return *this;
}

uint32_t Function::checksum() {
  char data[k_dataLengthInBytes/sizeof(char)] = {};
  strlcpy(data, m_text, TextField::maxBufferSize());
  data[k_dataLengthInBytes-2] = m_name != nullptr ? m_name[0] : 0;
  data[k_dataLengthInBytes-1] = m_active ? 1 : 0;
  return Ion::crc32((uint32_t *)data, k_dataLengthInBytes/sizeof(uint32_t));
}

void Function::setContent(const char * c) {
  strlcpy(m_text, c, sizeof(m_text));
  tidy();
}

Poincare::Expression * Function::expression() const {
  if (m_expression == nullptr) {
    m_expression = Expression::parse(m_text);
  }
  return m_expression;
}

Poincare::ExpressionLayout * Function::layout() {
  if (m_layout == nullptr && expression() != nullptr) {
    m_layout = expression()->createLayout(Expression::FloatDisplayMode::Decimal);
  }
  return m_layout;
}

template<typename T>
T Function::templatedEvaluateAtAbscissa(T x, Poincare::Context * context) const {
  Poincare::VariableContext<T> variableContext = Poincare::VariableContext<T>(symbol(), context);
  Poincare::Symbol xSymbol = Poincare::Symbol(symbol());
  Poincare::Complex<T> e = Poincare::Complex<T>::Float(x);
  variableContext.setExpressionForSymbolName(&e, &xSymbol);
  return expression()->approximate<T>(variableContext);
}

void Function::tidy() {
  delete m_layout;
  m_layout = nullptr;
  delete m_expression;
  m_expression = nullptr;
}

}

template float Shared::Function::templatedEvaluateAtAbscissa<float>(float, Poincare::Context*) const;
template double Shared::Function::templatedEvaluateAtAbscissa<double>(double, Poincare::Context*) const;
