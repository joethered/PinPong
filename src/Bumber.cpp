#include "Bumber.h"

Bumber::Bumber(std::size_t pointCount, const vector<sf::Vector2f> &vertices)
{
   shape = GamePolygon(pointCount, vertices);
   shape.setFillColor(sf::Color(10,255,100));

   outline = GamePolygon(pointCount, vertices);
   outline.setScale(1.1,1.1);
   outline.setFillColor(sf::Color(0,0,0));
   outline.setOutlineColor(sf::Color(10,255,100));
   outline.setOutlineThickness(2);

}

Bumber::~Bumber()
{
   //dtor
}


GamePolygon Bumber::getShape(){
   return shape;
}

GamePolygon Bumber::getOutline(){
   return outline;
}

void Bumber::setPosition(const sf::Vector2f &pos){
   shape.setPosition(pos);
   outline.setPosition(pos);
}

void Bumber::setPosition(float x, float y){
   shape.setPosition(x,y);
   outline.setPosition(x,y);
}

void Bumber::startAnimation(){
   clock.restart();
   outline.setScale(1.2,1.2);
   animate = true;
}

void Bumber::updateAnimation(){
   if (animate){
      dt = clock.getElapsedTime();
      int mils = dt.asMilliseconds();
      float scale = 1.2 - mils / 100.0;
      if (mils >= 100){
         animate = false;
         scale = 1.1;
      }
      outline.setScale(scale,scale);

   }
}
