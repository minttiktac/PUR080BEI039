#include "error.hpp"
#include "player.hpp"
#include "login.hpp"
int main()
{
    bool isLoggedIn = true;
    
    if (isLoggedIn  == true)    
    {
        return player();
        return 0;
    }
    else 
    {
        return login();
        return 0;
    }
    return 0;
}


// #include <SFML/Graphics.hpp>
// #include <vector>
// #include <cmath>

// using namespace sf;
// using namespace std;

// int main()
// {
//     RenderWindow window(VideoMode(800, 600), "Music Bar Animation");

//     const int numBars = 5;
//     vector<RectangleShape> bars(numBars);

//     float barWidth = 20.0f;
//     float spacing = 10.0f;
//     for (int i = 0; i < numBars; ++i)
//     {
//         bars[i].setSize(Vector2f(barWidth, 50));
//         bars[i].setPosition(i * (barWidth + spacing) + 50, window.getSize().y / 2);
//         bars[i].setFillColor(Color::Cyan);
//     }

//     Clock clock;
//     while (window.isOpen())
//     {
//         Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == Event::Closed)
//                 window.close();
//         }

//         float time = clock.getElapsedTime().asSeconds();

//         // Update the height of each bar independently
//         for (int i = 0; i < numBars; ++i)
//         {
//             float amplitude = 100.0f * std::sin(time * 4 + i); // Sine wave for smooth up-down animation
//             bars[i].setSize(Vector2f(barWidth, amplitude + 150)); // Base height of 150, amplitude adds to it
//             bars[i].setPosition(bars[i].getPosition().x, (window.getSize().y / 2) - amplitude / 2);
//         }

//         window.clear(Color::Black);
//         for (auto& bar : bars)
//         {
//             window.draw(bar);
//         }
//         window.display();
//     }

//     return 0;
// }
