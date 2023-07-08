#ifndef PROJET_H
#define PROJET_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct dj{
	uint32_t**ad;
	uint32_t**cout;
}dj;

typedef struct sommet{
	uint32_t id;
	char*ligne;
	uint32_t nbligne;
}sommet;

void affichersolution(int32_t*tab,char**station,sommet***s);
char**nomstations();
void destructiontotale(dj*d,sommet***s,char**station);
void detruirestation(char**station);
void detruiredj(dj*d,uint32_t nbsommet);
void detruiresommet(sommet*s);
void detruirestsommet(sommet***s);
int32_t* dijkstra(uint32_t**G,uint32_t**cost,uint32_t n,uint32_t startnode,uint32_t u,uint32_t nbligne);
char*trouverligne(sommet***tab,uint32_t id,uint32_t sommet);
dj*consdji(sommet***tab);
uint32_t has_ligne(sommet***tab,uint32_t x,char*s,uint32_t nbligne);
void ajouter(sommet***tab,uint32_t num,char*s,uint32_t nbligne);
sommet*init_sommet();
sommet***ouvrir_fichier_station();
char**ouvrir_fichier_sommet();
uint32_t trouverId(char **tableau, char *chaine, uint32_t taille);
uint32_t trouversommet(sommet***tab,uint32_t id,uint32_t nbtotal);
uint32_t trouverid(sommet***tab,uint32_t x,uint32_t nbtotal);
#endif
