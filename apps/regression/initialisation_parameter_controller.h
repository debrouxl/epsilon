#ifndef REGRESSION_INITIALISATION_PARAMETER_CONTROLLER_H
#define REGRESSION_INITIALISATION_PARAMETER_CONTROLLER_H

#include <escher.h>
#include "store.h"
#include "../i18n.h"

namespace Regression {

class InitialisationParameterController final : public ViewController, public SimpleListViewDataSource, public SelectableTableViewDataSource {
public:
  InitialisationParameterController(Responder * parentResponder, Store * store) :
    ViewController(parentResponder),
    m_selectableTableView(this),
    m_store(store) {}
  View * view() override {
    return &m_selectableTableView;
  }
  const char * title() override {
    return I18n::translate(I18n::Message::Initialization);
  }
  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  int numberOfRows() override;
  KDCoordinate cellHeight() override;
  HighlightCell * reusableCell(int index) override;
  int reusableCellCount() override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
private:
  constexpr static int k_totalNumberOfCells = 3;
  MessageTableCell m_cells[k_totalNumberOfCells];
  SelectableTableView m_selectableTableView;
  Store * m_store;
};

}

#endif
