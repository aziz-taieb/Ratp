#include <stdio.h>
#include "projet.h"
#define INFINITY 9999
#define MAX 387

int main()
{
	uint32_t i,k,u;
	char**station=nomstations();
	sommet***s=ouvrir_fichier_station();
	uint32_t nbsommet=0;
	for(i=0;i<304;i++){
		for(uint32_t j=0;j<s[i][0]->nbligne;j++){
			nbsommet++;
		}
	}
	dj*d=consdji(s);
	for(i=0;i<304;i++){
		printf("-%d %s\n",i+1,station[i]);
	}
	printf("Quel est la station de départ ?\n");
	scanf("%d",&u);
	k=trouversommet(s,u,nbsommet);
	for(i=0;i<s[u-1][0]->nbligne;i++){
		d->ad[nbsommet][k+i]=1;
		d->cout[nbsommet][k+i]=0;
	}
	printf("Quel est la station d'arrivé ?\n");
	scanf("%d",&k);
	u=trouversommet(s,k,nbsommet);
	int32_t*tab=dijkstra(d->ad,d->cout,nbsommet+1,nbsommet,u,s[k-1][0]->nbligne);
	affichersolution(tab,station,s);
	destructiontotale(d,s,station);
	return 0;
}
