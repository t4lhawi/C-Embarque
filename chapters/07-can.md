# **7. Gestion de CAN**
Le **Convertisseur Analogique-Numérique (CAN)** permet de convertir une **Signal Analogique** en une **Valeur Numérique sur 10 bits** (0 à 1023).
>   - Entrées Analogiques multiplexées **(`AN0` à `AN27`)**
>   - Résultat Stocké dans **`ADRESH:ADRESL`**
>   - Références de Tension configurables (**$`V_{DD}`$, $`V_{SS}`$, $`V_{REF±}`$, $`FVR`$**)
>   - Peut générer une interruption en fin de Conversion

- ### Étapes de Conversion A/N

   | Étape | Action | Description |
   |-------|--------|-------------|
   | **1** | **[Configurer le Port](#4-ports-dentréesortie-es)** | • `TRISx = 1` (Entrée)<br>• `ANSELx = 1` (Analogique) |
   | **2** | **[Configurer le Module CAN](#registres-de-contrôle-2)** | • `ADCS` ([Vitesse](#adcon2---configuration-de-lhorloge-et-du-format))<br>• `PVCFG/NVCFG` ([Références](#adcon1---configuration-des-références-de-tension))<br>• `CHS` ([Canal](#adcono---sélection-de-canal-et-activation-adc))<br>• `ADFM` ([Format](#adcon2---configuration-de-lhorloge-et-du-format))<br>• `ACQT` ([Délai](#adcon2---configuration-de-lhorloge-et-du-format))<br>• `ADON = 1` ([Activation](#adcono---sélection-de-canal-et-activation-adc)) |
   | **3** | **[Configurer l'Interruption](#5-gestion-des-interruptions)** (Optionnel) | • `ADIF = 0`<br>• `ADIE = 1`<br>• `PEIE = 1`<br>• `GIE = 1` |
   | **4** | **Attendre Acquisition** | Attente du **TACQ** (Si Manuel) |
   | **5** | **Démarrer Conversion** | `GO/DONE = 1` |
   | **6** | **Attendre Fin** | • Vérifier `GO/DONE = 0`<br>• OU `ADIF = 1` |
   | **7** | **Lire Résultat** | Lecture `ADRESH:ADRESL` |
   | **8** | **Désactiver Drapeau (Flag)** | `ADIF = 0` (Si Interruption) |

  > - **Configuration (Étapes 1-3) :** Préparation des registres et du matériel
  > - **Exécution (Étapes 4-7) :** Lancement et lecture de la conversion
  > - **Nettoyage (Étapes 8) :** Gestion des interruptions

- ### Registres de Contrôle

   - #### `ADCONO` - Sélection de Canal et Activation ADC
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
            <td>—</td>
            <td colspan="5"><strong>CHS&lt;4:0&gt;</strong></td>
            <td><strong>GO/DONE</strong></td>
            <td><strong>ADON</strong></td>
          </tr>
        </tbody>
      </table>
      
      - **Bits 6-2 : `CHS<4:0>` – Sélection du Canal Analogique**
           | CHS4 | CHS3 | CHS2 | CHS1 | CHS0 | Canal | Broche |
           |------|------|------|------|------|-------|--------|
           | 0 | 0 | 0 | 0 | 0 | **AN0** | RA0 |
           | 0 | 0 | 0 | 0 | 1 | **AN1** | RA1 |
           | 0 | 0 | 0 | 1 | 0 | **AN2** | RA2 |
           | 0 | 0 | 0 | 1 | 1 | **AN3** | RA3 |
           | 0 | 0 | 1 | 0 | 0 | **AN4** | RA5 |
           | 0 | 0 | 1 | 0 | 1 | **AN5** | RE0 |
           | 0 | 0 | 1 | 1 | 0 | **AN6** | RE1 |
           | 0 | 0 | 1 | 1 | 1 | **AN7** | RE2 |
           | 0 | 1 | 0 | 0 | 0 | **AN8** | RB2 |
           | 0 | 1 | 0 | 0 | 1 | **AN9** | RB3 |
           | 0 | 1 | 0 | 1 | 0 | **AN10** | RB1 |
           | 0 | 1 | 0 | 1 | 1 | **AN11** | RB4 |
           | 0 | 1 | 1 | 0 | 0 | **AN12** | RB0 |
           | 0 | 1 | 1 | 0 | 1 | **AN13** | RB5 |
           | 0 | 1 | 1 | 1 | 0 | **AN14** | RB6 |
           | 0 | 1 | 1 | 1 | 1 | **AN15** | RB7 |
           | 1 | 0 | 0 | 0 | 0 | **AN16** | RC2 |
           | 1 | 0 | 0 | 0 | 1 | **AN17** | RC3 |
           | 1 | 0 | 0 | 1 | 0 | **AN18** | RC6 |
           | 1 | 0 | 0 | 1 | 1 | **AN19** | RC7 |
           | 1 | 0 | 1 | 0 | 0 | **AN20** | RD0 |
           | 1 | 0 | 1 | 0 | 1 | **AN21** | RD1 |
           | 1 | 0 | 1 | 1 | 0 | **AN22** | RD2 |
           | 1 | 0 | 1 | 1 | 1 | **AN23** | RD3 |
           | 1 | 1 | 0 | 0 | 0 | **AN24** | RD4 |
           | 1 | 1 | 0 | 0 | 1 | **AN25** | RD5 |
           | 1 | 1 | 0 | 1 | 0 | **AN26** | RD6 |
           | 1 | 1 | 0 | 1 | 1 | **AN27** | RD7 |
           | 1 | 1 | 1 | 0 | 0 | **RÉSERVÉ** | — |
           | 1 | 1 | 1 | 0 | 1 | **CTMU** | Module CTMU interne |
           | 1 | 1 | 1 | 1 | 0 | **CNA** | Module DAC interne |
           | 1 | 1 | 1 | 1 | 1 | **FVR BUF2** | Référence FVR (1.024V/2.048V/4.096V) |
      
      - **Bit 1 : `GO/DONE` – Statut de Conversion A/D**
        - **`1`** = **Conversion en cours** – Démarre une nouvelle conversion si écrit à `1`
        - **`0`** = **Conversion terminée** – Mis à `0` automatiquement par le matériel après conversion
        
        > - Écrire `1` pour démarrer une conversion.
        > - Lire `0` pour vérifier que la conversion est terminée.
      
      - **Bit 0 : `ADON` – Activation du Convertisseur A/D**
        - **`1`** = **ADC activé** – Alimentation et circuits activés
        - **`0`** = **ADC désactivé** – Économie d'énergie
   
   
   - #### `ADCON1` - Configuration des Références de Tension
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
            <td><strong>TRIGSEL</strong></td>
            <td>—</td>
            <td>—</td>
            <td>—</td>
            <td colspan="2"><strong>PVCFG&lt;1:0&gt;</strong></td>
            <td colspan="2"><strong>NVCFG&lt;1:0&gt;</strong></td>
          </tr>
        </tbody>
      </table>
      
      - **Bit 7 : `TRIGSEL` – Sélection du Déclencheur Spécial**
        - **`1`** = **CTMU** – Déclenchement par le module CTMU (Charge Time Measurement Unit)
        - **`0`** = **CCP5** – Déclenchement par le module Capture/Compare/PWM 5
      
      - **Bits 3-2 : `PVCFG<1:0>` – Configuration de la Référence Positive VREF+**
        | PVCFG1 | PVCFG0 | Référence Positive VREF+ |
        |--------|--------|---------------------------|
        | 0 | 0 | **VDD** – Tension d'alimentation du microcontrôleur |
        | 0 | 1 | **Broche VREF+ (RA3)** – Référence externe |
        | 1 | 0 | **FVR BUF2** – Référence interne fixe (FVRCON) |
        | 1 | 1 | **RÉSERVÉ** (par défaut = VDD) |
      
      - **Bits 1-0 : `NVCFG<1:0>` – Configuration de la Référence Négative VREF-**
        | NVCFG1 | NVCFG0 | Référence Négative VREF- |
        |--------|--------|---------------------------|
        | 0 | 0 | **VSS** – Masse (0V) |
        | 0 | 1 | **Broche VREF- (RA2)** – Référence externe |
        | 1 | 0 | **RÉSERVÉ** (par défaut = VSS) |
        | 1 | 1 | **RÉSERVÉ** (par défaut = VSS) |
   
   
   - #### `ADCON2` - Configuration de l'Horloge et du Format
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
            <td><strong>ADFM</strong></td>
            <td>—</td>
            <td colspan="3"><strong>ACQT&lt;2:0&gt;</strong></td>
            <td colspan="3"><strong>ADCS&lt;2:0&gt;</strong></td>
          </tr>
        </tbody>
      </table>
      
      - **Bit 7 : `ADFM` – Format du Résultat de Conversion**
              <table>
                 <tr>
                    <th colspan="9">ADRESH (High Byte)</th>
                    <th colspan="8">ADRESL (Low Byte)</th>
                 </tr>
                 <tr>
                     <td rowspan="2"><strong>ADFM=0</strong></td>
                     <td><strong>Bit 7</td>
                     <td><strong>Bit 6</td>
                     <td><strong>Bit 5</td>
                     <td><strong>Bit 4</td>
                     <td><strong>Bit 3</td>
                     <td><strong>Bit 2</td>
                     <td><strong>Bit 1</td>
                     <td><strong>Bit 0</td>
                     <td><strong>Bit 7</td>
                     <td><strong>Bit 6</td>
                     <td>Bit 5</td>
                     <td>Bit 4</td>
                     <td>Bit 3</td>
                     <td>Bit 2</td>
                     <td>Bit 1</td>
                     <td>Bit 0</td>
                 </tr>
                 <tr>
                     <td colspan="8" align="center">MSB ← 10-bit A/D Result → LSB</td>
                     <td colspan="2" align="center">Bits [1:0]</td>
                     <td colspan="6" align="center">―</td>
                 </tr>
                 <tr>
                     <td rowspan="2"><strong>ADFM=1</strong></td>
                     <td>Bit 7</td>
                     <td>Bit 6</td>
                     <td>Bit 5</td>
                     <td>Bit 4</td>
                     <td>Bit 3</td>
                     <td>Bit 2</td>
                     <td><strong>Bit 1</td>
                     <td><strong>Bit 0</td>
                     <td><strong>Bit 7</td>
                     <td><strong>Bit 6</td>
                     <td><strong>Bit 5</td>
                     <td><strong>Bit 4</td>
                     <td><strong>Bit 3</td>
                     <td><strong>Bit 2</td>
                     <td><strong>Bit 1</td>
                     <td><strong>Bit 0</td>
                 </tr>
                 <tr>
                     <td colspan="6" align="center">―</td>
                     <td colspan="2" align="center">Bits [9:8]</td>
                     <td colspan="8" align="center">MSB ← 10-bit A/D Result → LSB</td>
                 </tr>
               </table>
      
      - **Bits 5-3 : `ACQT<2:0>` – Sélection du Temps d'Acquisition**
        | ACQT2 | ACQT1 | ACQT0 | Temps d'Acquisition |
        |-------|-------|-------|---------------------|
        | 0 | 0 | 0 | **0 TAD** |
        | 0 | 0 | 1 | **2 TAD** |
        | 0 | 1 | 0 | **4 TAD** |
        | 0 | 1 | 1 | **6 TAD** |
        | 1 | 0 | 0 | **8 TAD** |
        | 1 | 0 | 1 | **12 TAD** |
        | 1 | 1 | 0 | **16 TAD** |
        | 1 | 1 | 1 | **20 TAD** |
      
        > - **TAD** = Temps d'Horloge de CAN (ADC Clock Period)
        > - **TACQ** = Temps d'Acquisition du CAN (ADC Acquisition Time)
      
      - **Bits 2-0 : `ADCS<2:0>` – Sélection de l'Horloge CAN**
        | ADCS2 | ADCS1 | ADCS0 | Horloge CAN (TAD) | Formule       |
        |-------|-------|-------|-------------------| :-------------: |
        | 0 | 0 | 0 | **Fosc/2** | $`T_{AD} = 2 \times T_{osc}`$    |
        | 1 | 0 | 0 | **Fosc/4** | $`T_{AD} = 4 \times T_{osc}`$    |
        | 0 | 0 | 1 | **Fosc/8** | $`T_{AD} = 8 \times T_{osc}`$    |
        | 1 | 0 | 1 | **Fosc/16** | $`T_{AD} = 16 \times T_{osc}`$  |
        | 0 | 1 | 0 | **Fosc/32** | $`T_{AD} = 32 \times T_{osc}`$  |
        | 1 | 1 | 0 | **Fosc/64** | $`T_{AD} = 64 \times T_{osc}`$  |
        | x | 1 | 1 | **FRC** |        ―             |
      
         >   | **Étape** | **Action**                    | **Formule**                             |
         >   | --------- | ----------------------------- | --------------------------------------- |
         >   | 1         | **Période d’Horloge**         | $`T_{osc} = \dfrac{1}{F_{osc}}`$        |
         >   | 2         | **Période du CAN**            | $`T_{AD} = \text{ADCS} \times T_{osc}`$ |
         >   | 3         | **Choisir `ADCS`**            | $`T_{AD} \ge 1\mu s`$                  |
         
         > - **Plus Petit Diviseur Valide = Vitesse Maximale**
         > - **Modifier `ACQT` Ne Change pas la Vitesse de Conversion**



   - #### `FVRCON` - Contrôle de la Référence de Tension Fixe
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
            <td><strong>FVREN</strong></td>
            <td><strong>FVRST</strong></td>
            <td colspan="2"><strong>FVRS&lt;1:0&gt;</strong></td>
            <td>—</td>
            <td>—</td>
            <td>—</td>
            <td>—</td>
          </tr>
        </tbody>
      </table>
      
      - **Bit 7 : `FVREN` – Activation de la Référence de Tension Fixe**
        - **`0`** = **Désactivé** – Le module FVR est éteint (économie d'énergie)
        - **`1`** = **Activé** – Le module FVR est alimenté et opérationnel
      
      - **Bit 6 : `FVRST` – Indicateur de Prêt du FVR**
        - **`0`** = **Non prêt** – La sortie FVR n'est pas stable ou le module est désactivé
        - **`1`** = **Prêt** – La tension de référence est stable et peut être utilisée
        
        > **Note** : Ce bit est **lecture seule**. Il faut attendre qu'il passe à `1` après l'activation du FVR avant d'utiliser la référence.
      
      - **Bits 5-4 : `FVRS<1:0>` – Sélection du Niveau de Tension de Sortie**
        | FVRS1 | FVRS0 | Gain | Tension de Sortie (Typique) |
        |-------|-------|------|-----------------------------|
        | 0 | 0 | **Désactivé** | — |
        | 0 | 1 | **1×** | 1,024 V |
        | 1 | 0 | **2×** | 2,048 V |
        | 1 | 1 | **4×** | 4,096 V |
        
        > **Application** : 
        > - **1,024 V** : Pour CAN (ADC) basse tension
        > - **2,048 V / 4,096 V** : Pour comparateurs analogiques ou CAN haute précision

- ### Registres Associés
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
         <td><strong>ADCON0</strong></td>
         <td>—</td>
         <td align="center" colspan="5">CHS&lt;4:0&gt;</td>
         <td>GO/DONE</td>
         <td>ADON</td>
       </tr>
       <tr>
         <td><strong>ADCON1</strong></td>
         <td>TRIGSEL</td>
         <td>—</td>
         <td>—</td>
         <td>—</td>
         <td align="center" colspan="2">PVCFG&lt;1:0&gt;</td>
         <td align="center" colspan="2">NVCFG&lt;1:0&gt;</td>
       </tr>
       <tr>
         <td><strong>ADCON2</strong></td>
         <td>ADFM</td>
         <td>—</td>
         <td align="center" colspan="3">ACQT&lt;2:0&gt;</td>
         <td align="center" colspan="3">ADCS&lt;2:0&gt;</td>
       </tr>
       <tr>
         <td><strong>ADRESH</strong></td>
         <td align="center" colspan="8">A/D Result, High Byte</td>
       </tr>
       <tr>
         <td><strong>ADRESL</strong></td>
         <td align="center" colspan="8">A/D Result, Low Byte</td>
       </tr>
     </tbody>
   </table>
   
   > Consultez les sections suivantes pour la configuration :
   > - **[Ports d’Entrée/Sortie (E/S) (`TRISx`, `ANSELx`)](#4-ports-dentréesortie-es)**
   > - **[Activation des interruptions (`PIEx`)](#registres-dactivation-pie1-à-pie5)**
   > - **[Drapeaux d'interruption (`PIRx`)](#registres-de-flags-pir1-à-pir5)**
   > - **[Priorités d'interruption (`IPRx`)](#registres-de-priorité-ipr1-à-ipr5)**



- ### Fonctionnes Avancé MikroC
   | **Fonction**                  | **Description**                                |
   | ----------------------------- | ---------------------------------------------- |
   | **`ADC_Init()`**              | **Initialise** le Module CAN.                      |
   | **`ADC_Get_Sample(channel)`** | **Lit Un** Échantillon sur le Canal Sélectionné.   |
   | **`ADC_Read(channel)`**       | **Initialise** et **Lit** le CAN en une Seule Commande. |
