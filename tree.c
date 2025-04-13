#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * TODO: Implement all the functions in tree.h here.
 *
 * Use as many helper functions as you need, just declare them to be static.
 *
 */

static Tree *alloc_node(int data) {
  Tree *ret = calloc(1, sizeof(Tree));
  if (ret == NULL) {
    return NULL;
  }

  ret->data = data;

  return ret;
}
