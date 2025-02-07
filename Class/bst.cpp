#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[101];
    struct Student *left, *right;
};

struct Student *createStudent(int id, char *name) {
    struct Student *newStudent = (struct Student*)malloc(sizeof(Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}

struct Student *insert(struct Student *root, int id, char *name) {
    // Case 1: kalo tree blm dibuat, kita bikin root nodenya
    if (root == NULL) {
        return createStudent(id, name);
    }

    // Case 2: ID yang kita mau insert > current node punya ID
    else if (id > root->id) {
        root->right = insert(root->right, id, name);
    }
    
    // Case 3: ID yang mau kita insert < current node punya ID
    else if (id < root->id) {
        root->left = insert(root->left, id, name);
    }

    return root;
}

int main () {
    struct Student *root = NULL;

    puts("Inserting: ");
    root = insert(root, 3, "bill");
    root = insert(root, 1, "tom");
    root = insert(root, 16, "jake");
    root = insert(root, 78, "diana");
    root = insert(root, 33, "eve");

    puts("Inserting Succesfull!");

    return 0;
}