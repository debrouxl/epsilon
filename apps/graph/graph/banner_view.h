#ifndef GRAPH_BANNER_VIEW_H
#define GRAPH_BANNER_VIEW_H

#include "../../shared/banner_view.h"

namespace Graph {

class BannerView final : public Shared::BannerView {
public:
  BannerView();
  void setDisplayDerivative(bool displayDerivative) {
    m_displayDerivative = displayDerivative;
  }
  bool displayDerivative() {
    return m_displayDerivative;
  }
private:
  int numberOfSubviews() const override;
  TextView * textViewAtIndex(int i) const override;
  BufferTextView m_abscissaView;
  BufferTextView m_functionView;
  BufferTextView m_derivativeView;
  bool m_displayDerivative;
};

}

#endif
