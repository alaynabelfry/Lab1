#include <SFML/Graphics.hpp>
#include "TransformNode.h"

int main(int argc, char* argv) 
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "Purple");
  
  sf::RectangleShape bodyRect(sf::Vector2<float>(10.0f, 50.0f));
  sf::RectangleShape lowerRightArmRect(sf::Vector2<float>(15.0f, 5.0f));
  sf::RectangleShape upperRightArmRect(sf::Vector2<float>(15.0f, 5.0f));
  sf::RectangleShape lowerLeftArmRect(sf::Vector2<float>(15.0f, 5.0f));
  sf::RectangleShape upperLeftArmRect(sf::Vector2<float>(15.0f, 5.0f));
  sf::RectangleShape neckRect(sf::Vector2<float>(5.0f,10.0f));
  sf::CircleShape headShape(8.0f, 3);



  bodyRect.setFillColor(sf::Color::Magenta);
  lowerRightArmRect.setFillColor(sf::Color::Blue);
  upperRightArmRect.setFillColor(sf::Color::Red);
  lowerLeftArmRect.setFillColor(sf::Color::Blue);
  upperLeftArmRect.setFillColor(sf::Color::Red);
  neckRect.setFillColor(sf::Color::Yellow);
  headShape.setFillColor(sf::Color::Green);


  bool keyHeld = false;

  bool growing = true;
  float scaleFactor = 1.001;

  float growthFactor = 1.001f;
  float shrinkFactor = 0.999f;


  bodyRect.setOrigin(5.0f, 50.0f);
  bodyRect.setPosition(300, 300);
  bodyRect.setScale(4, 4);

  sf::Vector2<float> rightArmPosition((bodyRect.getLocalBounds().width*0.9f), (bodyRect.getLocalBounds().top + 3.0f));
  sf::Vector2<float> leftArmPosition((bodyRect.getLocalBounds().left*0.9f), (bodyRect.getLocalBounds().top + 3.0f));
  sf::Vector2<float> neckPosition(bodyRect.getLocalBounds().width/2.0f, bodyRect.getLocalBounds().top);
  sf::Vector2<float> headPosition(neckRect.getLocalBounds().width / 2.0f+8.0f, neckRect.getLocalBounds().top);
  sf::Vector2<float> rightArmOrigin(0.0f, 2.5f);
  sf::Vector2<float> leftArmOrigin(15.0f, 2.5f);
  sf::Vector2<float> neckOrigin(2.5f, 10.0f);
  sf::Vector2<float> headOrigin(16.0f, 8.0f);


  upperRightArmRect.setOrigin(rightArmOrigin);
  lowerRightArmRect.setOrigin(rightArmOrigin);
  upperLeftArmRect.setOrigin(leftArmOrigin);
  lowerLeftArmRect.setOrigin(leftArmOrigin);
  neckRect.setOrigin(neckOrigin);
  headShape.setOrigin(headOrigin);

  lowerRightArmRect.setPosition(15.0f, 2.5f);
  upperRightArmRect.setPosition(rightArmPosition);
  lowerLeftArmRect.setPosition(0.0f, 2.5f);
  upperLeftArmRect.setPosition(leftArmPosition);
  neckRect.setPosition(neckPosition);
  headShape.setPosition(headPosition);

  TransformNode body(&bodyRect);
  TransformNode upperRightArm(&upperRightArmRect);
  TransformNode lowerRightArm(&lowerRightArmRect);
  TransformNode upperLeftArm(&upperLeftArmRect);
  TransformNode lowerLeftArm(&lowerLeftArmRect);
  TransformNode neck(&neckRect);
  TransformNode head(&headShape);
  

  upperRightArm.AddChild(&lowerRightArm);
  upperLeftArm.AddChild(&lowerLeftArm);
  neck.AddChild(&head);
  body.AddChild(&neck);
  body.AddChild(&upperLeftArm);
  body.AddChild(&upperRightArm);


  sf::Clock deltaTime;
  while (window.isOpen())
  {
    float elaspedTime = deltaTime.restart().asSeconds();

    sf::Transform transform = bodyRect.getTransform();

    /*triangle.scale(scaleFactor, scaleFactor);
    float currentScale = triangle.getScale().x;
    if (currentScale >= 4.0f) {
      scaleFactor = shrinkFactor;
    }
    else if (currentScale <= 1.0f)
    {
      scaleFactor = growthFactor;
    }*/

    sf::Event sfEvent;
    while (window.pollEvent(sfEvent))
    {
      if (sfEvent.type == sf::Event::Closed)
      {
        window.close();
      }
      else if (sfEvent.type == sf::Event::KeyReleased)
      {
        keyHeld = false;
      }
      else if (sfEvent.type == sf::Event::KeyPressed)
      {
        keyHeld = true;
      }
    }

    if (keyHeld)
    {
      float angleAmount = 90.0f;
	  bodyRect.rotate(angleAmount * elaspedTime);
      lowerRightArmRect.rotate(angleAmount * elaspedTime);
      upperRightArmRect.rotate(angleAmount * elaspedTime);
	  lowerLeftArmRect.rotate(angleAmount * elaspedTime);
	  upperLeftArmRect.rotate(angleAmount * elaspedTime);
	  neckRect.rotate(angleAmount * elaspedTime);
    }

    window.clear(); // draw fullscreen graphic

    /*sf::Transform hierarchy = sf::Transform::Identity;

    window.draw(triangle);
    hierarchy = hierarchy * triangle.getTransform();

    window.draw(lowerRightArmRect, hierarchy); // DRAWING with the triangle's transform.
    hierarchy = hierarchy * lowerRightArmRect.getTransform();

    window.draw(upperRightArmRect, hierarchy); // DRAWING*/

    body.Draw(&window);

    window.display();
  }

  return 0;
}