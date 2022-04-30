#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "Dict.h"

typedef struct Cellule_t {
    void* data;
    struct Cellule_t** fils; //tableau qui va contenir les fils
} Cellule; 

struct Dict_t {
    Cellule* root;
    size_t nbkeys;
};


Dict* dictCreateEmpty() {
    Dict* d = malloc(sizeof(Dict));
    if (!d)
        return NULL;

    d->root = malloc(sizeof(Cellule));
    if(d->root == NULL)
        return NULL;

    d->nbkeys = 0;
    d->root->data = NULL;
    d->root->fils = calloc(26, sizeof(Cellule));
    if(d->root->fils == NULL)
        return 0;
    for(int i =0; i<26; i++) 
    {
        d->root->fils[i] = NULL; 
    }
    return d;
}

size_t dictNbKeys(Dict* d) {
    return d->nbkeys;
}

void dictFree(Dict* d) {
    Cellule* noeud = d->root;
    Cellule* tmp;
    Cellule* next;
    for(int i=0; i<26; i++)
    {
        if(noeud->fils[i])
        {
            d->root = noeud->fils[i];
            dictFree(d);
        }
    }
}


int dictContains(Dict* d, const char* key) //Retourne la cellule du mot key
{
    int nblettre = strlen(key);
    int lettre;
    Cellule* noeud = d->root;
    
    for(int i = 0; i < nblettre; i++)
    {
        lettre = key[i] - 97; // donne le numéro de la case corespondant à la lettre a = 0 et z = 26
        noeud = noeud->fils[lettre];
        if(!noeud) 
            return 0;
        
    }
    if(noeud->data == NULL)
        return 0;
    return 1;
}

void* dictSearch(Dict* d, const char* key) //Cherche la data donnée par  key
{
    int nblettre = strlen(key);
    int lettre;
    Cellule* noeud = d->root;
    
    for(int i = 0; i < nblettre; i++)
    {
        lettre = key[i] - 97; // donne le numéro de la case corespondant à la lettre
        noeud = noeud->fils[lettre];
        if(noeud == NULL) 
            return NULL;
    }

    if(noeud->data == NULL)
        return NULL;

    return noeud->data;
}

void* dictSearchLongest(Dict* d, const char* letters) 
{
    int nblettre = strlen(letters);
    int lettre;
    char* longuest;
    Cellule* noeud = d->root;
    
    for(int i =0; i<nblettre; i++)
    {
        lettre = letters[i] - 97; // donne le numéro de la case corespondant à la lettre
        noeud = noeud->fils[lettre];
        if(noeud == NULL) 
            return NULL;
    }

    if(noeud->data == NULL)
        return NULL;

    return longuest;
}

void dictInsert(Dict* d, const char* key, void* data) {
    //fprintf(stderr, "Je print la key : %s, la data : %s et la longueur du char %d  dans dictinsert \n \n", key, data, strlen(key));
    int nblettre = strlen(key );
    int lettre ;
    Cellule* noeud = d->root;
    Cellule* tmp = malloc(40 * sizeof(Cellule));
    
    for(int i = 0; i < nblettre; i++)
    {
        lettre = key[i] - 97 ; 
        tmp = noeud->fils[lettre];
        if(tmp == NULL || tmp == 0 )
        {
            noeud->fils[lettre] = malloc(2 * sizeof(Cellule));
            noeud = noeud->fils[lettre];
            noeud->fils = calloc(26,2 * sizeof(Cellule));
            noeud->data = NULL;
        }
        else
            noeud = noeud->fils[lettre];
    }
    noeud->data = data;
    d->nbkeys ++;
}