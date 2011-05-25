#ifndef __MEM_INTERNAL_H
#define __MEM_INTERNAL_H

/* Lingxiao
   struct fb : d�crit une zone de m�moire libre.
   La m�moire libre commence l� o� est plac� la structure.
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
  l'ordre croissant de la m�moire (NULL si c'est la derni�re).
    Deux zones libres ne peuvent pas �tre adjacentes (elles sont
  fusionn�es en une seule au besoin)

*/

struct fb {
	size_t taille;
	struct fb *next;
	/* ... */
};

/* struct db : d�crit une zone de m�moire occup�e.
   La zone allou�e commence apr�s cette structure de contr�le
   Le champ 'taille' contient la taille totale de cette zone
   (on comptabilise donc dedans la taille de la structure 'struct db')


 Zone de donn�es (data block)
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
  description : alloue une zone de donn�e pour stocker des donn�es
    au d�but d'une zone libre.
  parametres :
    - previous_fb : zone libre o� l'on veut placer la zone de donn�es
    - taille : taille de la zone de donn�e (y compris le descripteur)
  valeur de retour :
    adresse de la premi�re zone libre dont l'adresse est
    sup�rieure � 'previous_fb' : il s'agit d'une nouvelle zone libre cr�e
    � la fin de l'ancienne si la zone de donn�es n'a pas pris toute la place,
    sinon on renvoie la zone libre suivante (dont l'adresse �tait pr�sente
    dans le champ 'next' de l'ancienne zone libre)
  effet de bord : modifie la m�moire pour mettre en place la nouvelle zone
    de donn�e et �ventuellement la zone libre restante

  Note : vous n'�tes pas oblig� d'utiliser (et d'�crire) cette fonction
  si vous d�sirez faire autre chose
 */
struct fb* alloc_db_in_fb(struct fb* previous_fb, size_t taille);

#endif
