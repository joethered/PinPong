#include "GamePolygon.h"
#include <cmath>
#include <iostream>

using namespace std;

float dotProduct(const sf::Vector2f &point, const sf::Vector2f &axis){
   return point.x * axis.x + point.y * axis.y;

}

float magnitude(const sf::Vector2f &vec){
   return sqrt(vec.x * vec.x + vec.y * vec.y);
}

void normalize(sf::Vector2f &vec){
   float mag = magnitude(vec);
   vec.x /= mag;
   vec.y /= mag;
}

float distanceFormula(const sf::Vector2f &p1, const sf::Vector2f &p2){
   return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

float angle(const sf::Vector2f &v1, const sf::Vector2f &v2){
   float mag1 = magnitude(v1);
   float mag2 = magnitude(v2);
   float dot = dotProduct(v1, v2);
   return acos(dot / (mag1 * mag2));
}

GamePolygon::GamePolygon(size_t pointCount, const vector<sf::Vector2f> &vertices) : sf::ConvexShape(pointCount)
{
   //ctor
   rotating = false;
   rotLife = 0;

   for (int i = 0; i < pointCount; ++i){
      setPoint(i, vertices[i]);
   }

   centerOrigin();
   generateEdges();

}

GamePolygon::~GamePolygon()
{
   //dtor

}

void GamePolygon::centerOrigin(){
   int pCount = getPointCount();
   float x = 0;
   float y = 0;
   for (int i = 0; i < pCount; ++i){
      x += getPoint(i).x;
      y += getPoint(i).y;
   }
   x /= pCount;
   y /= pCount;

   setOrigin(x,y);
   center = sf::Vector2f(x,y);

}

sf::Vector2f GamePolygon::getCenter(){
   return center;
}

//Generates the a series of vectors for each edge
void GamePolygon::generateEdges(){
   int pCount = getPointCount();
   for (int i = 1; i < pCount; ++i){
      sf::Vector2f a = getPoint(i);
      sf::Vector2f b = getPoint(i-1);
      sf::Vector2f c = a - b;



      edges.push_back(c);
   }

}



//Returns the min and max magnitudes of the for this polygon's projection on to axis
sf::Vector2f GamePolygon::projPolyMags(const sf::Vector2f &axis){
   float dotProd = dotProduct(getTransform().transformPoint(getPoint(0)), axis);
   float minMag = dotProd;
   float maxMag = dotProd;
   for (int i = 0; i < getPointCount(); ++i){
      sf::Vector2f p = getTransform().transformPoint(getPoint(i));
      dotProd = dotProduct(p, axis);
      if (dotProd < minMag){
         minMag = dotProd;
      }else if (dotProd > maxMag) {
         maxMag = dotProd;
      }
   }

   sf::Vector2f projMags(minMag, maxMag);
   return projMags;
}

float GamePolygon::intervalDistance(float minA, float maxA, float minB, float maxB){
   if (minA < minB){
      return minB - maxA;
   }else{
      return minA - maxB;
   }
}


CollisionResult GamePolygon::checkCollision(GamePolygon &other){

   CollisionResult result;
   result.intersect = true;
   result.willIntersect = true;
   result.minIntervalDistance = numeric_limits<float>::max();
   result.translationAxis.x = 0;
   result.translationAxis.y = 0;

   int thisEdgeCount = getPointCount() - 1;
   int otherEdgeCount = other.getPointCount() - 1;
   result.minIntervalDistance = numeric_limits<float>::max();
   sf::Vector2f edge;


   for (int edgeIndex =  0; edgeIndex < thisEdgeCount + otherEdgeCount; ++edgeIndex){
      if (edgeIndex < thisEdgeCount) {
         edge = edges[edgeIndex];
      }else{
         edge = other.edges[edgeIndex - thisEdgeCount];
      }

      //Axis Perpendicular to cur edge
      sf::Vector2f axis(-edge.y, edge.x);
      normalize(axis);


      sf::Vector2f polyMagsThis = projPolyMags(axis);
      sf::Vector2f polyMagsOther = other.projPolyMags(axis);
      float minA = polyMagsThis.x;
      float maxA = polyMagsThis.y;
      float minB = polyMagsOther.x;
      float maxB = polyMagsOther.y;


      float intDist = intervalDistance(minA, maxA, minB, maxB);
      if (intDist > 0){
         result.intersect = false;
      }

      float velProj = dotProduct(axis, velocity);


      if (velProj < 0){
         minA += velProj;
      }else{
         maxA += velProj;
      }

      intDist = intervalDistance(minA, maxA, minB, maxB);
      //cout << intDist << endl;
      if (intDist > 0)
         result.willIntersect = false;

      if (!result.intersect && !result.willIntersect) break;

      intDist =  std::abs(intDist);
      if (intDist < result.minIntervalDistance){
         result.minIntervalDistance = intDist;
         result.translationAxis = axis;
      }

      sf::Vector2f d = center - other.center;
      if (dotProduct(d, result.translationAxis) < 0){
         result.translationAxis.x = -1 * result.translationAxis.x;
         result.translationAxis.y = -1 * result.translationAxis.y;
      }

   }
  // cout << result.minIntervalDistance << endl;

   if (result.willIntersect){
      result.translationAxis.x *= result.minIntervalDistance;
      result.translationAxis.y *= result.minIntervalDistance;
   }



   return result;

}


