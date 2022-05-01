#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Dict.h"
#include "LinkedList.h"
#include "Scrabble.h"

static void* sortWord(char* words);

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
    char* key = malloc(sizeof(char));
    char* data = malloc(sizeof(char));

    
    while(tmp) 
    {

      data = llData(tmp);
      
      memmove(key,data, strlen(data)*sizeof(char*));
      sortWord(key);
      dictInsert(dict->dico, key, data);
      //fprintf(stderr, "Je print la key : %s et la data associée : %s \n", key, dictSearch(dict->dico, key));
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
    char letter[5];
    letter[0]= 'a';
    letter[1]= 'b';
    letter[2]= 'c';
    letter[3]= 'd';
    letter[4]= '\0';

  int lengthletters = strlen(letters);
  char* sortedletters = calloc(lengthletters, sizeof(char));
  memmove(sortedletters, letters, lengthletters * sizeof(char));

  char* key = sortWord(sortedletters);
  char* LonguestWord = dictSearchLongest(sd->dico,key);
  //fprintf(stderr, "Je print le résultat : %s \n",LonguestWord);
  return LonguestWord;
    
}
 
void* sortWord(char* input) 
{
  char temp;
  int lengthinput = strlen(input);

  for (int i = 0; i < lengthinput; i++) 
  {
    for (int j = i + 1; j < lengthinput; j++) 
    {
      if (input[i] > input[j]) 
      {
        temp = input[i];
        input[i] = input[j];
        input[j] = temp;
      }
    }
  }
  return input;
}

