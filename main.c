#include <stdio.h>

#ifndef _WIN32
#include <sys/stat.h>
#endif

#include "login.h"
#include "albums.h"

void createDirectories()
{
#ifdef _WIN32
  _mkdir("./albums");
  _mkdir("./users");
#else
  mkdir("./albums", 0700);
  mkdir("./users", 0700);
#endif
}

int main()
{
  createDirectories();
#ifdef _WIN32
  system("chcp 65001");
#endif
  char *username;

  username = login();

  if (username == NULL)
  {
    printf("Nie udało się zalogować.\n");
    return 0;
  }

  printf("Zalogowano na konto: %s\n", username);

  manageAlbums(username);

  return 0;
}