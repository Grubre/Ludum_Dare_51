#include "Weapon.hpp"

Weapon::Weapon(std::string name, float _distance, sf::Vector2f _center) 
: distance(_distance), animationManager(name, {{"idle", 100.0}}, "idle"), center(_center)
{
    body.setTexture(animationManager.getTexture().get());
    body.setTextureRect(animationManager.getIntRect());

    sf::Vector2u TextureSize(animationManager.getTexture().get()->getSize());
    sf::Vector2f size(TextureSize.x, TextureSize.y);
    body.setSize(size);
    body.setOrigin(0, size.y/2.0);
}

sf::Vector2f Weapon::NewTranslateByAngle(float angle)
{
    sf::Vector2f newTranslate(cos(angle) * distance, sin(angle) * distance);
    return newTranslate;
}

void Weapon::onUpdate(const sf::Time& delta)
{
    sf::Vector2f newTraslation = NewTranslateByAngle(angle);
    newTraslation.x += center.x;
    newTraslation.y += center.y;
    setTranslation(newTraslation);
    setRotation(angle*180/M_PI);
}

void Weapon::onDraw(Renderer &renderer) const
{
    sf::RenderStates state;
    state.transform = global_transform.getTransform();
    renderer.draw_object_on_layer(body, 1, state);
}
