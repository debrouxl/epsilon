#ifndef POINCARE_GRID_LAYOUT_H
#define POINCARE_GRID_LAYOUT_H

#include <poincare/expression.h>
#include <poincare/expression_layout.h>

namespace Poincare {

class GridLayout final : public ExpressionLayout {
public:
  GridLayout(ExpressionLayout ** entryLayouts, int numberOfRows, int numberOfColumns, bool borrow) :
  ExpressionLayout(),
  m_entryLayouts(borrow ? entryLayouts : new ExpressionLayout *[numberOfColumns*numberOfRows]),
  m_numberOfRows(numberOfRows),
  m_numberOfColumns(numberOfColumns)
{
  for (int i = 0; i < m_numberOfRows*m_numberOfColumns; i++) {
    m_entryLayouts[i] = entryLayouts[i];
    m_entryLayouts[i]->setParent(this);
  }
  m_baseline = height()/2 + KDText::charSize().height()/2;
}

  ~GridLayout();
  GridLayout(const GridLayout& other) = delete;
  GridLayout(GridLayout&& other) = delete;
  GridLayout& operator=(const GridLayout& other) = delete;
  GridLayout& operator=(GridLayout&& other) = delete;
protected:
  void render(KDContext * ctx, KDPoint p, KDColor expressionColor, KDColor backgroundColor) override;
  KDSize computeSize() override;
  ExpressionLayout * child(uint16_t index) override;
  KDPoint positionOfChild(ExpressionLayout * child) override;
private:
  constexpr static KDCoordinate k_gridEntryMargin = 6;
  KDCoordinate rowBaseline(int i);
  KDCoordinate rowHeight(int i);
  KDCoordinate height();
  KDCoordinate columnWidth(int j);
  KDCoordinate width();
  ExpressionLayout ** m_entryLayouts;
  int m_numberOfRows;
  int m_numberOfColumns;
};

}

#endif
