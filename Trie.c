#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "Dict.h"

typedef struct Cellule_t {
    void* data;
    struct Cellule_t** fils; //tableau qui va contenir les fils
} Cellule; 

struct Dict_t {
    Cellule* root;
    size_t nbkeys;
};

static char* parcour(Cellule* noeud, char* letters, bool* tab, char* LonguestWord, int LonguestLenght);

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
    for(int i=0; i<26; i++)
    {
        if(noeud->fils[i])
        {
            d->root = noeud->fils[i];
            dictFree(d);
        }
    }
}


int dictContains(Dict* d, const char* key) {
    int nblettre = strlen(key );
    int lettre;
    Cellule* noeud = d->root;
    
    for(int i =0; i<nblettre; i++)
    {
        lettre = key[i] - 97; // donne le numéro de la case corespondant à la lettre
        noeud = noeud->fils[lettre];
        if(!noeud) 
            return 0;
        
    }
    if(noeud->data == NULL)
        return 0;
    return 1;
}

void* dictSearch(Dict* d, const char* key) {
    int nblettre = strlen(key);
    int lettre;
    Cellule* noeud = d->root;
    Cellule* tmp = malloc(sizeof(Cellule));
    
    for(int i = 0; i<nblettre; i++)
    {
        lettre = key[i] - 97; // donne le numéro de la case corespondant à la lettre
        tmp = noeud->fils[lettre];
        if(tmp == NULL) 
            return NULL;
    }

    if(noeud->data == NULL)
        return NULL;

    return noeud->data;
}

void* dictSearchLongest(Dict* d, const char* letters) {
    char* LonguestWord;
    int LengthLonguest = 0;
    int nbletters= strlen(letters);
    
    Cellule* start = malloc(sizeof(Cellule));
    start = d->root;

    bool tab[nbletters];
    for(int i=0; i<nbletters; i++)
    {
        tab[i]=true;
    }

    LonguestWord = parcour(start, letters, tab, LonguestWord, LengthLonguest);
    fprintf(stderr,"%s", LonguestWord);

    return LonguestWord;
}

void dictInsert(Dict* d, const char* key, void* data) {
    int nblettre = strlen(key);
    int lettre ;
    Cellule* noeud = d->root;
    Cellule* tmp = malloc(26*sizeof(Cellule));
    
    for(int i = 0; i < nblettre; i++)
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

char* parcour(Cellule* noeud, char* letters, bool* tab, char* LonguestWord, int LonguestLenght)
{
    int nbletters = strlen(letters);
    int j;
    for( int i=0; i<26; i++)
    {
        if(noeud->fils[i] != 0)
        {
            j =0;
            while(tab[j] && i != letters[j] - 97 && j < nbletters)
            {
                j++;
            }

            if (j == nbletters)
                continue;

            if(noeud->fils[i]->data)
            {
                int Lenght = strlen(noeud->fils[i]->data);
                if(Lenght > LonguestLenght)
                {
                    LonguestWord = noeud->fils[i]->data;
                    LonguestLenght = Lenght;
                }
            }
            tab[j] = false; // a vérifier
            LonguestWord = parcour(noeud->fils[i], letters, tab, LonguestWord, LonguestLenght);
            tab[j] = true;
        }
    }
    return LonguestWord;
}