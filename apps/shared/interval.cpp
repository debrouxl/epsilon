#include "interval.h"
#include <assert.h>

namespace Shared {

int Interval::numberOfElements() {
  computeElements();
  return m_numberOfElements;
}

void Interval::deleteElementAtIndex(int index) {
  m_numberOfElements--;
  for (int k = index; k < m_numberOfElements; k++) {
    m_intervalBuffer[k] = m_intervalBuffer[k+1];
  }
  m_intervalBuffer[m_numberOfElements] = 0.0;
}

double Interval::element(int i) {
  assert(i >= 0 && i < numberOfElements());
  computeElements();
  return m_intervalBuffer[i];
}

void Interval::setStart(double f) {
  m_start = f;
  m_needCompute = true;
}

void Interval::setEnd(double f) {
  m_end = f;
  m_needCompute = true;
}

void Interval::setStep(double f) {
  m_step = f;
  m_needCompute = true;
}

void Interval::setElement(int i, double f) {
  assert(i <= numberOfElements() && i < k_maxNumberOfElements);
  computeElements();
  m_intervalBuffer[i] = f;
  if (i == numberOfElements()) {
    m_numberOfElements++;
  }
}

void Interval::computeElements() {
  if (!m_needCompute) {
    return;
  }
  if ( m_start > m_end) {
    m_numberOfElements = 0;
  } else {
    m_numberOfElements = m_step > 0 ? 1 + (m_end - m_start)/m_step : k_maxNumberOfElements;
    m_numberOfElements = m_numberOfElements > k_maxNumberOfElements || m_numberOfElements < 0 ? k_maxNumberOfElements : m_numberOfElements;
  }
  for (int i = 0; i < m_numberOfElements; i += 1) {
    m_intervalBuffer[i] = m_start + i * m_step;
  }
  m_needCompute = false;
}

}
