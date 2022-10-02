#pragma once
#include "Nodes/Node.hpp"

template<bool (*comparator)(std::shared_ptr<Node> const &, std::shared_ptr<Node> const &)>
class SortNode : public Node{
    void onDraw([[maybe_unused]]Renderer &renderer) const override
    {

    }
    void onUpdate([[maybe_unused]] const sf::Time& delta) override
    {
        std::stable_sort(begin(children), end(children), comparator);
    }
};

using YSort = SortNode<[](std::shared_ptr<Node> const &a, std::shared_ptr<Node> const &b) -> bool {
    return  a->getLocalTranslation().y
          < b->getLocalTranslation().y;
}>;
