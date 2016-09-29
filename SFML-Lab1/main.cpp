#include <SFML/Graphics.hpp>
#include "TransformNode.h"


#define bodyScale 4
#define bodyX 10.0f
#define bodyY 60.0f

using namespace sf;



int main(int argc, char* argv) 
{
  RenderWindow window(VideoMode(600, 600), "Lab1");
  
  RectangleShape rightSholderRect(Vector2<float>(20.0f, 5.0f));
  RectangleShape rightElbowRect(Vector2<float>(20.0f, 5.0f));
  RectangleShape leftSholderRect(Vector2<float>(20.0f, 5.0f));
  RectangleShape leftElbowRect(Vector2<float>(20.0f, 5.0f));
  RectangleShape bodyRect(Vector2<float>(bodyX, bodyY));
  RectangleShape neckRect(Vector2<float>(2.5f, 15.0f));
  CircleShape headCirc(5.0f);

  bodyRect.setFillColor(Color::White);
  rightSholderRect.setFillColor(Color::Red);
  rightElbowRect.setFillColor(Color::Magenta);
  leftSholderRect.setFillColor(Color::Yellow);
  leftElbowRect.setFillColor(Color::Green);
  neckRect.setFillColor(Color::Blue);
  headCirc.setFillColor(Color::Cyan);

  // TODO: add defines for constants
  bodyRect.setOrigin(5.0f, 60.0f);
  bodyRect.setPosition(300 - bodyX * bodyScale / 2 + 20, 600 - bodyY * bodyScale + 60 * bodyScale); // Calculate the center of the X-axis.
  bodyRect.setScale(bodyScale, bodyScale);

  neckRect.setOrigin(1.75f, 15.0f);
  neckRect.setPosition(5.0f, 0.0f);

  rightSholderRect.setPosition(10, 0);

  leftSholderRect.setOrigin(20.0f, 0.0f);
  
  leftElbowRect.setOrigin(20.0f,5.0f);
  leftElbowRect.setPosition(0.0f,5.0f);

  rightElbowRect.setOrigin(0.0f, 5.0f);
  rightElbowRect.setPosition(20.0f, 5.0f);

  headCirc.setPosition(-2.0f, -2.5f);

  TransformNode body(&bodyRect);
  TransformNode rightSholder(&rightSholderRect);
  TransformNode leftSholder(&leftSholderRect);
  TransformNode leftElbow(&leftElbowRect);
  TransformNode neck(&neckRect);
  TransformNode rightElbow(&rightElbowRect);
  TransformNode head(&headCirc);

  body.AddChild(&rightSholder);
  body.AddChild(&leftSholder);
  body.AddChild(&neck);
  leftSholder.AddChild(&leftElbow);
  rightSholder.AddChild(&rightElbow);
  neck.AddChild(&head);

  Clock deltaTime;
  Clock timer;
  timer.restart();


  float bodyAngle = 5;
  float sholdersAngle = 10;
  float elbowAngle = -20;
  float neckAngle = -8;
  float headAngle = 50;
  float timeToRotate = 2.5;
  bool firstTime = true;
  while (window.isOpen())
  {  
	  if (timer.getElapsedTime().asSeconds() >= timeToRotate) {
		  if (firstTime) {
			  firstTime = false;
			  timeToRotate *= 2;
		  }
		  bodyAngle *= (-1);
		  sholdersAngle *= (-1);
		  elbowAngle *= (-1);
		  neckAngle *=(-1);
		 
		  timer.restart();
	  }
	 float elaspedTime = deltaTime.restart().asSeconds();
	 bodyRect.rotate(bodyAngle * elaspedTime);
	 leftSholderRect.rotate(sholdersAngle * elaspedTime);
	 rightSholderRect.rotate(-1 * sholdersAngle * elaspedTime);
	 leftElbowRect.rotate( elbowAngle * elaspedTime);
	 neckRect.rotate(neckAngle * elaspedTime);
	 rightElbowRect.rotate(-1 * elbowAngle * elaspedTime);

    window.clear(); // draw fullscreen graphic

    body.Draw(&window);

    window.display();
  }

  return 0;
}