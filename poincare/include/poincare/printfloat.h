#ifndef POINCARE_PRINTFLOAT_H
#define POINCARE_PRINTFLOAT_H

#include <poincare/integer.h>

namespace Poincare {

namespace PrintFloat {
  constexpr static int bufferSizeForFloatsWithPrecision(int numberOfSignificantDigits) {
    // The wors case is -1.234E-38
    return numberOfSignificantDigits + 7;
  }
  /* This function prints the integer i in the buffer with a '.' at the position
   * specified by the decimalMarkerPosition. It starts printing at the end of the
   * buffer and print from right to left. The integer given should be of the right
   * length to be written in bufferLength chars. If the integer is to small, the
   * empty chars on the left side are completed with '0'. If the integer is too
   * big, the printing stops when no more empty chars are available without
   * returning any warning.
   * Warning: the buffer is not null terminated but is ensured to hold
   * bufferLength chars. */
  void printBase10IntegerWithDecimalMarker(char * buffer, int bufferLength, Integer i, int decimalMarkerPosition);

  constexpr static int k_numberOfPrintedSignificantDigits = 7;
  constexpr static int k_numberOfStoredSignificantDigits = 14;

  /* We here define the buffer size to write the lengthest float possible.
   * At maximum, the number has 15 significant digits so, in the worst case it
   * has the form -1.99999999999999e-308 (15+7+1 char) (the auto mode is always
   * shorter. */
  constexpr static int k_maxFloatBufferLength = k_numberOfStoredSignificantDigits+7+1;
  /* We here define the buffer size to write the lengthest complex possible.
   * The worst case has the form
   * -1.99999999999999e-308*e^(-1.99999999999999e-308*i) (14+14+7+1 char) */
  constexpr static int k_maxComplexBufferLength = k_maxFloatBufferLength-1+k_maxFloatBufferLength-1+7+1;
}

}

#endif
