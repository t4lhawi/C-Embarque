#include <stdio.h>

int main() {
    signed char p1 = 0;  // variable 8 bits signée

    // 1. Mettre à 1 le bit b2
    p1 |= (1 << 2);

    // 2. Mettre à 1 les bits b3 et b6
    p1 |= (1 << 3) | (1 << 6);

    // 3. Mettre à 0 le bit b0
    p1 &= ~(1 << 0);

    // 4. Mettre à 0 les bits b4 et b5
    p1 &= ~((1 << 4) | (1 << 5));

    // 5. Inverser le bit b3 (XOR)
    p1 ^= (1 << 3);

    // 6. Mettre à 1 le bit b2 et à 0 le bit b0
    p1 |= (1 << 2);
    p1 &= ~(1 << 0);

    // 7. Mettre à 1 les bits b0 et b7 et à 0 les bits b3 et b4
    p1 |= (1 << 0) | (1 << 7);
    p1 &= ~((1 << 3) | (1 << 4));

    return 0;
}
