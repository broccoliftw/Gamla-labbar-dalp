/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150		49 ms		67 ms
    200		110 ms		159 ms
    300		327 ms		155 ms
    400		739 ms		288 ms
    800		5796 ms		1021 ms
   1600		46438 ms	4503 ms
   3200		450000 ms	19098 ms
   6400		6000000 ms	87448 ms
  12800		80000000 ms	356770 ms


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: värsta fall O(n⁴) eftersom 4 nästlade loopar.

Sortering: värsta fall O(n² * log n) eftersom två garanterade nästlade loopar, i värsta fall behövs längre innre loopar men som inte alls är lika långa som n.
