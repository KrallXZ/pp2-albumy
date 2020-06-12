#include "albums.h"
/** @em swap Funkcja zamieniajaca dane pomiedzy dwoma przekazanymi elementami listy.
*
*@param albums *a - element listy.
*@param albums *b - nastepny element listy, znajdujacy sie za elementem *a.
*/
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
/** @em sort Funkcja sortujaca elementy listy w wybrany przez uzytkownika sposob.
*
*@param albums *end - przekazywana jest lista wszystkich albumow.
*@param int w - zmienna okreslajaca sposob sortowania (rosnący bądz malejacy).
*/
void sort(albums *end, int w)
{
  if (end == NULL)
  {
    return;
  }

  printf("Posortowane według:\n\t[1] Artyści\n\t[2] Tytuły\n\t[3] Gatunki\n\t[4] Daty wydania\n\t[5] ID albumu\n");
  int choice = getNumberInput("Podaj jedną z opcji: ", 1, 1, 5);

  for (albums *current = end; current->previous != NULL; current = current->previous)
  {
    for (albums *previous = current->previous; previous != NULL; previous = previous->previous)
    {
      bool shouldSwap = false;
      if (w == 1)
      {
        if (choice == 1)
        {
          shouldSwap = (strcmp(current->artist, previous->artist) > 0) ? true : false;
        }
        else if (choice == 2)
        {
          shouldSwap = (strcmp(current->title, previous->title) > 0) ? true : false;
        }
        else if (choice == 3)
        {
          shouldSwap = (strcmp(current->genre, previous->genre) > 0) ? true : false;
        }
        else if (choice == 4)
        {
          if (current->date.year > previous->date.year)
          {
            shouldSwap = true;
          }
          else if (current->date.year == previous->date.year)
          {
            if (current->date.month > previous->date.month)
            {
              shouldSwap = true;
            }
            else if (current->date.month == previous->date.month)
            {
              if (current->date.day > previous->date.day)
              {
                shouldSwap = true;
              }
            }
          }
        }
        else if (choice == 5)
        {
          shouldSwap = current->id > previous->id ? true : false;
        }
      }
      if (w == 2)
      {
        if (choice == 1)
        {
          shouldSwap = (strcmp(current->artist, previous->artist) < 0) ? true : false;
        }
        else if (choice == 2)
        {
          shouldSwap = (strcmp(current->title, previous->title) < 0) ? true : false;
        }
        else if (choice == 3)
        {
          shouldSwap = (strcmp(current->genre, previous->genre) < 0) ? true : false;
        }
        else if (choice == 4)
        {
          if (current->date.year < previous->date.year)
          {
            shouldSwap = true;
          }
          else if (current->date.year == previous->date.year)
          {
            if (current->date.month < previous->date.month)
            {
              shouldSwap = true;
            }
            else if (current->date.month == previous->date.month)
            {
              if (current->date.day < previous->date.day)
              {
                shouldSwap = true;
              }
            }
          }
        }
        else if (choice == 5)
        {
          shouldSwap = current->id < previous->id ? true : false;
        }
      }

      if (shouldSwap)
      {
        swap(current, previous);
      }
    }
  }
}
