#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern char* strdup(const char*);  // strdup not declared in C99

#include "Dict.h"


typedef struct Node_t {
    char* key;
    void* data;
    struct Node_t* next;
} Node;

struct Dict_t {
    size_t size;
    size_t nbKeys;
    Node** array;
};


static size_t hash(const char* key) {
    size_t length = strlen(key);
    size_t sum = 0, base = 1, mod = 1000000007;

    for (size_t i = 0; i < length; i++) {
        sum = (sum + base * key[i]) % mod;
        base = (base * 256) % mod;
    }

    return sum;
}

Dict* dictCreateEmpty() {
    Dict* d = malloc(sizeof(Dict));
    if (!d)
        return NULL;

    d->size = 1000;
    d->nbKeys = 0;
    d->array = calloc(d->size, sizeof(Node*));
    if (!d->array) {
        free(d);
        return NULL;
    }

    return d;
}

size_t dictNbKeys(Dict* d) {
    return d->nbKeys;
}

void dictFree(Dict* d) {
    Node* a;
    Node* b;

    for (size_t i = 0; i < d->size; i++) {
        a = d->array[i];

        while (a) {
            b = a->next;
            free(a->key);
            free(a);
            a = b;
        }
    }

    free(d->array);
    free(d);
}

static Node* dictGet(Dict* d, const char* key) {
    Node* n = d->array[hash(key) % d->size];

    while (n && strcmp(n->key, key) != 0)
        n = n->next;

    return n;
}

int dictContains(Dict* d, const char* key) {
    return dictGet(d, key) != NULL;
}

void* dictSearch(Dict* d, const char* key) {
    //fprintf(stderr, "Je print key : %s \n", key);
    Node* n = dictGet(d, key);

    if (n)
        return n->data;
    else
        return NULL;
}

void dictInsert(Dict* d, const char* key, void* data) {
    //fprintf(stderr, "Je print key : %s et je print data : %s \n", key, data);
    Node* n = dictGet(d, key);

    if (n)
    {
        //fprintf(stderr, "Je passe ici \n");
        n->data = data;
    }
    else {
        size_t i = hash(key) % d->size;

        n = malloc(sizeof(Node));
        n->key = strdup(key);
        n->data = data;
        n->next = d->array[i];
        d->array[i] = n;
        d->nbKeys++;
    }
    
    double alpha = ((double) (d->nbKeys))/((double) (d->size));
    /*if(alpha > 0.7)
    {
        d->nbKeys = 0;

        Dict* news = dictCreateEmpty();
        int length = d->size;
        news->size = 2*d->size;
        news->array = calloc(2*d->size, sizeof(Node));
        Node* tmp = malloc(sizeof(Node));


        for(int i = 0; i < length; i++)
        {
            if(d->array[i] != 0)
            {
                tmp = d->array[i];
                //fprintf(stderr, "Je print key : %s, et data : %s \n", tmp->key, tmp->data);
                fprintf(stderr, "je rpint i : %d \n");
                dictInsert(news,tmp->key, tmp->data);
                
            }
        }
        for(int i = 0; i < 2 * d->size; i++)
        {
            d->array[i] = news->array[i];
            fprintf(stderr, "Je passe ici");
        }

        dictFree(news);

    }*/
    Node* tmp;
    char* datatmp;
    char* keytmp;
    Node* nexttmp;
    if(alpha > 0.7) //On re-hash
    {
        d->nbKeys = 0; 
        Node** arraytmp = calloc(d->size, sizeof(Node*));
        for(int i = 0; i < (int) d->size; i++)
        {
            arraytmp[i] = d->array[i];
        }
        d->array = calloc(2*d->size, sizeof(Node*)); //On alloue de la mémoire en plus dans la structure

        int lenght = d->size;
        d->size = 2*d->size;
        //fprintf(stderr, "Je print la taille du tab %d \n", d->size); 

        for(int i = 0; i < lenght; i++)
        {
            if(arraytmp[i] != 0 || arraytmp[i] != NULL)
            {
                tmp = arraytmp[i];
                
                keytmp = tmp->key;
                datatmp = tmp->data;
                nexttmp = tmp->next;
                //fprintf(stderr, "Je print la key : %s et la data : %s iciiiiii\n", arraytmp[i]->key, arraytmp[i]->data);

                dictInsert(d, keytmp, datatmp);
                while(nexttmp != NULL)
                {
                    //fprintf(stderr, "Je passe ici \n");
                    datatmp = nexttmp->data;
                    keytmp = nexttmp->key;
                    dictInsert(d, keytmp, datatmp);
                    nexttmp = nexttmp->next;
                }
            }
        }
        //fprintf(stderr, "Je print le nombre de keys %d \n", d->nbKeys);
        /*nexttmp = NULL;
        Node* nexttmpnext = NULL;
        for(int i = 0; i < lenght; i++)
        {
            if(arraytmp[i] != NULL)
            {
                nexttmp = arraytmp[i];
                free(arraytmp[i]);
                while(nexttmp != NULL)
                {
                    nexttmpnext = nexttmp->next;
                    free(nexttmp);
                }

            }
        }*/
        //free(arraytmp);
    }
    /*if(alpha > 0.7)
    {
        d->nbKeys = 0;
        Dict* newDict = dictCreateEmpty();
        newDict->array = calloc(d->size, sizeof(Node));

        Node* node;
        char* key;
        char* data;

        for(int i = 0; i < d->size; i++)
        {
            node = d->array[i];
            fprintf(stderr, "Je print i %d \n", i);
            if(node != NULL)
            {
                key = node->key;
                data = node->data;
                dictInsert(newDict, key, data);
                fprintf(stderr, "Je print key : %s, et data : %s \n", node->key, node->data);
            }
        }
    }*/
    /*if(alpha >= 0.7)
    {
        Node* n;
        Node** array = calloc(2 * d->size, sizeof(Node*));
        for(int i = 0; i < d->size; i++)
        {
            n = d->array[i];
            while(n != NULL)
            {
                int index = hash(n->key)%(2 * d->size);
                Node* iternode = array[index];
                if(index)
                {
                    while(iternode->next)
                    {
                        iternode = iternode->next;
                        iternode->next = n;
                    }
                }
                else
                    array[index] = n;
            }
            //fprintf(stderr, "Je print key : %s, et data : %s \n", n->key, n->data);
            Node* tmp = n->next;
            n->next = NULL;
            n = tmp;
        }
    }*/
}
