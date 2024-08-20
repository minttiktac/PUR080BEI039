    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <iostream>
    #include <cmath>

    using namespace std;
    using namespace sf;

    int main()
    {
        Music music;
        if (!music.openFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/Bulleya.wav"))
        {
            cout << "Error loading music file" << endl;
            return 1;
        }

        RenderWindow window(VideoMode(700, 500), "Melody Tunes");

        Image icon;
        if (!icon.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/icon.png"))
        {
            cout << "Error Loading Icon File" << endl;
            return 1;
        }
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        Texture background;
        if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/Melody.png"))
        {
            cout << "Error Loading Background File" << endl;
            return 1;
        }
        Sprite s(background);

        music.play();

        Font font;
        if (!font.loadFromFile("Poppins-Medium.ttf"))
        {
            cout << "Error loading font file" << endl;
            return 1;
        }
        Text text("Press P to Play/Pause\nPress S to Stop", font, 20);
        text.setFillColor(Color::White);
        text.setPosition(20, 350);

        RectangleShape rectangle(Vector2f(10, 10));
        rectangle.setPosition(345, 150);


        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::P)
                    {
                        if (music.getStatus() == Music::Playing)
                            music.pause();
                        else
                            music.play();
                    }
                    if (event.key.code == Keyboard::S)
                    {
                        music.stop();
                    }
                }
            }   

            float amplitude = abs(sin(music.getPlayingOffset().asSeconds() * 2));
            float newHeight = 10 + amplitude * 10;
            rectangle.setSize(Vector2f(10, newHeight));

            window.clear(Color::White);
            window.draw(s);
            window.draw(rectangle);

            window.draw(text);

            window.display();
        }

        return 0;
    }

