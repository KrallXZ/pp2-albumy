#include "albums.h"

void manageAlbums(char *username)
{
  printf("Ładowanie albumów...\n");
  int choice, id, i;
  char search[128];
  int nextId = 1;
  albums *end = readFromFile(&nextId, username);

  do
  {
    printf("Co chcesz zrobić ze swoimi albumami?\n");
    printf("\t[1] Dodać album\n\t[2] Wyświetlić listę albumów\n\t[3] Usunąć album\n\t[4] Szukanie albumu\n\t[5] Modyfikuj\n\t[6] Eksport do CSV\n\t[0] Zakończyć program\n");
    choice = getNumberInput("Wybór: ", 1, 0, 6);
    getchar();

    switch (choice)
    {
    case 1:
      getAlbum(&end, &nextId);
      saveToFile(end, username);
      break;
    case 2:
      sort(end);
      showAlbums(end);
      break;
    case 3:
      printf("Podaj ID albumu ktory chcesz usunac: ");
      scanf("%d%*c", &id);
      deleteAlbum(&end, id, username);
      saveToFile(end, username);
      break;
    case 4:
      printf("Wpisz tytul lub artyste: ");
      fgets(search, 128, stdin);
      search[strlen(search) - 1] = '\0';
      findAlbum(end, search);
      break;
    case 5:
      printf("Wpisz ID albumu ktory chcesz zmodyfikowac: ");
      scanf("%d", &id);
      changeAlbum(end, id);
      saveToFile(end, username);
      break;
    case 6:
      exportToCSV(end, username);
      break;
    }
  } while (choice != 0);
}
