#include <stdio.h>

int main() {
    int n = 10, p = 5, q = 10, r;
    r = n == (p = q);
    printf("A : n = %d p = %d q = %d r = %d\n", n, p, q, r);

    n = p = q = 5;
    n += p += q;
    printf("B : n = %d p = %d q = %d\n", n, p, q);

    q = n++ < p || p++ != 3;
    printf("C : n = %d p = %d q = %d\n", n, p, q);

    q = ++n == 3 && ++p == 3;
    printf("D : n = %d p = %d q = %d\n", n, p, q);

    return 0;
}

//-------------| Sortie ecran |-------------//
// A : n = 10 p = 10 q = 10 r = 1
// B : n = 15 p = 10 q = 5
// C : n = 16 p = 11 q = 5
// D : n = 17 p = 12 q = 5
