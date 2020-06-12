#include "albums.h"
/** @em getAlbum Funkcja dodajaca nowy album dla uzytkownika.
*
*@param albums **end - przekazywana jest lista wszystkich albumow.
*@param int *id - numer id aktualnie tworzonego albumu.
*/
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

  newAlbum->date.year = getNumberInput("\tRok (YYYY): ", 4, 0, 2020);
  newAlbum->date.month = getNumberInput("\tMiesiąc (MM): ", 2, 1, 12);
  newAlbum->date.day = getNumberInput("\tDzień (DD): ", 2, 1, 31);

  getchar();

  newAlbum->bought = getBooleanInput("Czy zakupiono", false);
  newAlbum->listened = getBooleanInput("Czy odsłuchano", false);

  *id += 1;

  newAlbum->previous = (*end);
  newAlbum->next = NULL;
  if (*end != NULL)
  {
    (*end)->next = newAlbum;
  }
  *end = newAlbum;
}
/** @em changeAlbum Funkcja modyfikujaca wybrame pola albumu.
*
*@param albums *end - przekazywana jest lista wszystkich albumow.
*@param int id - numer id albumu, ktory chcemy modifikowac.
*/
void changeAlbum(albums *end, int id)
{
  int w;
  do
  {
    if (end->id == id)
    {
      do
      {
        printf("Album nr %d:\n", end->id);
        printf("\tArtysta: %s\n", end->artist);
        printf("\tTytul: %s\n", end->title);
        printf("\tRok wydania: %d.%d.%d\n", end->date.day, end->date.month, end->date.year);
        printf("\tGatunek: %s\n", end->genre);
        printf("\tZakupiono: %s\n", end->bought ? "TAK" : "NIE");
        printf("\tOdsłuchano: %s\n", end->listened ? "TAK" : "NIE");
        printf("Ktora dana chcesz zmodyfikowac: \n");
        printf("\t[1] Artysta\n\t[2] Tytul\n\t[3] Gatunek\n\t[4] Data wydania\n\t[5] Zmien status zakupienia\n\t[6] Zmien stan odsluchania\n\t[0] Zakoncz modyfikacje\n");
        printf("Wybor: ");
        scanf("%d%*c", &w);
        switch (w)
        {
        case 1:
          printf("Zmien artyste: ");
          fgets(end->artist, 128, stdin);
          end->artist[strlen(end->artist) - 1] = '\0';
          break;
        case 2:
          printf("Zmien tytul: ");
          fgets(end->title, 64, stdin);
          end->title[strlen(end->title) - 1] = '\0';
          break;
        case 3:
          printf("Zmien gatunek: ");
          fgets(end->genre, 128, stdin);
          end->genre[strlen(end->genre) - 1] = '\0';
          break;
        case 4:
          printf("Zmien date\n");
          end->date.year = getNumberInput("\tRok (YYYY): ", 4, 0, 2020);
          end->date.month = getNumberInput("\tMiesiąc (MM): ", 2, 1, 12);
          end->date.day = getNumberInput("\tDzień (DD): ", 2, 1, 31);
          break;
        case 5:
          end->bought = getBooleanInput("Czy zakupiono", false);
          break;
        case 6:
          end->listened = getBooleanInput("Czy odsłuchano", false);
          break;
        }
      } while (w != 0);
      return;
    }
    end = end->previous;
  } while (end != NULL);
  if (end == NULL)
  {
    printf("Nie znaleziono albumu");
  }
}
/** @em deleteAlbum Funkcja usuwajaca wybrany album uzytkownika.
*
*@param albums **end - przekazywana jest lista wszystkich albumow.
*@param int id - numer id albumu, ktory chcemy usunąć.
*@param char *username - parametr okreslajacy nazwe aktualnie zalogowanego uzytkownika.
*/
void deleteAlbum(albums **end, int id, char *username)
{

  if (*end == NULL)
  {
    printf("Brak albumów!\n");
    return;
  }

  if (!getBooleanInput("Czy na pewno chcesz usunąć? ", false))
  {
    return;
  }

  if ((*end)->id == id)
  {
    albums *previous = (*end)->previous;
    free(*end);
    *end = previous;
    return;
  }

  albums *temp = (*end)->previous;
  while (temp != NULL && temp->id != id)
  {
    temp = temp->previous;
  }

  if (temp != NULL && temp->previous != NULL)
  {
    temp->previous->next = temp->next;
    temp->next->previous = temp->previous;
    free(temp);
    return;
  }
  if (temp != NULL)
  {
    temp->next->previous = NULL;
    free(temp);
  }

  printf("Nie znaleziono albumu.\n");
}
