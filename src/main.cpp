#include "configuration.hpp"
#include "events.hpp"
#include "star.hpp"
#include <SFML/Graphics.hpp>
#include <random>

std::vector<Star> createStars(uint32_t count, float scale) {
  std::vector<Star> stars;
  stars.reserve(count);

  // Random numbers generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(0.0f, 1.0f);

  // Define star free zone so they don't disappear right in front of the screen
  const sf::Vector2f window_world_size = conf::window_size_f * conf::near;
  const sf::FloatRect star_free_zone = {-window_world_size * 0.5f,
                                        window_world_size};

  // Create randomly distributed stars on the screen
  for (uint32_t i{count}; i--;) {
    const float x = (dis(gen) - 0.5f) * conf::window_size_f.x * scale;
    const float y = (dis(gen) - 0.5f) * conf::window_size_f.y * scale;
    const float z = dis(gen) * (conf::far - conf::near) + conf::near;

    // Discard any star that falls in the zone
    if (star_free_zone.contains(x, y)) {
      ++i; // Don't decrease the count
      continue;
    }
    // Else add it in the vector
    stars.push_back({{x, y}, z});
  }

  // Depth ordering
  std::sort(stars.begin(), stars.end(),
            [](const Star &s_1, const Star &s_2) { return s_1.z > s_2.z; });

  return stars;
}

void updateGeometry(uint32_t idx, const Star &s, sf::VertexArray &va) {
  const float scale = 1.0f / s.z;
  const float depth_ratio = (s.z - conf::near) / (conf::far - conf::near);
  const float color_ratio = 1.0f - depth_ratio;
  const auto c = static_cast<uint8_t>(color_ratio * 255.0f);

  const sf::Vector2f p = s.position * scale;
  const float r = conf::radius * scale;
  const uint32_t i = 4 * idx;

  va[i + 0].position = {p.x - r, p.y - r};
  va[i + 1].position = {p.x + r, p.y - r};
  va[i + 2].position = {p.x + r, p.y + r};
  va[i + 3].position = {p.x - r, p.y + r};

  const sf::Color color{c, c, c};
  va[i + 0].color = color;
  va[i + 1].color = color;
  va[i + 2].color = color;
  va[i + 3].color = color;
}

int main() {
  auto window = sf::RenderWindow{{conf::window_size.x, conf::window_size.y},
                                 "CMake SFML Project",
                                 sf::Style::Fullscreen};
  window.setFramerateLimit(conf::max_framerate);
  window.setMouseCursorVisible(false);

  sf::Texture texture;
  texture.loadFromFile("res/star.png");
  texture.setSmooth(true);
  texture.generateMipmap();

  std::vector<Star> stars = createStars(conf::count, conf::far);

  sf::VertexArray va{sf::PrimitiveType::Quads, 4 * conf::count};
  // Pre fill texture coordinates as they will remain constant
  const auto texture_size_f = static_cast<sf::Vector2f>(texture.getSize());
  for (uint32_t idx{conf::count}; idx--;) {
    const uint32_t i = 4 * idx;
    va[i + 0].texCoords = {0.0f, 0.0f};
    va[i + 1].texCoords = {texture_size_f.x, 0.0f};
    va[i + 2].texCoords = {texture_size_f.x, texture_size_f.y};
    va[i + 3].texCoords = {0.0f, texture_size_f.y};
  }

  uint32_t first = 0;
  while (window.isOpen()) {
    processEvents(window);

    // Fake travel toward increasing Z
    for (uint32_t i{conf::count}; i--;) {
      Star &s = stars[i];
      s.z -= conf::speed * conf::dt;
      if (s.z < conf::near) {
        // Offset the star by the excess travel it made behind near to keep the
        // ordering of the stars
        s.z = conf::far - (conf::near - s.z);
        // This star is now the first we need to draw because it is further away
        first = i;
      }
    }

    // Rendering occurs here
    window.clear();

    sf::CircleShape shape{conf::radius};
    shape.setOrigin(conf::radius, conf::radius);

    for (uint32_t i{0}; i < conf::count; ++i) {
      const uint32_t idx = (i + first) % conf::count;
      const Star &s = stars[idx];
      updateGeometry(i, s, va);
    }
    sf::RenderStates states;
    states.transform.translate(conf::window_size_f * 0.5f);
    states.texture = &texture;
    window.draw(va, states);

    window.display();
  }
}
