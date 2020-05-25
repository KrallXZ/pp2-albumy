void swap(albums *a, albums *b);
void sort(albums **end);

void swap(albums *a, albums *b)
{
  albums *tempAlbum = malloc(sizeof(albums));

  strcpy(tempAlbum->artist, a->artist);
  strcpy(a->artist, b->artist);
  strcpy(b->artist, tempAlbum->artist);

  strcpy(tempAlbum->genre, a->genre);
  strcpy(a->genre, b->genre);
  strcpy(b->genre, tempAlbum->genre);

  strcpy(tempAlbum->title, a->title);
  strcpy(a->title, b->title);
  strcpy(b->title, tempAlbum->title);

  tempAlbum->date = a->date;
  a->date = b->date;
  b->date = tempAlbum->date;

  tempAlbum->id = a->id;
  a->id = b->id;
  b->id = tempAlbum->id;

  tempAlbum->bought = a->bought;
  a->bought = b->bought;
  b->bought = tempAlbum->bought;

  tempAlbum->listened = a->listened;
  a->listened = b->listened;
  b->listened = tempAlbum->listened;
}

void sort(albums **end)
{
  if (*end == NULL)
  {
    return;
  }

  printf("Posortowane według:\n\t[1] Artyści\n\t[2] Tytuły\n\t[3] Gatunki\n\t[4] Daty wydania\n\t[5] ID albumu\n");
  int choice = getNumberInput("Podaj jedną z opcji: ", 1, 1, 5);

  bool shouldSwap = true;
  albums *tempPointer = NULL;

  while (shouldSwap)
  {
    shouldSwap = false;
    albums *first = *end;
    albums *second = (*end)->previous;

    while (second != tempPointer)
    {
      if (choice == 1)
      {
        shouldSwap = (strcmp(first->artist, second->artist) > 0) ? true : false;
      }
      else if (choice == 2)
      {
        shouldSwap = (strcmp(first->title, second->title) > 0) ? true : false;
      }
      else if (choice == 3)
      {
        shouldSwap = (strcmp(first->genre, second->genre) > 0) ? true : false;
      }
      else if (choice == 4)
      {
        if (first->date.year >= second->date.year)
        {
          if (first->date.month >= second->date.month)
          {
            if (first->date.day >= second->date.day)
            {
              shouldSwap = true;
            }
          }
          else
          {
            shouldSwap = false;
          }
        }
        else
        {
          shouldSwap = false;
        }
      }
      else if (choice == 5)
      {
        shouldSwap = first->id > second->id ? true : false;
      }

      if (shouldSwap)
      {
        swap(first, second);
      }

      first = first->previous;
      second = first->previous;
    }
    tempPointer = first;
  }
}
