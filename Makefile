#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################





# Compilateur C
CC = clang

# Dossiers pour les sources, objets, includes, et binaires
SRCDIR = ./src
INCDIR = ./include
OBJDIR = ./build
BINDIR = .

LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm
# Options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# Options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# Liste des executables
EXECUTABLES = $(BINDIR)/contours_en_eps \
              $(BINDIR)/contours_en_txt \
              $(BINDIR)/simplification_seg \
              $(BINDIR)/simplification_courbe2 \
              $(BINDIR)/simplification_courbe3

# Liste des objets (note: adding dependencies here)
OBJ = $(OBJDIR)/image.o \
      $(OBJDIR)/geometrie2d.o \
      $(OBJDIR)/postScript.o \
      $(OBJDIR)/type_sequence.o \
      $(OBJDIR)/extraction_contours.o \
      $(OBJDIR)/test_approx.o \
      $(OBJDIR)/contours_en_eps.o \
      $(OBJDIR)/contours_en_txt.o \
      $(OBJDIR)/simplification_seg.o \
      $(OBJDIR)/simplification_courbe2.o \
      $(OBJDIR)/simplification_courbe3.o


#############################################################################
# definition des regles
#############################################################################

########################################################

# Règle par défaut
all: directories $(EXECUTABLES)

# Crée les dossiers build/ et bin/ si nécessaires
directories:
	mkdir -p $(OBJDIR) $(BINDIR)

# Compilation générique des fichiers .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h
	@echo "Compilation du module $*"
	$(CC) -c $(COMPILOPTS) $< -o $@

# Règles explicites pour les modules sans .h ou avec des dépendances supplémentaires
$(OBJDIR)/image.o: $(SRCDIR)/image.c $(INCDIR)/image.h $(INCDIR)/types_macros.h
	$(CC) -c $(COMPILOPTS) $< -o $@

$(OBJDIR)/geometrie2d.o: $(SRCDIR)/geometrie2d.c $(INCDIR)/geometrie2d.h
	$(CC) -c $(COMPILOPTS) $< -o $@

$(OBJDIR)/postScript.o: $(SRCDIR)/postScript.c $(INCDIR)/postScript.h
	$(CC) -c $(COMPILOPTS) $< -o $@

$(OBJDIR)/type_sequence.o: $(SRCDIR)/type_sequence.c $(INCDIR)/type_sequence.h $(INCDIR)/geometrie2d.h
	$(CC) -c $(COMPILOPTS) $< -o $@

$(OBJDIR)/extraction_contours.o: $(SRCDIR)/extraction_contours.c $(INCDIR)/extraction_contours.h $(INCDIR)/image.h $(INCDIR)/type_sequence.h
	$(CC) -c $(COMPILOPTS) $< -o $@


$(OBJDIR)/test_approx.o: $(SRCDIR)/test_approx.c $(INCDIR)/image.h $(INCDIR)/type_sequence.h $(INCDIR)/geometrie2d.h $(INCDIR)/extraction_contours.h
	$(CC) -c $(COMPILOPTS) $< -o $@

$(OBJDIR)/contours_en_eps.o: $(SRCDIR)/contours_en_eps.c $(INCDIR)/extraction_contours.h $(INCDIR)/image.h $(INCDIR)/type_sequence.h $(INCDIR)/postScript.h
	$(CC) -c $(COMPILOPTS) $< -o $@


$(OBJDIR)/contours_en_txt.o: $(SRCDIR)/contours_en_txt.c $(INCDIR)/extraction_contours.h $(INCDIR)/image.h $(INCDIR)/type_sequence.h
	$(CC) -c $(COMPILOPTS) $< -o $@

$(OBJDIR)/simplification_seg.o: $(SRCDIR)/simplification_seg.c $(INCDIR)/simplification_seg.h $(INCDIR)/image.h $(INCDIR)/type_sequence.h $(INCDIR)/geometrie2d.h $(INCDIR)/postScript.h $(INCDIR)/extraction_contours.h
	$(CC) -c $(COMPILOPTS) $< -o $@	


$(OBJDIR)/simplification_courbe2.o: $(SRCDIR)/simplification_courbe2.c $(INCDIR)/simplification_courbe2.h $(INCDIR)/image.h $(INCDIR)/type_sequence.h $(INCDIR)/geometrie2d.h $(INCDIR)/postScript.h $(INCDIR)/extraction_contours.h
	$(CC) -c $(COMPILOPTS) $< -o $@	

$(OBJDIR)/simplification_courbe3.o: $(SRCDIR)/simplification_courbe3.c $(INCDIR)/simplification_courbe3.h $(INCDIR)/image.h $(INCDIR)/type_sequence.h $(INCDIR)/geometrie2d.h $(INCDIR)/postScript.h $(INCDIR)/extraction_contours.h
	$(CC) -c $(COMPILOPTS) $< -o $@	




# Création des exécutables

$(BINDIR)/contours_en_eps: $(OBJDIR)/contours_en_eps.o $(OBJDIR)/extraction_contours.o $(OBJDIR)/image.o $(OBJDIR)/type_sequence.o $(OBJDIR)/postScript.o
	@echo "Création de l'exécutable $@"
	$(CC) $^ $(LDOPTS) -o $@

$(BINDIR)/contours_en_txt: $(OBJDIR)/contours_en_txt.o $(OBJDIR)/extraction_contours.o $(OBJDIR)/image.o $(OBJDIR)/type_sequence.o
	@echo "Création de l'exécutable $@"
	$(CC) $^ $(LDOPTS) -o $@

$(BINDIR)/simplification_seg: $(OBJDIR)/simplification_seg.o $(OBJDIR)/image.o $(OBJDIR)/type_sequence.o $(OBJDIR)/geometrie2d.o $(OBJDIR)/postScript.o $(OBJDIR)/extraction_contours.o
	@echo "Création de l'exécutable $@"
	$(CC) $^ $(LDOPTS) -o $@

$(BINDIR)/simplification_courbe2: $(OBJDIR)/simplification_courbe2.o $(OBJDIR)/image.o $(OBJDIR)/type_sequence.o $(OBJDIR)/geometrie2d.o $(OBJDIR)/postScript.o $(OBJDIR)/extraction_contours.o
	@echo "Création de l'exécutable $@"
	$(CC) $^ $(LDOPTS) -o $@

$(BINDIR)/simplification_courbe3: $(OBJDIR)/simplification_courbe3.o $(OBJDIR)/image.o $(OBJDIR)/type_sequence.o $(OBJDIR)/geometrie2d.o $(OBJDIR)/postScript.o $(OBJDIR)/extraction_contours.o
	@echo "Création de l'exécutable $@"
	$(CC) $^ $(LDOPTS) -o $@

# Règle pour nettoyer le répertoire
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLES)