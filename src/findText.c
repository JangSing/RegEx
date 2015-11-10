#include "findText.h"
#include "Regex.h"

#include <stdio.h>
#include <stdlib.h>
/**
 * Find First (partial) word in the text and return the position of
 * the first letter
 *Eg.,
 *	text = Hello, my name is Alladin
 *	WordToFind = lad
 *  The return value is 20
 *
 * Input:
 *	text 	contains a bunch of words
 *	word 	is the (partial) word to find in the text
 * return:
 *	the position of the first letter found in text. if the word
 * 	cannot be found in the text, -1 is returned.
 */

Match *findText (char *text, char *word){
  int i=0;  //textIndex
  int j=0;  //wordIndex
  int firstIndex;
  int count=0;

  Match *match=malloc(sizeof(Match));

  match->possition=-1;

  while (text[i]!=0 )
  {
    if(word[j]==text[i])
    {
      if(count ==0)
        firstIndex = i;
      if((word[j+1]==0 && text[i+1]==0) || word[j+1]==0 ){
        match->possition=firstIndex;
        match->text=word;
        match->length=count+1;
        count = -1, j = 0;
      }
      else if(word[j+1]==text[i+1])
        j++;
      else if(word[j+1]!=text[i+1])
        count = -1, j = 0;
      count++;
    }
    i++;
  }


  return match;
}
