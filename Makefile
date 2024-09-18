#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond à toutes les dépendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'édition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = contours_en_eps contours_en_txt simplification_seg simplification_courbe2 simplification_courbe3


#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h types_macros.h
	$(CC) -c $(COMPILOPTS) $<

geometrie2d.o : geometrie2d.c geometrie2d.h
	$(CC) -c $(COMPILOPTS) $<
	
postScript.o : postScript.c postScript.h
	$(CC) -c $(COMPILOPTS) $<
	
type_sequence.o : type_sequence.c type_sequence.h geometrie2d.h
	$(CC) -c $(COMPILOPTS) $<

extraction_contours.o : extraction_contours.c extraction_contours.h image.h type_sequence.h
	$(CC) -c $(COMPILOPTS) $<
	
test_approx.o : test_approx.c image.h type_sequence.h geometrie2d.h extraction_contours.h
	$(CC) -c $(COMPILOPTS) $<
	
contours_en_eps.o: contours_en_eps.c extraction_contours.h image.h type_sequence.h postScript.h
	$(CC) -c $(COMPILOPTS) $<
	
contours_en_txt.o: contours_en_txt.c extraction_contours.h image.h type_sequence.h
	$(CC) -c $(COMPILOPTS) $<
	
simplification_seg.o : simplification_seg.c simplification_seg.h image.h type_sequence.h geometrie2d.h postScript.h extraction_contours.h
	$(CC) -c $(COMPILOPTS) $<
	

simplification_courbe2.o : simplification_courbe2.c simplification_courbe2.h image.h type_sequence.h geometrie2d.h postScript.h extraction_contours.h
	$(CC) -c $(COMPILOPTS) $<
	
simplification_courbe3.o : simplification_courbe3.c simplification_courbe3.h image.h type_sequence.h geometrie2d.h postScript.h extraction_contours.h
	$(CC) -c $(COMPILOPTS) $<
	

########################################################
# regles explicites de creation des executables

	
extraction_contours : extraction_contours.o image.o type_sequence.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@
	

test_approx : test_approx.o image.o type_sequence.o geometrie2d.o extraction_contours.o
	$(CC) $^ $(LDOPTS) -o $@
	
contours_en_eps: contours_en_eps.o extraction_contours.o image.o type_sequence.o postScript.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@	
	
contours_en_txt: contours_en_txt.o extraction_contours.o image.o type_sequence.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@	
	
simplification_seg : simplification_seg.o image.o type_sequence.o geometrie2d.o postScript.o extraction_contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@
	
simplification_courbe2 : simplification_courbe2.o image.o type_sequence.o geometrie2d.o postScript.o extraction_contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@
	
simplification_courbe3 : simplification_courbe3.o image.o type_sequence.o geometrie2d.o postScript.o extraction_contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@
	
	

# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
