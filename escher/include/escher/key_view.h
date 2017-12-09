#ifndef ESCHER_KEY_VIEW_H
#define ESCHER_KEY_VIEW_H

#include <escher/view.h>

class KeyView final : public View {
public:
  enum class Type {
    Up,
    Down,
    Left,
    Right,
    Plus,
    Minus
  };
  KeyView(Type type = Type::Up) : View(), m_type(type) {}
  void setType(Type type);
  void drawRect(KDContext * ctx, KDRect rect) const override;
  KDSize minimalSizeForOptimalDisplay() const override;
  constexpr static KDCoordinate k_keySize = 8;
private:
  const uint8_t * mask() const;
  Type m_type;
};

#endif

