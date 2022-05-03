#include "int_element.h"
#include "refcount.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

/* TODO: Implement all public int_element functions, including element interface functions.

You may add your own private functions here too. */

// the definition of the STRUCT int_element
struct int_element
{
    struct element_class *class;
    int int_val;
};

void int_print(struct element *int_to_print)
{
    printf("%d", int_element_get_value((struct int_element *)int_to_print));
}

int int_compare(struct element *e0, struct element *e1)
{
    if (is_int_element(e0))
    {
        if (is_int_element(e1))
        {
            int int0 = ((struct int_element *)(e0))->int_val;
            int int1 = ((struct int_element *)(e1))->int_val;

            if (int0 == int1)
                return 0;

            if (int0 > int1)
                return 1;

            if (int0 < int1)
                return -1;
        }
    }

    if (!is_int_element(e0))
        return 1;
    if (!is_int_element(e1))
        return -1;
}

struct element_class int_element_class = {int_print, int_compare};

/* Static constructor that creates new integer elements. */
struct int_element *int_element_new(int value)
{
    struct int_element *new_int = rc_malloc(sizeof(*new_int), NULL);

    if (new_int == NULL)
    {
        return NULL;
    }
    new_int->class = &int_element_class;
    new_int->int_val = value;

    return new_int;
}

/* Static function that obtains the value held in an int_element. */
int int_element_get_value(struct int_element *int_get_value)
{
    return int_get_value->int_val;
}

int is_int_element(struct element *int_to_test)
{
    return int_to_test->class == &int_element_class;
}