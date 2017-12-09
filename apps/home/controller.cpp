#include "controller.h"
#include "../apps_container.h"
extern "C" {
#include <assert.h>
}

namespace Home {

void Controller::ContentView::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(bounds(), KDColorWhite);
}

void Controller::ContentView::reloadBottomRightCorner(SimpleTableViewDataSource * dataSource) {
  /* We mark the bottom right corner (where an empty space can be) as dirty. */
  markRectAsDirty(KDRect(dataSource->cellWidth()*2, dataSource->cellHeight(), dataSource->cellWidth(), dataSource->cellHeight()));
}

int Controller::ContentView::numberOfSubviews() const {
  return 1;
}

View * Controller::ContentView::subviewAtIndex(int index) {
  assert(index == 0);
  return &m_selectableTableView;
}

void Controller::ContentView::layoutSubviews() {
  m_selectableTableView.setFrame(bounds());
}

bool Controller::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK || event == Ion::Events::EXE) {
    m_container->switchTo(m_container->appSnapshotAtIndex(m_selectionDataSource->selectedColumn()*k_numberOfRows+m_selectionDataSource->selectedRow()+1));
    return true;
  }

  if (event == Ion::Events::Home || event == Ion::Events::Back) {
    return m_view.selectableTableView()->selectCellAtLocation(0,0);
  } 

  return false;
}

void Controller::didBecomeFirstResponder() {
  if (m_selectionDataSource->selectedRow() == -1) {
    m_selectionDataSource->selectCellAtLocation(0, 0);
  } else {
    m_selectionDataSource->selectCellAtLocation(m_selectionDataSource->selectedColumn(), m_selectionDataSource->selectedRow());
  }
  app()->setFirstResponder(m_view.selectableTableView());
}

void Controller::viewWillAppear() {
}

int Controller::numberOfRows() {
  return k_numberOfRows;
}

int Controller::numberOfColumns() {
  return ((numberOfIcons()-1)/k_numberOfRows)+1;
}

KDCoordinate Controller::cellHeight() {
  return k_cellHeight;
}

KDCoordinate Controller::cellWidth() {
  return k_cellWidth;
}

int Controller::reusableCellCount() {
  return k_maxNumberOfCells;
}

void Controller::willDisplayCellAtLocation(HighlightCell * cell, int i, int j) {
  AppCell * appCell = (AppCell *)cell;
  int appIndex = (i*k_numberOfRows+j)+1;
  if (appIndex >= m_container->numberOfApps()) {
    appCell->setVisible(false);
  } else {
    appCell->setVisible(true);
    ::App::Descriptor * descriptor = m_container->appSnapshotAtIndex(appIndex)->descriptor();
    appCell->setAppDescriptor(descriptor);
  }
}

int Controller::numberOfIcons() {
  assert(m_container->numberOfApps() > 0);
  return m_container->numberOfApps() - 1;
}

void Controller::tableViewDidChangeSelection(SelectableTableView * t, int previousSelectedCellX, int previousSelectedCellY) {
  /* If the number of apps (including home) is odd, when we display the
   * rightest icon, the icon below is empty. As no icon is thus redrawn on the
   * previous one, the cell is not cleaned. We need to redraw a white rect on
   * the cell to hide the dirtyness below. Ideally, we would have redrawn all
   * the background in white and then redraw visible cells. However, the
   * redrawing takes time and is visible at scrolling. Here, we avoid the
   * background complete redrawing but the code is a bit
   * clumsy. */
  if (m_container->numberOfApps()%2 == 0 && t->selectedColumn() == numberOfColumns() -1) {
    m_view.reloadBottomRightCorner(this);
  }
  /* To prevent the selectable table view to select cells that are unvisible,
   * we reselect the previous selected cell as soon as the selected cell is
   * unvisible. This trick does not create an endless loop as we ensure not to
   * stay on a unvisible cell and to initialize the first cell on a visible one
   * (so the previous one is always visible). */
  int appIndex = (t->selectedColumn()*k_numberOfRows+t->selectedRow())+1;
  if (appIndex >= m_container->numberOfApps()) {
    t->selectCellAtLocation(previousSelectedCellX, previousSelectedCellY);
  }
}

}
