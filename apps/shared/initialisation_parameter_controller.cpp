#include "initialisation_parameter_controller.h"
#include <assert.h>
#include <math.h>

namespace Shared {

void InitialisationParameterController::didBecomeFirstResponder() {
  m_selectableTableView.selectCellAtLocation(0, 0);
  app()->setFirstResponder(&m_selectableTableView);
}

bool InitialisationParameterController::handleEvent(Ion::Events::Event event) {
if (event == Ion::Events::OK || event == Ion::Events::EXE) {
    static const RangeMethodPointer rangeMethods[k_totalNumberOfCells] = {&InteractiveCurveViewRange::setTrigonometric,
    &InteractiveCurveViewRange::roundAbscissa, &InteractiveCurveViewRange::normalize, &InteractiveCurveViewRange::setDefault};
    (m_graphRange->*rangeMethods[selectedRow()])();
    StackViewController * stack = (StackViewController *)parentResponder();
    stack->pop();
    return true;
  }
  return false;
}

int InitialisationParameterController::numberOfRows() {
  return k_totalNumberOfCells;
};


HighlightCell * InitialisationParameterController::reusableCell(int index) {
  assert(index >= 0);
  assert(index < k_totalNumberOfCells);
  return &m_cells[index];
}

int InitialisationParameterController::reusableCellCount() {
  return k_totalNumberOfCells;
}

KDCoordinate InitialisationParameterController::cellHeight() {
  return Metric::ParameterCellHeight;
}

void InitialisationParameterController::willDisplayCellForIndex(HighlightCell * cell, int index) {
  MessageTableCell * myCell = (MessageTableCell *)cell;
  static const I18n::Message titles[4] = {I18n::Message::Trigonometric, I18n::Message::RoundAbscissa, I18n::Message::Orthonormal, I18n::Message::DefaultSetting};
  myCell->setMessage(titles[index]);
}

}
