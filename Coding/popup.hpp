#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;


void showPopup(RenderWindow& window, const string& message, Vector2f popupSize = Vector2f(400, 60))
{
    RectangleShape popupBox(popupSize);
    popupBox.setFillColor(Color(0x071952FF));
    popupBox.setPosition(window.getSize().x / 2 - popupSize.x / 2, -popupSize.y);


    Font font;

    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return;
    }

    Text popupText(message, font, 20);
    popupText.setFillColor(Color::White);
    popupText.setPosition(popupBox.getPosition().x + 20, popupBox.getPosition().y + 12);

    float targetY = 50; 
    float speed = 500.f;

    Clock clock;
    while (popupBox.getPosition().y < targetY)
    {
        float deltaTime = clock.restart().asSeconds();
        popupBox.move(0, speed * deltaTime);
        popupText.setPosition(popupBox.getPosition().x + 20, popupBox.getPosition().y + 10);

        window.clear();
        window.draw(popupBox);
        window.draw(popupText);
        window.display();
    }

    sleep(seconds(2));

    while (popupBox.getPosition().y > -popupSize.y)
    {
        float deltaTime = clock.restart().asSeconds();
        popupBox.move(0, -speed * deltaTime);
        popupText.setPosition(popupBox.getPosition().x + 20, popupBox.getPosition().y + 10);

        window.draw(popupBox);
        window.draw(popupText);
        window.display();
    }
}

