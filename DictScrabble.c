#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Dict.h"
#include "LinkedList.h"
#include "Scrabble.h"


struct ScrabbleDict_t {
    Dict* dico;
};

/*struct List_t {
    Node* head;
    Node* tail;
    size_t length;
};

struct Node_t {
    char* key;
    void* data;
    struct Node_t* next;
};*/

char* ascendingOrderString(char* words) {
  int i, j;
  char temp;
  char* input = words;
  //fprintf(stderr, "Je print le char avant, %s \n",input);

  int stringLength = strlen(input);

  for (i = 0; i < stringLength - 1; i++) {
    for (j = i + 1; j < stringLength; j++) {
      if (input[i] > input[j]) {
        temp = input[i];
        input[i] = input[j];
        input[j] = temp;
      }
    }
  }
  //fprintf(stderr, "Je print le char après, %s \n",input);
  return input;
}

static void sortwordd(char* letters)
{
    //fprintf(stderr,"Je print la chaine de caractère avant :%s \n", letters);
    int length = strlen(letters);
    for(int i = 1; i < length; i++)
    {
        int j = i - 1;
        while(j >= 0 && letters[j] > letters[i])
        {
            letters[j + 1] = letters[j];
            j = j - 1;
        }
        letters[j + 1] = letters[i];
    }
    //fprintf(stderr,"Je print la chaine de caractère après,%s \n", letters);
}

ScrabbleDict* scrabbleCreateDict(List* words) {
    ScrabbleDict* dict = malloc(sizeof(ScrabbleDict));
    if(dict == NULL)    
        return 0;
    
    dict->dico = dictCreateEmpty();

    //dict->dico->size = llLength(words);
    //fprintf(stderr, "Je passe avant malloc");
    //fprintf(stderr, "Je passe après malloc");

    //fprintf(stderr,"Je print la length du dico, %d \n", dict->dico->size);
    //fprintf(stderr,"Je print la longueur du dico dans sort word,%d \n", dictNbKeys(dict));
    Node* tmp = llCreateEmpty();
    tmp = llHead(words);
    //tmp = words->head;
    char* key;
    char* test;

    strcpy(key, llData(tmp));

    /*Node* test = llCreateEmpty();
    test = llCreateNode(llData(words->head));*/

    while(tmp != llTail(words)) 
    {
        //fprintf(stderr, "Je passe dans le boucle \n");
        //fprintf(stderr,"Je print ici %s \n", tmp->data)

        /*fprintf(stderr,"Je print la key : %s \n", key);
        fprintf(stderr,"Je print le data :%s \n", data);*/

        //fprintf(stderr,"Je passe ici 1 \n");

        strcpy(key, llData(tmp));
        ascendingOrderString(llData(tmp));
        //fprintf(stderr,"Je passe après la fonction de tri");
        test = llData(tmp);

        //fprintf(stderr,"Je print la key : %s \n", key);
        //fprintf(stderr,"Je print le data :%s \n", test);
        
        //fprintf(stderr,"Je print le taille du dico dans le main, %d \n", dict->size);
        dictInsert(dict->dico, test, key);
        //llNext(tmp);
        //fprintf(stderr,"Je passe avant4\n");
        tmp = llNext(tmp);
        //printf("Je passe ici 4\n");
    }
    return dict;
}

void scrabbleFreeDict(ScrabbleDict* sd) {
    dictFree(sd->dico);
    free(sd);
}

char* scrabbleFindLongestWord(ScrabbleDict* sd, const char* letters) {
    //On va commencer par trier le mot
    fprintf(stderr,"Je print le char, %s \n", letters);
    char* word = letters;
    char* result;
    ascendingOrderString(word);
    fprintf(stderr,"Je print le char après le tric, %s \n", word);

    int stringLength = strlen(word);
    fprintf(stderr,"Je print la longueuer du char, %d \n", stringLength);
    for(int i = stringLength - 1; i > 0; i--)
    {
        if(dictSearch(sd->dico, word) != NULL)
        {
            result = dictSearch(sd->dico, word);
            //fprintf(stderr,"Je print le char, %s", result);
            return result;
        }
        else
            word[i] = '\0';
    }   
}
