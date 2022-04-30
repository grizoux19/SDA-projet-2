#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Dict.h"
#include "LinkedList.h"
#include "Scrabble.h"

char* getallcombinaison(ScrabbleDict*, char*, int, int);
char* checkk(ScrabbleDict*, char*, char*, int, int, int, int, char*);
char* ascendingOrderString(char*);
char* ascendingOrderString(char* input) 
{
  char temp;
  int stringLength = strlen(input);

  for (int i = 0; i < stringLength - 1; i++) 
  {
    for (int j = i + 1; j < stringLength; j++) 
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
    //tmp = llHead(words);
    //char* data = malloc(sizeof(char));
    //char* key = malloc(sizeof(char));
    char* sortedword = malloc(sizeof(char));
    
    while(tmp)
    {
        char* word = llData(tmp);
        memmove(sortedword, word, strlen(word)*sizeof(char*));
        sortedword = ascendingOrderString(sortedword);
        //fprintf(stderr, "Je print la key : %s, la data : %s et la longueur du char %d  dans dict\n", sortedword, word, strlen(word));
        dictInsert(dict->d, sortedword, word);
        //fprintf(stderr, "Je print la key : %s, la data : %s dans create \n", sortedword, dictSearch(dict->d, sortedword));
        tmp = llNext(tmp);
    }
    /*tmp = llHead(words);
    Node* n = malloc(sizeof(Node*));
    //fprintf(stderr, "Je print le nombre de key : %d \n", dictNbKeys(dict->d));
    while(tmp)
    {
        char* word = llData(tmp);
        memmove(sortedword, word, strlen(word)*sizeof(char*));
        sortedword = ascendingOrderString(sortedword);
        //fprintf(stderr, "Je print la key : %s, la data : %s et la longueur du char %d  dans dict\n", sortedword, word, strlen(word));
        n = dictSearch(dict->d, sortedword);
        if(n)
        {
        data = llData(n);
        if(data != NULL && data)
        {
            fprintf(stderr, "Je print la key : %s, la data : %s  dans dict\n", sortedword, data);
        }
        else
            fprintf(stderr, "data nulle \n");
        }
        tmp = llNext(tmp);
    }*/
    

    return dict;    
}

void scrabbleFreeDict(ScrabbleDict* sd) {
    dictFree(sd->d);
    free(sd);
}



char* checkk(ScrabbleDict* sd,char* word, char* tmp, int start, int end, int index, int r, char* result)
{
    //char* result = calloc(r, sizeof(char));
    if(index == r)
    {
        /*fprintf(stderr,"Je print le result : %s \n", tmp);
        Node* n = dictSearch(sd->d, tmp);
        if(n != NULL)
            return tmp;
        else
            return NULL;*/
        //fprintf(stderr,"Je print le result : %s \n", tmp);
        memmove(result, tmp, strlen(tmp) * sizeof(char*));
        return result;
    }
    for(int i = start; i <= end && end - i + 1 >= r - index; i++)
    {
        tmp[index] = word[i];
        checkk(sd, word, tmp, i + 1, end, index + 1, r, result);
    }

}

char* getallcombinaison(ScrabbleDict* sd, char* word, int length, int r)
{
    //char* tmp = calloc(length, sizeof(char*));
    char tmp[r];
    tmp[r] = '\0';

    //char* result = malloc(sizeomake f(char));
    //char* result = calloc(r, sizeof(char));
    char* result;
    checkk(sd, word, tmp, 0, length - 1, 0, r, result);
    //fprintf(stderr,"Je print le result : %s \n", result);
    return result;
}



char* scrabbleFindLongestWord(ScrabbleDict* sd, const char* letters) { //ATTENTION CHANGERS LETTERS
    
    char* word = malloc(sizeof(char));
    
    //fprintf(stderr,"Je print les lettres dans scrabble find longuest : %s \n",letters);

    /*char letter[5];
    letter[0]= 'a';
    letter[1]= 'b';
    letter[2]= 'c';
    letter[3]= 'd';
    letter[4]= 'e';
    letter[5]= '\0';*/
    memmove(word, letters, strlen(letters)*sizeof(char));
    
    char* result = malloc(sizeof(char));
    ascendingOrderString(word);
    int stringLength = strlen(word);

    //fprintf(stderr,"Je passe ici \n");
    Node* n = malloc(sizeof(Node*));
    for(int i = stringLength; i >= 0; i--)
    {
        result = getallcombinaison(sd, word, stringLength, i);
        n = dictSearch(sd->d, result);
        if(n != NULL)
            break;        
    }
    //fprintf(stderr,"Je print result %s \n \n", result);
    //fprintf(stderr," Je vais print la data de la clé : %s \n", dictSearch(sd->d, result));
    //exit(0);
    return result;
}

