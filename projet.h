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

void affichersolution(uint32_t*tab,char**station,sommet***s);
char**nomstations();
void destructiontotale(dj*d,sommet***s,char**station);
void detruirestation(char**station);
void detruiredj(dj*d,int nbsommet);
void detruiresommet(sommet*s);
void detruirestsommet(sommet***s);
uint32_t* dijkstra(uint32_t**G,uint32_t**cost,int n,int startnode,int u,int nbligne);
char*trouverligne(sommet***tab,uint32_t id,uint32_t sommet);
dj*consdji(sommet***tab);
uint32_t has_ligne(sommet***tab,int x,char*s,uint32_t nbligne);
void ajouter(sommet***tab,int num,char*s,uint32_t nbligne);
sommet*init_sommet();
sommet***ouvrir_fichier_station();
char**ouvrir_fichier_sommet();
int trouverId(char **tableau, char *chaine, int taille);
uint32_t trouversommet(sommet***tab,uint32_t id,uint32_t nbtotal);
uint32_t trouverid(sommet***tab,uint32_t x,uint32_t nbtotal);
#endif
