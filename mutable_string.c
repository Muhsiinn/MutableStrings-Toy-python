#include "mutable_string.h"

#include <stdlib.h>
#include <stdint.h>
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


int ms_append(MutableString *s,const char *text)
{
  if(s==NULL | text == NULL){
    return -1;
  }
  
  size_t text_length = strlen(text);

  if (text_length > SIZE_MAX -s ->length -1){
    return -1;
  }

  size_t new_length = s->length + text_length;
  size_t required_capacity = new_length + 1; 
  //if we use the required_capacity capacity here we will use memory without looking. that maybe a momory overuse 
  //
  if (required_capacity > s->capacity){
    size_t new_capacity = s->capacity;

    if(new_capacity == 0){
      new_capacity = 1; 
    }
    while (new_capacity < required_capacity){    

      if (new_capacity > SIZE_MAX/2){
        new_capacity = required_capacity;
        break; 

      }
      new_capacity *=2;


    }
    // if the new capacity is less than required we keep extending it. 
    char *new_data = realloc(s->data, new_capacity);
    if (new_data ==NULL){
      return -1; 
    }
    s->data = new_data;
    s-> capacity = new_capacity;
  }
  memcpy(s->data+s->length,text,text_length +1 );
  s->length = new_length;
  return 0; 

}

