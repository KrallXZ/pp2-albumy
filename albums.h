#ifndef ALBUMS_H
#define ALBUMS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "utils.h"

typedef struct date
{
    int year;
    int month;
    int day;
} Date;

typedef struct album
{
    int id;
    char artist[128];
    char title[64];
    char genre[128];
    Date date;
    bool bought;
    bool listened;
    struct album *previous;
    struct album *next;
} albums;

void findAlbum(albums *end, char search[]);
void showAlbums(albums *end);
void swap(albums *a, albums *b);
void sort(albums *end);
void manageAlbums(char *username);
void getAlbum(albums **end, int *id);
void changeAlbum(albums *end, int id);
void deleteAlbum(albums **end, int id, char *username);
void saveToFile(albums *end, char *username);
albums *readFromFile(int *nextId, char *username);
void exportToCSV(albums *end, char *username);

#endif