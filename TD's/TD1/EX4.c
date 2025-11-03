#include <stdio.h>

int main() {
    int a = 12, b = 23;

    // a >> 1 → division par 2
    printf("a >> 1 = %d (équivaut à a / 2)\n", a >> 1);

    // a >> 2 → division par 4
    printf("a >> 2 = %d (équivaut à a / 4)\n", a >> 2);

    // b << 1 → multiplication par 2
    printf("b << 1 = %d (équivaut à b * 2)\n", b << 1);

    // b << 2 → multiplication par 4
    printf("b << 2 = %d (équivaut à b * 4)\n", b << 2);

    return 0;
}