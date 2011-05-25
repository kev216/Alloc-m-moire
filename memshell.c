#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_BUFFER 128
#define TAILLE_MEMOIRE 512
static char memoire[TAILLE_MEMOIRE];

void aide()
{
  fprintf(stderr,"Aide :\n");
  fprintf(stderr,"Saisir l'une des commandes suivantes\n");
  fprintf(stderr,"\n");
  fprintf(stderr,"a taille  :   allouer un bloc de la taille souhaitee\n");
  fprintf(stderr,"l adresse :   librer un bloc alloue precedemment\n");
  fprintf(stderr,"i         :   afficher la liste des emplacements memoire inocupes\n");
  fprintf(stderr,"o         :   afficher la liste des emplacements memoire occupes\n");
  fprintf(stderr,"m         :   afficher le contenu de la memoire\n");
  fprintf(stderr,"h         :   afficher cette aide\n");
  fprintf(stderr,"q         :   quitter ce programme\n");
  fprintf(stderr,"\n");
}

void afficher_zone(void *adresse, size_t taille)
{
  printf("Adresse : %d, Taille : %d\n", (int) (adresse-(void *)memoire), (int) taille);
}

void afficher_zone_libre(void *adresse, size_t taille, int free)
{
  if (free)
	  afficher_zone(adresse, taille);
}

void afficher_zone_occupee(void *adresse, size_t taille, int free)
{
  if (!free)
	  afficher_zone(adresse, taille);
}

int main()
{
  char buffer[TAILLE_BUFFER];
  char commande;
  char *adresse;
  int offset;
  int taille, i;

  aide();
  mem_init(memoire,TAILLE_MEMOIRE);

  while (1)
    {
      printf("? ");
      fflush(stdout);
      commande = getchar();
      switch (commande)
        {
        case 'a':
          scanf ("%d",&taille);
          adresse = mem_alloc(taille);
	  if (adresse == NULL)
              printf("Echec de l'allocation\n");
	  else
              printf("Memoire allouee en %d\n", (int) (adresse-memoire));
          break;
        case 'l':
          scanf ("%d", &offset);
	  mem_free(memoire+offset);
	  printf("Memoire liberee\n");
          break;
        case 'i':
	  mem_show(afficher_zone_libre);
	  break;
        case 'o':
	  mem_show(afficher_zone_occupee);
	  break;
        case 'm':
          for (i=0; i<TAILLE_MEMOIRE; i++)
          printf("%d ", memoire[i]);
          printf("]\n");
	  break;
        case 'h':
          aide();
          break;
        case 'q':
          exit(0);
        default:
          fprintf(stderr,"Commande inconnue !\n");
        }
      /* vide ce qu'il reste de la ligne dans le buffer d'entree */
      fgets(buffer,TAILLE_BUFFER,stdin);
    }
  return 0;
}
