#include "str_element.h"
#include "refcount.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

/* TODO: Implement all public str_element functions, including element interface functions.

You may add your own private functions here too. */

struct str_element
{
    struct element_class *class;
    char *value;
};

void str_print(struct element *str_to_print)
{
    printf("%s", str_element_get_value((struct str_element*) str_to_print));
}

int str_compare(struct element *e0, struct element *e1)
{
    if (!is_str_element(e0))
        return -1;
    
    if (!is_str_element(e1))
        return 1;

    int compare_result = strcmp(((struct str_element*)(e0))->value, ((struct str_element*)(e0))->value);

    return compare_result;
}

struct element_class str_element_class = {str_print, str_compare};

void str_finalizer(void *p)
{
    struct str_element *str_to_free = p;
    rc_free_ref(str_to_free->value);
}

/* Static constructor that creates new string elements. */
struct str_element *str_element_new(char *value)
{
    struct str_element *new_str = rc_malloc(sizeof(*new_str), str_finalizer);

    if (new_str == NULL) {
        return NULL;
    }

    int new_str_len = strlen(value) + 1;
    new_str->value = rc_malloc(new_str_len, NULL);
    new_str->class = &str_element_class;
    memcpy(new_str->value, value, new_str_len);
    return new_str;


}

char *str_element_get_value(struct str_element *new_str)
{
    return new_str->value;
}

int is_str_element(struct element *str_to_test)
{
    return str_to_test->class == &str_element_class;
}