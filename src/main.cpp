#include <SFML/Graphics.hpp>
#include "events.hpp"

int main()
{
    auto window = sf::RenderWindow{{1920u, 1080u}, "CMake SFML Project"};
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        processEvents(window);

        window.clear();
        window.display();
    }
}
