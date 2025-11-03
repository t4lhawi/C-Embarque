#include <stdio.h>

int main() {
    unsigned char x = 0b10101100; // Exemple pour tester les bits

    // 1. le bit b6 est à 1
    (x & (1 << 6)) != 0;

    // 2. le bit b3 est à 0
    (x & (1 << 3)) == 0;

    // 3. le bit b2 est à 1 et le bit b4 est à 0
	((x & (1 << 2)) != 0) && ((x & (1 << 4)) == 0);

	// 4. le bit b2 est à 1 ou le bit b7 est à 0
	((x & (1 << 2)) != 0) || ((x & (1 << 7)) == 0);

    // 5. le bit b6 est l’inverse du bit b3 (sans décalage)
	(((x & (1 << 6)) != 0) != ((x & (1 << 3)) != 0));

    // 6. le bit b6 est l’inverse du bit b3 (avec & et ^)
	(((x >> 6) & 1) ^ ((x >> 3) & 1));


    return 0;
}
