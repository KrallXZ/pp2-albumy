#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>

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
} albums;

void getAlbum(albums **end, int *id);
void showAlbums(albums *end);
void manageAlbums(char *username);
void saveToFile(albums *end, char *username);
albums *readFromFile(int *nextId, char *username);

void find_album(albums *end, char title[]);
void delete_album(albums **end, int id);

void manageAlbums(char *username)
{
  printf("Ładowanie albumów...\n");
  int choice, numer;
  char artist[128], title[64];
  int nextId = 1;
  albums *end = readFromFile(&nextId, username);

  do
  {
    printf("Co chcesz zrobić ze swoimi albumami?\n");
    printf("\t[1] Dodać album\n\t[2] Wyświetlić listę albumów\n\t[3] Usunąć album\n\t[4] Szukanie albumu\n\t[0] Zakończyć program\n");
    printf("Wybór: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
      getAlbum(&end, &nextId);
      saveToFile(end, username);
      break;
    case 2:
      showAlbums(end);
      break;
    case 3:
      printf("Podaj ID albumu ktory chcesz usunac: ");
      scanf("%d", &numer);
      delete_album(&end, numer);
      saveToFile(end, username);
      break;
    case 4:
      printf("Podaj dane albumu\n");
      printf("Tytuł: ");
      scanf("%s", title);
      find_album(end, title);
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
  scanf("%d", &newAlbum->date.year);

  printf("\tMiesiac: ");
  scanf("%d", &newAlbum->date.month);

  printf("\tDzien: ");
  scanf("%d%*c", &newAlbum->date.day);

  newAlbum->bought = getBooleanInput("Czy zakupiono", false);
  newAlbum->listened = getBooleanInput("Czy odsłuchano", false);

  *id += 1;

  newAlbum->previous = (*end);
  *end = newAlbum;
}

void delete_front(albums **end)
{
  albums *prev = (*end)->previous;
  free(*end);
  *end = prev;
}

albums *find_prev_node(albums *end, int id)
{
  albums *prev = NULL;
  while ((NULL != end) && (end->id != id))
  {
    prev = end;
    end = end->previous;
  }
  return prev;
}

void delete_after(albums *node)
{
  albums *prev = node->previous;
  if (prev)
  {
    node->previous = prev->previous;
    free(prev);
  }
}

void delete_album(albums **end, int id)
{
  if (NULL == *end)
  {
    printf("Lista jest pusta");
    return;
  }
  if ((*end)->id == id)
  {
    return delete_front(end);
  }
  else
  {
    albums *prev = find_prev_node(*end, id);
    delete_after(prev);
  }
}

void find_album(albums *end, char title[])
{
  if (end == NULL)
  {
    printf("Lista jest pusta.\n");
    return;
  }
  do
  {
    if (strcmp(title, end->title) == 0)
    {
      printf("Album nr %d:\n", end->id);
      printf("\tArtysta: %s\n", end->artist);
      printf("\tTytul: %s\n", end->title);
      printf("\tRok wydania: %d.%d.%d\n", end->date.day, end->date.month, end->date.year);
      printf("\tGatunek: %s\n", end->genre);
      printf("\tZakupiono: %s\n", end->bought ? "TAK" : "NIE");
      printf("\tOdsłuchano: %s\n", end->listened ? "TAK" : "NIE");
    }
    end = end->previous;
  } while (end != NULL);
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
    printf("\tRok wydania: %d.%d.%d\n", album->date.day, album->date.month, album->date.year);
    printf("\tGatunek: %s\n", album->genre);
    printf("\tZakupiono: %s\n", album->bought ? "TAK" : "NIE");
    printf("\tOdsłuchano: %s\n", album->listened ? "TAK" : "NIE");
    album = album->previous;
  } while (album != NULL);
}

void saveToFile(albums *end, char *username)
{
  FILE *userAlbums;

  char path[100] = "./albums/";
  strcat(path, username);

  if (userAlbums = fopen(path, "wb"))
  {
    albums *current = end;
    do
    {
      fseek(userAlbums, 0, SEEK_END);
      fwrite(current, sizeof(albums), 1, userAlbums);

      printf("Zapisuję %s do pliku.\n", current->title);
      current = current->previous;
    } while (current != NULL);

    fclose(userAlbums);
  }
}

albums *readFromFile(int *nextId, char *username)
{
  FILE *userAlbums;

  char path[100] = "./albums/";
  strcat(path, username);

  if (userAlbums = fopen(path, "rb"))
  {
    fseek(userAlbums, 0, SEEK_END);
    unsigned int numberOfElements = (ftell(userAlbums) / sizeof(albums));

    albums *end;

    for (int i = 0; i < numberOfElements; i++)
    {
      albums *temp = malloc(sizeof(albums));
      fseek(userAlbums, sizeof(albums) * i, SEEK_SET);

      fread(temp, sizeof(albums), 1, userAlbums);
      temp->previous = (i == 0) ? NULL : end;

      end = temp;
    }

    fclose(userAlbums);

    *nextId = numberOfElements + 1;

    return end;
  }
}
