/*Musat Mihai-Robert - 313CB*/


#include <stdio.h>
#include "structuri.h"

Variabila *CitireVariabile(FILE *f);
int CautaVariabila(char *nume, Variabila *v);
int DetNumar(char *nume);
Arb MakeArb(char s[], int *valid);
int EvalArb(Nod *nod, int *valid);
void EliberareArb(Nod *nod);
void EliberareVar(Variabila *v);

