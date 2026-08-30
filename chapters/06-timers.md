# **6. Gestion des Timers**
Un Timer est un périphérique matériel qui agit comme **un chronomètre** ou **un compteur** indépendant du processeur. Il permet d'exécuter des tâches répétitives avec une précision temporelle parfaite sans bloquer le programme principal.

- ### Caractéristiques des Timers

   | Caractéristique | Timer 0 | Timer 1/3/5 | Timer 2/4/6 |
   |-----------------|--------|------------|------------|
   | **Taille** | `8/16-bit` | `16-bit` (`TMRxH:TMRxL`) | `8-bit` (`TMRx` et `PRx`) |
   | **Mode** | Timer / Compteur | Timer / Compteur | Timer |
   | **Pré-diviseur (Prescaler)** | `8-bit` Programmable Software | Pré-diviseur `2-bit` | Programmable Software (`1:1`, `1:4`, `1:16`) |
   | **Post-diviseur (Postscaler)** | Non | Non | Programmable (`1:1` à `1:16`) |
   | **Source Horloge** | Interne (Système) / Externe | Interne / Externe / 32kHz | Interne |
   | **Interruption** | Overflow | Overflow | Sur match `TMRx=PRx` |
   | **Applications** |	Délais, Comptage | Mesure, RTC, CCP | PWM, Timing |
   
   > - **Pré-diviseur :** Diviseur de Fréquence **AVANT** le Compteur.
   >    - **Sans Pré-diviseur :** 1 tic = 1s
   >    - **Pré-diviseur `1:8` :** 8 tics = 1s
   > - **Post-diviseur :** Diviseur de Fréquence **APRÈS** le Compteur, sur l'interruption.
   >    - **Sans Post-diviseur :** Interruption à Chaque Overflow
   >    - **Post-diviseur `1:10` :** Interruption Tous les 10 Overflows


- ### Timer 0 (TMR0)
   - #### Registre de Contrôle – `T0CON`
      <table>
        <thead>
          <tr align="center">
            <th>Bit 7</th>
            <th>Bit 6</th>
            <th>Bit 5</th>
            <th>Bit 4</th>
            <th>Bit 3</th>
            <th>Bit 2</th>
            <th>Bit 1</th>
            <th>Bit 0</th>
          </tr>
        </thead>
        <tbody>
          <tr align="center">
            <td><strong>TMR0ON</strong></td>
            <td><strong>T08BIT</strong></td>
            <td><strong>T0CS</strong></td>
            <td><strong>T0SE</strong></td>
            <td><strong>PSA</strong></td>
            <td colspan="3"><strong>T0PS&lt;2:0&gt;</strong></td>
          </tr>
        </tbody>
      </table>

      - **Bit 7 : `TMR0ON` – Timer0 Activation**
         - **`0`** = **Désactivé**
         - **`1`** = **Activé**
      
      - **Bit 6 : `T08BIT` – Mode Timer0**
         - **`0`** = **Mode `16-bit`**
         - **`1`** = **Mode `8-bit`**
      
      - **Bit 5 : `T0CS` – Source d'Horloge**
         - **`0`** = Horloge **Interne** (Cycle d'Instruction **Fosc/4**)
         - **`1`** = Horloge **Externe** (Broche **RA4 / T0CKI**)
      
      - **Bit 4 : `T0SE` – Front d'Horloge Externe**
         - **`0`** = Front **Montant** (LOW→HIGH)
         - **`1`** = Front **Descendant** (HIGH→LOW)
      
      - **Bit 3 : `PSA` – Attribution du Pré-diviseur**
         - **`0`** = **Attribué**
         - **`1`** = **NON Attribué**
      
      - **Bits 2-0 : `T0PS<2:0>` – Sélection du Pré-diviseur**
       
         | T0PS2 | T0PS1 | T0PS0 | Valeur Pré-diviseur |
         |-------|-------|-------|-------------------|
         | 0 | 0 | 0 | 1:2 |
         | 0 | 0 | 1 | 1:4 |
         | 0 | 1 | 0 | 1:8 |
         | 0 | 1 | 1 | 1:16 |
         | 1 | 0 | 0 | 1:32 |
         | 1 | 0 | 1 | 1:64 |
         | 1 | 1 | 0 | 1:128 |
         | 1 | 1 | 1 | 1:256 |

   - #### Mode Fonctionnement

      | Champ / Bit                 | **Mode Timer** (`T0CS = 0`)                      | **Mode Compteur** (`T0CS = 1`)                                            |
      | --------------------------- | ------------------------------------------------ | ------------------------------------------------------------------------- |
      | **T0CON<5> :** `T0CS`       | **`0`** : Source **Interne** (**Fosc/4**)        | **`1`** : Source **Externe** (Broche **RA4 / T0CKI**)                     |
      | **T0CON<4> :** `T0SE`       | **Ignoré** (Sans Effet)                          | **`0`** : Comptage sur **Front Montant**<br>**`1`** : Comptage sur **Front Descendant** |

   - #### Registres Associés

      <table>
        <thead>
          <tr>
            <th>Name</th>
            <th>Bit 7</th>
            <th>Bit 6</th>
            <th>Bit 5</th>
            <th>Bit 4</th>
            <th>Bit 3</th>
            <th>Bit 2</th>
            <th>Bit 1</th>
            <th>Bit 0</th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td><strong><a href="#mécanisme-de-contrôle">INTCON</a></strong></td>
            <td>GIE / GIEH</td>
            <td>PEIE / GIEL</td>
            <td>TMR0IE</td>
            <td>INT0IE</td>
            <td>RBIE</td>
            <td>TMR0IF</td>
            <td>INT0IF</td>
            <td>RBIF</td>
          </tr>
          <tr>
            <td><strong><a href="#mécanisme-de-contrôle">INTCON2</a></strong></td>
            <td>RBPU</td>
            <td>INTEDG0</td>
            <td>INTEDG1</td>
            <td>INTEDG2</td>
            <td>—</td>
            <td>TMR0IP</td>
            <td>—</td>
            <td>RBIP</td>
          </tr>
          <tr>
            <td><strong>T0CON</strong></td>
            <td>TMR0ON</td>
            <td>T08BIT</td>
            <td>T0CS</td>
            <td>T0SE</td>
            <td>PSA</td>
            <td align="center" colspan="3">T0PS&lt;2:0&gt;</td>
          </tr>
          <tr>
            <td><strong>TMR0H</strong></td>
            <td align="center" colspan="8">Timer0 Register, High Byte</strong></td>
          </tr>
          <tr>
            <td><strong>TMR0L</strong></td>
            <td align="center" colspan="8">Timer0 Register, Low Byte</strong></td>
          </tr>
        </tbody>
      </table>

      > - Si **T08BIT = 1 (`8-bit`)** :
      >    - `TMR0H` est **Ignoré**
      >    - Seul `TMR0L` est **Utilisé**


   - #### Période de Débordement $`T_0`$ (Overflow)
      - ##### En Mode Timer (`T0CS = 0`)
 
         |        Étapes                            |             En Mode Timer (`T0CS = 0`)                                             |
         | ---------------------------------------- | :--------------------------------------------------------------------------------: |
         | **Étape 1 :** Période d’Horloge Interne  | <div align="center">**$`T_H = \frac{4}{F_{osc}}`$**                                |
         | **Étape 2 :** Choix du Pré-diviseur      | <div align="center">**$`\text{Prediv} \in \{1, 2, 4, 8, 16, 32, 64, 128, 256\}`$** |
         | **Étape 3 :** Période d’un Incrément     | <div align="center">**$`T_{inc}​ = \text{Prediv} \times T_H`$**                     |
         | **Étape 4 :** Nombre d’Itérations        | <div align="center">**$`N = \frac{T_{désiré}}{T_{inc}}`$**                         |
         | **Étape 5 :** Valeur Initiale à Charger  | <div align="center">**$`\text{TMR0}_{init} = \text{Max} - \text{N} + 1`$**         |
         | **Formule Finale**                       | <div align="center">**$`T_0 ​= N \times \text{Prediv} \times \frac{4}{F_{osc​}}`$**  |​​​​
 
         > - **Vérifie :** **$`T_{inc}​ < 256`$** (Mode `8-bit`) ou **$`< 65536`$** (Mode `16-bit`)
         > - **Optimise :** Choisis le Pré-diviseur qui donne un Nombre d’Itérations Proche d'un Entier
         
      - ##### En Mode Compteur (`T0CS = 1`)

         |        Étapes                               |             En Mode Compteur (`T0CS = 1`)                                                 |
         | ------------------------------------------- | :---------------------------------------------------------------------------------------: |
         | **Étape 1 :** Choix du Pré-diviseur         | <div align="center">**$`\text{Prediv} \in \{1, 2, 4, 8, 16, 32, 64, 128, 256\}`$**        |
         | **Étape 2 :** Nombre d’Événements à Compter | <div align="center">**$`N = \text{Nombre d’Impulsions Souhaitées}`$**                     |
         | **Étape 3 :** Valeur Initiale à Charger     | <div align="center">**$`\text{TMR0}_{init} = \text{Max} - \text{N} + 1`$**                |
         | **Formule Finale**                          | <div align="center">**$`\text{Débordement Aprés N } \times \text{ Prediv Impulsions}`$**  |
 
     
     > - **Valeur Maximale**
     >    - **$`Max(8bits) = 255`$**
     >    - **$`Max(16bits) = 65535`$**
      
         
<!-- 
- ### Timer 1/3/5 (TMR1/3/5)

   - #### Registre de Contrôle – `TxCON` (x = 1, 3, 5)
      <table>
        <thead>
          <tr align="center">
            <th>Bit 7</th>
            <th>Bit 6</th>
            <th>Bit 5</th>
            <th>Bit 4</th>
            <th>Bit 3</th>
            <th>Bit 2</th>
            <th>Bit 1</th>
            <th>Bit 0</th>
          </tr>
        </thead>
        <tbody>
          <tr align="center">
            <td colspan="2"><strong>TMRxCS&lt;1:0&gt;</strong></td>
            <td colspan="2"><strong>TXCKPS&lt;1:0&gt;</strong></td>
            <td><strong>TXSOSCEN</strong></td>
            <td><strong>TXSYNC</strong></td>
            <td><strong>TXRD16</strong></td>
            <td><strong>TMRxON</strong></td>
          </tr>
        </tbody>
      </table>

      - **Bits 7-6 : `TMRxCS<1:0>` – Sélection de la Source d'Horloge du Timer**
         | TMRxCS1 | TMRxCS0 | Source d'Horloge |
         |---------|---------|------------------|
         | 0 | 0 | **Horloge d'Instruction (`Fosc/4`)** |
         | 0 | 1 | **Horloge Système (`Fosc`)** |
         | 1 | 0 | **Source Externe (Broche `TXCKI`) *ou* Oscillateur Secondaire** (selon **`TXSOSCEN`**) |
         | 1 | 1 | **Réservé – Ne pas Utiliser** |

         > - Si **`TMRxCS<1:0> = 10`** et **`TXSOSCEN = 0`** : Horloge Externe sur **Broche TXCKI** (Front Montant).
         > - Si **`TMRxCS<1:0> = 10`** et **`TXSOSCEN = 1`** : **Oscillateur à Quartz (Secondaire)** sur Broches **SOSC/SOSCO**.

      - **Bits 5-4 : `TXCKPS<1:0>` – Sélection du Pré-diviseur d'Horloge**
         | TXCKPS1 | TXCKPS0 | Valeur du Pré-diviseur |
         |---------|---------|------------------------|
         | 0 | 0 | **1:1** (Pas de division) |
         | 0 | 1 | **1:2** |
         | 1 | 0 | **1:4** |
         | 1 | 1 | **1:8** |

      - **Bit 3 : `TXSOSCEN` – Activation de l'Oscillateur Secondaire**
         - **`0`** = **Désactivé**
         - **`1`** = **Activé** (circuit oscillateur secondaire dédié)

      - **Bit 2 : `TXSYNC` – Synchronisation de l'Horloge Externe**
         - Si `TMRxCS<1:0> = 1X` (Source Externe) :
            - **`0`** = Synchronisation avec l'**Horloge Système (Fosc)**
            - **`1`** = **Pas de synchronisation**
         - Si `TMRxCS<1:0> = 0X` (Source Interne) : **Ce bit est ignoré.**

      - **Bit 1 : `TXRD16` – Mode de Lecture/Écriture `16-Bits`**
         - **`0`** = Lecture/écriture en **deux opérations `8-bits`**
         - **`1`** = Lecture/écriture en **une opération `16-bits`**

      - **Bit 0 : `TMRxON` – Activation du Timer**
         - **`0`** = **Arrêt** – Réinitialise la bascule de gâchette du Timer
         - **`1`** = **Marche**

   - #### Registre de Contrôle de la Porte (Gate) – `TXGCON` (x = 1, 3, 5)
      <table>
        <thead>
          <tr align="center">
            <th>Bit 7</th>
            <th>Bit 6</th>
            <th>Bit 5</th>
            <th>Bit 4</th>
            <th>Bit 3</th>
            <th>Bit 2</th>
            <th>Bit 1</th>
            <th>Bit 0</th>
          </tr>
        </thead>
        <tbody>
          <tr align="center">
            <td><strong>TMRxGE</strong></td>
            <td><strong>TxGPOL</strong></td>
            <td><strong>TxGTM</strong></td>
            <td><strong>TxGSPM</strong></td>
            <td><strong>TxGGO/DONE</strong></td>
            <td><strong>TxGVAL</strong></td>
            <td colspan="2"><strong>TxGSS&lt;1:0&gt;</strong></td>
          </tr>
        </tbody>
      </table>

      - **Bit 7 : `TMRxGE` – Activation de la Fonction Porte du Timer**
         - Si **`TMRxON = 0`** : Ce bit est **ignoré**.
         - Si **`TMRxON = 1`** :
            - **`0`** = Le Timer compte **indépendamment** de la fonction porte.
            - **`1`** = Le comptage du Timer est **contrôlé** par la fonction porte.

      - **Bit 6 : `TxGPOL` – Polarité de la Porte du Timer**
         - **`0`** = Porte **active à l'état BAS** (Le Timer compte quand la porte est BASSE).
         - **`1`** = Porte **active à l'état HAUT** (Le Timer compte quand la porte est HAUTE).

      - **Bit 5 : `TxGTM` – Mode Basculé (Toggle) de la Porte**
         - **`0`** = **Désactivé** – La bascule de la porte est réinitialisée.
         - **`1`** = **Activé** – La bascule de la porte du Timer bascule à **chaque front montant** de la source sélectionnée.

      - **Bit 4 : `TxGSPM` – Mode Impulsion Unique (Single-Pulse) de la Porte**
         - **`0`** = **Désactivé**
         - **`1`** = **Activé** – Le mode impulsion unique contrôle la porte du Timer.

      - **Bit 3 : `TxGGO/DONE` – État d'Acquisition en Mode Impulsion Unique**
         - **`0`** = L'acquisition de l'impulsion unique est **terminée** ou **n'a pas démarré**.
         - **`1`** = L'acquisition est **prête** et attend un front déclencheur.
         > - *Ce bit est **Automatiquement Réinitialisé** quand `TxGSPM` est mis à `0`.*

      - **Bit 2 : `TxGVAL` – État Actuel de la Porte du Timer (Lecture seule)**
         - Indique l'état actuel du signal de porte qui serait appliqué au Timer (`TMRxH:TMRxL`).
         > - *Non affecté par l'activation de la porte (`TMRxGE`).*

      - **Bits 1-0 : `TxGSS<1:0>` – Sélection de la Source de la Porte du Timer**
         | TxGSS1 | TxGSS0 | Source de la Porte |
         |--------|--------|---------------------|
         | 0 | 0 | **Broche de la porte du Timer (Timer Gate Pin)** |
         | 0 | 1 | **Signal de correspondance (Match) du Timer2/4/6** (Sortie de `PR2/PR4/PR6`) |
         | 1 | 0 | **Sortie du Comparateur 1** (optionnellement synchronisée – `sync_C1OUT`) |
         | 1 | 1 | **Sortie du Comparateur 2** (optionnellement synchronisée – `sync_C2OUT`) |

      - #### Mode Fonctionnement de la Porte

         | Champ / Bit               | **Fonction**                                                                                                     |
         |---------------------------|------------------------------------------------------------------------------------------------------------------|
         | **`TMRxGE`**              | Active (`1`) ou contourne (`0`) le contrôle du comptage par la porte, uniquement si le Timer est activé (`TMRxON=1`). |
         | **`TxGSS<1:0>`**          | Définit l'origine du signal qui contrôle la porte (broche, autre timer, comparateur).                           |
         | **`TxGPOL`**              | Définit si le comptage a lieu quand le signal de porte est HAUT (`1`) ou BAS (`0`).                              |
         | **`TxGTM`**               | Permet à la porte de basculer son état à chaque front montant de sa source, créant un signal alterné.            |
         | **`TxGSPM` & `TxGGO/DONE`**| Permet de capturer une **seule impulsion** contrôlée par la porte. `TxGGO/DONE` indique l'état de l'acquisition.|


   - #### Registres Associés (x = 1, 3, 5)
      <table>
        <thead>
          <tr>
            <th>Nom</th>
            <th>Bit 7</th>
            <th>Bit 6</th>
            <th>Bit 5</th>
            <th>Bit 4</th>
            <th>Bit 3</th>
            <th>Bit 2</th>
            <th>Bit 1</th>
            <th>Bit 0</th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td><strong>TxCON</strong></td>
            <td colspan="2">TMRxCS&lt;1:0&gt;</td>
            <td colspan="2">TxCKPS&lt;1:0&gt;</td>
            <td>TxSOSCEN</td>
            <td>TxSYNC</td>
            <td>TxRD16</td>
            <td>TMRxON</td>
          </tr>
          <tr>
            <td><strong>TxGCON</strong></td>
            <td>TMRxGE</td>
            <td>TxGPOL</td>
            <td>TxGTM</td>
            <td>TxGSPM</td>
            <td>TxGGO/<br>DONE</td>
            <td>TxGVAL</td>
            <td colspan="2">TxGSS&lt;1:0&gt;</td>
          </tr>
          <tr>
            <td><strong>TMRxH</strong></td>
            <td align="center" colspan="8">Timerx Register, High Byte</td>
          </tr>
          <tr>
            <td><strong>TMRxL</strong></td>
            <td align="center" colspan="8">Timerx Register, Low Byte</td>
          </tr>
        </tbody>
      </table>

      > Consultez les sections suivantes pour la configuration :  
      > - **[Activation des interruptions (`PIEx`)](#registres-dactivation-pie1-à-pie5)**
      > - **[Drapeaux d'interruption (`PIRx`)](#registres-de-flags-pir1-à-pir5)**
      > - **[Priorités d'interruption (`IPRx`)](#registres-de-priorité-ipr1-à-ipr5)**
 -->

   
- ### Timer 2/4/6 (TMR2/4/6)
   - #### Registre de Contrôle – `TxCON` (x = 2, 4, 6)
      <table>
        <thead>
          <tr align="center">
            <th>Bit 7</th>
            <th>Bit 6</th>
            <th>Bit 5</th>
            <th>Bit 4</th>
            <th>Bit 3</th>
            <th>Bit 2</th>
            <th>Bit 1</th>
            <th>Bit 0</th>
          </tr>
        </thead>
        <tbody>
          <tr align="center">
            <td><strong>—</strong></td>
            <td colspan="4"><strong>TxOUTPS&lt;3:0&gt;</strong></td>
            <td><strong>TMRxON</strong></td>
            <td colspan="2"><strong>TxCKPS&lt;1:0&gt;</strong></td>
          </tr>
        </tbody>
      </table>

      - **Bits 6-3 : `TxOUTPS<3:0>` – Sélection du Post-diviseur de Sortie**
         | TxOUTPS3 | TxOUTPS2 | TxOUTPS1 | TxOUTPS0 | Valeur du Post-diviseur |
         |----------|----------|----------|----------|-------------------------|
         | 0 | 0 | 0 | 0 | **1:1** (Pas de division) |
         | 0 | 0 | 0 | 1 | **1:2** |
         | 0 | 0 | 1 | 0 | **1:3** |
         | 0 | 0 | 1 | 1 | **1:4** |
         | 0 | 1 | 0 | 0 | **1:5** |
         | 0 | 1 | 0 | 1 | **1:6** |
         | 0 | 1 | 1 | 0 | **1:7** |
         | 0 | 1 | 1 | 1 | **1:8** |
         | 1 | 0 | 0 | 0 | **1:9** |
         | 1 | 0 | 0 | 1 | **1:10** |
         | 1 | 0 | 1 | 0 | **1:11** |
         | 1 | 0 | 1 | 1 | **1:12** |
         | 1 | 1 | 0 | 0 | **1:13** |
         | 1 | 1 | 0 | 1 | **1:14** |
         | 1 | 1 | 1 | 0 | **1:15** |
         | 1 | 1 | 1 | 1 | **1:16** |

      - **Bit 2 : `TMRxON` – Activation du Timerx**
         - **`0`** = **Désactivé**
         - **`1`** = **Activé**

      - **Bits 1-0 : `TxCKPS<1:0>` – Sélection du Pré-diviseur d'Horloge**
         | TxCKPS1 | TxCKPS0 | Valeur du Pré-diviseur |
         |---------|---------|------------------------|
         | 0 | 0 | **1:1** (Pas de division) |
         | 0 | 1 | **1:4** |
         | 1 | x | **1:16** |

   - #### Période de Timer `PRx`
 
      | Étapes                                       | En Mode Timer (`TMRxON = 1`)                                                    |
      |----------------------------------------------|:-------------------------------------------------------------------------------:|
      | **Étape 1 :** Période d’Horloge Interne | <div align="center">**$`T_H = \frac{4}{F_{osc}}`$**</div>                         |
      | **Étape 2 :** Choix du Pré-diviseur    | <div align="left">**$`\text{Prédiviseur} \in \{1, 4, 16\}`$** |
      | **Étape 3 :** Choix du Post-diviseur (Si Disponible) | <div align="left">**$`\text{Postdiviseur} \in \{1..16\}`$** |
      | **Étape 4 :** Valeur Période (`PRx`)     | <div align="center">**$`PRx = \frac{T_{x}}{\text{Prédiviseur} \times T_H \times Postdiviseur} - 1`$**</div> |
      | **Étape 5 :** Nombre d’Interruptions | <div align="center">**$`N_x = \frac{T_{donné}}{T_{x}}`$**</div> |

      > - Choisir **$`T_{x}`$** tel que **$`0 \le PRx \le 255`$**
      > - **Période d’un Incrément : $`T_{inc}​ = \text{Prediv} \times T_H`$**


   - #### Registres Associés (x = 2, 4, 6)
      <table>
        <thead>
          <tr>
            <th>Nom</th>
            <th>Bit 7</th>
            <th>Bit 6</th>
            <th>Bit 5</th>
            <th>Bit 4</th>
            <th>Bit 3</th>
            <th>Bit 2</th>
            <th>Bit 1</th>
            <th>Bit 0</th>
          </tr>
        </thead>
        <tbody align="center">
          <tr>
            <td><strong>TxCON</strong></td>
            <td>—</td>
            <td colspan="4">TxOUTPS&lt;3:0&gt;</td>
            <td>TMRxON</td>
            <td colspan="2">TxCKPS&lt;1:0&gt;</td>
          </tr>
          <tr>
            <td><strong>PRx</strong></td>
            <td align="center" colspan="8">Période du Timerx <strong>(8-bits)</strong></td>
          </tr>
          <tr>
            <td><strong>TMRx</strong></td>
            <td align="center" colspan="8">Compteur du Timerx <strong>(8-bits)</strong></td>
          </tr>
        </tbody>
      </table>
      
      > Consultez les sections suivantes pour la configuration :  
      > - **[Activation des interruptions (`PIEx`)](#registres-dactivation-pie1-à-pie5)**
      > - **[Drapeaux d'interruption (`PIRx`)](#registres-de-flags-pir1-à-pir5)**
      > - **[Priorités d'interruption (`IPRx`)](#registres-de-priorité-ipr1-à-ipr5)**