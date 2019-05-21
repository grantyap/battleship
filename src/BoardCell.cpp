#include "BoardCell.h"

BoardCell::BoardCell(Scene::Context& context) : Button("", context.font), mContext(context) {}

BoardCell::BoardCell(const BoardCell& bc) : Button("", bc.mContext.font), mContext(bc.mContext) {}

void BoardCell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Button::draw(target, states);
}