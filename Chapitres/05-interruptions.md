# **5. Gestion des Interruptions**
Une interruption est un événement qui provoque l'**arrêt immédiat du programme principal** pour exécuter une fonction spécifique appelée **ISR** (Interrupt Service Routine). Une fois le traitement terminé, le microcontrôleur reprend l'exécution du programme principal exactement là où il s'était arrêté.

- ## Types des Interruptions (Sources)

   - ### **Interruptions Externes**

      | Source | Broche  | Description                         |
      | ------ | ------- | ----------------------------------- |
      | INT0   | `RB0`     | Interruption sur front externe      |
      | INT1   | `RB1`     | Interruption sur front externe      |
      | INT2   | `RB2`     | Interruption sur front externe      |
      | RBIF   | `RB4` à `RB7` | Changement d’état des broches PORTB |


   - ### **Interruptions Internes**

      <table>
        <thead>
          <tr>
            <th>Catégorie</th>
            <th>Source</th>
            <th>Description</th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td rowspan="3"><strong><a href="#6-gestion-des-timers">Timers</a></strong></td>
            <td>Timer 0</td>
            <td>Débordement du Timer0</td>
          </tr>
          <tr>
            <td>Timers 1/3/5</td>
            <td>Débordement du Timer1/3/5</td>
          </tr>
          <tr>
            <td>Timers 2/4/6</td>
            <td>Débordement du Timer2/4/6</td>
          </tr>
          <tr>
            <td rowspan="3"><strong>Analogiques</strong></td>
            <td>ADC</td>
            <td>Fin de conversion A/N</td>
          </tr>
          <tr>
            <td>Comparateurs</td>
            <td>Interruption comparateur</td>
          </tr>
          <tr>
            <td>HLVD</td>
            <td>Détection basse tension</td>
          </tr>
          <tr>
            <td rowspan="3"><strong>Communication</strong></td>
            <td>USART RX</td>
            <td>Réception série</td>
          </tr>
          <tr>
            <td>USART TX</td>
            <td>Fin d’émission</td>
          </tr>
          <tr>
            <td>SSP</td>
            <td>SPI / I²C</td>
          </tr>
          <tr>
            <td rowspan="2"><strong>Contrôle</strong></td>
            <td>CCP1</td>
            <td>Capture / Compare / PWM</td>
          </tr>
          <tr>
            <td>CCP2</td>
            <td>Capture / Compare / PWM</td>
          </tr>
          <tr>
            <td rowspan="2"><strong>Mémoire / Bus</strong></td>
            <td>EEPROM / FLASH</td>
            <td>Fin d’écriture</td>
          </tr>
          <tr>
            <td>Bus Collision</td>
            <td>Collision sur le bus</td>
          </tr>
        </tbody>
      </table>


- ##  Mécanisme de Contrôle

   - ### Registres de Contrôle
      | **Catégorie** | **Registres** | **Fonction** | **Description** |
      |-------------|--------------|--------------|--------------------------------|
      | **[Contrôle Global](#registres-de-contrôle-global)** | `INTCON`, `INTCON2`, `INTCON3` | Interruptions de Base et Contrôle Global | **Bits GIE/PEIE :** <br>`0` = Interruptions désactivées <br>`1` = Interruptions activées<br><br>**Bits IE :** <br>`0` = Source désactivée <br>`1` = Source activée<br><br>**Bits IF :** <br>`0` = Pas d'événement <br>`1` = Événement détecté |
      | **[Priorité](#registres-de-priorité-ipr1-à-ipr5)** | `IPR1` à `IPR5` | Niveaux de Priorité **([si IPEN=1](#modes-de-fonctionnement))** | **Bits IPx :** <br>`0` = Priorité basse <br>`1` = Priorité haute (uniquement valide si `IPEN=1`) |
      | **[Activation](#registres-dactivation-pie1-à-pie5)** | `PIE1` à `PIE5` | Masques d'Activation Individuelle | **Bits IEx :** <br>`0` = Interruption masquée <br>`1` = Interruption autorisée |
      | **[Flags](#registres-de-flags-pir1-à-pir5)** | `PIR1` à `PIR5` | Indicateurs d'Événements Périphériques | **Bits IFx :** <br>`0` = Événement non survenu <br>`1` = Événement survenu (à effacer manuellement) |
      | **[Configuration](#registres-de-configuration)** | `RCON` | Choix du Mode | **Bit IPEN :** <br>`0` = Mode Priorité Unique (GIE/PEIE) <br>`1` = Mode Deux Priorités (GIEH/GIEL) |

      > - **INTCON** = **INT**errupt **CON**trol
      > - **IPR** = **I**nterrupt **P**riority **R**egister
      > - **PIE** = **P**eripheral **I**nterrupt **E**nable  
      > - **PIR** = **P**eripheral **I**nterrupt **R**equest
      > - **RCON** = **R**eset **CON**trol


   - ### Contrôle Global (Bits Système)  
      | Bit | Registre | Nom | Fonction | Description |
      |-----|----------|-----|----------|-------------|
      | **IPEN** | `RCON<7>` | Interrupt Priority Enable | Définit l'architecture d'interruption | `0` = Mode priorité unique<br>`1` = Mode deux priorités |
      | **GIEH/GIE** | `INTCON<7>` | Global Interrupt Enable (High) | Gardien principal (nom change selon IPEN) | `0` = Interruptions désactivées<br>`1` = Interruptions activées |
      | **GIEL/PEIE** | `INTCON<6>` | Global Interrupt Enable Low | Contrôle secondaire (nom change selon IPEN) | `0` = Périphériques désactivés<br>`1` = Périphériques activés |

      > - Si (Interruption == `INT0` || `Timer0` || `RB4-RB7`)
      >    - → **`GIE = 1`** Suffit
      > - Si (Interruption == `INT1` || `INT2` || `Timers1/2/3/4/5/6` || `CAN`)
      >    - → **`GIE = 1`** ET **`PEIE = 1`** Obligatoires


   - ### Contrôle par Source (Bits Spécifiques)  
      | Bit | Symbole | Localisation | Fonction | Description |
      |-----|---------|--------------|----------|-------------|
      | **IE** | `PIE1<bit>` | Registres PIE1-PIE5 | Autorise l'interruption pour ce périphérique spécifique | `0` = Source masquée<br>`1` = Source autorisée |
      | **IF** | `PIR1<bit>` | Registres PIR1-PIR5 | Indicateur matériel d'événement (set automatiquement) | `0` = Pas d'événement<br>`1` = Événement détecté (à effacer) |
      | **IP** | `IPR1<bit>` | Registres IPR1-IPR5 | Définit la priorité (seulement si `IPEN=1`) | `0` = Priorité basse<br>`1` = Priorité haute |


- ## Priorité des interruptions
   - ### Niveaux de Priorité
      | Priorité           | Adresse vecteur | Routine                |
      | ------------------ | --------------- | ---------------------- |
      | **Haute priorité** | `0008h`         | `void interrupt()`     |
      | **Basse priorité** | `0018h`         | `void interrupt_low()` |
      
      >  - La gestion des priorités est assurée par les registres `IPRx`.
      >  - **Exception :** l’interruption `INT0` ne possède pas de bit de priorité → toujours **haute priorité**.

   - ### Modes de Fonctionnement   
      | Bit | IPEN = 0 (Mode Simple) | IPEN = 1 (Mode Priorité) |
      |-----|------------------------|--------------------------|
      | **INTCON<7> :** `(GIE/GIEH)` | `GIE = 1` : Active **Tout**<br>`GIE = 0` : Désactive Tout | `GIEH = 1` : Active **Haute Priorité**<br>`GIEH = 0` : Désactive Tout |
      | **INTCON<6> :** `(PEIE/GIEL)` | `PEIE = 1` : Active **Périphériques**<br>`PEIE = 0` : Désactive Périphériques | `GIEL = 1` : Active **Basse Priorité**<br>`GIEL = 0` : Désactive Basse Priorité |


- ## Registres de Gestion d'Interruption

   - ### **Registres de Contrôle Global**
   
      - **INTCON - Contrôle Interruptions de Base**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | **GIE/GIEH** | **PEIE/GIEL** | **TMR0IE** | **INT0IE** | **RBIE** | **TMR0IF** | **INT0IF** | **RBIF** |
      
         > - **Bits 7-6** : Contrôle global (noms changent selon IPEN)
         > - **Bits 5-3** : Activation des interruptions de base
         > - **Bits 2-0** : Flags d'interruption de base
      
      - **INTCON2 - Configuration Interruptions Externes**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | **RBPU** | **INTEDG0** | **INTEDG1** | **INTEDG2** | — | **TMR0IP** | — | **RBIP** |
      
      - **INTCON3 - Interruptions Externes 1 & 2**
   
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | **INT2IP** | **INT1IP** | — | **INT2IE** | **INT1IE** | — | **INT2IF** | **INT1IF** |
   
   
   - ### **Registres de Priorité (IPR1 à IPR5)**
   
      - **IPR1 - Priorités Périphériques (Groupe 1)**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | — | **ADIP** | **RC1IP** | **TX1IP** | **SSP1IP** | **CCP1IP** | **TMR2IP** | **TMR1IP** |
      
      - **IPR2 - Priorités Périphériques (Groupe 2)**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | **OSCFIP** | **C1IP** | **C2IP** | **EEIP** | **BCL1IP** | **HLVDIP** | **TMR3IP** | **CCP2IP** |
      
      - **IPR3 - Priorités Périphériques (Groupe 3)**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | **SSP2IP** | **BCL2IP** | **RC2IP** | **TX2IP** | **CTMUIP** | **TMR5GIP** | **TMR3GIP** | **TMR1GIP** |
      
      - **IPR4 - Priorités Périphériques (Groupe 4)**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | — | — | — | — | — | **CCP5IP** | **CCP4IP** | **CCP3IP** |
      
      - **IPR5 - Priorités Périphériques (Groupe 5)**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | — | — | — | — | — | **TMR6IP** | **TMR5IP** | **TMR4IP** |
      
      > **Valeurs IP bits :** `0` = Basse priorité, `1` = Haute priorité (si IPEN=1)
   
   
   - ### **Registres d'Activation (PIE1 à PIE5)**
   
      - **PIE1 - Activation Périphériques (Groupe 1)**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | — | **ADIE** | **RC1IE** | **TX1IE** | **SSP1IE** | **CCP1IE** | **TMR2IE** | **TMR1IE** |
      
      - **PIE2 - Activation Périphériques (Groupe 2)**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | **OSCFIE** | **C1IE** | **C2IE** | **EEIE** | **BCL1IE** | **HLVDIE** | **TMR3IE** | **CCP2IE** |
      
      - **PIE3 à PIE5** - Structure identique à IPR3-IPR5 mais avec suffixe **IE**
      

      > **Valeurs IE bits :** `0` = Désactivé, `1` = Activé
   
   
   - ### **Registres de Flags (PIR1 à PIR5)**
   
      - **PIR1 - Flags Périphériques (Groupe 1)**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | — | **ADIF** | **RC1IF** | **TX1IF** | **SSP1IF** | **CCP1IF** | **TMR2IF** | **TMR1IF** |
      
      - **PIR2 à PIR5** - Structure identique à PIE2-PIE5 mais avec suffixe **IF**
      
      > **Valeurs IF bits :** `0` = Pas d'événement, `1` = Événement détecté (à effacer manuellement)
      
   
   - ### **Registres de Configuration**
   
      - **ANSELB - Configuration Analogique/Digital**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | — | — | **ANSB5** | **ANSB4** | **ANSB3** | **ANSB2** | **ANSB1** | **ANSB0** |
      
      - **IOCB - Interrupt-on-Change Port B**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | **IOCB7** | **IOCB6** | **IOCB5** | **IOCB4** | — | — | — | — |
      
      
      - **RCON - Registre de Contrôle Système**
      
         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
         |-------|-------|-------|-------|-------|-------|-------|-------|
         | **IPEN** | **SBOREN** | — | **RI** | **TO** | **PD** | **POR** | **BOR** |
      
         > - **Bit 7 (IPEN)** : `0`=Mode simple, `1`=Mode deux priorités
         > - **Bits 4-0** : Indicateurs de reset (Power-on, Brown-out, etc.)