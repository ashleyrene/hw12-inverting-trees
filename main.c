#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    assert(argc == 3);  // ensure correct number of arguments

    Tree *root = read_from_file(argv[1]);
    assert(root != NULL);  // ensure tree was read successfully

    Tree *inverted = invert_tree(root);
    assert(inverted != NULL);  // should not be NULL if root wasn't

    preorder_print(inverted, argv[2]);

    free_tree(inverted);    // free memory
    return EXIT_SUCCESS;
}
