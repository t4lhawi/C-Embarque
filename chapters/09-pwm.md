## **9. Gestion de PWM**
La **Modulation de Largeur d'Impulsion (PWM)** est une méthode permettant de fournir de l'énergie à une charge en basculant rapidement entre les états logiques ‘1’ et ‘0’. 
> Cette Fonction est Gérée par les Périphériques **Capture/Compare/PWM (CCP)**.


- ### Caractéristiques du PWM
   | **Caractéristique**     | **Description**                                                                           |
   | ----------------------- | ----------------------------------------------------------------------------------------- |
   | **Modules disponibles** | **5 modules PWM** :<br>• **3 modules ECCP** (Enhanced)<br>• **2 modules CCP** (standards) |
   | **Période**             | Durée totale d’un cycle PWM (**ON + OFF**)                                                |
   | **Rapport Cyclique**    | Pourcentage du temps où le signal est à l’état haut (**0 % à 100 %**)                     |
   | **Résolution**          | Précision du signal PWM pouvant atteindre **10 bits** (**1024 pas**)                      |

   > | <div align="center">**$`\text{Période PWM} = (PRx + 1) \times 4 \times T_{OSC} \times \text{Prescaler}`$**              |
   > | :---------------------------------------------------------------------------------------------------------------------: |
   > | <div align="center">**$`\text{Largeur d’impulsion} = (CCPRxL:CCPxCON<5:4>) \times T_{OSC} \times \text{Prescaler}`$**   |
   > | <div align="center">**$`\text{Rapport Cyclique} = \frac{CCPRxL:CCPxCON<5:4>}{4 \times (PRx + 1)}`$**                    |
   > | <div align="center">**$`\text{Résolution} = \frac{\ln \big( 4 \cdot (PRx + 1) \big)}{\ln 2} \text{bits}`$**             |



- ### Étapes de Configuration

   | **Étape** | **Action**                                   | **Description**                                                                  |
   | --------- | -------------------------------------------- | -------------------------------------------------------------------------------- |
   | **1**     | Désactiver la Sortie PWM                     | • `TRISx = 1` (Broche PWM configurée en **entrée**)                              |
   | **2**     | Sélectionner le Timer                        | • Choisir **Timer2 / Timer4 / Timer6**<br>• Configuration via `CCPTMRSx`         |
   | **3**     | Configurer la Période PWM                    | • Charger la Période dans `PRx`                                                  |
   | **4**     | Configurer le Module PWM                     | • Activer le Mode PWM dans `CCPxCON`                                             |
   | **5**     | Régler le Rapport Cyclique                   | • `CCPRxL` (8-bits MSB)<br>• `CCPxCON<5:4>` (2 bits LSB)                         |
   | **6**     | Démarrer le Timer                            | • Régler le Pré-diviseur<br>• `TMRxON = 1`                                       |
   | **7**     | Activer la sortie PWM                        | • Attendre le **Premier Débordement** du Timer<br>• `TRISx = 0` (Sortie activée) |



- ### Registres de Contrôle

   - #### `CCPxCON` – Registre de Contrôle du Module CCPx Standard (x = 1, 2, 3, 4, 5)
      <table>
         <tr>
            <td colspan="8" align="center"><strong>x = 1, 2, 3</strong></td>
         </tr>
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
          <tr>
              <td colspan="2" align="center"><strong>PxM&lt;1:0&gt;</strong></td>
              <td colspan="2" align="center"><strong>DCxB&lt;1:0&gt;</strong></td>
              <td colspan="4" align="center"><strong>CCPxM&lt;3:0&gt;</strong></td>
          </tr>
          <tr>
            <td colspan="8" align="center"><strong>x = 4, 5</strong></td>
          </tr>
          <tr align="center">
            <td>—</td>
            <td>—</td>
            <td colspan="2"><strong>DCxB&lt;1:0&gt;</strong></td>
            <td colspan="4"><strong>CCPxM&lt;3:0&gt;</strong></td>
          </tr>
      </table>
      
      - **Bits 7-6 : `PxM<1:0>` – Configuration de la sortie PWM (ECCP uniquement)**
          - Configure le mode de sortie PWM pour les modules **ECCP (CCP1-3)**. Non présent sur **CCP4/5**.
      
      - **Bits 5-4 : `DCxB<1:0>` – Bits de Poids Faible du Rapport Cyclique PWM**
         - Ces deux bits constituent les bits de poids faible (LSb) du rapport cyclique PWM. Les 8 bits de poids fort (MSb) se trouvent dans le registre `CCPRxL`.
      
      - **Bits 3-0 : `CCPxM<3:0>` – Sélection du Mode du Module ECCPx**
         - **`11xx` = Mode PWM**


            > <table>
            >     <tr>
            >         <th colspan="10">Rapport Cyclique PWM (10 bits)</th>
            >     </tr>
            >     <tr>
            >         <td colspan="8" align="center"><strong>CCPRxL (MSB - Bits [9:2])</strong></td>
            >         <td colspan="2" align="center"><strong>DCxB&lt;1:0&gt; (LSB - Bits [1:0])</strong></td>
            >     </tr>
            >     <tr>
            >         <td align="center">Bit 9<br>(MSB)</td>
            >         <td align="center">Bit 8</td>
            >         <td align="center">Bit 7</td>
            >         <td align="center">Bit 6</td>
            >         <td align="center">Bit 5</td>
            >         <td align="center">Bit 4</td>
            >         <td align="center">Bit 3</td>
            >         <td align="center">Bit 2</td>
            >         <td align="center">Bit 1</td>
            >         <td align="center">Bit 0<br>(LSB)</td>
            >     </tr>
            > </table>



   - #### `CONFIG3H` – Configuration PWM et des Entrées/Sorties (CONFIG3H)
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
            <td><strong>MCLRE</strong></td>
            <td>—</td>
            <td><strong>P2BMX</strong></td>
            <td><strong>T3CMX</strong></td>
            <td><strong>HFOFST</strong></td>
            <td><strong>CCP3MX</strong></td>
            <td><strong>PBADEN</strong></td>
            <td><strong>CCP2MX</strong></td>
          </tr>
        </tbody>
      </table>
      
      - **Bits associés à la sélection des sorties CCP :**
           <table>
             <thead>
               <tr align="center">
                 <th>Module CCP</th>
                 <th>Bit de Configuration</th>
                 <th>Broche I/O lorsque Bit = 0</th>
                 <th>Broche I/O lorsque Bit = 1</th>
               </tr>
             </thead>
             <tbody>
               <tr align="center">
                 <td>CCP1</td>
                 <td>—</td>
                 <td colspan="2" align="center"><strong>RB3</strong> (fixe)</td>
               </tr>
               <tr align="center">
                 <td>CCP2</td>
                 <td><strong>CCP2MX</strong></td>
                 <td><strong>RB3</strong></td>
                 <td><strong>RC1</strong></td>
               </tr>
               <tr align="center">
                 <td>CCP3</td>
                 <td><strong>CCP3MX</strong></td>
                 <td><strong>RE0</strong></td>
                 <td><strong>RB5</strong></td>
               </tr>
               <tr align="center">
                 <td>CCP4</td>
                 <td>—</td>
                 <td colspan="2" align="center"><strong>RD1</strong> (fixe)</td>
               </tr>
               <tr align="center">
                 <td>CCP5</td>
                 <td>—</td>
                 <td colspan="2" align="center"><strong>RE2</strong> (fixe)</td>
               </tr>
             </tbody>
           </table>


   - #### `CCPTMRS0` – Registre de Sélection du Timer pour PWM 0
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
            <td colspan="2"><strong>C3TSEL&lt;1:0&gt;</strong></td>
            <td>—</td>
            <td colspan="2"><strong>C2TSEL&lt;1:0&gt;</strong></td>
            <td>—</td>
            <td colspan="2"><strong>C1TSEL&lt;1:0&gt;</strong></td>
          </tr>
        </tbody>
      </table>
      
      - **Bits 7-6 : `C3TSEL<1:0>` – Sélection du Timer pour CCP3**
        | C3TSEL1 | C3TSEL0 | Modes Capture/Compare | Mode PWM |
        |---------|---------|------------------------|----------|
        | 0 | 0 | Timer1 | Timer2 |
        | 0 | 1 | Timer3 | Timer4 |
        | 1 | 0 | Timer5 | Timer6 |
        | 1 | 1 | **RÉSERVÉ** | |
      
      - **Bits 4-3 : `C2TSEL<1:0>` – Sélection du Timer pour CCP2**
        | C2TSEL1 | C2TSEL0 | Modes Capture/Compare | Mode PWM |
        |---------|---------|------------------------|----------|
        | 0 | 0 | Timer1 | Timer2 |
        | 0 | 1 | Timer3 | Timer4 |
        | 1 | 0 | Timer5 | Timer6 |
        | 1 | 1 | **RÉSERVÉ** | |
      
      - **Bits 1-0 : `C1TSEL<1:0>` – Sélection du Timer pour CCP1**
        | C1TSEL1 | C1TSEL0 | Modes Capture/Compare | Mode PWM |
        |---------|---------|------------------------|----------|
        | 0 | 0 | Timer1 | Timer2 |
        | 0 | 1 | Timer3 | Timer4 |
        | 1 | 0 | Timer5 | Timer6 |
        | 1 | 1 | **RÉSERVÉ** | |

   - #### `CCPTMRS1` – Registre de Sélection du Timer pour PWM 1
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
            <td>—</td>
            <td>—</td>
            <td>—</td>
            <td colspan="2"><strong>C5TSEL&lt;1:0&gt;</strong></td>
            <td colspan="2"><strong>C4TSEL&lt;1:0&gt;</strong></td>
          </tr>
        </tbody>
      </table>
      
      - **Bits 3-2 : `C5TSEL<1:0>` – Sélection du Timer pour CCP5**
        | C5TSEL1 | C5TSEL0 | Modes Capture/Compare | Mode PWM |
        |---------|---------|------------------------|----------|
        | 0 | 0 | Timer1 | Timer2 |
        | 0 | 1 | Timer3 | Timer4 |
        | 1 | 0 | Timer5 | Timer6 |
        | 1 | 1 | **RÉSERVÉ** | |
      
      - **Bits 1-0 : `C4TSEL<1:0>` – Sélection du Timer pour CCP4**
        | C4TSEL1 | C4TSEL0 | Modes Capture/Compare | Mode PWM |
        |---------|---------|------------------------|----------|
        | 0 | 0 | Timer1 | Timer2 |
        | 0 | 1 | Timer3 | Timer4 |
        | 1 | 0 | Timer5 | Timer6 |
        | 1 | 1 | **RÉSERVÉ** | |




- ### Registres Associés
   <table>
     <thead>
       <tr align="center">
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
         <td><strong>CCPxCON (x = 1, 2, 3)</strong></td>
         <td>—</td>
         <td>—</td>
         <td colspan="2"><strong>DCxB&lt;1:0&gt;</strong></td>
         <td colspan="4"><strong>CCPxM&lt;3:0&gt;</strong></td>
       </tr>
         <tr>
           <td><strong>CCPxCON (x = 4, 5)</strong></td>
           <td colspan="2" align="center"><strong>PxM&lt;1:0&gt;</strong></td>
           <td colspan="2" align="center"><strong>DCxB&lt;1:0&gt;</strong></td>
           <td colspan="4" align="center"><strong>CCPxM&lt;3:0&gt;</strong></td>
          </tr>
       </tr>
       <tr>
           <td><strong>CCPTMRS0</strong></td>
           <td colspan="2" align="center"><strong>C3TSEL&lt;1:0&gt;</strong></td>
           <td align="center">—</td>
           <td colspan="2" align="center"><strong>C2TSEL&lt;1:0&gt;</strong></td>
           <td align="center">—</td>
           <td colspan="2" align="center"><strong>C1TSEL&lt;1:0&gt;</strong></td>
       </tr>
       <tr>
           <td><strong>CCPTMRS1</strong></td>
           <td align="center">—</td>
           <td align="center">—</td>
           <td align="center">—</td>
           <td align="center">—</td>
           <td colspan="2" align="center"><strong>C5TSEL&lt;1:0&gt;</strong></td>
           <td colspan="2" align="center"><strong>C4TSEL&lt;1:0&gt;</strong></td>
       </tr>
     </tbody>
   </table>
   
   > Consultez les sections suivantes pour la configuration :
   > - **[Ports d’Entrée/Sortie (E/S) (`TRISx`)](#4-ports-dentréesortie-es)**
   > - **[Activation des interruptions (`PIEx`)](#registres-dactivation-pie1-à-pie5)**
   > - **[Drapeaux d'interruption (`PIRx`)](#registres-de-flags-pir1-à-pir5)**
   > - **[Priorités d'interruption (`IPRx`)](#registres-de-priorité-ipr1-à-ipr5)**
   > - **[Gestion des Timers (`TMRx`, `TxCON`, `PRx`)](#6-gestion-des-timers)**

- ### Fonctionnes Avancé MikroC
   | **Fonction**             | **Description**                                  |
   | ------------------------ | ------------------------------------------------ |
   | **`PWM1_Init(freq)`**    | **Initialise** le Module PWM1 à la Fréquence `freq`. |
   | **`PWM1_Set_Duty(val)`** | **Définit** le Rapport Cyclique du PWM.              |
   | **`PWM1_Start()`**       | **Démarre** le Signal PWM.                           |
   | **`PWM1_Stop()`**        | **Arrête** le Signal PWM.                            |