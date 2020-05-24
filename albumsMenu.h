void manageAlbums(char *username);

void manageAlbums(char *username)
{
  printf("Ładowanie albumów...\n");
  int choice, id, i;
  char artist[128], title[64];
  int nextId = 1;
  albums *end = readFromFile(&nextId, username);

  do
  {
    printf("Co chcesz zrobić ze swoimi albumami?\n");
    printf("\t[1] Dodać album\n\t[2] Wyświetlić listę albumów\n\t[3] Usunąć album\n\t[4] Szukanie albumu\n\t[5] Modyfikuj\n\t[6] Sortuj\n\t[0] Zakończyć program\n");
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
      scanf("%d", &id);
      deleteAlbum(&end, id, username);
      saveToFile(end, username);
      break;
    case 4:
      printf("Podaj dane albumu\n");
      printf("Tytuł: ");
      scanf("%s", title);
      findAlbum(end, title);
      break;
    case 5:
      printf("Wpisz ID albumu ktory chcesz zmodyfikowac: ");
      scanf("%d", &id);
      changeAlbum(end, id);
      saveToFile(end, username);
      break;
    case 6:
      puts("Po czym chcesz sortowac\n");
      printf("\t[1] Artysci\n\t[2] Tytuly\n\t[3] Gatunki\n\t[4] Daty wydania\n");
      printf("Wybor: ");
      scanf("%d&%*c", &i);
      switch (i)
      {
      case 1:
        sortuj(&end, i);
        showAlbums(end);
        break;
      case 2:
        sortuj(&end, i);
        showAlbums(end);
        break;
      case 3:
        sortuj(&end, i);
        showAlbums(end);
        break;
      case 4:
        sortuj(&end, i);
        showAlbums(end);
        break;
      }
      break;
    }
  } while (choice != 0);
}