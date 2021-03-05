#pragma once

class RobotConfiguration {
    private:
        const float speed;
        const float health;
        const float robotRotation;
        const float turretRotation;

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