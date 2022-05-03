#include <stdio.h>
#include <stdlib.h>

#include "int_element.h"
#include "str_element.h"
#include "element.h"

/* If the string is numeric, return an int_element. Otherwise return a str_element. */
struct element *parse_string(char *str)
{
  char *endp;
  /* strtol returns a pointer to the first non-numeric character in endp.
     If it gets to the end of the string, that character will be the null terminator. */
  int value = strtol(str, &endp, 10);
  if (str[0] != '\0' && endp[0] == '\0')
  {
    /* String was non-empty and strtol conversion succeeded - integer */
    return (struct element *)int_element_new(value);
  }
  else
  {
    return (struct element *)str_element_new(str);
  }
}

int helpSort(const void *e0, const void *e1)
{
  if (e0 != NULL || e1 != NULL)
  {
    struct element **ptre0 = (struct element **)e0;
    struct element **ptre1 = (struct element **)e1;
    int result = (*ptre0)->class->compare((*ptre0), (*ptre1));
    return result;
  }

  else if (e0 == NULL)
    return 1;
  else if (e1 == NULL)
    return -1;
}

int main(int argc, char **argv)
{
  /* TODO: Read elements into a new array using parse_string */

  struct element **arrgs = malloc((argc - 1) * sizeof(struct element *));

      for (int i = 0; i < argc - 1; i++)
  {
    arrgs[i] = parse_string(argv[i + 1]);
  }
  /* TODO: Sort elements with qsort */
  qsort(arrgs, argc - 1, sizeof(struct element), helpSort);

      printf("Sorted: ");

  /* TODO: Print elements, separated by a space */
  for (int i = 0; i < argc - 1; i++)
  {
    arrgs[i]->class->print(arrgs[i]);
    printf(" ");
    rc_free_ref((void*)arrgs[i]);
  }
  free(arrgs);
  printf("\n");
}
