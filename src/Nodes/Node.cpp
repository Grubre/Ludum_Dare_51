#include <memory>
#include <vector>
#include <algorithm>
#include "Nodes/Node.hpp" 

using StrongNode = std::shared_ptr<Node>;
using WeakNode = std::weak_ptr<Node>;

void Node::change_parent(StrongNode new_parent) {
    if(auto locked_parent = parent.lock()){
        locked_parent->remove_child(shared_from_this());
    }
    new_parent->children.push_back(shared_from_this());
    parent = new_parent;
}

void Node::remove_child(StrongNode child) {
    children.erase(std::find(children.begin(),children.end(),child));
}

void Node::draw(Renderer &renderer) const {
    onDraw(renderer);

    for(auto child : children) {
        child->draw(renderer);
    }
}

void Node::update(const sf::Time& delta) {
    onUpdate(delta);

    for(auto child : children) {
        child->update(delta);
    }
}

void Node::update_transform() {
    if(auto locked_parent = parent.lock()) {
        global_transform = combineTransforms(locked_parent->global_transform, local_transform);
    }
    else {
        global_transform = local_transform;
    }

    for(auto child : children) {
        child->update_transform();
    }
}

void Node::translate(sf::Vector2f vec) {
    local_transform.move(vec);
    update_transform();
}
void Node::setTranslation(sf::Vector2f vec) {
    local_transform.setPosition(vec);
    update_transform();
}
void Node::setGlobalTranslation(sf::Vector2f vec) {
    setTranslation((local_transform.getTransform().getInverse() * global_transform.getTransform()).getInverse() * vec); 
}

void Node::rotate(float deegres) {
    local_transform.rotate(deegres);
    update_transform();
}
void Node::setRotation(float deegres) {
    local_transform.setRotation(deegres);
    update_transform();
}

void Node::scale(sf::Vector2f vec) {
    local_transform.scale(vec);
    update_transform();
}
void Node::setScale(sf::Vector2f vec) {
    local_transform.setScale(vec);
    update_transform();
}
