#include <SFML/Graphics.hpp>
#include "events.hpp"
#include "configuration.hpp"

int main()
{
    auto window = sf::RenderWindow{{conf::window_size.x, conf::window_size.y}, "CMake SFML Project"};
    window.setFramerateLimit(conf::max_framerate);

    while (window.isOpen())
    {
        processEvents(window);

        window.clear();
        window.display();
    }
}
