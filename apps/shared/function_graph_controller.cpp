#include "function_graph_controller.h"
#include "text_field_delegate_app.h"
#include <assert.h>
#include <cmath>
#include <float.h>

using namespace Poincare;

namespace Shared {

FunctionGraphController::FunctionGraphController(Responder * parentResponder, ButtonRowController * header, InteractiveCurveViewRange * interactiveRange, CurveView * curveView, CurveViewCursor * cursor, uint32_t * modelVersion, uint32_t * rangeVersion, Expression::AngleUnit * angleUnitVersion) :
  InteractiveCurveViewController(parentResponder, header, interactiveRange, curveView, cursor, modelVersion, rangeVersion),
  m_indexFunctionSelectedByCursor(0),
  m_initialisationParameterController(this, interactiveRange),
  m_angleUnitVersion(angleUnitVersion)
{
}

bool FunctionGraphController::isEmpty() const {
  if (functionStore()->numberOfActiveFunctions() == 0) {
    return true;
  }
  return false;
}

void FunctionGraphController::viewWillAppear() {
  if (functionGraphView()->context() == nullptr) {
    TextFieldDelegateApp * myApp = (TextFieldDelegateApp *)app();
    functionGraphView()->setContext(myApp->localContext());
  }
  Expression::AngleUnit newAngleUnitVersion = Preferences::sharedPreferences()->angleUnit();
  if (*m_angleUnitVersion != newAngleUnitVersion) {
    *m_angleUnitVersion = newAngleUnitVersion;
    initCursorParameters();
  }
  InteractiveCurveViewController::viewWillAppear();
}

bool FunctionGraphController::handleEnter() {
  Function * f = functionStore()->activeFunctionAtIndex(m_indexFunctionSelectedByCursor);
  curveParameterController()->setFunction(f);
  StackViewController * stack = stackController();
  stack->push(curveParameterController());
  return true;
}

void FunctionGraphController::reloadBannerView() {
  char buffer[k_maxNumberOfCharacters+PrintFloat::bufferSizeForFloatsWithPrecision(Constant::LargeNumberOfSignificantDigits)];
  /*int numberOfChar = 0;
  const char * legend = "0=";
  int legendLength = sizeof("0=") - 1;
  strcpy(buffer, legend);
  numberOfChar += legendLength;
  numberOfChar += Complex<float>::convertFloatToText(m_cursor->x(), buffer+numberOfChar, PrintFloat::bufferSizeForFloatsWithPrecision(Constant::MediumNumberOfSignificantDigits), Constant::MediumNumberOfSignificantDigits);
  legend = "   ";
  strcpy(buffer+numberOfChar, legend);*/
  convertFloatToText(m_cursor->x(), buffer, "0=", sizeof("0=") - 1, "   ", Constant::MediumNumberOfSignificantDigits);
  buffer[0] = functionStore()->symbol();
  bannerView()->setLegendAtIndex(buffer, 0);

  /*numberOfChar = 0;
  legend = "0(x)=";
  legendLength = sizeof("0(x)=") - 1;
  strcpy(buffer, legend);
  numberOfChar += legendLength;
  numberOfChar += Complex<float>::convertFloatToText(m_cursor->y(), buffer+numberOfChar, PrintFloat::bufferSizeForFloatsWithPrecision(Constant::MediumNumberOfSignificantDigits), Constant::MediumNumberOfSignificantDigits);
  legend = "   ";
  strcpy(buffer+numberOfChar, legend);*/
  if (functionStore()->numberOfActiveFunctions() == 0) {
    return;
  }
  assert(m_indexFunctionSelectedByCursor < functionStore()->numberOfActiveFunctions());
  Function * f = functionStore()->activeFunctionAtIndex(m_indexFunctionSelectedByCursor);
  convertFloatToText(m_cursor->x(), buffer, "0(x)=", sizeof("0(x)=") - 1, "   ", Constant::MediumNumberOfSignificantDigits);
  buffer[0] = f->name()[0];
  buffer[2] = functionStore()->symbol();
  bannerView()->setLegendAtIndex(buffer, 1);
}

InteractiveCurveViewRangeDelegate::Range FunctionGraphController::computeYRange(InteractiveCurveViewRange * interactiveCurveViewRange) {
  TextFieldDelegateApp * myApp = (TextFieldDelegateApp *)app();
  float min = FLT_MAX;
  float max = -FLT_MAX;
  float xMin = interactiveCurveViewRange->xMin();
  float xMax = interactiveCurveViewRange->xMax();
  float step = (xMax - xMin)/curveView()->resolution();
  if (functionStore()->numberOfActiveFunctions() <= 0) {
    InteractiveCurveViewRangeDelegate::Range range;
    range.min = xMin;
    range.max = xMax;
    return range;
  }
  for (int i=0; i<functionStore()->numberOfActiveFunctions(); i++) {
    Function * f = functionStore()->activeFunctionAtIndex(i);
    float y = 0.0f;
    for (int i = 0; i <= curveView()->resolution(); i++) {
      float x = xMin + i*step;
      y = f->evaluateAtAbscissa(x, myApp->localContext());
      if (!std::isnan(y) && !std::isinf(y)) {
        min = min < y ? min : y;
        max = max > y ? max : y;
      }
    }
  }
  InteractiveCurveViewRangeDelegate::Range range;
  range.min = min;
  range.max = max;
  return range;
}

float FunctionGraphController::addMargin(float x, float range, bool isMin) {
  float ratio = isMin ? -k_displayBottomMarginRatio : k_displayTopMarginRatio;
  return x+ratio*range;
}

void FunctionGraphController::initRangeParameters() {
  interactiveCurveViewRange()->setDefault();
  initCursorParameters();
  m_indexFunctionSelectedByCursor = 0;
}

bool FunctionGraphController::moveCursorVertically(int direction) {
  Function * actualFunction = functionStore()->activeFunctionAtIndex(m_indexFunctionSelectedByCursor);
  TextFieldDelegateApp * myApp = (TextFieldDelegateApp *)app();
  double y = actualFunction->evaluateAtAbscissa(m_cursor->x(), myApp->localContext());
  Function * nextFunction = actualFunction;
  double nextY = direction > 0 ? DBL_MAX : -DBL_MAX;
  for (int i = 0; i < functionStore()->numberOfActiveFunctions(); i++) {
    Function * f = functionStore()->activeFunctionAtIndex(i);
    double newY = f->evaluateAtAbscissa(m_cursor->x(), myApp->localContext());
    bool isNextFunction = direction > 0 ? (newY > y && newY < nextY) : (newY < y && newY > nextY);
    if (isNextFunction) {
      m_indexFunctionSelectedByCursor = i;
      nextY = newY;
      nextFunction = f;
    }
  }
  if (nextFunction == actualFunction) {
    return false;
  }
  m_cursor->moveTo(m_cursor->x(), nextY);
  interactiveCurveViewRange()->panToMakePointVisible(m_cursor->x(), m_cursor->y(), k_cursorTopMarginRatio, k_cursorRightMarginRatio, k_cursorBottomMarginRatio, k_cursorLeftMarginRatio);
  return true;
}

bool FunctionGraphController::isCursorVisible() {
  return interactiveCurveViewRange()->isCursorVisible(k_cursorTopMarginRatio, k_cursorRightMarginRatio, k_cursorBottomMarginRatio, k_cursorLeftMarginRatio);
}

}
