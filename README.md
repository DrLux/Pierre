### Problem Resolver -> Pierre ###
![alt text](http://i.imgur.com/ADZkwP1.jpg)

### Per compilare ###
Recarsi nella cartella principale (pierre) e digitare il comando make. 	
	Esempio: Laboratorio/Pierre> make

L' eseguibile si troverà nella cartella "bin", mentre tutti i file oggeto saranno spostati automaticamente nella cartella "build"


### Sorgenti ###
I sorgenti si trovano nella cartella "source" mentre i relativi header nella cartella "header"

Molti sorgenti sono relativi alle strutture dati utilizzate: (list, priority_list,redblack, rbt_helper)

I sorgenti che fanno parte propriamente di Pierre sono: 

pierre = contiene il main. Comunica con l' utente e inizilizza, risolve, stampa il problema

bt_algorithms = contiene l'implementazione degli algoritmi

node = contiene i costruttori dei nodi usati dagli alberi di ricerca

problem = contiene i costruttori dei problemi gia codificati in pierre

common =  elementi comuni a tutti i problemi. Praticamente giusto il costruttore dei generici stati

I moduli codificati per esempio sono "lake" ed "8-puzzle"

					 pierre.h 
					     |
					bt_algorithms.h 
			              /      |        \                   
		          priority_list.h  node.h    redblack_tree.h
					     |
					  problem.h
					     |
				     *MODULO_PROBLEMA*
					     |
					  common.h
					     |
					   list.h 



