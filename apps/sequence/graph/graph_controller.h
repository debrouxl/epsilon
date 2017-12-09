#ifndef SEQUENCE_GRAPH_CONTROLLER_H
#define SEQUENCE_GRAPH_CONTROLLER_H

#include "graph_view.h"
#include "banner_view.h"
#include "curve_parameter_controller.h"
#include "curve_view_range.h"
#include "term_sum_controller.h"
#include "../../shared/function_graph_controller.h"
#include "../sequence_store.h"

namespace Sequence {

class GraphController final : public Shared::FunctionGraphController {
public:
  GraphController(Responder * parentResponder, SequenceStore * sequenceStore, CurveViewRange * graphRange, Shared::CurveViewCursor * cursor, uint32_t * modelVersion, uint32_t * rangeVersion, Poincare::Expression::AngleUnit * angleUnitVersion, ButtonRowController * header);
  void viewWillAppear() override;
  I18n::Message emptyMessage() override;
  TermSumController * termSumController() {
    return &m_termSumController;
  }
private:
  BannerView * bannerView() override {
    return &m_bannerView;
  }
  bool handleEnter() override;
  bool moveCursorHorizontally(int direction) override;
  void initCursorParameters() override;
  CurveViewRange * interactiveCurveViewRange() override {
    return m_graphRange;
  }
  SequenceStore * functionStore() const override {
    return m_sequenceStore;
  }
  GraphView * functionGraphView() override {
    return &m_view;
  }
  CurveParameterController * curveParameterController() override {
    return &m_curveParameterController;
  }
  BannerView m_bannerView;
  GraphView m_view;
  CurveViewRange * m_graphRange;
  CurveParameterController m_curveParameterController;
  TermSumController m_termSumController;
  SequenceStore * m_sequenceStore;
};


}

#endif
