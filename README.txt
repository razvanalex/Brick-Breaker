------------------------------------------------------------------------------
							Tema 1 - EGC
------------------------------------------------------------------------------

AUTOR: Smadu Razvan-Alexandru  335CB

FISIERE INCLUSE:
	- ./libs/*
	- ./Resources/*
	- ./Source/* -> Tema este implementata in folderul Tema1 din Laboratoare
	- ./Visual Studio/*
	- ./README

README
	Codul a fost scris in Visual Studio 2017 Enterprise Edition. Identarea 
	este la 4 spatii. La consola este afisat powerup-ul curent si cat timp
	mai este disponibil. E posibil sa mai apara probleme la coliziune in 
	colturi, (foarte rar, cand bila isi schimba dimensiunea). 
	
	Proiectul este impartit in 3 filtre: Entities, Tools si Primiteves2D.
	In Entities se afla etitati derivate din Primiteves2D, cum ar fi Wall,
	Ball sau Paddle. In Primiteves2D se afla, dupa cum spune si numele,
	primitive cum ar fi patrat, cerc, obiect generic. In tools se afla 
	unelte folosite in randare, calcul de coliziuni, managementul caramizilor,
	etc. Restul detaliilor se gases in comentariile de cod (in limba engleza).
	Jocul poate fi jucat pana la nesfarsit. La fiecare nivel, caramizile sunt 
	din ce in ce mai dure. 

	Daca bila mare nu este prinsa, si se pierde o viata, va aparea mai sus decat
	daca ar fi fost mica. Asta face parte tot din BIG_BALL powerup. 
	Daca va eroare ca nu s-a putu incarca solutia, probabil a putut, dar din 
	diverse modive a aparut si eroarea. Ar trebui totusi sa mearga in aceste
	circumstante. Atentie! Trebuie setat Debug x64 sau orice altceva decat 
	Debug default.
