#include <stddef.h>

typedef struct {

  char *data;
  size_t length;
  size_t capacity;
}MutableString;

MutableString *ms_create(const char *intial);
void ms_destroy(MutableString *s);

int ms_append(MutableString *s,const char *text);
int ms_replace(MutableString *s,size_t index,char c);
int ms_insert(MutableString *s, size_t index,char c);
int ms_delete(MutableString *s, size_t index);
