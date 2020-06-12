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
    /** \brief rok wydania albumu.*/
    int year;
    /** \brief miesiac wydania albumu.*/
    int month;
    /** \brief dzien wydania albumu.*/
    int day;
} Date;

typedef struct album
{
    /** \brief unikalny mumer albumu.*/
    int id;
    /** \brief nazwa artysty.*/
    char artist[128];
    /** \brief tytuł albumu.*/
    char title[64];
    /** \brief gatunek albumu.*/
    char genre[128];
    Date date;
    /** \brief okreslenie, czy album jest zakupiony.*/
    bool bought;
    /** \brief okreslenie, czy album zostal przesluchany.*/
    bool listened;
    /** \brief wskaznik na poprzedni element listy.*/
    struct album *previous;
    /** \brief wskaznik na nastêpny element listy.*/
    struct album *next;
} albums;

void findAlbum(albums *end, char search[]);
void showAlbums(albums *end);
void swap(albums *a, albums *b);
void sort(albums *end, int w);
void manageAlbums(char *username);
void getAlbum(albums **end, int *id);
void changeAlbum(albums *end, int id);
void deleteAlbum(albums **end, int id, char *username);
void saveToFile(albums *end, char *username);
albums *readFromFile(int *nextId, char *username);
void exportToCSV(albums *end, char *username);

#endif
