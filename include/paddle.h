#ifndef PADDLE_H
#define PADDLE_H
#include "GamePolygon.h"
#include <SFML/Graphics.hpp>


class Paddle
{
   public:
      Paddle();
      virtual ~Paddle();
      GamePolygon getMainShape();

      sf::Vector2f getPosition();
      void setColor(sf::Color color);
      void move(const sf::Vector2f &offset);
      void move(float x, float y);
      void setPosition(const sf::Vector2f &pos);
      void setPosition(float x, float y);
      sf::Vector2f getPos();
      void setRotation(float theta);
      int getRotLife();
      void setRotLife(int life);
      bool isRotating();
      void setRotating(bool r);

      bool rot;


      sf::CircleShape pivot;
   protected:
   private:
      GamePolygon mainShape;



};

#endif // PADDLE_H
