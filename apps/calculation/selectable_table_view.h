#ifndef CALCULATION_SELECTABLE_TABLE_VIEW_H
#define CALCULATION_SELECTABLE_TABLE_VIEW_H

#include <escher.h>
#include "history_view_cell.h"
namespace Calculation {

class CalculationSelectableTableView final : public ::SelectableTableView {
public:
  CalculationSelectableTableView(Responder * parentResponder, TableViewDataSource * dataSource,
    SelectableTableViewDataSource * selectionDataSource, SelectableTableViewDelegate * delegate = nullptr);
  void scrollToCell(int i, int j) override;
  void scrollToSubviewOfTypeOfCellAtLocation(HistoryViewCell::SubviewType subviewType, int i, int j);
};

}

#endif
