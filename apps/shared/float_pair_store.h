#ifndef SHARED_FLOAT_PAIR_STORE_H
#define SHARED_FLOAT_PAIR_STORE_H

#include <stdint.h>

namespace Shared {

class FloatPairStore {
public:
  FloatPairStore() : m_numberOfPairs(0), m_data{} {}
  // Delete the implicit copy constructor: the object is heavy
  FloatPairStore(const FloatPairStore&) = delete;
  double get(int i, int j);
  void set(double f, int i, int j);
  int numberOfPairs() {
    return m_numberOfPairs;
  }
  void deletePairAtIndex(int j);
  void deleteAllPairs();
  void resetColumn(int i);
  double sumOfColumn(int i);
  double range();
  double maxValueOfColumn(int i);
  double minValueOfColumn(int i);
  double columnProductSum();
  uint32_t storeChecksum();
  constexpr static int k_maxNumberOfPairs = 100;
protected:
  virtual double defaultValue(int i, int j);
  int m_numberOfPairs;
  double m_data[2][k_maxNumberOfPairs];
};

}

#endif
