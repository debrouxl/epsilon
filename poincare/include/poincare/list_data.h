#ifndef POINCARE_LIST_DATA_H
#define POINCARE_LIST_DATA_H

#include <poincare/expression.h>

namespace Poincare {

class ListData final {
public:
  ListData(Expression * operand);
  ~ListData();
  ListData(const ListData& other) = delete;
  ListData(ListData&& other) = delete;
  ListData& operator=(const ListData& other) = delete;
  ListData& operator=(ListData&& other) = delete;
  int numberOfOperands() const {
    return m_numberOfOperands;
  }
  Expression ** operands() const {
    return m_operands;
  }
  const Expression * operand(int i) const;
  void pushExpression(Expression * operand);
private:
  int m_numberOfOperands;
  Expression ** m_operands;
};

}

#endif
