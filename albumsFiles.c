#include "albums.h"

void saveToFile(albums *end, char *username)
{
  FILE *userAlbums;

  char path[100] = "./albums/";
  strcat(path, username);

  if (end == NULL)
  {
    remove(path);
    return;
  }

  if (userAlbums = fopen(path, "wb"))
  {
    albums *current = end;

    while (current != NULL)
    {
      fseek(userAlbums, 0, SEEK_END);
      fwrite(current, sizeof(albums), 1, userAlbums);

      // printf("Zapisuję %s do pliku.\n", current->title);
      current = current->previous;
    }

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
      temp->next = NULL;

      if (i != 0)
      {
        end->next = temp;
      }

      if (temp->id >= *nextId)
      {
        *nextId = temp->id + 1;
      }

      end = temp;
    }

    fclose(userAlbums);

    return end;
  }
}

void exportToCSV(albums *end, char *username)
{
  FILE *userAlbums;

  char path[100] = "./albums/";
  strcat(path, username);
  strcat(path, ".csv");

  if (userAlbums = fopen(path, "w"))
  {
    albums *current = end;

    fprintf(userAlbums, "\"ID\";\"Nazwa\";\"Artysci\";\"Data\";\"Gatunek\";\"Kupiony\";\"Przesluchany\"\n");

    while (current != NULL)
    {
      fprintf(userAlbums, "%d;\"%s\";\"%s\";\"%d.%d.%d\";\"%s\";\"%s\";\"%s\"\n", current->id, current->title, current->artist, current->date.day, current->date.month, current->date.year, current->genre, current->bought ? "TAK" : "NIE", current->listened ? "TAK" : "NIE");

      // printf("Zapisuję %s do pliku.\n", current->title);
      current = current->previous;
    }

    fclose(userAlbums);

    printf("Zapisano do pliku %s\n", path);
  }
}