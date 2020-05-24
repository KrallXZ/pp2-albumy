void findAlbum(albums *end, char title[]);
void showAlbums(albums *end);

void findAlbum(albums *end, char title[])
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
