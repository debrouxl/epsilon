#ifndef GRAPH_GRAPH_CONTROLLER_H
#define GRAPH_GRAPH_CONTROLLER_H

#include "graph_view.h"
#include "banner_view.h"
#include "curve_parameter_controller.h"
#include "../../shared/function_graph_controller.h"
#include "../../shared/curve_view_cursor.h"
#include "../../shared/interactive_curve_view_range.h"
#include "../cartesian_function_store.h"

namespace Graph {

class GraphController final : public Shared::FunctionGraphController {
public:
  GraphController(Responder * parentResponder, CartesianFunctionStore * functionStore, Shared::InteractiveCurveViewRange * curveViewRange, Shared::CurveViewCursor * cursor, uint32_t * modelVersion, uint32_t * rangeVersion, Poincare::Expression::AngleUnit * angleUnitVersion, ButtonRowController * header);
  I18n::Message emptyMessage() override;
private:
  BannerView * bannerView() override {
    return &m_bannerView;
  }
  void reloadBannerView() override;
  bool moveCursorHorizontally(int direction) override;
  void initCursorParameters() override;
  Shared::InteractiveCurveViewRange * interactiveCurveViewRange() override {
    return m_graphRange;
  }
  CartesianFunctionStore * functionStore() const override {
    return m_functionStore;
  }
  GraphView * functionGraphView() override {
    return &m_view;
  }
  CurveParameterController * curveParameterController() override {
    return &m_curveParameterController;
  }
  BannerView m_bannerView;
  GraphView m_view;
  Shared::InteractiveCurveViewRange * m_graphRange;
  CurveParameterController m_curveParameterController;
  CartesianFunctionStore * m_functionStore;
};

}

#endif
