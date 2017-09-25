#include <escher/highlight_cell.h>

void HighlightCell::setHighlighted(bool highlight) {
  m_highlighted = highlight;
  reloadCell();
}

void HighlightCell::reloadCell() {
  markRectAsDirty(bounds());
}
