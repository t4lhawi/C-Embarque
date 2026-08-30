# **8. Gestion de CNA**
Le **Convertisseur Numérique-Analogique (CNA)** convertit une **Donnée Numérique** en une **Tension Analogique** proportionnelle, définie par des Tensions de Référence, avec un Nombre Fini de Niveaux (**32** pour un CNA **`5-bits`**).


- ## Étapes de Conversion N/A
   | **Étape** | **Action**                                  | **Description**                                                                                                         |
   | --------- | ------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------- |
   | **1**     | **Source de Référence Positive** | Sélection de $`V_{SRC+}`$ :<br>• **VDD**<br>• **VREF+ Externe**<br>• **FVR BUF1**                                         |
   | **2**     | **Source de Référence Négative** | Sélection de $`V_{SRC-}`$ :<br>• **VSS**<br>• **VREF− Externe**                                                           |
   | **3**     | **Valeur Numérique du CNA**      | Réglage de `DACR<4:0>` (0 → 31), Déterminant le Niveau de Tension de Sortie                                             |
   | **4**     | **Tension de Sortie**           | $`V_{OUT} = \left(\dfrac{V_{SRC+} - V_{SRC-}}{2^5}\right) \times DACR<4:0> + V_{SRC-}`$                                 |
   | **5**     | **Destination de la Sortie**     | • Entrée Positive d’un **Comparateur**<br>• Module **CAN (ADC)**<br>• Broche **DACOUT (RA2)** |


- ## Registres de Contrôle

   - ### `VREFCON1` – Contrôle de la Référence de Tension (CNA)
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
           <td><strong>DACEN</strong></td>
           <td><strong>DACLPS</strong></td>
           <td><strong>DACOE</strong></td>
           <td>—</td>
           <td colspan="2"><strong>DACPSS&lt;1:0&gt;</strong></td>
           <td>—</td>
           <td><strong>DACNSS</strong></td>
         </tr>
       </tbody>
      </table>
   
      - **Bit 7 : `DACEN` – Activation du CNA**
         - **`0`** = **Désactivé** – Le module CNA est arrêté
         - **`1`** = **Activé** – Le module DAC est opérationnel
      
      - **Bit 6 : `DACLPS` – Sélection de la Source de Tension (Low-Power)**
         - **`0`** = **Référence Négative du DAC sélectionnée  $`V_{SRC-}`$**
         - **`1`** = **Référence Positive du DAC sélectionnée  $`V_{SRC+}`$**
      
      - **Bit 5 : `DACOE` – Activation de la Sortie CNA**
         - **`0`** = **Sortie désactivée** – La tension CNA n’est pas disponible sur la broche `DACOUT`
         - **`1`** = **Sortie activée** – La tension DAC est disponible sur la broche `DACOUT`
      
      - **Bits 3-2 : `DACPSS<1:0>` – Sélection de la Source Positive du CNA**
      
         | DACPSS1 | DACPSS0 | Source de Référence Positive  |
         | ------- | ------- | ----------------------------- |
         | 0       | 0       | **VDD**                       |
         | 0       | 1       | **VREF+**                     |
         | 1       | 0       | **Sortie FVR BUF1**           |
         | 1       | 1       | **Réservé – Ne pas utiliser** |
      
      - **Bit 0 : `DACNSS` – Sélection de la Source Négative du CNA**
         - **`0`** = **VSS**
         - **`1`** = **VREF−**

   - ### `VREFCON2` – Contrôle de la Référence de Tension (Valeur de Sortie CNA)
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
           <td colspan="5"><strong>DACR&lt;4:0&gt;</strong></td>
         </tr>
       </tbody>
      </table>
      
      - **Bits 4–0 : `DACR<4:0>` – Sélection de la Tension de Sortie du CNA**
         - Ces bits définissent la **valeur numérique** appliquée au convertisseur numérique–analogique (CNA).
         - Ils permettent de régler la tension de sortie du CNA sur **32 niveaux** possibles (5 bits).
      
           > **$`V_{OUT} = \left(\dfrac{V_{SRC+} - V_{SRC-}}{2^5}\right) \times DACR<4:0> + V_{SRC-}`$**


- ## Registres Associés

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
           <tr align="center">
               <td><strong>VREFCON0</strong></td>
               <td>FVREN</td>
               <td>FVRST</td>
               <td colspan="2">FVRS&lt;1:0&gt;</td>
               <td>—</td>
               <td>—</td>
               <td>—</td>
               <td>—</td>
           </tr>
           <tr align="center">
               <td><strong>VREFCON1</strong></td>
               <td>DACEN</td>
               <td>DACLPS</td>
               <td>DACOE</td>
               <td>—</td>
               <td colspan="2">DACPSS&lt;1:0&gt;</td>
               <td>—</td>
               <td>DACNSS</td>
           </tr>
           <tr align="center">
               <td><strong>VREFCON2</strong></td>
               <td>—</td>
               <td>—</td>
               <td>—</td>
               <td>—</td>
               <td>—</td>
               <td colspan="3">DACR&lt;4:0&gt;</td>
           </tr>
       </tbody>
   </table>
