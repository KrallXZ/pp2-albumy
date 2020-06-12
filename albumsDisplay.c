#include "albums.h"
/** @em findAlbum Funkcja słuzy do przeszukiwania listy albumow po tytule lub artyscie.
*
*@param albums *end - przekazywana jest lista wszystkich albumow aktualnie zalogowanego uzytkownika.
*@param char search[] - przekazana wartosc tytulu lub artysty w celu przeszukania listy.
*/
void findAlbum(albums *end, char search[])
{
  if (end == NULL)
  {
    printf("Lista jest pusta.\n");
    return;
  }
  char temp[128];
  char temp1[128];
  do
  {
    strcpy(temp, end->title);
    strcpy(temp1, end->artist);
    for (int i = 0; i < strlen(temp); i++)
    {
      temp[i] = tolower(temp[i]);
    }
    for (int i = 0; i < strlen(temp1); i++)
    {
      temp1[i] = tolower(temp1[i]);
    }
    for (int i = 0; i < strlen(search); i++)
    {
      search[i] = tolower(search[i]);
    }
    if (strstr(temp, search) != NULL || strstr(temp1, search) != NULL)
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
/** @em showAlbums - funkcja wyswietlajaca liste albumow akualnie zalogowanego uzytkownika.
*
*@param albums *end - przekazywana jest lista wszystkich albumow.
*/
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
