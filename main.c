#include <stdio.h>
#include <stdbool.h>

#include "login.h"
#include "albums.h"

int main()
{
  bool isLogged;

  do
  {
    isLogged = login();
  } while (!isLogged);

  printf("Zalogowano na konto: %s\n", _username);

  manageAlbums();

  return 0;
}