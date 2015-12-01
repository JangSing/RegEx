#include "unity.h"
#include "Regex.h"
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_module_generator_needs_to_be_implemented(void)
{
  LinkedList *list=createLinkedList();
  
  Match *match;
  char *str="a";
  char *pattern[]={"\\a","\\s","\\d"};
  int i;
  
  for(i=0;i<sizeof(pattern)/4;i++)
    AddLast(createListElement(pattern[i]),list );
  
  match=matchObjectregEx("a 1asas",list);
    
  printf("%s\n",match->text);

}
