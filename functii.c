/*Musat Mihai-Robert - 313CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "structuri.h"
#include "defines.h"

Variabila *v;
char *adr;

//citesc variabilele si le pun in structura
Variabila *CitireVariabile(FILE *f) {
    
    int n, i;
    fscanf(f, "%d\n", &n);
    Variabila *v = (Variabila *)malloc((n + 1) * sizeof(Variabila));
    v[0].val = n;
    v[0].nume = NULL;
    for(i = 1; i <= n; ++i) {
        char buf[15], eg;
        fscanf(f, "%s %c %d", buf, &eg, &v[i].val);
        v[i].nume = (char *)malloc(strlen(buf) + 1);
        strcpy(v[i].nume, buf);
    }
    return v;
}

//verific daca o variabila cu un anumit nume se afla in structura 
int CautaVariabila(char *nume, Variabila *v) {
    
    int n = v[0].val, i;
    for(i = 1; i <= n; ++i) {
        if(strcmp(nume, v[i].nume) == 0) {
            return i;
        }
    }
    if(adr == NULL) {
        adr = (char *)malloc(sizeof(nume) + 1);
        strcpy(adr, nume);
    }
    return 0;
}

//transform variabila cu un anumit nume in numarul corespunzator
int DetNumar(char *nume)  {
    
    int val = 0, semn = 1, st = 0, i;
	if(nume[0] == '-') {
		semn = -1;
		st++;
	}
    for(i = st; i < strlen(nume); ++i) {
        if('0' <= nume[i] && nume[i] <= '9') {
            val = val * 10 + nume[i] - '0';
        }
    }
    return val * semn;
}

//functia de construire a arborelui 
Arb MakeArb(char s[], int *valid) {
    
    char *p = strtok(s, " \n");
    if(p == NULL) {
        printf("Null in MakeArb");
        return NULL;
    }
    Nod *nod = (Nod *)malloc(sizeof(Nod));
    if(strcmp(p, "+") == 0) {
        nod->tip = OPERATOR;
        nod->val = PLUS;
        nod->fs = MakeArb(NULL, valid);
        nod->fd = MakeArb(NULL, valid);
    } else if(strcmp(p, "-") == 0) {
        nod->tip = OPERATOR;
        nod->val = MINUS;
        nod->fs = MakeArb(NULL, valid);
        nod->fd = MakeArb(NULL, valid);
    } else if(strcmp(p, "*") == 0) {
        nod->tip = OPERATOR;
        nod->val = MUL;
        nod->fs = MakeArb(NULL, valid);
        nod->fd = MakeArb(NULL, valid);
    } else if(strcmp(p, "/") == 0) {
        nod->tip = OPERATOR;
        nod->val = DIV;
        nod->fs = MakeArb(NULL, valid);
        nod->fd = MakeArb(NULL, valid);
    } else if(strcmp(p, "^") == 0 ) {
        nod->tip = OPERATOR;
        nod->val = PUT;
        nod->fs = MakeArb(NULL, valid);
        nod->fd = MakeArb(NULL, valid);
    } else if(strcmp(p, "sqrt") == 0) {
        nod->tip = OPERATOR;
        nod->val = RAD;
        nod->fs = MakeArb(NULL, valid);
        nod->fd = NULL;
    } else if( isalpha(p[0]) ) {
        nod->tip = VARIABILA;
        nod->val = CautaVariabila(p, v);
        nod->fs = nod->fd = NULL;
    } else {
        nod->tip = CONSTANTA;
        nod->val = DetNumar(p);
        nod->fs = nod->fd = NULL;
    }
    return nod;
}

//evaluez arborele la fiecare pas in functie de operatori si variabile 
int EvalArb(Nod *nod, int *valid) {
    
    if(nod->tip == CONSTANTA) {
        return nod->val;
    } else if (nod->tip == VARIABILA) {
        if(*valid == OK && nod->val == 0) {
            printf("Variable %s undeclared\n", adr);
            *valid = UNDEF;
        } else {
            return v[nod->val].val;
        }
    } else if(nod->tip == OPERATOR) {
        if(nod->val == PLUS) {
            return EvalArb(nod->fs, valid) + EvalArb(nod->fd, valid);
        } else if(nod->val == MINUS) {
            return EvalArb(nod->fs, valid) - EvalArb(nod->fd, valid);
        } else if(nod->val == MUL) {
            return EvalArb(nod->fs, valid) * EvalArb(nod->fd, valid);
        } else if(nod->val == DIV) {
            int vals = EvalArb(nod->fs, valid);
            int vald = EvalArb(nod->fd, valid);
            if(*valid == OK && vald == 0) {
                *valid = DIVZERO;
            } else {
                if(vald == 0) {
                   return 0;
                }
                return vals / vald;
            }

        } else if(nod->val == PUT) {
            int vals = EvalArb(nod->fs, valid);
            int vald = EvalArb(nod->fd, valid);
            int ans = 1, i;
            for(i = 0; i < vald; ++i) {
                ans = ans * vals;
            }
            return ans;
        } else if(nod->val == RAD) {
            int vals = EvalArb(nod->fs, valid);
            if(*valid == OK && vals < 0) {
                *valid = RADNEG;
            } else {
                if(vals < 0) {
                   return 0;
                }
                return sqrt(1.0 * vals);
            }
        }
    } else {
        printf("Unknow operation\n");
        return 0;
    }
    return 0;
}

//functie de eliberare a arborelui 
void EliberareArb(Nod *nod) {
    
    if(nod == NULL) {
        return;
    }
    if(nod->fs != NULL) {
        EliberareArb(nod->fs);
    }
    if(nod->fd != NULL) {
        EliberareArb(nod->fd);
    }
    free(nod);
}

//functie de eliberare a unei structuri a unei variabile 
void EliberareVar(Variabila *v) {
    
    int n = v[0].val, i;
    for(i = 1; i <= n; ++i) {
        free(v[i].nume);
    }
    free(v);
}

