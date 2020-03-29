#ifndef SHARED_FUNCTION_H
#define SHARED_FUNCTION_H

#include <poincare/function.h>
#include <poincare/symbol.h>
#include <escher/i18n.h>
#include "expression_model_handle.h"

#if __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace Shared {

class Function : public ExpressionModelHandle {
public:
  enum class NameNotCompliantError {
    None = 0,
    CharacterNotAllowed,
    NameCannotStartWithNumber,
    ReservedName
  };
  static NameNotCompliantError BaseNameCompliant(const char * baseName);

  /* Possible arguments: n, x, t, θ
   * The CodePoint θ is two char long. */
  constexpr static int k_parenthesedArgumentCodePointLength = 3;
  constexpr static int k_parenthesedThetaArgumentByteLength = 4;
  constexpr static int k_parenthesedXNTArgumentByteLength = 3;
  constexpr static int k_maxNameWithArgumentSize = Poincare::SymbolAbstract::k_maxNameSize + k_parenthesedThetaArgumentByteLength; /* Function name and null-terminating char + "(θ)" */;

  // Constructors
  Function(Ion::Storage::Record record) : ExpressionModelHandle(record){}

  // Properties
  bool isActive() const;
  KDColor color() const;
  void setActive(bool active);

  // Definition Interval
  virtual bool shouldClipTRangeToXRange() const { return true; } // Returns true if the function will not be displayed if t is outside x range.
  virtual float tMin() const { return NAN; }
  virtual float tMax() const { return NAN; }
  virtual float rangeStep() const { return NAN; }

  // Name
  int name(char * buffer, size_t bufferSize);
  int nameWithArgument(char * buffer, size_t bufferSize);
  virtual int printValue(double cursorT, double cursorX, double cursorY, char * buffer, int bufferSize, int precision, Poincare::Context * context);
  virtual I18n::Message parameterMessageName() const = 0;

  // Evaluation
#if POINCARE_FLOAT_SUPPORT
  virtual Poincare::Coordinate2D<float> evaluateXYAtParameter(float t, Poincare::Context * context) const = 0;
#endif
  virtual Poincare::Coordinate2D<double> evaluateXYAtParameter(double t, Poincare::Context * context) const = 0;
  virtual Poincare::Expression sumBetweenBounds(double start, double end, Poincare::Context * context) const = 0;
protected:
  /* RecordDataBuffer is the layout of the data buffer of Record
   * representing a Function. We want to avoid padding which would:
   * - increase the size of the storage file
   * - introduce junk memory zone which are then crc-ed in Storage::checksum
   *   creating dependency on uninitialized values. */
  class RecordDataBuffer {
  public:
    RecordDataBuffer(KDColor color) : m_color(color), m_active(true) {}
    KDColor color() const {
      return KDColor::RGB16(m_color);
    }
    bool isActive() const { return m_active; }
    void setActive(bool active) { m_active = active; }
  private:
#if __EMSCRIPTEN__
    /* Record::value() is a pointer to an address inside
     * Ion::Storage::sharedStorage(), and it might be unaligned. However, for
     * emscripten memory representation, loads and stores must be aligned;
     * performing a normal load or store on an unaligned address can fail
     * silently. We thus use 'emscripten_align1_short' type, the unaligned
     * version of uint16_t type to avoid producing an alignment error on the
     * emscripten platform. */
    static_assert(sizeof(emscripten_align1_short) == sizeof(uint16_t), "emscripten_align1_short should have the same size as uint16_t");
    emscripten_align1_short m_color __attribute__((packed));
#else
    uint16_t m_color __attribute__((packed));
#endif
    bool m_active;
  };
private:
  RecordDataBuffer * recordData() const;
};

}

#endif
