#Definisce il nome della cartella che conterra i file in .c
SRCDIR := source

#Definisce la cartella dove ci saranno i file da includere, cioè i file .h 
INC := -I header

#Definisce la cartella dove verranno messi i file .o
BUILDDIR := build

#Definisce la cartella dove verra messo l' eseguibile
TARGET := bin/iaps


#avvia il comando find da shell che cerca tutti i file .c nella cartella specificata da SRCDIR, -type f = (regular file)
SOURCES := $(shell find $(SRCDIR) -type f -name *.c)

#OBJECTS: trasforma il path dei file da SRCDIR e li dirotta su BUILDDIR modificando i .c in .o
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.c=.o)) 

#Tutti i flag per le opzioni aggiuntive del compilatore (o2 è l'ottimizzatore automatico di secondo livello)   
CFLAGS=-c -Wall -pedantic -std=gnu99 -O2
LDFLAGS=-lm
CC=gcc


all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
#$@: Produce un file di output con il nome che metto prima dei :, in questo caso prende il nome contenuto nella variabile TARGET

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) $< -o $@
#$<: include solo la prima dipendenza

clean:
	rm -r $(BUILDDIR) $(TARGET)


#Altri tipi di opzioni disponibili

#$?: Fornisce la lista di dipendenze che sono state modificate dall' ultima compilazione
#$^: fornisce TUTTE le dipendenze, indipendentemente dai cambiamenti recenti o meno efffettuati sulle stesse. Nomi duplicati verranno rimossi
#$: fornisce TUTTE le dipendenze, indipendentemente dai cambiamenti recenti o meno efffettuati sulle stesse.

