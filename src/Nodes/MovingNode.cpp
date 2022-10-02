#include "MovingNode.hpp"

MovingNode::MovingNode(std::string name, float idleAnimationTime, float _speed) : animationManager(name, {{"idle", idleAnimationTime}}, "idle")
{
    speed = _speed;
    sf::Vector2u TextureSize(animationManager.getTexture().get()->getSize());
    sf::Vector2f size(TextureSize.x, TextureSize.y);
    body.setSize(size);
    body.setOrigin(size.x/2, size.y/2);
}

void MovingNode::addNewWaypoint(sf::Vector2f n)
{
    waypoints.push(n);
}

sf::Vector2f MovingNode::NewTranslateByWaypoints(const sf::Time& delta)
{
    sf::Vector2f newTranslate = getGlobalTranslation();
    float distanceToWalk = speed * delta.asSeconds();
    while(distanceToWalk > 0.0 && !waypoints.empty())
    {
        float Ydiff, Xdiff;
        int Ysign, Xsign;

        Ydiff = waypoints.front().y - getGlobalTranslation().y;
        Ysign = Ydiff > 0 ? 1 : -1;

        Xdiff = waypoints.front().x - getGlobalTranslation().x;
        Xsign = Xdiff > 0 ? 1 : -1;

        float distanceToNextWaypoint = sqrt(pow(Xdiff, 2) + pow(Ydiff, 2));

        if(distanceToNextWaypoint <= distanceToWalk)
        {
            distanceToWalk -= distanceToNextWaypoint;
            newTranslate = {waypoints.front().x, waypoints.front().y};
            waypoints.pop();
            continue;
        }

        float newDistanceToNextWaypoint = distanceToNextWaypoint - distanceToWalk;
        if(Ydiff != 0.0)
        {
            float scaleXtoY = abs(Xdiff/Ydiff);
            float k = sqrt(pow(newDistanceToNextWaypoint,2) / (pow(scaleXtoY, 2) + 1));
            newTranslate =  {waypoints.front().x - Xsign*k * scaleXtoY, waypoints.front().y - Ysign*k};
        }
        else
        {
            newTranslate = {waypoints.front().x - Xsign*newDistanceToNextWaypoint, waypoints.front().y};
        }
        
        distanceToWalk = 0.0;
    }
    return newTranslate;
}

void MovingNode::onUpdate(const sf::Time& delta)
{
    setTranslation(NewTranslateByWaypoints(delta));

    animationManager.update(delta, false);
    body.setTexture(animationManager.getTexture().get());
    body.setTextureRect(animationManager.getIntRect());
}

void MovingNode::onDraw(Renderer &renderer) const
{
    sf::RenderStates state;
    state.transform = global_transform.getTransform();
    renderer.draw_object_on_layer(body, 1, state);
}
