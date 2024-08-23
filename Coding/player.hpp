#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "error.hpp"
#include "popup.hpp"
#include "slider.hpp"

using namespace std;
using namespace sf;

int player()
{

    Color color(0x071952FF);

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
    Texture playBackTexture, playForwardTexture, playNextTexture, playPrevTexture;
    if (!playBackTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/arrow-left.png") || !playForwardTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/arrow-right.png") || !playPrevTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/previous.png") || !playNextTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/next.png"))
    {
        error("Error loading Icons.");
        return 1;
    }
    RenderWindow window(VideoMode(700, 500), "Melody Tunes");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Sprite backgroundSprite(background);
    Vector2u textureSize = background.getSize();
    Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);

    music.pause();

    Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return 1;
    }

    RectangleShape rectangle(Vector2f(10, 10));
    rectangle.setFillColor(color);
    rectangle.setPosition(345, 150);

    Sprite playSprite(playTexture);
    Sprite pauseSprite(pauseTexture);

    Vector2f iconSize(70.f, 70.f);
    playSprite.setScale(iconSize.x / playTexture.getSize().x, iconSize.y / playTexture.getSize().y);
    pauseSprite.setScale(iconSize.x / pauseTexture.getSize().x, iconSize.y / pauseTexture.getSize().y);

    playSprite.setPosition(windowSize.x / 2 - iconSize.x / 2, windowSize.y / 2 - iconSize.y / 2);
    pauseSprite.setPosition(windowSize.x / 2 - iconSize.x / 2, windowSize.y / 2 - iconSize.y / 2);

    Sprite playBack(playBackTexture);
    Sprite playForward(playForwardTexture);
    Vector2f iconSize2(40.f, 40.f);
    playBack.setScale(iconSize2.x / playBackTexture.getSize().x, iconSize2.y / playBackTexture.getSize().y);
    playForward.setScale(iconSize2.x / playForwardTexture.getSize().x, iconSize2.y / playForwardTexture.getSize().y);

    playBack.setPosition((windowSize.x / 2 - iconSize2.x / 2) - 70, windowSize.y/2 - iconSize2.y / 2);
    playForward.setPosition((windowSize.x / 2 - iconSize2.x / 2) + 70, windowSize.y/2 - iconSize2.y / 2);


    Sprite playNext(playNextTexture);
    Sprite playPrev(playPrevTexture);
    Vector2f iconSize3(30.f, 30.f);
    playNext.setScale(iconSize3.x / playBackTexture.getSize().x, iconSize3.y / playBackTexture.getSize().y);
    playPrev.setScale(iconSize3.x / playForwardTexture.getSize().x, iconSize3.y / playForwardTexture.getSize().y);

    playNext.setPosition((windowSize.x / 2 - iconSize3.x / 2) + 130, (windowSize.y/2 - iconSize3.y / 2) + 4);
    playPrev.setPosition((windowSize.x / 2 - iconSize3.x / 2) - 130, (windowSize.y/2 - iconSize3.y / 2) + 4);

    Slider playerSlider(Vector2f(100, 450), Vector2f(500, 10));
    playerSlider.setTotalDuration(music.getDuration().asSeconds());
    playerSlider.setThumbPosition(0);


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
            if (event.type == Event::MouseButtonPressed)
            {
                if (playForward.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime + seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
            {
                Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime + seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (playBack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime - seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
                }
                if (playerSlider.onTrackClick(Vector2f(event.mouseButton.x, event.mouseButton.y)) == 2)
                {
                    float ratio = (event.mouseButton.x - playerSlider.getTrackPosition()) / playerSlider.getTrackWidth();
                    float newTime = ratio * 100;
                    playerSlider.setThumbPosition(newTime);
                    music.setPlayingOffset(seconds(newTime * music.getDuration().asSeconds() / 100));
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
            {
                Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime - seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
            }
        }


        float currentValue = playerSlider.getThumbPosition();
        Time currentTime = music.getPlayingOffset();
        Time duration = music.getDuration();
        playerSlider.setCurrentDuration(currentTime.asSeconds());
        currentValue = (currentTime.asSeconds() / duration.asSeconds()) * 100;
        playerSlider.setThumbPosition(currentValue);

        float amplitude = abs(sin(music.getPlayingOffset().asSeconds() * 2));
        float newHeight = 10 + amplitude * 10;
        rectangle.setSize(Vector2f(10, newHeight));

        window.clear(Color::White);
        window.draw(backgroundSprite);
        window.draw(rectangle);
        window.draw(playBack);
        window.draw(playForward);
        window.draw(playPrev);
        window.draw(playNext);
        if (isPlaying)
            window.draw(pauseSprite);
        else
            window.draw(playSprite);
        playerSlider.draw(window);
        window.display();
    }

    return 0;
}
