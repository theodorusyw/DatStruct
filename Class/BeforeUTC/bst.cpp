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

    // Case 4: kalo valuenya udah ada, kita return nodenya saja

    return root;
}

void inorder(struct Student *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("Student ID: %d, Name: %s\n", root->id, root->name);
    inorder(root->right);
}

void preorder(struct Student *root) {
    if (root == NULL) return;
    printf("Student ID: %d, Name: %s\n", root->id, root->name);
    preorder(root->left);
    preorder(root->right);
}
void postorder(struct Student *root) {
    if (root == NULL) return;
    printf("Student ID: %d, Name: %s\n", root->id, root->name);
    postorder(root->left);
    postorder(root->right);
}

struct Student *search(struct Student *root ,int id) {
    // Case 1: kalo Search ga ketemu
    if (root == NULL) {
        puts("Not Found!");
        return NULL;
    }

    //Case 2: kalos Search ketemu
    else if (root->id == id) {
        puts("Found!");
        return root;
    }

    // Case 3: kalo ID yang mau disearch lebih besar dari current id
    else if (id > root->id) {
        return search(root->right, id);
    }

    // Case 4: kalo ID yang mau disearch lebih kecil dari current id
    else if (id < root->id) {
        return search(root->left, id);
    }
}
struct Student *update(struct Student *root ,int id, char *name) {
    // Case 1: kalo update ga ketemu
    if (root == NULL) {
        puts("Not Found!");
        return NULL;
    }

    //Case 2: kalos update ketemu
    else if (root->id == id) {
        puts("Found!");
        return root;
    }

    // Case 3: kalo ID yang mau diupdate lebih besar dari current id
    else if (id > root->id) {
        return update(root->right, id, name);
    }

    // Case 4: kalo ID yang mau diupdate lebih kecil dari current id
    else if (id < root->id) {
        return update(root->left, id, name);
    }
}


int main() {
    struct Student *root = NULL;

    // Insertion
    puts("Inserting: ");
    root = insert(root, 3, "bill");
    root = insert(root, 1, "tom");
    root = insert(root, 16, "jake");
    root = insert(root, 78, "diana");
    root = insert(root, 33, "eve");
    puts("Inserting Succesfull!");

    // Traversal
    puts("Inorder Traversal: ");
    inorder(root);

    // Searching
    struct Student *searchedStudent = search(root, 378);
    if (searchedStudent != NULL) {
        printf("Found Student with id %d and name %s\n", searchedStudent->id, searchedStudent->name);
    }

    // Updating
    puts("\nUpdating: ");
    struct Student *updatedStudent = update(root, 1, "tommy");
    if (updatedStudent != NULL) {
        printf("Updated Students with id %d and name %s\n", updatedStudent->id, updatedStudent->name);
    }

    puts("\nTraversal After Updating: ");
    inorder(root);
    puts("\nPreorder:");
    preorder(root);
    puts("\nPostorder:");
    postorder(root);

    return 0;
}