#ifndef BUMBER_H
#define BUMBER_H

#include "GamePolygon.h"

//BumBer?  Ugh...
class Bumber
{
   public:
      Bumber(std::size_t pointCount = 0, const vector<sf::Vector2f> &vertices = vector<sf::Vector2f>());
      virtual ~Bumber();
      GamePolygon getShape();
      GamePolygon getOutline();
      void setPosition(const sf::Vector2f &pos);
      void setPosition(float x, float y);
      void startAnimation();
      void updateAnimation();

   protected:
   private:
      bool animate;
      sf::Clock clock;
      sf::Time dt;
      GamePolygon shape;
      GamePolygon outline;
};

#endif // BUMBER_H
