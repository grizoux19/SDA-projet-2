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
    return d->size;
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
    //fprintf(stderr, "Je passe dans dictget \n");
    
    Node* n = d->array[hash(key) % d->size];

    //fprintf(stderr, "Je passe dans dictget \n ");
    while (n && strcmp(n->key, key) != 0)
        n = n->next;
    //fprintf(stderr, "Je passe dans dictget dernière fois \n ");
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
    //fprintf(stderr, "Je print la size du dico dans dicoinsert, %d \n", d->size);
    Node* n = dictGet(d, key);
    double alpha = ((double) (d->nbKeys))/((double) (d->size));
    if(alpha > 0.7) //On reash
    {
        Node** array = malloc(2*d->size * sizeof(Node*));
    }

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

    //fprintf(stderr, "Je fini de passer dans dictInsert \n");
    }
}
