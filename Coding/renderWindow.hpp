#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "error.hpp"
#include "popup.hpp"

using namespace std;
using namespace sf;

int render_window()
{

    Music music;
    if (!music.openFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Bulleya.wav"))
    {
        error("Error Loading Music File.");
        return 1;
    }

    Image icon;
    if (!icon.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/icon.png"))
    {
        error("Error Loading Icon File.");
        return 1;
    }

    Texture background;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Melody.png"))
    {
        error("Error Loading Background File.");
        return 1;
    }

    Texture playTexture;
    if (!playTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/play.png"))
    {
        error("Error Loading Play Icon.");
        return 1;
    }

    Texture pauseTexture;
    if (!pauseTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/pause.png"))
    {
        error("Error Loading Pause Icon.");
        return 1;
    }

    RenderWindow window(VideoMode(700, 500), "Melody Tunes");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Sprite backgroundSprite(background);
    Vector2u textureSize = background.getSize();
    Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);
    showPopup(window,"Welcome to music player.");

    music.pause();

    Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return 1;
    }

    Text text("Click the icon to Play/Pause\nPress S to Stop", font, 20);
    text.setFillColor(Color::White);
    text.setPosition(20, 350);

    RectangleShape rectangle(Vector2f(10, 10));
    rectangle.setPosition(345, 150);

    Sprite playSprite(playTexture);
    Sprite pauseSprite(pauseTexture);

    Vector2f iconSize(50.f, 50.f);
    playSprite.setScale(iconSize.x / playTexture.getSize().x, iconSize.y / playTexture.getSize().y);
    pauseSprite.setScale(iconSize.x / pauseTexture.getSize().x, iconSize.y / pauseTexture.getSize().y);

    playSprite.setPosition(windowSize.x / 2 - iconSize.x / 2, windowSize.y / 2 - iconSize.y / 2);
    pauseSprite.setPosition(windowSize.x / 2 - iconSize.x / 2, windowSize.y / 2 - iconSize.y / 2);

    bool isPlaying = false;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if ((event.type == Event::MouseButtonPressed) || (event.type == Event::KeyPressed && event.key.code == Keyboard::Space))
            { 
                if (playSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) ||
                    pauseSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    if (music.getStatus() == Music::Playing)
                    {
                        music.pause();
                        isPlaying = false;
                    }
                    else
                    {
                        music.play();
                        isPlaying = true;
                    }
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
            {
                if (music.getStatus() == Music::Playing)
                {
                    music.pause();
                    isPlaying = false;
                }
                else
                {
                    music.play();
                    isPlaying = true;
                }
            }
        }

        float amplitude = abs(sin(music.getPlayingOffset().asSeconds() * 2));
        float newHeight = 10 + amplitude * 10;
        rectangle.setSize(Vector2f(10, newHeight));

        window.clear(Color::White);
        window.draw(backgroundSprite);
        window.draw(rectangle);
        window.draw(text);

        if (isPlaying)
            window.draw(pauseSprite);
        else
            window.draw(playSprite);

        window.display();
    }

    return 0;
}
