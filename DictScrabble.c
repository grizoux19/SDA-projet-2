#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Dict.h"
#include "LinkedList.h"
#include "Scrabble.h"

char* ascendingOrderString(char* words) 
{
  int i, j;
  char temp;
  char* input = words;

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
  return input;
}


struct ScrabbleDict_t {
    Dict* d;
};

char* copydata(char* input)
{
    int length = strlen(input);
    char* output;
    /*char output[length + 1];
    /*for(int i = 0; i < length; i++) 
    {
        output[i] = input[i];
    }
    output[length] = '\0';*/
    output = input;
    return output;
}

ScrabbleDict* scrabbleCreateDict(List* words) 
{
    ScrabbleDict* dict = malloc(sizeof(ScrabbleDict));
    if(dict == NULL)
        return 0;

    dict->d = dictCreateEmpty();
    if(dict->d == NULL)
        return 0;

    Node* tmp;
    tmp = llHead(words);
    char* data;
    char* key;
    while(tmp != llTail(words)) 
    {
        strcpy(data, llData(tmp));
        //data = copydata(llData(tmp));
        key = ascendingOrderString(llData(tmp));
        dictInsert(dict->d, key, data);
        tmp = llNext(tmp);
        //fprintf(stderr, "Je print la data disct search %s\n", dictSearch(dict->d, key));
        //fprintf(stderr, "Je print data %s et key %s \n \n",data,key);
    }
    return dict;    
}

void scrabbleFreeDict(ScrabbleDict* sd) {
    // à compléter
}

char* scrabbleFindLongestWord(ScrabbleDict* sd, const char* letters) {
    //On va commencer par trier le mot
    //fprintf(stderr,"Je print le char, %s \n", letters);
    char* word = letters;
    char* result;
    ascendingOrderString(word);
    //fprintf(stderr,"Je print le char après le tric, %s \n", word);

    int stringLength = strlen(word);
    //fprintf(stderr,"Je print la longueuer du char, %d \n", stringLength);
    for(int i = stringLength - 1; i > 0; i--)
    {
        if(dictSearch(sd->d, word) != NULL)
        {
            result = dictSearch(sd->d, word);
            //fprintf(stderr,"Je print le char, %s", result);
            return result;
        }
        else
            word[i] = '\0';
    }   
}

