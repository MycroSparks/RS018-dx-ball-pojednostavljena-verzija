# RS018-dx-ball-pojednostavljena-verzija
DX Ball pojednostavljena verzija

﻿Izvestaj br. 1 (Bice izmena verovatno u toku rada =] )

1. Sta je planirano da program radi:

	Igrica pocinje sa lopticom na plocici i postavljenim blokovima, od kojih neki imaju posebne power-up-ove. 
Jednim klikom se loptica odvaja od plocice i razbija blokove, pri cemu se u povratku odbija od plocice pod uglom pod kojim je i udarila u nju.
Kada se unisti blok sa posebnim mogucnostima, power-up pada i treba ga uhvatiti plocicom koju pomera igrac. Ako igrac ne uhvati lopticu, gubi
i igrica pocinje od pocetka, ako unisti sve blokove, pobedjuje.
Power-up 1: povecavanje brzine;
Power-up 2: lepljenje za plocicu;
Power-up 3: udvostrucavanje loptice;
Power-up 4: unistavanje blokova oko dodirnog

2. Kakva će biti arhitektura programa -- na koje delove će program biti podeljen:

	Program ce imati po klasu za lopticu, plocicu, blok i power-up, pri cemu svaki power-up nasledjuje glavnu power-up klasu. Imacemo
i glavnu klasu koja kontrolise input igraca, cuva informacije u skoru/proteklom vremenu, i u zavisnosti od engina u kojem radimo,
ova klasa mozda bude imala i dodatne funkcionalnosti(kontrola frejmova i glavnog loop-a igrice).

3. Od čega planirate da krenete:
	
	Planiramo da krenemo od klasa za lopticu i plocicu.


IZVESTAJ BR.2:

	Prilicno smo blizu kraja, popravljamo samo neke sitnice, moramo samo ulepsati igricu, da bude dopadljiva. 
	Promenili smo engine, tj. presli smo ipak na Qt, nismo se snasli sa Unreal Engine-om. 
