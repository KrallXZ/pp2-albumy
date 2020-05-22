#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_ATTEMPTS 3

// char _username[64];

bool getPassword(char username[]);
bool checkPassword(char username[], char password[]);
bool checkIfAccountExists(char username[]);
char *login();
bool makeAccount(char *username);

bool makeAccount(char *username)
{
  FILE *userFile;
  char path[100] = "./users/";
  strcat(path, username);
  userFile = fopen(path, "w");
  if (userFile != NULL)
  {
    char password[64];
    printf("Podaj swoje nowe hasło: ");
    fgets(password, 64, stdin);
    fputs(password, userFile);
    fclose(userFile);

    return true;
  }

  return false;
}

bool getPassword(char username[])
{
  int attempt = 1;
  char password[64];

  while (attempt <= 3)
  {
    printf("[%d/%d] ❓ Podaj hasło: ", attempt, MAX_ATTEMPTS);
    fgets(password, 64, stdin);

    if (checkPassword(username, password))
    {
      return true;
    }

    printf("Złe hasło!\n");
    attempt += 1;
  }

  printf("Przekroczono ilość prób!\n\n");
  return false;
}

bool checkPassword(char username[], char password[])
{
  FILE *userFile;
  char path[100] = "./users/";
  strcat(path, username);

  if (userFile = fopen(path, "r"))
  {
    char passwordFromFile[64];
    fgets(passwordFromFile, 64, userFile);
    fclose(userFile);

    if (strcmp(password, passwordFromFile) == 0)
    {
      return true;
    }
  }

  return false;
}

bool checkIfAccountExists(char username[])
{
  FILE *userFile;
  char path[100] = "./users/";
  strcat(path, username);

  if (userFile = fopen(path, "r"))
  {
    fclose(userFile);
    return true;
  }

  return false;
}

char *login()
{
  char *username = malloc(sizeof(char) * 64);
  printf("❓ Podaj login: ");
  scanf("%s%*c", username);

  if (checkIfAccountExists(username))
  {
    bool success = getPassword(username);

    if (success == true)
    {
      return username;
    }
  }
  else
  {
    printf("❗ Brak konta w bazie!\n");
    bool createNewAccount = getBooleanInput("Czy utworzyć nowe konto", true);

    if (createNewAccount)
    {
      printf("Trwa tworzenie konta... 😉\n");
      if (makeAccount(username))
      {
        return username;
      }

      printf("Nie udało się utworzyć konta.\n");
    }
  }

  return NULL;
}