#ifndef ESCHER_SCROLL_VIEW_DATA_SOURCE_H
#define ESCHER_SCROLL_VIEW_DATA_SOURCE_H

#include <kandinsky.h>

class ScrollViewDataSource {
public:
  ScrollViewDataSource() : m_offset(KDPointZero) {}
  KDPoint offset() const {
    return m_offset;
  }
  bool setOffset(KDPoint offset) {
  if (offset != m_offset) {
    m_offset = offset;
    return true;
  }
  return false;
}
private:
  KDPoint m_offset;
};

#endif
