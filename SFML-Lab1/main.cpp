#include <SFML/Graphics.hpp>
#include "TransformNode.h"

int main(int argc, char* argv) 
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "Purple");
  
  sf::CircleShape triangle(10, 3);
  sf::RectangleShape lowerArmRect(sf::Vector2<float>(15.0f, 5.0f));
  sf::RectangleShape upperArmRect(sf::Vector2<float>(15.0f, 5.0f));

  triangle.setFillColor(sf::Color::Magenta);
  lowerArmRect.setFillColor(sf::Color::Blue);
  upperArmRect.setFillColor(sf::Color::Red);

  bool keyHeld = false;

  bool growing = true;
  float scaleFactor = 1.001;

  float growthFactor = 1.001f;
  float shrinkFactor = 0.999f;

  //triangle.setOrigin(10, 10);
  triangle.setOrigin(20.0f, 20.0f);
  triangle.setPosition(300, 300);
  triangle.setScale(4, 4);

  sf::Vector2<float> armPosition((triangle.getLocalBounds().width / 1.75f), (triangle.getLocalBounds().height / 1.5f));
  sf::Vector2<float> armOrigin(0.0f, 2.5f);

  upperArmRect.setOrigin(armOrigin);
  lowerArmRect.setOrigin(armOrigin);

  lowerArmRect.setPosition(15.0f, 2.5f);
  upperArmRect.setPosition(armPosition);

  TransformNode head(&triangle);
  TransformNode upperArm(&upperArmRect);
  TransformNode lowerArm(&lowerArmRect);

  upperArm.AddChild(&lowerArm);
  head.AddChild(&upperArm);

  sf::Clock deltaTime;
  while (window.isOpen())
  {
    float elaspedTime = deltaTime.restart().asSeconds();

    sf::Transform transform = triangle.getTransform();

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
      lowerArmRect.rotate(angleAmount * elaspedTime);
      upperArmRect.rotate(angleAmount * elaspedTime);
    }

    window.clear(); // draw fullscreen graphic

    /*sf::Transform hierarchy = sf::Transform::Identity;

    window.draw(triangle);
    hierarchy = hierarchy * triangle.getTransform();

    window.draw(lowerArmRect, hierarchy); // DRAWING with the triangle's transform.
    hierarchy = hierarchy * lowerArmRect.getTransform();

    window.draw(upperArmRect, hierarchy); // DRAWING*/

    head.Draw(&window);

    window.display();
  }

  return 0;
}