#ifndef SHARED_MEMOIZED_CURVE_VIEW_RANGE_H
#define SHARED_MEMOIZED_CURVE_VIEW_RANGE_H

#include "curve_view_range.h"

namespace Shared {

class MemoizedCurveViewRange : public CurveViewRange {
public:
  MemoizedCurveViewRange();
  //CurveViewWindow
  float xMin() override {
    return m_xMin;
  }
  float xMax() override {
    return m_xMax;
  }
  float yMin() override {
    return m_yMin;
  }
  float yMax() override {
    return m_yMax;
  }
  float xGridUnit() override {
    return m_xGridUnit;
  }
  float yGridUnit() override {
    return m_yGridUnit;
  }
  virtual void setXMin(float f);
  virtual void setXMax(float f);
  virtual void setYMin(float f);
  virtual void setYMax(float f);

protected:
  // Window bounds of the data
  float m_xMin;
  float m_xMax;
  float m_yMin;
  float m_yMax;
  float m_xGridUnit;
  float m_yGridUnit;
};

}

#endif
