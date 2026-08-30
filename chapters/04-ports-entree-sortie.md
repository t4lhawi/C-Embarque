# **4. Ports d’Entrée/Sortie (E/S)**

- ### Registres de Contrôle

   | Registre    | Fonction                                             | Configuration                                    |
   | ----------- | ---------------------------------------------------- | ------------------------------------------------ |
   | **PORTx**   | Lecture/Écriture logique réel des broches            | Entrée / Sortie                                  |
   | **LATx**    | Registre tampon (Latch) pour une écriture **Stable** | Sortie Uniquement                                |
   | **TRISx**   | Direction du Port                                    | 1 = Entrée<br>0 = Sortie                         |
   | **ANSELx**  | Sélection du Mode Analogique ou Numérique            | 1 = **Entrée** Analogique<br>0 = Numérique (Digital) |
   | **SLRCONx** | Contrôle du Slew Rate (réduction des EMI)            | Sortie (selon port / MCU)                        |

   > - **Lire** avec `PORTx`, **Écrire** avec `LATx` pour Évite Risque de **Read-Modify-Write (RMW)**
   > - `ANSELx = 1` ⇒ Entrée Analogique ⇒ `TRISx = 1` **Obligatoire !!**
   > - Pour toute E/S Digitale ⇒ `ANSELx = 0`
   > - Manipulation des Sorties **Toujours via `LATx`**


- ### Registres Associés au PORTA

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
         <td><strong>ANSELA</strong></td>
         <td>—</td>
         <td>—</td>
         <td>ANSA5</td>
         <td>—</td>
         <td>ANSA3</td>
         <td>ANSA2</td>
         <td>ANSA1</td>
         <td>ANSA0</td>
       </tr>
       <tr>
         <td><strong>CM1CON0</strong></td>
         <td>C1ON</td>
         <td>C1OUT</td>
         <td>C1OE</td>
         <td>C1POL</td>
         <td>C1SP</td>
         <td>C1R</td>
         <td align="center" colspan="2">C1CH&lt;1:0&gt;</td>
       </tr>
       <tr>
         <td><strong>CM2CON0</strong></td>
         <td>C2ON</td>
         <td>C2OUT</td>
         <td>C2OE</td>
         <td>C2POL</td>
         <td>C2SP</td>
         <td>C2R</td>
         <td align="center" colspan="2">C2CH&lt;1:0&gt;</td>
       </tr>
       <tr>
         <td><strong>LATA</strong></td>
         <td>LATA7</td>
         <td>LATA6</td>
         <td>LATA5</td>
         <td>LATA4</td>
         <td>LATA3</td>
         <td>LATA2</td>
         <td>LATA1</td>
         <td>LATA0</td>
       </tr>
       <tr>
         <td><strong>VREFCON1</strong></td>
         <td>DACEN</td>
         <td>DACLPS</td>
         <td>DACOE</td>
         <td>—</td>
         <td align="center" colspan="2">DACPSS&lt;1:0&gt;</td>
         <td>—</td>
         <td>DACNSS</td>
       </tr>
       <tr>
         <td><strong>VREFCON2</strong></td>
         <td>—</td>
         <td>—</td>
         <td>—</td>
         <td align="center" colspan="5">DACR&lt;4:0&gt;</td>
       </tr>
       <tr>
         <td><strong>HVLDCON</strong></td>
         <td>VDRMAG</td>
         <td>BGVST</td>
         <td>IRVST</td>
         <td>HLVDEN</td>
         <td align="center" colspan="4">HLVDL&lt;3:0&gt;</td>
       </tr>
       <tr>
         <td><strong>PORTA</strong></td>
         <td>RA7</td>
         <td>RA6</td>
         <td>RA5</td>
         <td>RA4</td>
         <td>RA3</td>
         <td>RA2</td>
         <td>RA1</td>
         <td>RA0</td>
       </tr>
       <tr>
         <td><strong>SLRCON</strong></td>
         <td>—</td>
         <td>—</td>
         <td>—</td>
         <td>SLRE</td>
         <td>SLRD</td>
         <td>SLRC</td>
         <td>SLRB</td>
         <td>SLRA</td>
       </tr>
       <tr>
         <td><strong>SRCON0</strong></td>
         <td>SRLEN</td>
         <td align="center" colspan="3">SRCLK&lt;2:0&gt;</td>
         <td>SRQEN</td>
         <td>SRNQEN</td>
         <td>SRPS</td>
         <td>SRPR</td>
       </tr>
       <tr>
         <td><strong>SSP1CON1</strong></td>
         <td>WCOL</td>
         <td>SSPOV</td>
         <td>SSPEN</td>
         <td>CKP</td>
         <td align="center" colspan="4">SSPM&lt;3:0&gt;</td>
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
         <td><strong>TRISA</strong></td>
         <td>TRISA7</td>
         <td>TRISA6</td>
         <td>TRISA5</td>
         <td>TRISA4</td>
         <td>TRISA3</td>
         <td>TRISA2</td>
         <td>TRISA1</td>
         <td>TRISA0</td>
       </tr>
     </tbody>
   </table>
   
   > - — = emplacements non implémentés, lus comme ‘0’.
   > - **`<n:m>` → on prend tous les bits du bit n jusqu’au bit m, inclus.**

- ### Registres Associés au PORTB

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
         <td><strong>ANSELB</strong></td>
         <td>—</td>
         <td>—</td>
         <td>ANSB5</td>
         <td>ANSB4</td>
         <td>ANSB3</td>
         <td>ANSB2</td>
         <td>ANSB1</td>
         <td>ANSB0</td>
       </tr>
       <tr>
         <td><strong>ECCP2AS</strong></td>
         <td>CCP2ASE</td>
         <td align="center" colspan="3">CCP2AS&lt;2:0&gt;</td>
         <td align="center" colspan="2">PSS2AC&lt;1:0&gt;</td>
         <td align="center" colspan="2">PSS2BD&lt;1:0&gt;</td>
       </tr>
       <tr>
         <td><strong>CCP2CON</strong></td>
         <td align="center" colspan="2">P2M&lt;1:0&gt;</td>
         <td align="center" colspan="2">DC2B&lt;1:0&gt;</td>
         <td align="center" colspan="4">CCP2M&lt;3:0&gt;</td>
       </tr>
       <tr>
         <td><strong>ECCP3AS</strong></td>
         <td>CCP3ASE</td>
         <td align="center" colspan="3">CCP3AS&lt;2:0&gt;</td>
         <td align="center" colspan="2">PSS3AC&lt;1:0&gt;</td>
         <td align="center" colspan="2">PSS3BD&lt;1:0&gt;</td>
       </tr>
       <tr>
         <td><strong>CCP3CON</strong></td>
         <td align="center" colspan="2">P3M&lt;1:0&gt;</td>
         <td align="center" colspan="2">DC3B&lt;1:0&gt;</td>
         <td align="center" colspan="4">CCP3M&lt;3:0&gt;</td>
       </tr>
       <tr>
         <td><strong>INTCON</strong></td>
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
         <td><strong>INTCON2</strong></td>
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
         <td><strong>INTCON3</strong></td>
         <td>INT2IP</td>
         <td>INT1IP</td>
         <td>—</td>
         <td>INT2IE</td>
         <td>INT1IE</td>
         <td>—</td>
         <td>INT2IF</td>
         <td>INT1IF</td>
       </tr>
       <tr>
         <td><strong>IOCB</strong></td>
         <td>IOCB7</td>
         <td>IOCB6</td>
         <td>IOCB5</td>
         <td>IOCB4</td>
         <td>—</td>
         <td>—</td>
         <td>—</td>
         <td>—</td>
       </tr>
       <tr>
         <td><strong>LATB</strong></td>
         <td>LATB7</td>
         <td>LATB6</td>
         <td>LATB5</td>
         <td>LATB4</td>
         <td>LATB3</td>
         <td>LATB2</td>
         <td>LATB1</td>
         <td>LATB0</td>
       </tr>
       <tr>
         <td><strong>PORTB</strong></td>
         <td>RB7</td>
         <td>RB6</td>
         <td>RB5</td>
         <td>RB4</td>
         <td>RB3</td>
         <td>RB2</td>
         <td>RB1</td>
         <td>RB0</td>
       </tr>
       <tr>
         <td><strong>SLRCON</strong></td>
         <td>—</td>
         <td>—</td>
         <td>—</td>
         <td>SLRE</td>
         <td>SLRD</td>
         <td>SLRC</td>
         <td>SLRB</td>
         <td>SLRA</td>
       </tr>
       <tr>
         <td><strong>T1GCON</strong></td>
         <td>TMR1GE</td>
         <td>T1GPOL</td>
         <td>T1GTM</td>
         <td>T1GSPM</td>
         <td>T1GGO / ¬<span style="text-decoration: overline">DONE</span></td>
         <td>T1GVAL</td>
         <td align="center" colspan="2">T1GSS&lt;1:0&gt;</td>
       </tr>
       <tr>
         <td><strong>T3CON</strong></td>
         <td align="center" colspan="2">TMR3CS&lt;1:0&gt;</td>
         <td align="center" colspan="2">T3CKPS&lt;1:0&gt;</td>
         <td>T3SOSCEN</td>
         <td>¬T3SYNC</td>
         <td>T3RD16</td>
         <td>TMR3ON</td>
       </tr>
       <tr>
         <td><strong>T5CON</strong></td>
         <td>TMR5GE</td>
         <td>T5GPOL</td>
         <td>T5GTM</td>
         <td>T5GSPM</td>
         <td>T5GGO / ¬DONE</td>
         <td>T5GVAL</td>
         <td align="center" colspan="2">T5GSS&lt;1:0&gt;</td>
       </tr>
       <tr>
         <td><strong>TRISB</strong></td>
         <td>TRISB7</td>
         <td>TRISB6</td>
         <td>TRISB5</td>
         <td>TRISB4</td>
         <td>TRISB3</td>
         <td>TRISB2</td>
         <td>TRISB1</td>
         <td>TRISB0</td>
       </tr>
       <tr>
         <td><strong>WPUB</strong></td>
         <td>WPUB7</td>
         <td>WPUB6</td>
         <td>WPUB5</td>
         <td>WPUB4</td>
         <td>WPUB3</td>
         <td>WPUB2</td>
         <td>WPUB1</td>
         <td>WPUB0</td>
       </tr>
     </tbody>
   </table>
   
   > - — = emplacements non implémentés, lus comme ‘0’.
   > - Les **bits grisés ne sont pas utilisés pour PORTB**.
   > - **`<n:m>` → on prend tous les bits du bit n jusqu’au bit m, inclus.**



- ### Registres Associés au PORTC

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
         <td><strong>ANSELC</strong></td>
         <td>ANSC7</td>
         <td>ANSC6</td>
         <td>ANSC5</td>
         <td>ANSC4</td>
         <td>ANSC3</td>
         <td>ANSC2</td>
         <td>—</td>
          <td>—</td>
       </tr>
       <tr>
         <td><strong>ECCP1AS</strong></td>
         <td>CCP1ASE</td>
         <td align="center" colspan="3">CCP1AS&lt;2:0&gt;</td>
         <td align="center" colspan="2">PSS1AC&lt;1:0&gt;</td>
         <td align="center" colspan="2">PSS1BD&lt;1:0&gt;</td>
       </tr>
       <tr>
         <td><strong>CCP1CON</strong></td>
         <td align="center" colspan="2">P1M&lt;1:0&gt;</td>
         <td align="center" colspan="2">DC1B&lt;1:0&gt;</td>
         <td align="center" colspan="4">CCP1M&lt;3:0&gt;</td>
       </tr>
       <tr>
         <td><strong>ECCP2AS</strong></td>
         <td>CCP2ASE</td>
         <td align="center" colspan="3">CCP2AS&lt;2:0&gt;</td>
         <td align="center" colspan="2">PSS2AC&lt;1:0&gt;</td>
         <td align="center" colspan="2">PSS2BD&lt;1:0&gt;</td>
       </tr>
       <tr>
         <td><strong>CCP2CON</strong></td>
         <td align="center" colspan="2">P2M&lt;1:0&gt;</td>
         <td align="center" colspan="2">DC2B&lt;1:0&gt;</td>
         <td align="center" colspan="4">CCP2M&lt;3:0&gt;</td>
       </tr>
       <tr>
         <td><strong>CTMUCONH</strong></td>
         <td>CTMUEN</td>
         <td>—</td>
         <td>CTMUSIDL</td>
         <td>TGEN</td>
         <td>EDGEN</td>
         <td>EDGSEQEN</td>
         <td>IDISSEN</td>
         <td>CTTRIG</td>
       </tr>
       <tr>
         <td><strong>LATC</strong></td>
         <td>LATC7</td>
         <td>LATC6</td>
         <td>LATC5</td>
         <td>LATC4</td>
         <td>LATC3</td>
         <td>LATC2</td>
         <td>LATC1</td>
         <td>LATC0</td>
       </tr>
       <tr>
         <td><strong>PORTC</strong></td>
         <td>RC7</td>
         <td>RC6</td>
         <td>RC5</td>
         <td>RC4</td>
         <td>RC3</td>
         <td>RC2</td>
         <td>RC1</td>
         <td>RC0</td>
       </tr>
       <tr>
         <td><strong>RCSTA1</strong></td>
         <td>SPEN</td>
         <td>RX9</td>
         <td>SREN</td>
         <td>CREN</td>
         <td>ADDEN</td>
         <td>FERR</td>
         <td>OERR</td>
         <td>RX9D</td>
       </tr>
       <tr>
         <td><strong>SLRCON</strong></td>
         <td>—</td>
         <td>—</td>
         <td>—</td>
         <td>SLRE</td>
         <td>SLRD</td>
         <td>SLRC</td>
         <td>SLRB</td>
         <td>SLRA</td>
       </tr>
       <tr>
         <td><strong>SSP1CON1</strong></td>
         <td>WCOL</td>
         <td>SSPOV</td>
         <td>SSPEN</td>
         <td>CKP</td>
         <td align="center" colspan="4">SSPM&lt;3:0&gt;</td>
       </tr>
       <tr>
         <td><strong>T1CON</strong></td>
         <td align="center" colspan="2">TMR1CS&lt;1:0&gt;</td>
         <td align="center" colspan="2">T1CKPS&lt;1:0&gt;</td>
         <td>T1SOSCEN</td>
         <td>¬T1SYNC</td>
         <td>T1RD16</td>
         <td>TMR1ON</td>
       </tr>
       <tr>
         <td><strong>T3CON</strong></td>
         <td align="center" colspan="2">TMR3CS&lt;1:0&gt;</td>
         <td align="center" colspan="2">T3CKPS&lt;1:0&gt;</td>
         <td>T3SOSCEN</td>
         <td>¬T3SYNC</td>
         <td>T3RD16</td>
         <td>TMR3ON</td>
       </tr>
       <tr>
         <td><strong>T3GCON</strong></td>
         <td>TMR3GE</td>
         <td>T3GPOL</td>
         <td>T3GTM</td>
         <td>T3GSPM</td>
         <td>T3GGO / ¬DONE</td>
         <td>T3GVAL</td>
         <td align="center" colspan="2">T3GSS&lt;1:0&gt;</td>
       </tr>
       <tr>
         <td><strong>T5CON</strong></td>
         <td align="center" colspan="2">TMR5CS&lt;1:0&gt;</td>
         <td align="center" colspan="2">T5CKPS&lt;1:0&gt;</td>
         <td>T5SOSCEN</td>
         <td>¬T5SYNC</td>
         <td>T5RD16</td>
         <td>TMR5ON</td>
       </tr>
       <tr>
         <td><strong>TRISC</strong></td>
         <td>TRISC7</td>
         <td>TRISC6</td>
         <td>TRISC5</td>
         <td>TRISC4</td>
         <td>TRISC3</td>
         <td>TRISC2</td>
         <td>TRISC1</td>
         <td>TRISC0</td>
       </tr>
       <tr>
         <td><strong>TXSTA1</strong></td>
         <td>CSRC</td>
         <td>TX9</td>
         <td>TXEN</td>
         <td>SYNC</td>
         <td>SENDB</td>
         <td>BRGH</td>
         <td>TRMT</td>
         <td>TX9D</td>
       </tr>
     </tbody>
   </table>
   
   > - — = **emplacements non implémentés, lus comme ‘0’**.
   > - Les **bits grisés ne sont pas utilisés pour PORTC**.
   > - **`<n:m>` → on prend tous les bits du bit n jusqu’au bit m, inclus.**

- ### Registres Associés au PORTD

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
         <td><strong>ANSELD</strong></td>
         <td>ANSD7</td>
         <td>ANSD6</td>
         <td>ANSD5</td>
         <td>ANSD4</td>
         <td>ANSD3</td>
         <td>ANSD2</td>
         <td>ANSD1</td>
         <td>ANSD0</td>
       </tr>
       <tr>
         <td><strong>BAUDCON2</strong></td>
         <td>ABDOVF</td>
         <td>RCIDL</td>
         <td>DTRXP</td>
         <td>CKTXP</td>
         <td>BRG16</td>
         <td>—</td>
         <td>WUE</td>
         <td>ABDEN</td>
       </tr>
       <tr>
         <td><strong>CCP1CON</strong></td>
         <td align="center" colspan="2">P1M&lt;1:0&gt;</td>
         <td align="center" colspan="2">DC1B&lt;1:0&gt;</td>
         <td align="center" colspan="4">CCP1M&lt;3:0&gt;</td>
       </tr>
       <tr>
         <td><strong>CCP2CON</strong></td>
         <td align="center" colspan="2">P2M&lt;1:0&gt;</td>
         <td align="center" colspan="2">DC2B&lt;1:0&gt;</td>
         <td align="center" colspan="4">CCP2M&lt;3:0&gt;</td>
       </tr>
       <tr>
         <td><strong>CCP4CON</strong></td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
         <td align="center" colspan="2">DC4B&lt;1:0&gt;</td>
         <td align="center" colspan="4">CCP4M&lt;3:0&gt;</td>
       </tr>
       <tr>
         <td><strong>LATD</strong></td>
         <td>LATD7</td>
         <td>LATD6</td>
         <td>LATD5</td>
         <td>LATD4</td>
         <td>LATD3</td>
         <td>LATD2</td>
         <td>LATD1</td>
         <td>LATD0</td>
       </tr>
       <tr>
         <td><strong>PORTD</strong></td>
         <td>RD7</td>
         <td>RD6</td>
         <td>RD5</td>
         <td>RD4</td>
         <td>RD3</td>
         <td>RD2</td>
         <td>RD1</td>
         <td>RD0</td>
       </tr>
       <tr>
         <td><strong>RCSTA2</strong></td>
         <td>SPEN</td>
         <td>RX9</td>
         <td>SREN</td>
         <td>CREN</td>
         <td>ADDEN</td>
         <td>FERR</td>
         <td>OERR</td>
         <td>RX9D</td>
       </tr>
       <tr>
         <td><strong>SLRCON</strong></td>
         <td>—</td>
         <td>—</td>
         <td>—</td>
         <td>SLRE</td>
         <td>SLRD</td>
         <td>SLRC</td>
         <td>SLRB</td>
         <td>SLRA</td>
       </tr>
       <tr>
         <td><strong>SSP2CON1</strong></td>
         <td>WCOL</td>
         <td>SSPOV</td>
         <td>SSPEN</td>
         <td>CKP</td>
         <td align="center" colspan="4">SSPM&lt;3:0&gt;</td>
       </tr>
       <tr>
         <td><strong>TRISD</strong></td>
         <td>TRISD7</td>
         <td>TRISD6</td>
         <td>TRISD5</td>
         <td>TRISD4</td>
         <td>TRISD3</td>
         <td>TRISD2</td>
         <td>TRISD1</td>
         <td>TRISD0</td>
       </tr>
   
     </tbody>
   </table>
   
   > - — = **emplacements non implémentés, lus comme ‘0’**.
   > - **`<n:m>` → on prend tous les bits du bit n jusqu’au bit m, inclus.**

- ### Registres Associés au PORTE

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
         <td><strong>ANSELE</strong></td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
         <td>ANSE2</td>
         <td>ANSE1</td>
         <td>ANSE0</td>
       </tr>
       <tr>
         <td><strong>INTCON2</strong></td>
         <td>¬RBPU</td>
         <td>INTEDG0</td>
         <td>INTEDG1</td>
         <td>INTEDG2</td>
         <td>—</td>
         <td>TMR0IP</td>
         <td>—</td>
         <td>RBIP</td>
       </tr>
       <tr>
         <td><strong>LATE</strong></td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
         <td>LATE2</td>
         <td>LATE1</td>
         <td>LATE0</td>
       </tr>
       <tr>
         <td><strong>PORTE</strong></td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
         <td>RE3</td>
         <td>RE2</td>
         <td>RE1</td>
         <td>RE0</td>
       </tr>
       <tr>
         <td><strong>SLRCON</strong></td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
         <td>SLRE</td>
         <td>SLRD</td>
         <td>SLRC</td>
         <td>SLRB</td>
         <td>SLRA</td>
       </tr>
       <tr>
         <td><strong>TRISE</strong></td>
         <td>WPUE3</td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
          <td>—</td>
         <td>TRISE2</td>
         <td>TRISE1</td>
         <td>TRISE0</td>
       </tr>
   
     </tbody>
   </table>
   
   > - — = **emplacements non implémentés, lus comme ‘0’**.
   > - Les **bits grisés ne sont pas utilisés pour PORTC**.