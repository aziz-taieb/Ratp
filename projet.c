#include "projet.h"
#include <errno.h>

sommet***ouvrir_fichier_station(){
  FILE *file;
  char fileName[] = "Metro Paris Data - Aretes.csv";
  file = fopen(fileName, "r");

  if (file == NULL) {
    printf("Impossible d'ouvrir le fichier %s en lecture seule\n", fileName);
    return NULL;
  }
  int num1;
  int num2;
  char num3[20];
  sommet***tab=malloc(sizeof(sommet**)*304);
  for(int i=0 ; i<304; i++){
    tab[i]=malloc(sizeof(sommet*)*16);
  }

  for(int i=0 ; i<304 ; i++){
    for(int j=0 ; j<16 ;j++){
      tab[i][j]=init_sommet();
    }
  }
	int nbligne[304];
	for(int i=0 ; i<304 ; i++){
		nbligne[i]=0;
	}
  fscanf(file,"%s",num3);
  int n;
  while (fscanf(file, "%d,%d,%s", &num1, &num2, num3) == 3) {
    n=nbligne[num1-1];
    if(!has_ligne(tab,num1,num3,n)){
      ajouter(tab,num1,num3,n);
      nbligne[num1-1]++;
    }
    n=nbligne[num2-1];
    if(!has_ligne(tab,num2,num3,n)){
      ajouter(tab,num2,num3,n);
      nbligne[num2-1]++;
    }
  }
  for(int i=0;i<304;i++) tab[i][0]->nbligne=nbligne[i];
  fclose(file);
  return tab;
}
sommet*init_sommet(){
  sommet*s=malloc(sizeof(sommet));
  s->id=0;
  s->ligne=malloc(sizeof(char)*5);
  return s;
}
uint32_t has_ligne(sommet***tab,int x,char*s,uint32_t nbligne){
  for(int i=0;i<nbligne;i++){
    if(strcmp(tab[x-1][i]->ligne,s)==0)
    return 1;
  }
  return 0;
}
void ajouter(sommet***tab,int num,char*s,uint32_t nbligne){
  strcpy(tab[num-1][nbligne]->ligne,s);
  tab[num-1][nbligne]->id=num;
}
uint32_t trouversommet(sommet***tab,uint32_t id,uint32_t nbtotal){
  int i,j=0;
  for(i=0;i<id-1;i++){
    j=j+tab[i][0]->nbligne;
  }
  return j;
}
dj*consdji(sommet***tab){
  int i,j,k,nbsommet=0;
	for(i=0;i<304;i++){
		for(int j=0;j<tab[i][0]->nbligne;j++){
			nbsommet++;
		}
	}
	nbsommet++;
  dj*d=malloc(sizeof(dj));
	d->ad=malloc(sizeof(uint32_t*)*nbsommet);
	for(i=0;i<nbsommet;i++){
		d->ad[i]=malloc(sizeof(uint32_t)*nbsommet);
	}
	d->cout=malloc(sizeof(uint32_t*)*nbsommet);
	for(i=0;i<nbsommet;i++){
		d->cout[i]=malloc(sizeof(uint32_t)*nbsommet);
	}
  for(i=0;i<nbsommet;i++){
    for(j=0;j<nbsommet;j++){
      d->ad[i][j]=0;
      d->cout[i][j]=9999;
    }
  }
	nbsommet--;
  FILE *file;
  char fileName[] = "Metro Paris Data - Aretes.csv";
  file = fopen(fileName, "r");

  if (file == NULL) {
    printf("Impossible d'ouvrir le fichier %s en lecture seule\n", fileName);
    return NULL;
  }
  int num1;
  int num2;
  char num3[20];
  fscanf(file,"%s",num3);
  while (fscanf(file, "%d,%d,%s", &num1, &num2, num3) == 3) {
    j=0;
    k=0;
    while(strcmp(tab[num1-1][j]->ligne,num3)!=0){
      j++;
    }
    while(strcmp(tab[num2-1][k]->ligne,num3)!=0){
      k++;
    }
    d->ad[trouversommet(tab,num1,nbsommet)+j][trouversommet(tab,num2,nbsommet)+k]=1;
    d->cout[trouversommet(tab,num1,nbsommet)+j][trouversommet(tab,num2,nbsommet)+k]=1;
  }
  for(i=0;i<nbsommet;i++){
    for(j=0;j<nbsommet;j++){
      if(i==j){
        d->cout[i][j]=9999;
      }else if(trouverid(tab,i,nbsommet)==trouverid(tab,j,nbsommet)){
        d->ad[i][j]=1;
        d->ad[j][i]=1;
        d->cout[i][j]=5;
        d->cout[j][i]=5;
      }
    }
  }
  fclose(file);
  return d;
}
uint32_t trouverid(sommet***tab,uint32_t x,uint32_t nbtotal){
  int i=0,j=1;
  while(i<x){
    i=i+tab[j][0]->nbligne;
    j++;
  }
  return j;
}
char*trouverligne(sommet***tab,uint32_t id,uint32_t sommet){
  uint32_t i=abs(trouversommet(tab,id,387)-sommet);
  return tab[id-1][i]->ligne;
}
uint32_t* dijkstra(uint32_t**G,uint32_t**cost,int n,int startnode,int u,int nbligne)
{
	uint32_t distance[388];
  uint32_t pred[388];
	uint32_t visited[388];
  uint32_t count, mindistance ,nextnode, i;
	for(i=0;i<n;i++){
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	while(count<n-1)
	{
		mindistance=9999;
		for(i=0;i<n;i++){
			if(distance[i]<mindistance&&!visited[i])
			{
  			mindistance=distance[i];
  			nextnode=i;
			}
	}
		visited[nextnode]=1;
		for(i=0;i<n;i++)
			if(!visited[i])
				if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
					count++;
	}
	int z=0,min=distance[u];
	for(i=1;i<nbligne;i++){
		if(distance[u+i]<min){
			min=distance[u+i];
      z=i;
    }
	}
	printf("Temps du trajet =%d\n",distance[u+z]);
  uint32_t*tab=malloc(sizeof(int)*(distance[u+z]+3));
  tab[0]=u+z;
  int ind,k=1;
  int j=u+z;
  while(j!=startnode){
    min=9999;
    for(i=0;i<388;i++){
      if((cost[i][j]==1||cost[i][j]==0)&&distance[i]<min){
        min=distance[i];
        ind=i;
      }else if(cost[i][j]==5&&distance[i]+5<min){
        min=distance[i]+5;
        ind=i;
      }
    }
    j=ind;
    tab[k]=ind;
    k++;
  }
  tab[k-1]=-1;
  return tab;
}
void detruiresommet(sommet*s){
	free(s->ligne);
	free(s);
}
void detruirestsommet(sommet***s){
	for(int i=0;i<304;i++){
		for(int j=0;j<s[i][0]->nbligne;j++){
			detruiresommet(s[i][j]);
		}
		free(s[i]);
	}
	free(s);
}
void detruiredj(dj*d,int nbsommet){
	for(int i=0;i<nbsommet+1;i++){
		free(d->ad[i]);
		free(d->cout[i]);
	}
	free(d->ad);
	free(d->cout);
	free(d);
}
char**nomstations(){
  FILE *file = fopen("Metro Paris Data - Stations.csv", "r");
  if (file == NULL) {
      printf("Impossible d'ouvrir le fichier\n");
      printf("%d\n",errno);
      return NULL;
  }
  int i=0;
  char**station=malloc(sizeof(char*)*304);
  for(i=0;i<304;i++){
    station[i]=malloc(sizeof(char)*50);
  }
  i=-1;
  char ligne[2000];
  while (fgets(ligne, sizeof(ligne), file) != NULL)
  {
      char *n = strtok(ligne, ",");
      char *id = strtok(NULL, ",");
      if(i!=-1)
      {
        strcpy(station[i],n);
      }
      i++;
  }
  fclose(file);
  return station;
}
void detruirestation(char**station){
  int i;
  for(i=0;i<304;i++){
    free(station[i]);
  }
  free(station);
}
void destructiontotale(dj*d,sommet***s,char**station){
  detruiredj(d,387);
  detruirestsommet(s);
  detruirestation(station);
}
void affichersolution(uint32_t*tab,char**station,sommet***s){
  int k=0,l=0;
  while(tab[k]!=-1){
    k++;
  }
  for(int i=k-1;i>=0;i--){
    l=trouverid(s,tab[i],387);
    printf("\n%s  Ligne %s\n",station[l-1],trouverligne(s,l,tab[i]));
    if(i-1>=0&&trouverid(s,tab[i-1],387)==trouverid(s,tab[i],387)){
      printf("\nChanger de ligne , prenez la ligne %s \n",trouverligne(s,trouverid(s,tab[i],387),tab[i-1]));
    }
    else if(i!=0){
      printf("      ||| \n");
      printf("      ||| \n");
      printf("      ||| \n");
    }
  }
  free(tab);
}
