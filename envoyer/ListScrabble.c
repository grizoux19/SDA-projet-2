#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Scrabble.h"


struct ScrabbleDict_t {
    List* words;
};

static bool match(const char* letters, char* word)
{
    size_t nbLetters = strlen(letters);
    size_t lengthWord = strlen(word);

    if (lengthWord > nbLetters)
        return false;
    
    int tmp;

    char* tab = calloc(26, sizeof(char));

    for(size_t i = 0; i < nbLetters; i++)
    {
        tmp = letters[i] - 97;
        tab[tmp]++;
    }
    for(size_t i = 0; i < lengthWord; i++)
    {
        tmp = word[i] - 97;
        if(tab[tmp] == 0)
            return false;
        else
            tab[tmp]--;
    }   
    free(tab); 
    return true;
}

ScrabbleDict* scrabbleCreateDict(List* words) {
    ScrabbleDict* sd = malloc(sizeof(ScrabbleDict));
    if (!sd)
        return NULL;

    sd->words = words;

    return sd;
}

void scrabbleFreeDict(ScrabbleDict* sd) {
    free(sd);
}

char* scrabbleFindLongestWord(ScrabbleDict* dict, const char* letters) {
    char* longestWord = NULL;
    size_t longestLength = 0;

    for (Node* p = llHead(dict->words); p != NULL; p = llNext(p)) {
        char* word = llData(p);

        if (match(letters, word)) {
            size_t length = strlen(word);

            if (length > longestLength) {
                longestWord = word;
                longestLength = length;
            }
        }
    }
    return longestWord;
}
