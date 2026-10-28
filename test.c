

#include <stdio.h>
#include "mutable_string.h"

int main(void)
{
    MutableString *s = ms_create("hello");

    if (s == NULL) {
        fprintf(stderr, "Creation failed\n");
        return 1;
    }

    if (ms_append(s, " Musi") != 0) {
        fprintf(stderr, "Append failed\n");
        ms_destroy(s);
        return 1;
    }

    printf("String: %s\n", s->data);
    printf("Length: %zu\n", s->length);
    printf("Capacity: %zu\n", s->capacity);

    ms_destroy(s);
    return 0;
}
