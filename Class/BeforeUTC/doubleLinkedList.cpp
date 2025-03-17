#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct player { // Struct lagu
    char judul[101];
    struct player* next;
    struct player* prev;
}*h, *t, *c;

int songCount = 0; // buat ID

void addSong(const char* title) { // Function push
    player* newSong = (struct player*)malloc(sizeof(player)); // alokasiin memory buat node baru pake malloc
    strcpy(newSong->judul, title);
    songCount++;
    if (h == NULL) {
        h = t = newSong;
        h->next = h;
        h->prev = h;
    } else {
        newSong->prev = t;
        newSong->next = h;
        t->next = newSong;
        h->prev = newSong;
        t = newSong;
    }
}

void showPlaylist() {
    if (h == NULL) {
        printf("There is no song !\n");
        return;
    }

    printf("Playlist:\n");
    struct player* c = h;
    int index = 1;
    do {
        printf("%d. %s\n", index++, c->judul);
        c = c->next;
    } while (c != h);
}

void playNext() {
    if (c == NULL) {
        c = h;
    } else {
        c = c->next;
    }
    printf("Now playing: %s\n", c->judul);
}

void playPrevious() {
    if (c == NULL) {
        c = h;
    } else {
        c = c->prev;
    }
    printf("Now playing: %s\n", c->judul);
}

void playOnce() {
    if (c == NULL) {
        c = h;
    }
    printf("Now playing: %s\n", c->judul);
    c = NULL; // Stop after one play
}

void playLoop(int times) {
    if (h == NULL) {
        printf("There is no song !\n");
        return;
    }

    if (c == NULL) {
        c = h;
    }
    
    for (int i = 0; i < times; i++) {
        printf("Now playing: %s\n", c->judul);
    }
}

void selectSong(int songNumber) {
    if (h == NULL) {
        printf("There is no song !\n");
        return;
    }

    if (songNumber < 1 || songNumber > songCount) {
        printf("There is no song !!\n");
        return;
    }

    c = h; // Mulai dari h
    for (int i = 1; i < songNumber; i++) {
        c = c->next;
    }

    printf("Now playing: %s\n", c->judul);
}

int main() {
    int n;
    int song;
    printf("How many song you want to insert : ");
    scanf("%d", &n); getchar();

    for(int i = 0; i < n; i++){
        char *judul = (char*)malloc(sizeof(char));
        printf("Insert Song Title %d: ", i+1);
        scanf("%[^\n]", judul); getchar();
        addSong(judul);
    }

    showPlaylist();
    printf("Select Song you want to listen: ");
    scanf("%d", &song); getchar();
    selectSong(song);
    
    printf("Next Song >> \n");
    playNext();
    printf("\n");

    printf("Next Song >> \n");
    playNext();
    printf("\n");
    
    printf("Prev Song >> \n");
    playPrevious();
    printf("\n");

    printf("Which one song you want to listen once ?: ");
    scanf("%d", &song); getchar();
    selectSong(song);
    playOnce();

    printf("Which song you want to listen?: ");
    scanf("%d", &song); getchar();
    selectSong(song);
    int loop;
    printf("How many times will you loop this song: ");
    scanf("%d", &loop);
    playLoop(loop);

    return 0;
}