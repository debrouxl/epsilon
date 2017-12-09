#ifndef ESCHER_MESSAGE_TABLE_CELL_WITH_GAUGE_H
#define ESCHER_MESSAGE_TABLE_CELL_WITH_GAUGE_H

#include <escher/message_table_cell.h>
#include <escher/gauge_view.h>

class MessageTableCellWithGauge final : public MessageTableCell {
public:
  MessageTableCellWithGauge(I18n::Message message = (I18n::Message)0, KDText::FontSize size = KDText::FontSize::Small);
  View * accessoryView() const override;
  void setHighlighted(bool highlight) override;
private:
  GaugeView m_accessoryView;
};

#endif
