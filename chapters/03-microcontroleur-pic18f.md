# **3. Microcontrôleur PIC18F**
Le **[PIC18F&sup1;](https://en.wikipedia.org/wiki/PIC_microcontrollers)** fait partie de la famille des microcontrôleurs 8 bits de Microchip, conçus pour les systèmes embarqués nécessitant **performance**, **faible consommation**, et **contrôle bas niveau**.


- ### **Architecture du Microcontrôleur PIC18F45K22**
   ![arch_pic](https://github.com/user-attachments/assets/7c2701f0-caba-4d97-b3a2-a83eb048764c)

   
   - **[Architecture Harvard&sup2;](https://en.wikipedia.org/wiki/Harvard_architecture) (Au Niveau de la Mémoire) :**
      - Séparation entre **mémoire programme** et **mémoire données**
      - Accès parallèles permettant **plus de rapidité**
      - Pipeline matériel pour exécuter certaines instructions en un seul cycle
   
   ![arch_mem_pic](https://github.com/user-attachments/assets/7c8c3a9f-9458-432b-9d27-180e6de747bd)
   
   
   - **[Architecture RISC&sup3;](https://en.wikipedia.org/wiki/Reduced_instruction_set_computer) (Au Niveau du Processeur) :**
      - Ensemble d’instructions réduit, simple et optimisé
      - **Exécution rapide** : la majorité des instructions en **1 cycle**
      - Idéal pour le contrôle temps réel et les applications industrielles


> **Le PIC18F se distingue également par :**
  > - Des **ports d’E/S configurables** (digital/analogique)
  > - Une gestion avancée des **interruptions**
  > - Plusieurs **Timers 8/16 bits**
  > - Interfaces intégrées : **UART, SPI, I²C, PWM**
  > - Convertisseur **ADC 10 ou 12 bits** selon modèle


- ### **Pins du Microcontrôleur PIC18F45K22**

   ![pic18f](https://github.com/user-attachments/assets/f27b1d27-621b-4148-b83b-737ff575455a)
      
   | **Pin** | **Nom**          | **Fonction principale**   |
   | ------- | ---------------- | ------------------------- |
   | 1       | MCLR / Vpp / RE3 | Reset + programmation     |
   | 2       | RA0 / AN0        | E/S digitale + ADC        |
   | 3       | RA1 / AN1        | E/S digitale + ADC        |
   | 4       | RA2 / AN2        | E/S digitale + ADC        |
   | 5       | RA3 / AN3        | E/S digitale + ADC        |
   | 6       | RA4              | E/S digitale (open-drain) |
   | 7       | RA5 / AN4 / SS   | ADC + SPI Slave Select    |
   | 8       | RE0 / AN5        | ADC                       |
   | 9       | RE1 / AN6        | ADC                       |
   | 10      | RE2 / AN7        | ADC                       |
   | 11      | Vdd              | Alimentation +5V          |
   | 12      | Vss              | Masse                     |
   | 13      | RA7              | Horloge externe (OSC1)    |
   | 14      | RA6              | Horloge externe (OSC2)    |
   | 15      | RC0              | Timer                     |
   | 16      | RC1 / CCP2       | PWM                       |
   | 17      | RC2 / CCP1       | PWM                       |
   | 18      | RC3 / SCL / SCK  | I²C / SPI Clock           |
   | 19      | RD0              | E/S digitale              |
   | 20      | RD1              | E/S digitale              |
   | 21      | RD2              | E/S digitale              |
   | 22      | RD3              | E/S digitale              |
   | 23      | RC4 / SDA / SDI  | I²C / SPI data            |
   | 24      | RC5 / SDO        | SPI                       |
   | 25      | RC6 / TX         | UART Transmission         |
   | 26      | RC7 / RX         | UART Réception            |
   | 27      | RD4              | E/S digitale              |
   | 28      | RD5              | E/S digitale              |
   | 29      | RD6              | E/S digitale              |
   | 30      | RD7              | E/S digitale              |
   | 31      | Vss              | Masse (-)                 |
   | 32      | Vdd              | Alimentation (+)          |
   | 33      | RB0 / INT0       | Interruption externe      |
   | 34      | RB1 / INT1       | Interruption              |
   | 35      | RB2 / INT2       | Interruption              |
   | 36      | RB3 / CCP2       | PWM / Capture             |
   | 37      | RB4              | E/S digitale              |
   | 38      | RB5              | E/S digitale              |
   | 39      | RB6 / PGC        | Programmation ICSP        |
   | 40      | RB7 / PGD        | Programmation ICSP        |


   > **ADC = “Analog Digital Converter”**
   > - Il sert à **convertir une tension analogique** (0 à 5 V) en une **valeur numérique** (0 à 1023 pour un ADC 10 bits).
   
   > **PGC = “Program Clock (Horloge de programmation)”**
   > - Donne le timing
   
   > **PGD = “Program Data (Données de programmation)”**
   > - Transporte les valeurs 0/1 pour programmer la mémoire Flash
   
   > **Rxx = “Registres / Pins (RA0, RB5, RC6, etc.)”**
   > - **R = Register (PORT)**
   > - **A/B/C/D/E = le port**
   > - **numéro = le bit/pin**
   
   > **CCP = “Capture / Compare / PWM”**
   > - **Capture :** Mesurer la durée d’un signal, une fréquence…
   > - **Compare :** Déclencher un événement à un moment précis.
   > - **PWM :** Générer un signal PWM (moteurs, servos, LED dimming…)
   
   
   > **MCLR = “Master Clear (Broche Reset)”**
   > - Réinitialiser (redémarrer) le PIC
   > - Activer le mode programmation (Vpp ≈ 12 V)
   > - Utilisé par Pickit/ICD