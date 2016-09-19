#include <SFML/Graphics.hpp>

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

  triangle.setOrigin(10, 10);
  triangle.setPosition(300, 300);
  triangle.setScale(4, 4);

  sf::Vector2<float> armPosition((triangle.getLocalBounds().width / 1.75f), (triangle.getLocalBounds().height / 1.5f));
  sf::Vector2<float> armOrigin(0.0f, 2.5f);

  lowerArmRect.setPosition(15.0f, 2.5f);
  upperArmRect.setPosition(armPosition);

  while (window.isOpen())
  {
    sf::Transform transform = triangle.getTransform();

    triangle.scale(scaleFactor, scaleFactor);
    float currentScale = triangle.getScale().x;
    if (currentScale >= 4.0f) {
      scaleFactor = shrinkFactor;
    }
    else if (currentScale <= 1.0f)
    {
      scaleFactor = growthFactor;
    }

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
      lowerArmRect.rotate(angleAmount);
      upperArmRect.rotate(angleAmount);
    }

    window.clear(); // draw fullscreen graphic
    window.draw(triangle);
    window.draw(lowerArmRect); // DRAWING
    window.draw(upperArmRect); // DRAWING

    window.display();
  }

  return 0;
}