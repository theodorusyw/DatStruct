#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Struktur node untuk AVL Tree
struct node {
    int val;                // Nilai dari node
    int height;             // Tinggi dari node
    struct node* left;      // Pointer ke anak kiri
    struct node* right;     // Pointer ke anak kanan
};

// Fungsi untuk membuat node baru
node* createNode(int val) {
    node* c = (node*) malloc(sizeof(node)); // Alokasi memori untuk node baru
    c->val = val;                           // Set nilai node
    c->height = 1;                          // Tinggi awal node adalah 1
    c->left = NULL;                         // Anak kiri NULL
    c->right = NULL;                        // Anak kanan NULL
    return c;                               // Kembalikan node baru
}

// Fungsi untuk mendapatkan tinggi node
int height(node* root) {
    if (root == NULL) {
        return 0; // Jika node NULL, tinggi adalah 0
    } else {
        return root->height; // Kembalikan tinggi node
    }
}

// Fungsi untuk mendapatkan nilai maksimum dari dua angka
int max(int a, int b) {
    return (a > b) ? a : b; // Kembalikan nilai maksimum
}

// Fungsi untuk mendapatkan balance factor dari node
int getBalance(node* root) {
    if (root == NULL) {
        return 0; // Jika node NULL, balance factor adalah 0
    } else {
        return height(root->left) - height(root->right); // Selisih tinggi anak kiri dan kanan
    }
}

// Fungsi untuk melakukan rotasi kiri
node* leftRotate(node* x) {
    node* y = x->right; // Simpan anak kanan
    node* T2 = y->left; // Simpan sub-pohon kiri dari anak kanan

    y->left = x;        // Lakukan rotasi
    x->right = T2;

    // Update tinggi node
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // Kembalikan node baru setelah rotasi
}

// Fungsi untuk melakukan rotasi kanan
node* RightRotate(node* y) {
    node* x = y->left; // Simpan anak kiri
    node* T2 = x->right; // Simpan sub-pohon kanan dari anak kiri

    x->right = y;       // Lakukan rotasi
    y->left = T2;

    // Update tinggi node
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // Kembalikan node baru setelah rotasi
}

// Fungsi untuk menyisipkan node ke dalam AVL Tree
node* insertNode(node* root, int val) {
    if (root == NULL) {
        return createNode(val); // Jika root NULL, buat node baru
    } else if (val < root->val) {
        root->left = insertNode(root->left, val); // Sisipkan ke anak kiri
    } else if (val > root->val) {
        root->right = insertNode(root->right, val); // Sisipkan ke anak kanan
    } else {
        return root; // Jika nilai sudah ada, kembalikan root
    }

    // Update tinggi node
    root->height = max(height(root->left), height(root->right)) + 1;

    // Hitung balance factor
    int balance = getBalance(root);

    // Kasus rotasi untuk menjaga keseimbangan
    if (balance > 1 && val < root->left->val) {
        return RightRotate(root); // Left-Left (LL)
    }

    if (balance < -1 && val > root->right->val) {
        return leftRotate(root); // Right-Right (RR)
    }

    if (balance > 1 && val > root->left->val) {
        root->left = leftRotate(root->left); // Left-Right (LR)
        return RightRotate(root);
    }

    if (balance < -1 && val < root->right->val) {
        root->right = RightRotate(root->right); // Right-Left (RL)
        return leftRotate(root);
    }

    return root; // Kembalikan root setelah penyisipan
}

// Fungsi untuk mendapatkan node dengan nilai minimum
node* minValueNode(node* root) {
    node* current = root;
    while (current->left != NULL) {
        current = current->left; // Cari node paling kiri
    }
    return current;
}

// Fungsi untuk menghapus node dari AVL Tree
node* deleteNode(node* root, int val) {
    if (root == NULL) {
        return root; // Jika root NULL, kembalikan root
    }

    if (val < root->val) {
        root->left = deleteNode(root->left, val); // Hapus dari anak kiri
    } else if (val > root->val) {
        root->right = deleteNode(root->right, val); // Hapus dari anak kanan
    } else {
        // Node ditemukan
        if ((root->left == NULL) || (root->right == NULL)) {
            node* temp = root->left ? root->left : root->right; // Simpan anak tunggal
            if (temp == NULL) {
                temp = root;
                root = NULL; // Jika tidak ada anak, hapus node
            } else {
                *root = *temp; // Salin data anak ke root
            }
            free(temp); // Bebaskan memori
        } else {
            // Node memiliki dua anak
            node* temp = minValueNode(root->right); // Cari pengganti dari anak kanan
            root->val = temp->val; // Salin nilai pengganti
            root->right = deleteNode(root->right, temp->val); // Hapus pengganti
        }
    }

    if (root == NULL) {
        return root; // Jika root NULL, kembalikan root
    }

    // Update tinggi node
    root->height = 1 + max(height(root->left), height(root->right));

    // Hitung balance factor
    int balance = getBalance(root);

    // Kasus rotasi untuk menjaga keseimbangan
    if (balance > 1 && getBalance(root->left) >= 0) {
        return RightRotate(root); // Left-Left (LL)
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left); // Left-Right (LR)
        return RightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root); // Right-Right (RR)
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = RightRotate(root->right); // Right-Left (RL)
        return leftRotate(root);
    }

    return root; // Kembalikan root setelah penghapusan
}

// Fungsi untuk menampilkan AVL Tree secara in-order
void display(node* root) {
    if (root != NULL) {
        display(root->left); // Tampilkan anak kiri
        printf("%d ", root->val); // Tampilkan nilai root
        display(root->right); // Tampilkan anak kanan
    }
}

// Fungsi utama
int main() {
    node* root = NULL;

    // Menyisipkan node ke dalam AVL Tree
    root = insertNode(root, 20);
    root = insertNode(root, 15);
    root = insertNode(root, 25);
    root = insertNode(root, 10);
    root = insertNode(root, 30);
    root = insertNode(root, 5);

    // Menampilkan AVL Tree
    display(root);
    printf("\n");

    // Menghapus node dari AVL Tree
    root = deleteNode(root, 10);

    // Menampilkan AVL Tree setelah penghapusan
    display(root);
    printf("\n");

    // Menampilkan nilai root
    printf("Root: %d\n", root->val);

    return 0;
}