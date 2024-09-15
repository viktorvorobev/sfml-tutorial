#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow{{1920u, 1080u}, "CMake SFML Project"};
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear();
        window.display();
    }
}
