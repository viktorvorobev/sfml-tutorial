#include <SFML/Graphics.hpp>
#include <random>
#include "events.hpp"
#include "configuration.hpp"
#include "star.hpp"

std::vector<Star> createStars(uint32_t count)
{
    std::vector<Star> stars;
    stars.reserve(count);

    // Random numbers generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    // Create randomly distributed stars on the screen
    for (uint32_t i{count}; i--;)
    {
        const float x = dis(gen) * conf::window_size_f.x;
        const float y = dis(gen) * conf::window_size_f.y;

        stars.push_back({{x, y}});
    }

    return stars;
}

int main()
{
    auto window = sf::RenderWindow{{conf::window_size.x, conf::window_size.y}, "CMake SFML Project"};
    window.setFramerateLimit(conf::max_framerate);

    std::vector<Star> stars = createStars(conf::count);

    while (window.isOpen())
    {
        processEvents(window);

        // Rendering occurs here
        window.clear();

        sf::CircleShape shape{conf::radius};
        shape.setOrigin(conf::radius, conf::radius);

        for (auto const &s : stars)
        {
            shape.setPosition(s.position);
            window.draw(shape);
        }
        window.display();
    }
}
