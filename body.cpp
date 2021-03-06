#include "body.hpp"
#include "system.hpp"
#include "cmath"

static std::uint64_t current_id = 0;

Body::Body(std::string name, double mass, double radius,
           QVector2D initPosition, QVector2D initVelocity) :
    id_{current_id},
    name_{name},
    position_{initPosition},
    velocity_{initVelocity},
    acceleration_{},
    mass_{mass},
    radius_{radius}
{
    ++current_id;
}

void Body::update(const System& system)
{
    QVector2D netGravitationalForce{0, 0};
    constexpr double G = 1;

    // Calculates force
    const auto bodies = system.bodys();
    for (auto body_ptr : bodies) {
        if (id_ == body_ptr->id()) {
            continue;
        }

        const auto distance = position_.distanceToPoint(body_ptr->position());

        const auto length_cube = std::abs(std::pow(distance, 3));
        netGravitationalForce += (G * mass_ * body_ptr->mass())
                / length_cube * (body_ptr->position() - position_);
    }
    // Todo: Updates the acceleration
    acceleration_ = netGravitationalForce / mass_;

    // Todo: Updates the velocity and position
    velocity_ += acceleration_ * system.getDelta() / 1000;
    position_ += velocity_ * system.getDelta() / 1000;
}

std::string Body::name() const
{
    return name_;
}

QVector2D Body::position() const
{
    return position_;
}

double Body::mass() const
{
    return mass_;
}

std::string Body::toString()
{
    return "Body:" + name_ +
            "\nposition " + std::to_string(position_.x()) + ", " + std::to_string(position_.y()) +
            "\nvelocity " + std::to_string(velocity_.x()) + ", " + std::to_string(velocity_.y()) +
            "\nacceleration " + std::to_string(acceleration_.x()) + ", " + std::to_string(acceleration_.y()) +
            "\nmass " +  std::to_string(mass_);

}

double Body::radius() const
{
    return radius_;
}

std::uint64_t Body::id() const
{
    return id_;
}
