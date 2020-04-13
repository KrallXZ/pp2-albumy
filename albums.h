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
  char released[32];
  bool bought;
  bool listened;
  struct album *previous;
} albums;

void getAlbum(albums **end, int *id);
void showAlbums(albums *end);
void manageAlbums();
void saveToFile(albums *end);
albums *readFromFile(int *nextId);

void manageAlbums()
{
  int choice;
  int nextId = 1;
  albums *end = readFromFile(&nextId);

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
      saveToFile(end);
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

  printf("\tWydano: ");
  fgets(newAlbum->released, 32, stdin);
  newAlbum->released[strlen(newAlbum->released) - 1] = '\0';

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
    printf("\tWydano: %s\n", album->released);
    printf("\tGatunek: %s\n", album->genre);
    printf("\tZakupiono: %s\n", album->bought ? "TAK" : "NIE");
    printf("\tOdsłuchano: %s\n", album->listened ? "TAK" : "NIE");
    album = album->previous;
  } while (album != NULL);
}

void saveToFile(albums *end)
{
  FILE *userAlbums;

  char path[100] = "./albums/";
  strcat(path, _username);

  if (userAlbums = fopen(path, "wb"))
  {
    albums *current = end;
    do
    {
      fseek(userAlbums, 0, SEEK_END);
      fwrite(current, sizeof(albums), 1, userAlbums);

      //printf("Zapisuję %s do pliku.\n", current->title);
      current = current->previous;
    } while (current != NULL);

    fclose(userAlbums);
  }
}

albums *readFromFile(int *nextId)
{
  FILE *userAlbums;

  char path[100] = "./albums/";
  strcat(path, _username);

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