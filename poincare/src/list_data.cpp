extern "C" {
#include <assert.h>
#include <stdlib.h>
}
#include <poincare/list_data.h>

namespace Poincare {

ListData::ListData(Expression * operand) :
  m_numberOfOperands(1),
  m_operands(new Expression*[1])
{
  assert(operand != nullptr);
  m_operands[0] = operand;
}

ListData::~ListData() {
  for (int i=0; i<m_numberOfOperands; i++) {
    delete m_operands[i];
  }
  delete[] m_operands;
}

void ListData::pushExpression(Expression * operand) {
  Expression ** newOperands = new Expression *[m_numberOfOperands+1];
  for (int i=0; i<m_numberOfOperands; i++) {
    newOperands[i] = m_operands[i];
  }
  delete [] m_operands;
  newOperands[m_numberOfOperands] = operand;
  m_operands = newOperands;
  m_numberOfOperands++;
}

const Expression * ListData::operand(int i) const {
  assert(i >= 0);
  assert(i < m_numberOfOperands);
  return m_operands[i];
}

}
