﻿Kontroller:
 - Piltaster for å flytte spiller
 - Esc for å avslutte spillet
 - P for pause/unpause

Spillet starter i pause modus

Bricks har liv, representert med en farge, hvor rød viser at bricken har 1 liv igjen.
Når alle bricks er borte/døde (unntak av uknuselige bricks) vil neste level laste inn
og spillet starte med en gang. Om det ikke er flere levler igjen (eller ikke finner level
fila), vil spillet starte på level 1.

Ballen vil sprette fra alle overflater utenom under spilleren hvor spilleren vil heller 
miste et liv og ballen flyttes til rett over spilleren. Om ballen treffer venstre 1/3 eller
høyre 1/3 av spilleren vil ballen reflekteres i motgående retning (om ballen kommer fra venstre
og treffer venstre 1/3 av spilleren, vil ballen gå til venstre istedenfor høyre).

Levels:
I prosjektmappen ligger det en mappe som heter "res", inni her ligger en mappe som heter "sprites"
og "levels". "sprites" mappen brukes til å ha alle bilder som er i bruk i seg. "levels" har alle
levler i seg. Disse levelene holder et spesifikt møsnter:
 - Navnet på levelen må være "Level_X.lvl" hvor X er tallet på levelen (1, 2, 3 osv)

Levelene er bygget opp på denne måten:
 - 10x6 grid av bricks
 - Tallene bestemmer livene til hver brick
 - En x betyr uknuselig brick
 - For nå er det bare implementert bricks med 1-5 liv, så ikke sett høyere tall enn det

Eksempel på en level:

5500440055
0033003300
0000xx0000
0022222200
0110110110
0000000000

Konsoll:
I konsollen skrives ut informasjon som ikke vises på skjermen.
 - Poeng
 - Liv
 - Pause/Unpause
 - Long frames

Long frames skrives til konsoll når en frame to lengre enn 0,04 sekunder å fullføre (alle oppdateringer,
kalkulasjoner og tegning til skjerm). Long frames ble implementert for å finne mulige feil underveis, men
brukes ikke til annet enn å stoppe ballen og spilleren fra å forsvinne synlig fra spillet om spilleren
tar tak i vinduet mens spillet pågår.

Score og liv skrives i konsoll fortløpende når endringer skjer. Og total score blir skrevet når spilleren
har null liv igjen og spillet er over.

Når spillet er over må spilelt lukkes og åpåpnes på nytt for å spilles igjen.




