#pragma once

class RobotConfiguration {
    private:
        float speed;
        float health;
        float robotRotation;
        float turretRotation;
        int minFireCountdown;
        bool canNotShootAndMove;

    public:
        RobotConfiguration(): RobotConfiguration(0, 0, 0, 0, 0, true) {}

        RobotConfiguration(float speed, float health, float robotRotation, float turretRotation, 
                           int minFireCountdown, bool canNotShootAndMove):
        speed(speed),
        health(health),
        robotRotation(robotRotation),
        turretRotation(turretRotation),
        minFireCountdown(minFireCountdown),
        canNotShootAndMove(canNotShootAndMove)
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

        bool canShootAndMove() {
            return !canNotShootAndMove;
        }
};