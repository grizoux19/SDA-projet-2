#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Dict.h"

typedef struct Cellule_t {
    void* data;
    struct Cellule_t** fils;
} Cellule; 

struct Dict_t {
    Cellule* root;
    size_t nbkeys;
};

static void parcourFree(Cellule* noeud);
static Cellule* dictSearchLonguestCellule(Cellule*, char*, size_t);

Dict* dictCreateEmpty() {
    Dict* d = malloc(sizeof(Dict));
    if (!d)
        return NULL;

    d->root = malloc(sizeof(Cellule));
    if(d->root == NULL)
        return NULL;

    d->nbkeys = 0;
    d->root->data = NULL;
    d->root->fils = calloc(26,sizeof(Cellule));
    if(d->root->fils == NULL)
        return 0;

    return d;
}

size_t dictNbKeys(Dict* d) {
    return d->nbkeys;
}

void dictFree(Dict* d) {
    Cellule* noeud = d->root;
    //parcourFree(noeud);
    free(d);
}


int dictContains(Dict* d, const char* key) {
    int nblettre = strlen(key );
    int lettre;
    Cellule* noeud = d->root;
    
    for(int i =0; i<nblettre; i++)
    {
        lettre = key[i] - 97;
        noeud = noeud->fils[lettre];
        if(!noeud) 
            return 0;
        
    }
    if(noeud->data == NULL)
        return 0;
    return 1;
}

void* dictSearch(Dict* d, const char* key) {
    int nblettre = strlen(key );
    int lettre;
    Cellule* noeud = d->root;
    
    for(int i =0; i<nblettre; i++)
    {
        lettre = key[i] - 97;
        noeud = noeud->fils[lettre];
        if(noeud == NULL) 
            return NULL;
    }

    if(noeud->data == NULL)
        return NULL;

    return noeud->data;
}

void* dictSearchLongest(Dict* d, const char* letters) {
    
    Cellule* best = malloc(sizeof(Cellule));
    Cellule* start = d->root;

    char input[strlen(letters)];
    //memmove(input, letters, strlen(letters)*sizeof(char));
    strcpy(input, letters);

    best = dictSearchLonguestCellule(start, input, 0);
    if(best == NULL)
        return NULL;
    return best->data;
}

void dictInsert(Dict* d, const char* key, void* data) {
    int nblettre = strlen(key);
    int lettre ;
    Cellule* noeud = d->root;
    Cellule* tmp = malloc(26 * sizeof(Cellule));
    
    for( int i =0; i<nblettre; i++)
    {
        lettre = key[i] - 97 ; 
        tmp = noeud->fils[lettre];

        if(tmp == NULL || tmp == 0 )
        {
            noeud->fils[lettre] = malloc(sizeof(Cellule));
            noeud = noeud->fils[lettre];
            noeud->fils = calloc(26,sizeof(Cellule));
            noeud->data = NULL;
        }
        else
            noeud = noeud->fils[lettre];
        
    }
    noeud->data = data;
    d->nbkeys ++;
}


static Cellule* dictSearchLonguestCellule(Cellule* n, char* letters, size_t longuestlength)
{
    Cellule* longuestword = NULL;
    if(n->data != NULL && strlen(n->data) > longuestlength)
    {
        longuestlength = strlen(n->data);
        longuestword = n;
    }
    for(int i = 0; i < 26; i++)
    {
        char* tmp = letters;
        char* next = letters;

        while(*letters)
        {
            if(*letters == i + 97 && n->fils[i] != NULL)
            {
                *letters = 1;
                char* lettersbis = malloc(strlen(tmp)* sizeof(char));

                int j;
                for(j = 0; *tmp;)
                {
                    if(*tmp != 1)
                    {
                        lettersbis[j] = *tmp;
                        j++;
                    }
                    tmp++;
                }
                tmp = next;
                lettersbis[j] = '\0';

                *letters = i + 97;
                Cellule* noeud = dictSearchLonguestCellule(n->fils[i], lettersbis, longuestlength);
                
                if(noeud != NULL && strlen(noeud->data) > longuestlength)
                {
                    longuestlength = strlen(noeud->data);
                    longuestword = noeud;
                }
                free(lettersbis);
            }
            letters++;
        }
        letters = tmp;
    }
    return longuestword;
}
void parcourFree(Cellule* noeud)
{
    for(int i = 0; i<26; i++)
    {
        if(noeud->fils[i] != NULL)
        {
            parcourFree(noeud->fils[i]);
            free(noeud->fils[i]);
        }
    }
    free(noeud->fils);
}