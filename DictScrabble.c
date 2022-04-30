#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Dict.h"
#include "LinkedList.h"
#include "Scrabble.h"

char* ascendingOrderString(char* input) 
{
  int i, j;
  char temp;

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

    Node* tmp = llHead(words);
    //tmp = llHead(words);
    char* data = malloc(sizeof(char));
    char* key = malloc(sizeof(char));
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

/*void* cut(char input[], char output[], int j)
{
    int length = strlen(input);
    for(int i = 0; i < length; i++)
    {
        if(j != i)
            output[i] = input[i];
        else
            continue;
    }
    fprintf(stderr, "Je prunt la cut %s\n", output);
}*/

/*void* cut(char input[], char output[], int j)
{
    int length = strlen(input);
    int k = 0;// Pour le tableau input
    int i = 0;//Pour le tableau ouput
    for(; i < length; k++)
    {
        if(j != k)
        {
            memmove(output + i, input + k, sizeof(char));
            i++;
        }        
    }
    //fprintf(stderr, "Je prunt la cut %s\n", output);
}


char* search(Dict* sd, char* input, int length)
{
    Node* n;
    //fprintf(stderr, "Je print input %s \n", input);
    n = dictSearch(sd, input);
    
    if(n != NULL && llData(n))
        return llData(n);
    else //On doit fournir toutes le combinaisons possible du bail
    {
        for(int i = 0; i < length; i++)
        {
            if(length - 1 == 0)
                return 0;
            char tmp[length - 1];
            cut(input, tmp, i);
            dictSearch(sd, tmp);
            search(sd, tmp, length - 1);
        }
    }
}*/
char* checkk(ScrabbleDict*, char*, char*, int, int, int, int);
char* checkk(ScrabbleDict* sd,char* word, char* tmp, int start, int end, int index, int r)
{
    
    if(index == r)
    {
        /*fprintf(stderr,"Je print le result : %s \n", tmp);
        Node* n = dictSearch(sd->d, tmp);
        if(n != NULL)
            return tmp;
        else
            return NULL;*/
        fprintf(stderr,"Je print le result : %s \n", tmp);
        return tmp;
    }
    for(int i = start; i <= end && end - i + 1 >= r - index; i++)
    {
        tmp[index] = word[i];
        checkk(sd, word, tmp, i + 1, end, index + 1, r);
    }

}

char* getallcombinaison(ScrabbleDict* sd, char* word, int length, int r)
{
    char* tmp = calloc(length, sizeof(char));
    tmp[length] = '\0';

    //char* result = malloc(sizeof(char));
    char* result = malloc(sizeof(char));
    result = checkk(sd, word, tmp, 0, length - 1, 0, r);
    //fprintf(stderr,"Je print le result : %s \n", result);
    return result;
}



char* scrabbleFindLongestWord(ScrabbleDict* sd, const char* letters) { //ATTENTION CHANGERS LETTERS
    
    char* word = malloc(sizeof(char));
    
    char letter[6];
    letter[0]= 'a';
    letter[1]= 'b';
    letter[2]= 'c';
    letter[3]= 'd';
    letter[4]= 'e';
    letter[5]= '\0';
    memmove(word, letter, strlen(letter)*sizeof(char));
    
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
    fprintf(stderr,"Je print result %s", result);
    return result;
}

