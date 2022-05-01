#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Dict.h"
#include "LinkedList.h"
#include "Scrabble.h"

void* makeCombinaisons(ScrabbleDict*, char*, int, int, int, char*, int);
void* sortWord(char*);
void* allCombinaisons(ScrabbleDict*, char*, int, int);

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

struct ScrabbleDict_t {
    Dict* d;
};

ScrabbleDict* scrabbleCreateDict(List* words) 
{
    ScrabbleDict* dict = malloc(sizeof(ScrabbleDict));
    if(dict == NULL)
        return 0;
    
    dict->d = dictCreateEmpty();
    if(dict->d == NULL)
        return 0;

    Node* tmp = llHead(words);
    char* sortedword = malloc(sizeof(char));
    
    while(tmp)
    {
        char* word = llData(tmp);
        memmove(sortedword, word, strlen(word)*sizeof(char*));
        sortWord(sortedword);
        //fprintf(stderr, "Je print la key : %s, la data : %s et la longueur du char %d  dans dict\n", sortedword, word, strlen(word));
        dictInsert(dict->d, sortedword, word);
        //fprintf(stderr, "Je print la key : %s, la data : %s dans create \n", sortedword, dictSearch(dict->d, sortedword));
        tmp = llNext(tmp);
    }
    free(tmp);
    free(sortedword);    
    return dict;    
}

void scrabbleFreeDict(ScrabbleDict* sd) {
    dictFree(sd->d);
    free(sd);
}

void* makeCombinaisons(ScrabbleDict* sb, char* sortedletters, int lengthletters, int i, int index, char* output, int j)
{
    if(index == i)
    {
        //fprintf(stderr,"Je print le mot : %s \n", output);
        return dictSearch(sb->d,(void*) output);
    }
    if(j >= lengthletters)
        return NULL;

    output[index] = sortedletters[j];
    void*  result = makeCombinaisons(sb, sortedletters, lengthletters, i, index + 1, output, j + 1);
    if(result != NULL)
        return result;
    else
    {
        return makeCombinaisons(sb, sortedletters, lengthletters, i, index, output, j + 1);        
    }
}

void* allCombinaisons(ScrabbleDict* sb, char* sortedletters, int lengthletters, int i)
{
    char output[i + 1];
    output[i + 1] = '\0';

    return makeCombinaisons(sb, sortedletters, lengthletters, i, 0, output, 0);

}

char* scrabbleFindLongestWord(ScrabbleDict* sd, const char* letters) 
{ 
    int lengthletters = strlen(letters);
    char* sortedletters = calloc(lengthletters, sizeof(char));
    memmove(sortedletters, letters, lengthletters * sizeof(char));
    sortWord(sortedletters);
    //fprintf(stderr, "Je print les lettres triées : %s\n", sortedletters);

    char* result = calloc(lengthletters, sizeof(char));
    for(int i = lengthletters ; i ; i--)
    {
        fprintf(stderr, "Je print i : %d \n",i);
        result = allCombinaisons(sd, sortedletters, lengthletters, i);
        if(result != NULL)
            break;
    }
    fprintf(stderr,"Je print result: %s\n", result);
    free(sortedletters);
    //exit(0);
    return result;
}

