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
    d->array = calloc(d->size, sizeof(Node));
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
        n->data = data;
    else {
        size_t i = hash(key) % d->size;

        n = malloc(sizeof(Node));
        n->key = strdup(key);
        n->data = data;
        n->next = d->array[i];
        d->array[i] = n;
        d->nbKeys++;
    }

    /*Node** array = malloc(d->size * sizeof(Node*));
        array = d->array;

        d->array = calloc(2*d->size, sizeof(Node*));
        int length = d->size;
        d->size = 2*d->size;*/

    
    double alpha = ((double) (d->nbKeys))/((double) (d->size));
    /*if(alpha > 0.7)
    {
        d->nbKeys = 0;

        Dict* news = dictCreateEmpty();
        int length = d->size;
        news->size = 2*d->size;
        news->array = calloc(2*d->size, sizeof(Node));


        for(int i = 0; i < length; i++)
        {
            if(d->array[i] != 0)
            {
                Node* tmp = malloc(sizeof(Node*));
                tmp = d->array[i];
                //fprintf(stderr, "Je print key : %s, et data : %s \n", tmp->key, tmp->data);
                dictInsert(news,tmp->key, tmp->data);
            }
        }

    }*/
    if(alpha > 0.7)
    {
        Dict* newDict = dictCreateEmpty();
        int length = d->size;
        newDict->size = 2*d->size;
        newDict->array = calloc()
    }
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
