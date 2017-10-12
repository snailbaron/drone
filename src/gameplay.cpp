#include "gameplay.hpp"
#include "config.hpp"
#include "gfx_utils.hpp"

#include <SFML/Window.hpp>

Gameplay::Gameplay()
{
    _drone = std::make_unique<Drone>();

    _camera.follow(_drone->position);

    auto makeWall = []
    {
        auto wallLength = 10.0;
        auto wallWidth = 0.3;

        auto obstacle = std::make_unique<Obstacle>();
        obstacle->points = {
            {wallWidth / 2, wallLength / 2},
            {-wallWidth / 2, wallLength / 2},
            {-wallWidth / 2, -wallLength / 2},
            {wallWidth / 2, -wallLength / 2},
        };
        return obstacle;
    };

    auto wall = makeWall();
    wall->position->location = {-3.0, 5.0};
    _actors.push_back(std::move(wall));

    wall = makeWall();
    wall->position->location = {3.0, 5.0};
    _actors.push_back(std::move(wall));

    wall = makeWall();
    wall->position->location = {-4.7, 14.6};
    wall->position->angle = 20.0;
    _actors.push_back(std::move(wall));

    wall = makeWall();
    wall->position->location = {4.7, 14.6};
    wall->position->angle = -20.0;
    _actors.push_back(std::move(wall));

    wall = makeWall();
    wall->position->location = {-3.3, 23.0};
    wall->position->angle = -40.0;
    _actors.push_back(std::move(wall));

    wall = makeWall();
    wall->position->location = {3.3, 23.0};
    wall->position->angle = 40.0;
    _actors.push_back(std::move(wall));

    auto enemy = std::make_unique<Enemy>();
    enemy->position->location = {-1.0, 20.0};
    _actors.push_back(std::move(enemy));

    enemy = std::make_unique<Enemy>();
    enemy->position->location = {1.0, 20.0};
    _actors.push_back(std::move(enemy));

    _controllers.push_back(std::make_unique<KeyboardMovementController>(
        _drone->movement));
}

void Gameplay::processInputEvent(const sf::Event& event)
{
    for (const auto& controller : _controllers) {
        controller->processInput(event);
    }
}

void Gameplay::update(double delta)
{
    _drone->update(delta);

    for (const auto& actor : _actors) {
        actor->update(delta);
    }

    _camera.update(delta);

    for (const auto& controller: _controllers) {
        controller->applyInput(delta);
    }
}

void Gameplay::render(Screen& screen) const
{
    screen.clear();

    auto screenSize = screen.size();
    auto scale = screenSize.y / 10.f;
    sf::Transform transform;
    transform.translate(gfxVector(screenSize / 2));
    transform.scale(scale, -scale);
    transform.translate(gfxVector(-_camera.position->location));

    for (const auto& actor : _actors) {
        actor->render(screen, transform);
    }

    _drone->render(screen, transform);

    screen.present();
}
