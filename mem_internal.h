#ifndef __MEM_INTERNAL_H
#define __MEM_INTERNAL_H

/* Lingxiao
   struct fb : décrit une zone de mémoire libre.
   La mémoire libre commence là où est placé la structure.
   Le champ 'taille' contient la taille totale de la zone libre
   (on comptabilise donc dedans la taille de la structure 'struct fb')


 Zone libre (free block)
 +------------------------+-------------------------------------+
 | struct fb   	       	  |            	      	                |
 |             	       	  |            	      	                |
 | size_t | struct fb |	  |            	      	                |
 | taille | * next    |...|                                     |
 |        |           |   |                                     |
 +--------------------+---+-------------------------------------+

    Le champ 'next' contient l'adresse de la prochaine zone libre dans
  l'ordre croissant de la mémoire (NULL si c'est la dernière).
    Deux zones libres ne peuvent pas être adjacentes (elles sont
  fusionnées en une seule au besoin)

*/

struct fb {
	size_t taille;
	struct fb *next;
	/* ... */
};

/* struct db : décrit une zone de mémoire occupée.
   La zone allouée commence après cette structure de contrôle
   Le champ 'taille' contient la taille totale de cette zone
   (on comptabilise donc dedans la taille de la structure 'struct db')


 Zone de données (data block)
 +-------------+--------------------------------------------+---+
 | struct db   |       	               	      	            |   |
 |             |       	               	      	            |   |
 | size_t  |   |    USER DATA          	      	            |pad|
 | taille  |...|                                            |   |
 |         |   |                                            |   |
 +---------+---+--------------------------------------------|---+

*/

struct db {
	size_t taille;
	/* ... */
};

/*
  alloc_db_in_fb
  description : alloue une zone de donnée pour stocker des données
    au début d'une zone libre.
  parametres :
    - previous_fb : zone libre où l'on veut placer la zone de données
    - taille : taille de la zone de donnée (y compris le descripteur)
  valeur de retour :
    adresse de la première zone libre dont l'adresse est
    supérieure à 'previous_fb' : il s'agit d'une nouvelle zone libre crée
    à la fin de l'ancienne si la zone de données n'a pas pris toute la place,
    sinon on renvoie la zone libre suivante (dont l'adresse était présente
    dans le champ 'next' de l'ancienne zone libre)
  effet de bord : modifie la mémoire pour mettre en place la nouvelle zone
    de donnée et éventuellement la zone libre restante

  Note : vous n'êtes pas obligé d'utiliser (et d'écrire) cette fonction
  si vous désirez faire autre chose
 */
struct fb* alloc_db_in_fb(struct fb* previous_fb, size_t taille);

#endif
