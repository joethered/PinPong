#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GamePolygon.h"
#include "paddle.h"
#include "Ball.h"
#include "Bumber.h"
#include <cmath>
#include <iostream>


using namespace std;


int main()
{
   const int SCREEN_WIDTH = 1280;
   const int SCREEN_HEIGHT = 720;


   sf::ContextSettings settings;
   settings.antialiasingLevel = 8;

   sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Pin Pong", sf::Style::Default, settings);


   // Create a graphical text to display
   sf::Font font;
   if (!font.loadFromFile("arial.ttf"))
      return EXIT_FAILURE;
   sf::Text p1Score_txt("0", font, 36);
   p1Score_txt.setPosition(20,0);

   sf::Text p2Score_txt("0", font, 36);
   p2Score_txt.setPosition(SCREEN_WIDTH - 120, 0);

   sf::Text ballCount_txt("Balls: 9", font, 36);
   ballCount_txt.setOrigin(50,0);
   ballCount_txt.setPosition(SCREEN_WIDTH / 2, 0);


   Paddle player1{};
   player1.setColor(sf::Color(50,120,255));
   player1.setPosition(50,SCREEN_HEIGHT / 2);

   Paddle player2{};
   player2.setColor(sf::Color(250,80,50));
   player2.setPosition(SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2);



   Ball ball;
   float startSpeed = 1;
   ball.setRadius(10);
   ball.setFillColor(sf::Color(200, 200, 200));
   ball.setVelocity(180, startSpeed);
   ball.setPosition(640,360);
   ball.setOrigin(10,10);


   vector<GamePolygon> walls;
   vector<sf::Vector2f> vertices;

   vertices.push_back(sf::Vector2f(0, SCREEN_HEIGHT));
   vertices.push_back(sf::Vector2f(0, SCREEN_HEIGHT - 10));
   vertices.push_back(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT - 10));
   vertices.push_back(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
   walls.push_back(GamePolygon(4, vertices));

   walls[0].setFillColor(sf::Color(240, 240, 240));
   walls[0].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 10);


   walls.push_back(GamePolygon(4, vertices));


   walls[1].setFillColor(sf::Color(240, 240, 240));
   walls[1].setPosition(SCREEN_WIDTH / 2, 50);

   vector<Bumber> bumpers;
   vertices.clear();
   int bumperRadius = 50;
   int bumperPoints = 9;
   for (int theta = 0; theta < 360; theta += 360/bumperPoints){
      float x = bumperRadius * cos(theta * 3.14159265 / 180);
      float y = bumperRadius * sin(theta * 3.14159265 / 180);
      vertices.push_back(sf::Vector2f(x,y));
   }

   for (int i = 0; i < 3; ++i){
      bumpers.push_back(Bumber(bumperPoints, vertices));

   }

   bumpers[0].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 8.0);
   bumpers[1].setPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT * 5 / 6.0);
   bumpers[2].setPosition(SCREEN_WIDTH * 3 / 4.0, SCREEN_HEIGHT * 5 / 6.0);



   //Sound Initialization
   sf::SoundBuffer paddle1_bfr;
   if (!paddle1_bfr.loadFromFile("paddle1.wav")){
      cout << "Error: could not load 'paddle1.wav'" << endl;
   }
   sf::Sound paddle1_sfx;
   paddle1_sfx.setBuffer(paddle1_bfr);


   /*sf::SoundBuffer paddle2_bfr;
   if (!paddle2_bfr.loadFromFile("paddle2.wav")){
      cout << "Error: could not load 'paddle2.wav'" << endl;
   }
   sf::Sound paddle2_sfx;
   paddle2_sfx.setBuffer(paddle2_bfr);


   sf::SoundBuffer bell1_bfr;
   bell1_bfr.loadFromFile("bell1.wav");
   sf::Sound bell1_sfx;
   bell1_sfx.setBuffer(bell1_bfr);


   sf::SoundBuffer bell2_bfr;
   bell2_bfr.loadFromFile("bell2.wav");
   sf::Sound bell2_sfx;
   bell2_sfx.setBuffer(bell2_bfr);
*/



   bool wPressed = false;
   bool commaPressed = false;

   int p1Score = 0;
   int p2Score = 0;
   int ballCount = 15;

   sf::Clock clock;

   sf::CircleShape circle(3);
   circle.setFillColor(sf::Color(200,0,0));
   // Start the game loop
   while (window.isOpen())
   {
      window.clear();
      // Process events
      sf::Event event;
      while (window.pollEvent(event))
      {
         // Close window: exit
         if (event.type == sf::Event::Closed)
            window.close();
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
         window.close();
      }

      sf::Time dt = clock.getElapsedTime();

      float dt_mil = dt.asMicroseconds() * .005;


      //Player 1
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
         player1.move(0, -1 * dt_mil);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
         player1.move(0, 1 * dt_mil);
      }

      if (player1.getMainShape().rotating){
         player1.setRotLife(player1.getRotLife() - 1);
         if (player1.getRotLife() == 0){
            player1.setRotating(false);
         }
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
         if (!wPressed){
            if (player1.rot){
               paddle1_sfx.play();
               player1.setRotation(-30);
               player1.rot = false;
            }else{
               //paddle2_sfx.play();
               player1.setRotation(30);
               player1.rot = true;
            }
            player1.setRotating(true);
            player1.setRotLife(30);
         }
         wPressed = true;
      }else{
         wPressed = false;
      }


      //Player 2
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
         player2.move(0, -1 * dt_mil);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
         player2.move(0, dt_mil);
      }

      if (player2.getMainShape().rotating){
         player2.setRotLife(player2.getRotLife() - 1);
         if (player2.getRotLife() == 0){
            player2.setRotating(false);
         }
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
         if (!commaPressed){
            if (player2.rot){
               paddle1_sfx.play();
               player2.setRotation(-30);
               player2.rot = false;
            }else{
               //paddle2_sfx.play();
               player2.setRotation(30);
               player2.rot = true;
            }
            player2.setRotating(true);
            player2.setRotLife(30);
         }
         commaPressed = true;
      }else{
         commaPressed = false;
      }


      //s.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

      window.draw(player1.getMainShape());
      window.draw(player1.pivot);
      window.draw(player2.getMainShape());
      window.draw(player2.pivot);

      CollisionResult r = ball.checkCollision(player1.getMainShape());

      if (r.intersect){
         float speed = magnitude(ball.getVelocity());
         sf::Vector2f transVec = r.minIntervalDistance * r.translationAxis;
         ball.move(transVec);
         if (player1.isRotating()){
            speed *= 2;
         }
         ball.setVelocity(r.reflection, speed);
         ball.setOwner(-1);
      }

      r = ball.checkCollision(player2.getMainShape());

      if (r.intersect){
         float speed = magnitude(ball.getVelocity());
         sf::Vector2f transVec = r.minIntervalDistance * r.translationAxis;
         ball.move(transVec);
         if (player2.isRotating()){
            speed *= 2;
         }
         ball.setVelocity(r.reflection, speed);
         ball.setOwner(1);
      }

      for (int i = 0; i < walls.size(); ++i){
         r = ball.checkCollision(walls[i]);
         if (r.intersect){
            float speed = magnitude(ball.getVelocity());
            sf::Vector2f transVec = r.minIntervalDistance * r.translationAxis;
            ball.move(transVec);
            ball.setVelocity(r.reflection, speed * 0.95);
         }
      }


      for (int i = 0; i < bumpers.size(); ++i){
         bumpers[i].updateAnimation();
         r = ball.checkCollision(bumpers[i].getShape());
         if (r.intersect){
            bumpers[i].startAnimation();
            float speed = startSpeed * 2;
            sf::Vector2f transVec = r.minIntervalDistance * r.translationAxis;
            ball.move(transVec);
            ball.setVelocity(r.reflection, speed);
            if (ball.getOwner() < 0){
               p1Score += 150;
            }
            if (ball.getOwner() > 0){
               p2Score += 150;
            }
         }
      }

      ball.move(ball.getVelocity().x * dt_mil, ball.getVelocity().y * dt_mil);




      if (ball.getPosition().x < -10 || ball.getPosition().x > SCREEN_WIDTH + 10 || \
          ball.getPosition().y < -10 || ball.getPosition().y > SCREEN_HEIGHT + 10){
         if (ball.getPosition().x > SCREEN_WIDTH){
            if (ball.getOwner() < 0){
               p1Score += 1000;
            }else{
               p2Score += 400;
            }
         }
         if (ball.getPosition().x < 0){
            if (ball.getOwner() > 0){
               p2Score += 1000;
            }else{
               p1Score += 400;
            }
         }

         float speed = startSpeed;
         ball.setPosition(640,360);
         if (ball.getOwner() != 0){
            speed *= ball.getOwner();
         }

         ball.setVelocity(180, speed);
         ball.setOwner(0);
         ballCount -= 1;

         if (ballCount <= 0){
            ballCount = 0;
            ball.setPosition(-100,-100);
            ball.setVelocity(0, 0);
         }
      }

      p1Score_txt.setString(to_string(p1Score));
      window.draw(p1Score_txt);

      p2Score_txt.setString(to_string(p2Score));
      window.draw(p2Score_txt);

      ballCount_txt.setString("Balls: " + to_string(ballCount));
      window.draw(ballCount_txt);




      for (int i = 0; i < walls.size(); ++i){
         window.draw(walls[i]);
      }

      for (int i = 0; i < bumpers.size(); ++i){
         window.draw(bumpers[i].getOutline());
         window.draw(bumpers[i].getShape());
      }

      window.draw(ball);

      // Update the window
      window.display();

      clock.restart();
    }
    return EXIT_SUCCESS;
}




