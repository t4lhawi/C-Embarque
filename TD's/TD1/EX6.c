#include <stdio.h>

short test_bit(char C1, short n) {
    return (C1 & (1 << n)) ? 1 : 0;
}

void print_binary(char C1) {
    for (int i = 7; i >= 0; i--)
        printf("%d", (C1 >> i) & 1);
    printf("\n");
}

void set_bit(char *C1, short n) {
    *C1 |= (1 << n);
}

void clear_bit(char *C1, short n) {
    *C1 &= ~(1 << n);
}

char rotate_bits(char C1, short n) {
    n = n % 8;
    return (C1 << n) | (C1 >> (8 - n));
}

int main() {
    char A1 = 0b10101100;

    printf("Valeur initiale de A1 = ");
    print_binary(A1);

    // test_bit
    short n = 3;
    printf("\nTest du bit %d : %d\n", n, test_bit(A1, n));

    // set_bit
    set_bit(&A1, 1);
    printf("Après set_bit(1) : ");
    print_binary(A1);

    // clear_bit
    clear_bit(&A1, 3);
    printf("Après clear_bit(3) : ");
    print_binary(A1);

    // rotation
    A1 = rotate_bits(A1, 2);
    printf("Après rotation gauche de 2 : ");
    print_binary(A1);

    // rotation droite equivalente à gauche de (8 - n)
    char B = rotate_bits(A1, 6);
    printf("Rotation gauche de 6 (équiv. droite de 2) : ");
    print_binary(B);

    return 0;
}
