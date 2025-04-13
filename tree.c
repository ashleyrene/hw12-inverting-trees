#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

static Tree *alloc_node(int data) {
    Tree *ret = calloc(1, sizeof(Tree));
    if (!ret) {
        return NULL;
    }
    ret->data = data;
    return ret;
}

// recursively reads a binary tree from a binary file
static Tree *read_tree(FILE *fp) {
    int value;
    unsigned char structure;

    // read value of the node
    if (fread(&value, sizeof(int), 1, fp) != 1) {
        return NULL;
    }
    // read structural information of the node
    if (fread(&structure, sizeof(unsigned char), 1, fp) != 1) {
        return NULL;
    }

    Tree *node = alloc_node(value);
    if (!node) {
        return NULL;
    }
    // recursively read left and right subtrees
    if (structure & 0b10) {
        node->left = read_tree(fp);
    }
    if (structure & 0b01) {
        node->right = read_tree(fp);
    }

    return node;
}
// opens and reads binary file 
Tree *read_from_file(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        return NULL;
    }

    Tree *root = read_tree(fp);
    fclose(fp);
    return root;
}
// recursively writes a binary tree to a file
static void write_tree(Tree *root, FILE *fp) {
    if (!root) return;
    // set structural byte 
    unsigned char structure = 0;
    if (root->left) structure |= 0b10;
    if (root->right) structure |= 0b01;
    // write node data and structure byte
    fwrite(&root->data, sizeof(int), 1, fp);
    fwrite(&structure, sizeof(unsigned char), 1, fp);

    write_tree(root->left, fp);
    write_tree(root->right, fp);
}
// opens binary file and writes binary tree
void preorder_print(Tree *root, char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return;

    write_tree(root, fp);
    fclose(fp);
}
// recursively inverts a binary tree by swapping children
Tree *invert_tree(Tree *root) {
    if (!root) return NULL;
    // swap children
    Tree *temp = root->left;
    root->left = invert_tree(root->right);
    root->right = invert_tree(temp);

    return root;
}
//free all memory allocated 
void free_tree(Tree *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
