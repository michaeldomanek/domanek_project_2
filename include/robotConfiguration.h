#pragma once

class RobotConfiguration {
    private:
        const float speed;
        const float health;
        const float robotRotation;
        const float turretRotation;
        const int minFireCountdown;

    public:
        RobotConfiguration(float speed, float health, float robotRotation, float turretRotation, int minFireCountdown):
        speed(speed),
        health(health),
        robotRotation(robotRotation),
        turretRotation(turretRotation),
        minFireCountdown(minFireCountdown)
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

        int getMinFireCountdown() {
            return minFireCountdown;
        }
};