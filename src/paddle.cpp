#include "paddle.h"

Paddle::Paddle()
{

   vector<sf::Vector2f> vertices;
   vertices.push_back(sf::Vector2f(0, 0));
   vertices.push_back(sf::Vector2f(0, -30));
   vertices.push_back(sf::Vector2f(5, -90));
   vertices.push_back(sf::Vector2f(7, -97));
   vertices.push_back(sf::Vector2f(10, -100));
   vertices.push_back(sf::Vector2f(20, -100));
   vertices.push_back(sf::Vector2f(28, -97));
   vertices.push_back(sf::Vector2f(30, -90));
   vertices.push_back(sf::Vector2f(35, -30));
   vertices.push_back(sf::Vector2f(35, 0));
   vertices.push_back(sf::Vector2f(30, 60));
   vertices.push_back(sf::Vector2f(28, 67));
   vertices.push_back(sf::Vector2f(20, 70));
   vertices.push_back(sf::Vector2f(10, 70));
   vertices.push_back(sf::Vector2f(7, 67));
   vertices.push_back(sf::Vector2f(5, 60));


   mainShape = GamePolygon(16, vertices);

   pivot.setPosition(mainShape.getPosition());
   pivot.setRadius(14);
   pivot.setOrigin(14, 14);
   pivot.setFillColor(sf::Color(130, 130, 125));

   rot = false;

   mainShape.setRotation(-30);
}

Paddle::~Paddle()
{
   //dtor
}

sf::Vector2f Paddle::getPosition(){
   return mainShape.getPosition();
}

GamePolygon Paddle::getMainShape(){
   return mainShape;
}
void Paddle::setColor(sf::Color color){

   mainShape.setFillColor(color);
}

void Paddle::move(const sf::Vector2f &offset){
   mainShape.move(offset);
   pivot.move(offset);

}

void Paddle::move(float x, float y){
   mainShape.move(x,y);
   pivot.move(x,y);

}

void Paddle::setPosition(const sf::Vector2f &pos){
   mainShape.setPosition(pos);
   pivot.setPosition(pos);
}
void Paddle::setPosition(float x, float y){
   mainShape.setPosition(x,y);
   pivot.setPosition(x,y);
}

sf::Vector2f Paddle::getPos(){
   return getPosition();
}

void Paddle::setRotation(float theta){
   mainShape.setRotation(theta);
   mainShape.rotating = true;
   mainShape.rotLife = 3;
}


int Paddle::getRotLife(){
   return mainShape.rotLife;
}

void Paddle::setRotLife(int life){
   mainShape.rotLife = life;
}

bool Paddle::isRotating(){
   return mainShape.rotating;
}

void Paddle::setRotating(bool r){
   mainShape.rotating = r;
}
