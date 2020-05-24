void saveToFile(albums *end, char *username);
albums *readFromFile(int *nextId, char *username);

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

      printf("Zapisuję %s do pliku.\n", current->title);
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

      end = temp;
    }

    fclose(userAlbums);

    *nextId = numberOfElements + 1;

    return end;
  }
}