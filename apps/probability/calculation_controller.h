#ifndef PROBABILITY_CALCULATION_CONTROLLER_H
#define PROBABILITY_CALCULATION_CONTROLLER_H

#include <escher.h>
#include "law/law.h"
#include "law_curve_view.h"
#include "image_table_view.h"
#include "calculation/calculation.h"
#include "../shared/text_field_delegate.h"

namespace Probability {

class CalculationController final : public ViewController, public Shared::TextFieldDelegate {
public:
  CalculationController(Responder * parentResponder, Law * law, Calculation * calculation);
  View * view() override {
    return &m_contentView;
  }
  const char * title() override {
    return m_titleBuffer;
  }
  void reload();
  void setCalculationAccordingToIndex(int index, bool forceReinitialisation = false);
  bool handleEvent(Ion::Events::Event event) override;
  void viewWillAppear() override;
  void didBecomeFirstResponder() override;
  void selectSubview(int subviewIndex);
  bool textFieldShouldFinishEditing(TextField * textField, Ion::Events::Event event) override;
  bool textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) override;
  bool textFieldDidReceiveEvent(TextField * textField, Ion::Events::Event event) override;
private:
  void updateTitle();
  Shared::TextFieldDelegateApp * textFieldDelegateApp() override;
  Calculation * m_calculation;
  class ContentView final : public View {
  public:
    ContentView(Responder * parentResponder, CalculationController * calculationController, Calculation * Calculation, Law * law);
    void setCalculation(Calculation * calculation, int index);
    void layoutSubviews() override;
    void drawRect(KDContext * ctx, KDRect rect) const override;
    LawCurveView * lawCurveView() {
      return &m_lawCurveView;
    }
    ImageTableView * imageTableView() {
      return &m_imageTableView;
    }
    EditableTextCell * calculationCellAtIndex(int index) {
      return &m_calculationCell[index];
    }
    void willDisplayEditableCellAtIndex(int index);
    constexpr static int k_maxNumberOfEditableFields = 3;
  private:
    constexpr static KDCoordinate k_largeTextFieldWidth = 60;
    constexpr static KDCoordinate k_textFieldWidth = 50;
    constexpr static KDCoordinate k_textWidthMargin = 5;
    constexpr static KDCoordinate k_titleHeightMargin = 5;
    int numberOfSubviews() const override;
    View * subviewAtIndex(int index) override;
    MessageTextView m_titleView;
    LawCurveView m_lawCurveView;
    ImageTableView m_imageTableView;
    MessageTextView m_text[k_maxNumberOfEditableFields];
    char m_draftTextBuffer[TextField::maxBufferSize()];
    EditableTextCell m_calculationCell[k_maxNumberOfEditableFields];
    Calculation * m_calculation;
  };
  ContentView m_contentView;
  Law * m_law;
  int m_highlightedSubviewIndex;
  constexpr static int k_maxNumberOfTitleCharacters = 30;
  char m_titleBuffer[k_maxNumberOfTitleCharacters];
};

}

#endif
