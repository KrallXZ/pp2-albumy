#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct album
{
  int id;
  char artist[128];
  char title[64];
  char genre[128];
  int year;
  bool bought;
  bool listened;
  struct album *previous;
} albums;

void getAlbum(albums **end, int *id);
void showAlbums(albums *start);
void manageAlbums();

void manageAlbums()
{
  int choice;
  int nextId = 1;
  albums *end = NULL;

  do
  {
    printf("Co chcesz zrobić ze swoimi albumami?\n");
    printf("\t[1] Dodać album\n\t[2] Wyświetlić listę albumów\n\t[0] Zakończyć program\n");
    printf("Wybór: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
      getAlbum(&end, &nextId);
      break;
    case 2:
      showAlbums(end);
      break;
    }
  } while (choice != 0);
}

void getAlbum(albums **end, int *id)
{
  albums *newAlbum = (albums *)malloc(sizeof(albums));

  printf("Tworzenie nowego albumu...\n");
  newAlbum->id = *id;

  printf("\tArtyści: ");
  fgets(newAlbum->artist, 128, stdin);
  newAlbum->artist[strlen(newAlbum->artist) - 1] = '\0';

  printf("\tTytuł: ");
  fgets(newAlbum->title, 64, stdin);
  newAlbum->title[strlen(newAlbum->title) - 1] = '\0';

  printf("\tGatunki: ");
  fgets(newAlbum->genre, 128, stdin);
  newAlbum->genre[strlen(newAlbum->genre) - 1] = '\0';

  printf("\tRok: ");
  scanf("%d", &newAlbum->year);
  getchar();

  char bought;
  do
  {
    printf("\tCzy zakupiono (T/N): ");
    scanf("%c", &bought);
    getchar();
  } while (bought != 'T' && bought != 'N');
  newAlbum->bought = bought == 'T' ? true : false;

  char listened;
  do
  {
    printf("\tCzy odsłuchano (T/N): ");
    scanf("%c", &listened);
    getchar();
  } while (listened != 'T' && listened != 'N');
  newAlbum->listened = listened == 'T' ? true : false;

  *id += 1;

  newAlbum->previous = (*end);
  *end = newAlbum;
}

void showAlbums(albums *end)
{
  if (end == NULL)
  {
    printf("Lista jest pusta.\n");
    return;
  }

  albums *album = end;
  do
  {
    printf("Album nr %d:\n", album->id);
    printf("\tArtysta: %s\n", album->artist);
    printf("\tTytul: %s\n", album->title);
    printf("\tRok wydania: %d\n", album->year);
    printf("\tGatunek: %s\n", album->genre);
    printf("\tZakupiono: %s\n", album->bought ? "TAK" : "NIE");
    printf("\tOdsłuchano: %s\n", album->listened ? "TAK" : "NIE");
    album = album->previous;
  } while (album != NULL);
}