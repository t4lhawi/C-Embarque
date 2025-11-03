#include <stdio.h>

int main() {
    char nb = 123; // Exemple : valeur quelconque (0–255)

    int centaines = nb / 100;       // Extraction des centaines
    int dizaines  = (nb / 10) % 10; // Extraction des dizaines
    int unites    = nb % 10;        // Extraction des unités

    printf("nb = %d → centaines = %d, dizaines = %d, unites = %d\n\n", nb, centaines, dizaines, unites);

    return 0;
}
