#include <SFML/Graphics.hpp>
#include <cmath>
#include "boid.h"
#include "utils.h"

using namespace sf;

/// @brief Creates a new boid!!
/// @param pos Position of boid
/// @param color Color to draw this boid
/// @param scale Scale to draw this boid
/// @param view_radius radius around boid to view for flocking behaviors
/// @param container Vector of boid pointers that this boid is created in
Boid::Boid(Vector2f pos, Color color, float scale, float view_radius, std::vector<Boid*>& container)
: container(container), view_radius(view_radius), wander_angle(0) {
    // set up boid shape, like a lil arrow :]
    render_shape.setPointCount(4);
    render_shape.setPoint(0, Vector2f(0, -1));
    render_shape.setPoint(1, Vector2f(-0.7, 1));
    render_shape.setPoint(2, Vector2f(0, 0.7));
    render_shape.setPoint(3, Vector2f(0.7, 1));

    // set shape properties
    render_shape.setPosition(pos);
    render_shape.setFillColor(color);
    render_shape.setScale(scale, scale);

    // initialize physics component
    physics.set_position(pos);
    physics.set_max_speed(250);
}

#pragma region //* Steering behaviors

Vector2f Boid::Seek(const Vector2f& target) {
    Vector2f dir = target - physics.get_position();
    if (dir != Vector2f(0, 0))
        dir = Utils::vec_normalize(dir);
    Vector2f desired_velocity = dir * physics.get_max_speed();
    return desired_velocity - physics.get_velocity();
}

Vector2f Boid::Seek(Boid& target) {
    return Seek(target.get_position());
}

Vector2f Boid::Flee(const Vector2f& target) {
    Vector2f dir = physics.get_position() - target;
    if (dir != Vector2f(0, 0))
        dir = Utils::vec_normalize(dir);
    Vector2f desired_velocity = dir * physics.get_max_speed();
    return desired_velocity - physics.get_velocity();
}

Vector2f Boid::Flee(Boid& target) {
    return Flee(target.get_position());
}

Vector2f Boid::Wander(float time, float radius) {
    Vector2f target_pos = CalcFuturePos(time);

    // calculate random value between -angle_range and +angle_range,
    //   and use it to modify current wander angle
    float angle_range = M_PI / 15;
    float rand_value = (((float)rand() / RAND_MAX) * 2 - 1) * angle_range;
    wander_angle += rand_value;

    // adjust target position based on radius and angle
    target_pos.x += cosf(wander_angle) * radius;
    target_pos.y += sinf(wander_angle) * radius;

    return Seek(target_pos);
}

Vector2f Boid::StayInRect(const IntRect& rectangle) {
    if (!rectangle.contains((Vector2i)get_position())) {
        Vector2i center = rectangle.getPosition() + (rectangle.getSize() / 2);
        return Seek((Vector2f)center);
    }

    return Vector2f(0, 0);
}

Vector2f Boid::Separate(float radius) {
    Vector2f force(0, 0);

    for (Boid* boid : container) {
        // skip current boid
        if (boid == this)
            continue;

        float d = Utils::dist(get_position(), boid->get_position());
        if (d <= radius) {
            force += (Flee(boid->get_position()) * (1 / d));
        }
    }

    return force;
}

Vector2f Boid::Cohesion(float radius) {
    Vector2f center_point(0, 0);
    float count = 0;

    for (Boid* boid : container) {
        float d_sqr = Utils::dist_sqr(get_position(), boid->get_position());
        if (d_sqr <= (radius * radius)) {
            center_point += boid->get_position();
            count++;
        }
    }

    center_point /= count;

    return Seek(center_point);
}

Vector2f Boid::Alignment(float radius) {
    Vector2f direction(0, 0);

    for (Boid* boid : container) {
        // skip current boid
        if (boid == this)
            continue;

        float d_sqr = Utils::dist_sqr(get_position(), boid->get_position());
        if (d_sqr <= (radius * radius)) {
            direction += boid->get_direction();
        }
    }

    if (direction != Vector2f(0, 0))
        direction = Utils::vec_normalize(direction) * physics.get_max_speed();

    return direction - physics.get_velocity();
}

Vector2f Boid::CalcFuturePos(float time) {
    return physics.get_velocity() * time + get_position();
}

#pragma endregion

/// @brief Updates logic for this boid
/// @param delta_time Time passed since last frame
/// @param view_bounds Rectangular bounds of the game window's view
void Boid::Update(
    float delta_time,
    const IntRect& view_bounds
) {
    physics.ApplyForce(Wander(0.3f, 30) * 10.0f);
    physics.ApplyForce(StayInRect(view_bounds) * 10.0f);

    physics.ApplyForce(Alignment(view_radius) * 5.0f);
    physics.ApplyForce(Separate(view_radius) * 5.0f);
    physics.ApplyForce(Cohesion(view_radius) * 0.7f);

    physics.Update(delta_time);
    render_shape.setPosition(physics.get_position());
}

/// @brief Draws this boid to a render window
/// @param window RenderWindow to draw boid to
void Boid::Draw(RenderWindow& window) {
    float angle_rad = atan2(get_direction().y, get_direction().x);
    float angle_deg = angle_rad * (float)(180 / M_PI) + 90;
    render_shape.setRotation(angle_deg);

    window.draw(render_shape);
}

/// @brief Getter for position of this boid
/// @return Vector2f center-aligned position of this boid
Vector2f Boid::get_position() { return physics.get_position(); }

/// @brief Getter for direction of this boid
/// @return Vector2f direction (normalized) of this boid
sf::Vector2f Boid::get_direction() { return physics.get_direction(); }
