#include <stdio.h>
#include <stdbool.h>

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
  bool isLogged;

  do
  {
    isLogged = login();
  } while (!isLogged);

  printf("Zalogowano na konto: %s\n", _username);

  manageAlbums();

  return 0;
}