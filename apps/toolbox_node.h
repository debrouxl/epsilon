#ifndef APPS_TOOLBOX_NODE_H
#define APPS_TOOLBOX_NODE_H

#include "node.h"

class ToolboxNode final : public Node {
public:
  constexpr ToolboxNode(I18n::Message label = I18n::Message::Default, I18n::Message text = I18n::Message::Default, I18n::Message insertedText = I18n::Message::Default, const ToolboxNode * children = nullptr, int numberOfChildren = 0) :
    Node(label, numberOfChildren),
    m_children(children),
    m_text(text),
    m_insertedText(insertedText)
  {
  }
  const Node * children(int index) const override {
    return &m_children[index];
  }
  I18n::Message text() const {
    return m_text;
  }
  I18n::Message insertedText() const {
    return m_insertedText;
  }
private:
  const ToolboxNode * m_children;
  I18n::Message m_text;
  I18n::Message m_insertedText;
};

#endif

