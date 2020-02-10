/*Musat Mihai-Robert - 313CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "structuri.h"
#include "defines.h"
#include "functii.h"

Variabila *v;
char *adr;

int main(int argc, char* argv[])
{
    FILE *fin = fopen(argv[1], "r");
    if(!fin) {
        printf("Err deschidere date.in\n");
        return 0;
    }
    freopen(argv[2], "w", stdout);
    v = CitireVariabile(fin);
    int m, i;
    fscanf(fin, "%d\n", &m);
    for(i = 0; i < m; ++i) {
        char buf[MAX];
        int valid = OK, ans;
        fgets(buf, MAX, fin);
        Arb a = MakeArb(buf, &valid);
        ans = EvalArb(a, &valid);
        if(valid == OK) {
            printf("%d\n", ans);
        } else if(valid == RADNEG || valid == DIVZERO){
            printf("Invalid expression\n");
        }
        if(adr != NULL) {
            free(adr);
            adr = NULL;
        }
        EliberareArb(a);
    }
    EliberareVar(v);
    fclose(fin);
    return 0;
}

