#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>

namespace conf {
// Winow configuration
const sf::Vector2u window_size = {1920, 1080};
const sf::Vector2f window_size_f = static_cast<sf::Vector2f>(window_size);
const uint32_t max_framerate = 144;
const float dt = 1.0f / static_cast<float>(max_framerate);

// Star configuration
const uint32_t count = 1000;
const float radius = 20.0f;
const float far = 10.0f;
const float near = 1.0f;
} // namespace conf
