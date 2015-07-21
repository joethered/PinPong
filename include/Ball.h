#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include "GamePolygon.h"



class Ball : public sf::CircleShape
{
   public:
      virtual ~Ball();
      CollisionResult checkCollision(const GamePolygon &poly);
      CollisionResult checkCollision(Ball &otherBall);
      sf::Vector2f getVelocity();
      void setVelocity(const sf::Vector2f &vel);
      void setVelocity(const sf::Vector2f &dir, float speed);
      void setVelocity(float angle, float speed);
      void setOwner(int o);
      int getOwner();
   protected:
   private:
      int owner;
      bool collidable;
      sf::Vector2f velocity;
};

#endif // BALL_H
