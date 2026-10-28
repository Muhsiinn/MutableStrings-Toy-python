#include "mutable_string.h"

#include <stdlib.h> 
#include <string.h> 


MutableString *ms_create(const char *inital)
{

  if (inital==NULL){
    return NULL;
  }
  
  size_t length = strlen(inital);

  MutableString *s = malloc(sizeof(MutableString));

  if (s==NULL){
    return NULL;
  }

  s->capacity = length + 1;
  s->data = malloc(s->capacity);

  if(s->data==NULL){
    free(s);
    return NULL;
  }
  memcpy(s->data,inital,length+1);
  s->length=length;

  return  s;


}

void ms_destroy(MutableString *s)
{
  if(s==NULL){
    return;

  }

  free(s->data);
  free(s);
}

