#include <stdio.h>
#include "mutable_string.h"

int main(void)
{

MutableString *s = ms_create("Muhsin is a good boy");

if (s==NULL){
    fprintf(stderr,"Allocation failed\n");
    return  1;
  }
printf("String: %s\n",s->data);
printf("length: %zu\n",s->length);
printf("Capacity: %zu\n",s->capacity);

ms_destroy(s);
return 0;


}
