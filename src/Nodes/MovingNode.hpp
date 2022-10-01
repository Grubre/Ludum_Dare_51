#pragma once
#include "Node.hpp"
#include "Animation/All.hpp"
#include <queue>
#include <math.h>

class MovingNode : public Node
{
public:
    MovingNode(std::string name, float idleAnimationTime, float _speed) : animationManager(name, {{"idle", idleAnimationTime}}, "idle")
    {
        speed = _speed;
        sf::Vector2u TextureSize(animationManager.getTexture().get()->getSize());
        sf::Vector2f size(TextureSize.x, TextureSize.y);
        body.setSize(size);
        body.setOrigin(size.x/2, size.y/2);
    }

    void setScale(float scale)
    {
        body.setScale(scale, scale);
    }

    void addNewWaypoint(sf::Vector2f n)
    {
        waypoints.push(n);
    }

protected:
    AnimationManager animationManager;
    sf::RectangleShape body;
    float speed;
    sf::Vector2f NewPositionByWaypoints(const sf::Time& delta)
    {
        sf::Vector2f newPositon = body.getPosition();
        float distanceToWalk = speed * delta.asSeconds();
        while(distanceToWalk > 0.0 && !waypoints.empty())
        {
            float Ydiff, Xdiff;
            int Ysign, Xsign;

            Ydiff = waypoints.front().y - body.getPosition().y;
            Ysign = Ydiff > 0 ? 1 : -1;

            Xdiff = waypoints.front().x - body.getPosition().x;
            Xsign = Xdiff > 0 ? 1 : -1;

            float distanceToNextWaypoint = sqrt(pow(Xdiff, 2) + pow(Ydiff, 2));

            if(distanceToNextWaypoint <= distanceToWalk)
            {
                distanceToWalk -= distanceToNextWaypoint;
                newPositon = {waypoints.front().x, waypoints.front().y};
                waypoints.pop();
                continue;
            }

            float newDistanceToNextWaypoint = distanceToNextWaypoint - distanceToWalk;
            if(Ydiff != 0.0)
            {
                float scaleXtoY = abs(Xdiff/Ydiff);
                float k = sqrt(pow(newDistanceToNextWaypoint,2) / (pow(scaleXtoY, 2) + 1));
                newPositon =  {waypoints.front().x - Xsign*k * scaleXtoY, waypoints.front().y - Ysign*k};
            }
            else
            {
                newPositon = {waypoints.front().x - Xsign*newDistanceToNextWaypoint, waypoints.front().y};
            }
            
            distanceToWalk = 0.0;
        }
        return newPositon;
    }

private:
    std::queue<sf::Vector2f> waypoints;

    void onUpdate(const sf::Time& delta) override
    {
        body.setPosition(NewPositionByWaypoints(delta));

        animationManager.update(delta, false);
        body.setTexture(animationManager.getTexture().get());
        body.setTextureRect(animationManager.getIntRect());
    }

    void onDraw(Renderer &renderer) const override 
    {
        renderer.draw_object_on_layer(body, 1);
    }
};
