#pragma once

class BulletConfiguration {
    private:
        const float speed;
        const float damage;
        const unsigned int size;
    public:
        BulletConfiguration(float speed, float damage, unsigned int size):
        speed(speed),
        damage(damage),
        size(size)
        {}

        float getSpeed() {
            return speed;
        }

        float getDamage() {
            return damage;
        }

        unsigned int getSize() {
            return size;
        }

};