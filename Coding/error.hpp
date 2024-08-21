#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstring>

using namespace std;
using namespace sf;

void error(string message)
{
    RenderWindow window(VideoMode(700, 500), "Melody Tune");
    Image icon;
    if (!icon.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/icon.png"))
    {
        cout << "Error Loading Icon File." << endl << "Proceeding Without Loading." << endl;
    }
    else {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    Texture background;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Melody-Error.png"))
    {
        cout << "Error Loading Error Image File." << endl << "Proceeding Without Loading." << endl;
    }

    Font font;

    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        cout << "Error Loading Font File." << endl;
    }

    Sprite s(background);

    string t_message = message + "\nPlease try restarting the program.";

    Text text(t_message, font, 20);
    Color color(0x071952FF);
    text.setFillColor(color);
    text.setPosition(225, 400);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        
        window.clear(Color::White);
        window.draw(s);

        window.draw(text);
        window.display();
    }
}