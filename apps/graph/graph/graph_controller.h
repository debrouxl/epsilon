#ifndef GRAPH_GRAPH_CONTROLLER_H
#define GRAPH_GRAPH_CONTROLLER_H

#include "graph_view.h"
#include "graph_controller_helper.h"
#include "banner_view.h"
#include "curve_parameter_controller.h"
#include "../../shared/function_graph_controller.h"
#include "../../shared/curve_view_cursor.h"
#include "../../shared/round_cursor_view.h"
#include "../../shared/interactive_curve_view_range.h"
#include "../cartesian_function_store.h"

namespace Graph {

class GraphController final : public Shared::FunctionGraphController, public GraphControllerHelper {
public:
  GraphController(Responder * parentResponder, CartesianFunctionStore * functionStore, Shared::InteractiveCurveViewRange * curveViewRange, Shared::CurveViewCursor * cursor, int * indexFunctionSelectedByCursor, uint32_t * modelVersion, uint32_t * rangeVersion, Poincare::Expression::AngleUnit * angleUnitVersion, ButtonRowController * header);
  I18n::Message emptyMessage() override;
  void viewWillAppear() override;
  bool displayDerivativeInBanner() const {
    return m_displayDerivativeInBanner;
  }
  void setDisplayDerivativeInBanner(bool displayDerivative) {
    m_displayDerivativeInBanner = displayDerivative;
  }
private:
  void selectFunctionWithCursor(int functionIndex) override;
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
  View * cursorView() override {
    return &m_cursorView;
  }
  CurveParameterController * curveParameterController() override {
    return &m_curveParameterController;
  }
  Shared::RoundCursorView m_cursorView;
  BannerView m_bannerView;
  GraphView m_view;
  Shared::InteractiveCurveViewRange * m_graphRange;
  CurveParameterController m_curveParameterController;
  CartesianFunctionStore * m_functionStore;
  bool m_displayDerivativeInBanner;
};

}

#endif
