#include "Ball.h"
#include <cmath>
#include <iostream>

using namespace std;

Ball::~Ball()
{
   //dtor
}

sf::Vector2f Ball::getVelocity(){
   return velocity;
}


void Ball::setVelocity(const sf::Vector2f &vel){
   velocity = vel;
}

void Ball::setVelocity(const sf::Vector2f &dir, float speed){
   velocity = dir;
   normalize(velocity);
   velocity.x = speed * velocity.x;
   velocity.y = speed * velocity.y;
}
void Ball::setVelocity(float angle, float speed){
   angle = angle * 3.1415926 / 180;
   velocity.x = speed * cos(angle);
   velocity.y = speed * sin(angle);
}


CollisionResult Ball::checkCollision(const GamePolygon &poly){
   CollisionResult result;
   result.intersect = false;
   result.willIntersect = false;
   result.minIntervalDistance = std::numeric_limits<float>::max();
   result.translationAxis.x = 0;
   result.translationAxis.y = 0;


   sf::Vector2f p = getPosition();

   /*if (poly.rotating){


      sf::Vector2f tp = p - poly.getPosition();
      poly.getTransform().transformPoint(tp);
      tp = tp - poly.getPosition();
      poly.getTransform().transformPoint(tp);

      p = tp;

   }*/

   sf::Vector2f e1 = poly.getTransform().transformPoint(poly.getPoint(0));

   sf::Vector2f impactPoint(numeric_limits<float>::max(), numeric_limits<float>::max());

   sf::Vector2f prevPos = p - velocity;
   float travelDist = numeric_limits<float>::max();
   int impactEdgeIndex = -1;


   for (int i = 1; i < poly.getPointCount() + 1; ++i){
      sf::Vector2f e2;
      if (i < poly.getPointCount()){
         e2 =  poly.getTransform().transformPoint(poly.getPoint(i));
      }else{
         e2 =  poly.getTransform().transformPoint(poly.getPoint(0));
      }
      float edgeLengthSqr = pow(e1.x - e2.x, 2) + pow(e1.y - e2.y, 2);

      sf::Vector2f l = e2-e1;

      normalize(l);
      float projMag = (dotProduct(l, p-e1));

      if (projMag < 0){
         projMag = 0;
      }else if (projMag > sqrt(edgeLengthSqr)){
         projMag = sqrt(edgeLengthSqr);
      }

      normalize(l);
      sf::Vector2f projPoint = (projMag * l) + e1;



      float dist = distanceFormula(p, projPoint);

      int posX = getPosition().x;
      int rad = getRadius();
      if (dist < rad){
         result.intersect = true;
         float curTravelDist = distanceFormula(prevPos, projPoint);
         if (curTravelDist < travelDist){
            travelDist = curTravelDist;
            impactPoint = projPoint;
            impactEdgeIndex = i-1;

         }
      }



      e1 = e2;
   }

   if (result.intersect){
      result.translationAxis = sf::Vector2f(p.x - impactPoint.x, p.y - impactPoint.y);
      normalize(result.translationAxis);
      result.minIntervalDistance = distanceFormula(p, impactPoint);
      result.impactEdge = poly.edges[impactEdgeIndex];
      sf::Vector2f velVec(velocity);
      normalize(velVec);
      result.reflection = velVec - 2 * dotProduct(velVec, result.translationAxis) * result.translationAxis;
      normalize(result.reflection);



   }

   return result;

}

void Ball::setOwner(int o){
   owner = o;
   if (o < 0){
      setFillColor(sf::Color(50,120,255));
   }else if (o > 0){
      setFillColor(sf::Color(250,80,50));
   }else{
      setFillColor(sf::Color(200, 200, 200));
   }
}

int Ball::getOwner(){
   return owner;
}
