#ifndef GAMEPOLYGON_H
#define GAMEPOLYGON_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

using namespace std;

float dotProduct(const sf::Vector2f &point, const sf::Vector2f &axis);
float magnitude(const sf::Vector2f &vec);
void normalize(sf::Vector2f &vec);
float distanceFormula(const sf::Vector2f &p1, const sf::Vector2f &p2);
float angle(const sf::Vector2f &v1, const sf::Vector2f &v2);

struct CollisionResult {
   bool willIntersect;
   bool intersect;
   float minIntervalDistance;
   sf::Vector2f translationAxis;
   sf::Vector2f impactEdge;
   sf::Vector2f reflection;

};


class GamePolygon : public sf::ConvexShape
{
   public:
      GamePolygon(std::size_t pointCount = 0, const vector<sf::Vector2f> &vertices = vector<sf::Vector2f>());
      virtual ~GamePolygon();
      void centerOrigin();
      CollisionResult checkCollision (GamePolygon &other);
      void generateEdges();
      sf::Vector2f getCenter();
      sf::Vector2f velocity;
      vector<sf::Vector2f> edges;
      bool rotating;
      int rotLife;
   protected:
   private:
      sf::Vector2f center;
      bool collidable;



      sf::Vector2f projPolyMags(const sf::Vector2f &axis);
      float intervalDistance(float minA, float maxA, float minB, float maxB);
      void rotateAbout(float angle, const sf::Vector2f & point);




      /*Math funcs I need:
      Dot product
      interval distance
      */
};

#endif // GAMEPOLYGON_H
