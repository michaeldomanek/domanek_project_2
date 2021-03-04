#pragma once

class RobotConfiguration {
    private:
        const float speed{2.0f};
        const float health{100.0f};
        const float robotRotation{1};
        const float turretRotation{1.5f};

    public:
        RobotConfiguration(float speed, float health, float robotRotation, float turretRotation):
        speed(speed),
        health(health),
        robotRotation(robotRotation),
        turretRotation(turretRotation)
        {}

        float getSpeed() {
            return speed;
        }

        float getHealth() {
            return health;
        }

        float getRobotRotation() {
            return robotRotation;
        }

        float getTurretRotation() {
            return turretRotation;
        }
};