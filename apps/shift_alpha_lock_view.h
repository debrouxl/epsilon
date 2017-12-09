#ifndef APPS_SHIFT_ALPHA_LOCK_VIEW_H
#define APPS_SHIFT_ALPHA_LOCK_VIEW_H

#include <escher.h>
#include "lock_view.h"
#include "i18n.h"

class ShiftAlphaLockView final : public View {
public:
  ShiftAlphaLockView() :
    View(),
    m_shiftAlphaView(KDText::FontSize::Small, I18n::Message::Default, 1.0f, 0.5f, KDColorWhite, Palette::YellowDark),
    m_status(Ion::Events::ShiftAlphaStatus::Default) {}
  void drawRect(KDContext * ctx, KDRect rect) const override;
  bool setStatus(Ion::Events::ShiftAlphaStatus status);
  KDSize minimalSizeForOptimalDisplay() const override;
private:
  constexpr static KDCoordinate k_lockRightMargin = 5;
  int numberOfSubviews() const override;
  void layoutSubviews() override;
  View * subviewAtIndex(int index) override;
  LockView m_lockView;
  MessageTextView m_shiftAlphaView;
  Ion::Events::ShiftAlphaStatus m_status;
};

#endif
