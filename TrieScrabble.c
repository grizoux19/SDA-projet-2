#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Dict.h"
#include "LinkedList.h"
#include "Scrabble.h"

static char* ascendingOrderString(char* words);

struct ScrabbleDict_t {
    Dict * dico;
};


ScrabbleDict* scrabbleCreateDict(List* words) {
    ScrabbleDict* dict = malloc(sizeof(ScrabbleDict));
    if(dict == NULL)    
        return 0;

    dict->dico = dictCreateEmpty();
    
    Node* tmp;
    tmp = llHead(words);
    char* sortedword = malloc(sizeof(char));

    
    while(tmp)
    {
        char* word = llData(tmp);
        memmove(sortedword, word, strlen(word)*sizeof(char*));
        sortedword = ascendingOrderString(sortedword);
        //fprintf(stderr, "Je print la key : %s, la data : %s et la longueur du char %d  dans dict\n", sortedword, word, strlen(word));
        dictInsert(dict->dico, sortedword, word);
        //fprintf(stderr, "Je print la key : %s, la data : %s dans create \n", sortedword, dictSearch(dict->d, sortedword));
        tmp = llNext(tmp);
    }

    free(tmp);
    return dict;
}

void scrabbleFreeDict(ScrabbleDict* sd) {
    dictFree(sd->dico);
    free(sd);
}

char* scrabbleFindLongestWord(ScrabbleDict* sd, const char* letters) {
  char* key = ascendingOrderString(letters);
  char* LonguestWord = dictSearchLongest(sd->dico,key);
  return LonguestWord;
    
}
 
char* ascendingOrderString(char* words) { // ca devrait pas etre word ?
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