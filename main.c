#include <stdio.h>
#include <stdbool.h>

#include "login.h"

int main()
{
  bool isLogged;

  do
  {
    isLogged = login();
  } while (!isLogged);

  printf("Zalogowano na konto: %s\n", _username);

  return 0;
}