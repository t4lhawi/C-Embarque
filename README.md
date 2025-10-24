## **Plan du Contenu :**

* **[Qu’est-ce qu’un système embarqué ?](#1-quest-ce-quun-système-embarqué-)**
* **[Pourquoi le langage C sur PIC18F ?](#2-pourquoi-le-langage-c-sur-pic18f-)**
* **[Types de données utiles sur PIC18F](#3-types-de-données-utiles-sur-pic18f)**
* **[Manipulation des registres et bits](#4-manipulation-des-registres-et-bits)**
* **[Pointeurs et mémoire du PIC18F](#5-pointeurs-et-mémoire-du-pic18f)**
* **[Structure d’un programme C sur MPLAB XC8](#6-structure-dun-programme-c-sur-mplab-xc8)**
* **[Entrées/Sorties (GPIO)](#7-entréessorties-gpio)**
* **[Timers et interruptions](#8-timers-et-interruptions)**
* **[Communication série (UART, SPI, I2C)](#9-communication-série-uart-spi-i2c)**
* **[Bonnes pratiques sur PIC18F](#10-bonnes-pratiques-sur-pic18f)**

---

<h3 align="center"><a href="https://github.com/mohamedtalhaouii/Programmation-C" target="_blank">Lien de Programmation en Langage C</a></h3>

---

## **1. Qu’est-ce qu’un système embarqué ?**

* C’est un **système électronique autonome** exécutant un programme dédié à une tâche spécifique.
* Il fonctionne avec des **ressources limitées** : mémoire, énergie, puissance.
* Il doit souvent réagir **en temps réel**.
* Le **PIC18F** est un microcontrôleur typique utilisé dans ces systèmes.

---

## **2. Pourquoi le langage C sur PIC18F ?**

* Langage **rapide** et **efficace** pour le bas niveau.
* Permet d’accéder directement aux **registres matériels**.
* Compatible avec le compilateur **MPLAB XC8**.
* Utilisé pour configurer et piloter les **périphériques internes** (GPIO, timers, UART, etc.).

```c
#include <xc.h>        // Bibliothèque principale Microchip
#define _XTAL_FREQ 8000000   // Définir la fréquence du quartz
```

---

## **3. Types de données utiles sur PIC18F**

👉 Utiliser des **tailles fixes** (bibliothèque `<stdint.h>`) pour maîtriser la mémoire.

| Type       | Taille  | Exemple d’usage                   |
| ---------- | ------- | --------------------------------- |
| `uint8_t`  | 8 bits  | Lecture d’un port GPIO            |
| `uint16_t` | 16 bits | Valeur d’un Timer                 |
| `uint32_t` | 32 bits | Compteur logiciel                 |
| `volatile` | —       | Variable modifiée par le matériel |

```c
volatile uint8_t bouton;     // variable modifiée par interruption
uint16_t compteurTemps;      // compteur local
```

---

## **4. Manipulation des registres et bits**

Chaque périphérique du PIC18F est contrôlé par des **registres** :

* `TRISx` → définit la direction (entrée/sortie).
* `PORTx` → lit les niveaux logiques.
* `LATx`  → écrit sur les sorties.

### 🧩 Opérations sur les bits

```c
REG |= (1 << n);   // Met le bit n à 1
REG &= ~(1 << n);  // Met le bit n à 0
REG ^= (1 << n);   // Inverse le bit n
if (REG & (1 << n)) { ... } // Teste le bit n
```

---

## **5. Pointeurs et mémoire du PIC18F**

Le PIC18F contient plusieurs zones mémoire :

* **Programme (Flash)** → contient le code C compilé.
* **RAM (Données)** → variables temporaires.
* **EEPROM** → données conservées après coupure d’alimentation.

Les périphériques sont mappés en mémoire, accessibles via des **pointeurs volatiles**.

```c
#define REGISTRE (*(volatile uint8_t*)0xF80)
```

---

## **6. Structure d’un programme C sur MPLAB XC8**

Le programme suit une structure fixe :
initialisation → boucle infinie → interruptions éventuelles.

```c
#include <xc.h>
#define _XTAL_FREQ 8000000

void main(void) {
    initialisation();     // Configuration GPIO, Timer, UART...
    
    while(1) {
        // Programme principal (boucle infinie)
    }
}
```

⚠️ `main()` ne se termine jamais : le microcontrôleur fonctionne en continu.

---

## **7. Entrées/Sorties (GPIO)**

* **GPIO = General Purpose Input/Output**
* Sert à lire des capteurs ou commander des LED, moteurs, relais...

| Registre | Fonction                           |
| -------- | ---------------------------------- |
| `TRISx`  | Direction (1 = entrée, 0 = sortie) |
| `PORTx`  | Lecture des broches                |
| `LATx`   | Écriture sur les sorties           |

```c
TRISBbits.TRISB0 = 0;  // RB0 en sortie
LATBbits.LATB0 = 1;    // Allumer la LED RB0
```

---

## **8. Timers et interruptions**

* Les **timers** servent à mesurer le temps ou générer des signaux périodiques (PWM).
* Les **interruptions** permettent d’exécuter un code automatiquement lors d’un événement (timer, bouton, UART...).

```c
void __interrupt() ISR(void) {
    if (INTCONbits.TMR0IF) {
        // Action lors du déclenchement du timer
        INTCONbits.TMR0IF = 0; // Réinitialiser le drapeau
    }
}
```

---

## **9. Communication série (UART, SPI, I2C)**

* **UART** → communication série simple (TX/RX) avec PC.
* **SPI** → transfert rapide de données avec plusieurs périphériques.
* **I2C** → bus à 2 fils pour relier plusieurs composants.

```c
// Exemple générique
TXREG = data;    // Envoi UART
SSPBUF = data;   // Envoi SPI
```

---

## **10. Bonnes pratiques sur PIC18F**

* Toujours utiliser `volatile` pour les variables matérielles.
* Définir correctement `_XTAL_FREQ` avant les fonctions de délai.
* Éviter `malloc` / `free` → risque de fragmentation mémoire.
* Organiser le projet en fichiers `.h` et `.c`.
* Lire attentivement la **datasheet du PIC18F** avant toute configuration.
* Tester chaque module individuellement avant intégration finale.

---

<h3 align="center"> 🧑🏻‍💻 | Made By : <a href="https://github.com/mohamedtalhaouii" target="_blank">Mohamed Talhaoui</a></h3>
