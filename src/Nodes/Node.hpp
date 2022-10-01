#pragma once
#include "Standard/event.hpp"
#include "Standard/math.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>
#include "Renderer/Renderer.hpp"

class Node;

template<class T, typename... Us>
concept DerivedFromNode =
  std::derived_from<T, Node> && std::constructible_from<T, Us...>;

class Node : public std::enable_shared_from_this<Node>
{
  public:
    using StrongNode = std::shared_ptr<Node>;
    using WeakNode = std::weak_ptr<Node>;

  private:
    std::vector<StrongNode> children;
    WeakNode parent;

  protected:
    unsigned int render_layer_id = 1;
    sf::Transformable local_transform;
    sf::Transformable global_transform;
    sf::Color color_id;
    virtual void onDraw(Renderer &renderer) const {}
    virtual void onUpdate([[maybe_unused]] const sf::Time& delta) {}

  public:
    // Konstruktor musi być publiczny, żeby działała funkcja 'create', ale
    // lepiej z niego nie korzystać
    Node() = default;
    // UPDATE FUNCTIONS
    void draw(Renderer &renderer) const;
    void update(const sf::Time& delta);
    void update_transform();
    // MANAGING CHILDREN / PARENTS
    void change_parent(StrongNode new_parent);
    void remove_child(StrongNode child);

    // FACTORY PATTERN
    template<class T, typename... Us>
    requires DerivedFromNode<T, Us...>
    static std::shared_ptr<T> create(StrongNode parent, Us... /*values*/);
    template<class T, typename... Us>
    requires DerivedFromNode<T, Us...>
    static std::shared_ptr<T> create(Us... /*values*/);

    // GETTERS AND SETTERS
    void setActive(bool _active);
    bool isActive();

    void setVisible(bool _visible);
    bool isVisible();

    // Transforms

    // void translate(float x, float y);
    void translate(sf::Vector2f vec);
    // void setTranslation(float x, float y);
    void setTranslation(sf::Vector2f vec);
    void rotate(float deegres);
    void setRotation(float deegres);
    // void scale(float x, float y);
    void scale(sf::Vector2f vec);
    // void setScale(float x, float y);
    void setScale(sf::Vector2f vec);

    sf::Vector2f getGlobalTranslation()
    {
      return global_transform.getPosition();
    }
    float getGlobalRotation() { return global_transform.getRotation(); }
    sf::Vector2f getGlobalScale() { return global_transform.getScale(); }
    sf::Vector2f getLocalTranslation() { return local_transform.getPosition(); }
    float getLocalRotation() { return local_transform.getRotation(); }
    sf::Vector2f getLocalScale() { return local_transform.getScale(); }
};

template<class T, typename... Us>
requires DerivedFromNode<T, Us...> std::shared_ptr<T>
Node::create(Us... values)
{
    std::shared_ptr<T> new_node = std::shared_ptr<T>(new T(values...));

    return new_node;
}

template<class T, typename... Us>
requires DerivedFromNode<T, Us...> std::shared_ptr<T>
Node::create(StrongNode parent, Us... values)
{
    std::shared_ptr<T> new_node = create<T>(values...);

    parent->children.push_back(new_node);
    new_node->parent = parent;

    return new_node;
}
