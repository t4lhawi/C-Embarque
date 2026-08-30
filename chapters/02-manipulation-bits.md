## **2. Manipulation des Bits**

- ### Représentation Binaire d’un Octet (`char`)
   Un type `char` est codé sur 8 bits, numérotés de b0 à b7.
   <table>
     <thead>
       <tr>
         <th>b7</th>
         <th>b6</th>
         <th>b5</th>
         <th>b4</th>
         <th>b3</th>
         <th>b2</th>
         <th>b1</th>
         <th>b0</th>
       </tr>
     </thead>
     <tbody>
       <tr>
         <td><strong>MSB</strong></td>
         <td colspan="6"></td>
         <td><strong>LSB</strong></td>
       </tr>
     </tbody>
   </table>
   
   > - `LSB` : bit de poids Faible
   > - `MSB` : bit de poids Fort

- ### **Opérations Bit à Bit (Bitwise)**

   | Opération          | Symbole | Code             | Description                                                                 |
   | ------------------ | ------- | ---------------- | --------------------------------------------------------------------------- |
   | **AND bit à bit**  | `&`     | `a = x & y`      | Compare bit par bit. Le résultat vaut **1 seulement si les deux bits = 1**. |
   | **OR bit à bit**   | `\|`    | `a = x \| y`     | Compare bit par bit. Le résultat vaut **1 si au moins un bit = 1**.         |
   | **XOR bit à bit**  | `^`     | `a = x ^ y`      | Résultat vaut **1 si les bits sont différents**.                            |
   | **NOT (négation)** | `~`     | `a = ~x`         | Inverse tous les bits (0→1, 1→0).                                           |


- ### **Opérations Courantes sur un Bit Précis**

   | Opération                        | Code                        | Description                       |
   | -------------------------------- | --------------------------- | --------------------------------- |
   | **Mettre un bit à 1 (SET)**      | `x \|= (1 << n)`            | Active le bit *n*.                |
   | **Mettre un bit à 0 (CLEAR)**    | `x &= ~(1 << n)`            | Désactive le bit *n*.             |
   | **Inversion d’un bit (TOGGLE)**  | `x ^= (1 << n)`             | Complémente le bit n : 0 ↔ 1.     |
   | **Extraction d’un bit**          | `(x >> n) & 1`              | Extrait l’état du bit (0 ou 1).   |
   | **Test logique d’un bit (TEST)** | `if (x & (1 << n))`         | Vrai si le bit *n* vaut 1.        |
   | **Copier la valeur d’un bit**    | `bit = (x & (1 << n)) != 0` | Copie la valeur du bit n dans une variable.  |
   | **Échange de deux bits (SWAP)**  | `char bi = (x >> i) & 1;`<br> `char bj = (x >> j) & 1;`<br> `x = (x & ~((1 << i) \| (1 << j))) \| (bi << j) \| (bj << i);` | Échange les valeurs des bits *i* et *j*. |




- ### **Décalages de Bits**

   | Opération             | Symbole | Code     | Description                                                                          |
   | --------------------- | ------- | -------- | ------------------------------------------------------------------------------------ |
   | **Décalage à Gauche** | `<<`    | `x << n` | Décale les bits vers la gauche (≈ $`x \times 2^{n}`$).                               |
   | **Décalage à Droite** | `>>`    | `x >> n` | Décale les bits vers la droite (≈ $`\left\lfloor \dfrac{x}{2^{n}} \right\rfloor`$).  |



- ### **Rotations de Bits**

   | Opération             | Code                         | Description                                                            |
   | --------------------- | ---------------------------- | ---------------------------------------------------------------------- |
   | **Rotation à Gauche** | `(x << n) \| (x >> (8 - n))` | Décalage circulaire vers la gauche (valeur conservée modulo $`2^8`$)   |
   | **Rotation à Droite** | `(x >> n) \| (x << (8 - n))` | Décalage circulaire vers la droite (valeur conservée modulo $`2^8`$)   |

   > - Les rotations conservent tous les bits, contrairement aux décalages.
   > - Pour un `char`, on considère **8 bits** (adapter 8 selon la taille du type).

- ### **Masques de Bits (Bit Masks)**

   | Opération                          | Code             | Description                           |
   | ---------------------------------- | ---------------- | ------------------------------------- |
   | **Créer un masque**                | `mask = 1 << n`  | Masque avec seulement le bit n actif. |
   | **Garder seulement certains bits** | `x & mask`       | Filtre tout sauf les bits du masque.  |
   | **Mettre certains bits à 1**       | `x \| mask`      | Force les bits du masque à 1.         |
   | **Mettre certains bits à 0**       | `x & ~mask`      | Force les bits du masque à 0.         |


   > `|=` → mettre à **1**
   
   > `&=~` → mettre à **0**
   
   > `^=` → **toggle**
   
   > `&` → tester
   
   > `<<` / `>>` → décaler