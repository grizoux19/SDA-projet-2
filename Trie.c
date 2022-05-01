#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

static char* parcour(Cellule* noeud, char* letters, bool* tab, char* LonguestWord, int LonguestLenght);
static void parcourFree(Cellule* noeud);
static Cellule* dictSearchLonguestCellule(Cellule*, char*, int);

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
    parcourFree(noeud);
    free(d);
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
    int nblettre = strlen(key );
    int lettre;
    Cellule* noeud = d->root;
    
    for(int i =0; i<nblettre; i++)
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

void* dictSearchLongest(Dict* d, const char* letters) {
    int nbletters= strlen(letters);
    
    Cellule* best = malloc(sizeof(Cellule));
    Cellule* start = d->root;;

    best = dictSearchLonguestCellule(start, letters, 0);
    fprintf(stderr,"%s\n", best->data);

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

/*static Node* dictSearchLongestRec(Node* n, char* s, size_t maxLength){

    Node* best = NULL;

    if(n->data != NULL && n->length > maxLength)
    {
        best = n;
        maxLength = n->length;
    }
    
    for(size_t i = 0; i < 26; i++)
    {
        char* tmp = s;
        char* ref = s;
        while(*s)
        {

            if(*s == (char)(i+'a') && n->array[i] != NULL)
            {
                *s = 1;
                char* s_prime = malloc(strlen(tmp)*sizeof(char));

                int j = 0;
                while(*tmp){
                    if(*tmp != 1){
                        s_prime[j] = *tmp;
                        j++;
                    }
                    tmp++;
                }
                tmp = ref;
                s_prime[j] = '\0';

                *s = (char)(i+97);
                Node* node = dictSearchLongestRec(n->array[i], s_prime, maxLength);
                free(s_prime);
                
                if(node != NULL && node->length > maxLength)
                {
                    maxLength = node->length;
                    best = node;
                }
            }
            s++;
        }
        s = tmp;
    }

    return best;
}*/

static Cellule* dictSearchLonguestCellule(Cellule* n, char* letters, int longuestlength)//, int actlength)
{
    Cellule* best = NULL;
    if(n->data != NULL && strlen(n->data) > longuestlength)
    {
        best = n;
        longuestlength = strlen(n->data);
    }
    for(int i = 0; i < 26; i++)
    {
        char* tmp = letters;
        char* ref = letters;

        while(*letters)
        {
            if(*letters == (char) (i + 'a') && n->fils[i] != NULL)
            {
                *letters = 1;
                char* lettersbis = malloc(strlen(tmp)* sizeof(char));

                int j = 0;
                while(*tmp)
                {
                    if(*tmp != 1)
                    {
                        lettersbis[j] = *tmp;
                        j++;
                    }
                    tmp++;
                }
                tmp = ref;
                lettersbis[j] = '\0';

                *letters = (char) (i + 97);
                Cellule* noeud = dictSearchLonguestCellule(n->fils[i], lettersbis, longuestlength);
                free(lettersbis);

                if(noeud != NULL && strlen(noeud->data) > longuestlength)
                {
                    longuestlength = strlen(noeud->data);
                    best = noeud;
                }
            }
            letters++;
        }
        letters = tmp;
    }
    return best;
}

char* parcour(Cellule* noeud, char* letters, bool* tab, char* LonguestWord, int LonguestLenght)
{
    int nbletters = strlen(letters);
    int j;
    for( int i=0; i<26; i++)
    {
        if(noeud->fils[i] != 0)
        {
            for( j =0; j < nbletters; j++ )
            {
                if(i == letters[j] - 97  && tab[j])
                    break;
            }

            if (j == nbletters)
                continue;
            fprintf(stderr, "%p \n",noeud->fils[i]->data );

            if( noeud->fils[i]->data)
            {
                int Lenght = strlen(noeud->fils[i]->data);
                if(Lenght > LonguestLenght)
                {
                    LonguestWord = noeud->fils[i]->data;
                    fprintf(stderr,"%s\n",LonguestWord);
                    LonguestLenght = Lenght;
                    fprintf(stderr,"%d\n",LonguestLenght);
                }
            }
            tab[j] = false; // a vérifier
            LonguestWord = parcour(noeud->fils[i], letters, tab, LonguestWord, LonguestLenght);
            tab[j] = true;
        }
    }
    return LonguestWord;
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