#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode {
    int valueNode;
    struct tnode *next;
    struct tnode *prev;
}*h, *t, *c;

void pushHead(int value) {
    c = (struct tnode*)malloc(sizeof(struct tnode));
    c->valueNode = value;
    c->next = NULL;
    c->prev = NULL;

    if (!h) {
        h = t = c;
    } else {
        c->next = h;
        h->prev = c;
        h = c;
    }
}

void pushTail(int value) {
    c = (struct tnode*)malloc(sizeof(struct tnode));
    c->valueNode = value;
    c->next = NULL;
    c->prev = NULL;

    if (!h) {
        h = t = c;
    } else {
        t->next = c;
        c->prev = t;
        t = c;
    }
}

void pushMiddle(int value) {
    c = (struct tnode*)malloc(sizeof(struct tnode));
    c->valueNode = value;
    c->next = NULL;
    c->prev = NULL;

    if (!h) {
        h = t = c;
    } else if (h->valueNode > value) {
        c->next = h;
        h->prev = c;
        h = c;
    } else if (t->valueNode < value) {
        t->next = c;
        c->prev = t;
        t = c;
    } else {
        struct tnode *temp;
        temp = h;

        while (value > temp->valueNode) {
            temp = temp->next;
        }

        c->next = temp->next;
        temp->next->prev = c;
        c->prev = temp;
        temp->next = c;
    }
}

void popHead() {
    if (h == NULL) return;
    struct tnode *temp = h;
    h = h->next;
    h->prev = NULL;
    free(temp);
}

int main() {

    return 0;
}