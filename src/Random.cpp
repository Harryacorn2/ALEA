#include "Random.h"

unsigned long Random::x = 123456789;
unsigned long Random::y = 362436069;
unsigned long Random::z = 521288629;

unsigned long Random::GetLong() {
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}

int Random::GetInt(int i) {
    unsigned long x = GetLong();
    return (x % i);
}

int Random::GetIntInRange(int i, int j) {
    int t = j - i;
    t++;
    unsigned long x = GetLong();
    x = x % t;
    x += i;
}
