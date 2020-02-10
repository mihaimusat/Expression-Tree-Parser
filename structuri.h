/*Musat Mihai-Robert - 313CB*/

#ifndef _ARBORE_H_
#define _ARBORE_H_

typedef struct Variabila {
    char *nume;
    int val;
} Variabila;

typedef struct nod {
    int tip, val;
    struct nod *fs, *fd;
} Nod, *Arb;

#endif
