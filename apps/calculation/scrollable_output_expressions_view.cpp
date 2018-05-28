#include "scrollable_output_expressions_view.h"
#include <assert.h>
using namespace Poincare;

namespace Calculation {

ScrollableOutputExpressionsView::ScrollableOutputExpressionsView(Responder * parentResponder) :
  ScrollableView(parentResponder, &m_outputView, this),
  m_outputView(this)
{
}

void ScrollableOutputExpressionsView::didBecomeFirstResponder() {
  app()->setFirstResponder(&m_outputView);
}

KDSize ScrollableOutputExpressionsView::minimalSizeForOptimalDisplay() const {
  return m_outputView.minimalSizeForOptimalDisplay();
}

}
