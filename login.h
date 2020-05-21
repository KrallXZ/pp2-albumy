#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"

#define MAX_ATTEMPTS 3

char _username[64];

bool getPassword(char username[]);
bool checkPassword(char username[], char password[]);
bool checkIfAccountExists(char username[]);
bool login();
void makeAccount(char username[]);

void makeAccount(char username[])
{
  FILE *userFile;
  char path[100] = "./users/";
  strcat(path, username);
  userFile = fopen(path, "w");
  if (userFile != NULL)
  {
    char password[64];
    printf("Podaj swoje nowe hasło: ");
    scanf("%s", password);
    fputs(password, userFile);
    fclose(userFile);
  }
}

bool getPassword(char username[])
{
  int attempt = 1;
  char password[64];

  while (attempt <= 3)
  {
    printf("[%d/%d] ❓ Podaj hasło: ", attempt, MAX_ATTEMPTS);
    scanf("%s", password);

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
    fscanf(userFile, "%s", passwordFromFile);
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

bool login()
{
  char username[64];
  printf("❓ Podaj login: ");
  scanf("%s", username);

  if (checkIfAccountExists(username))
  {
    bool success = getPassword(username);

    if (success == true)
    {
      strcpy(_username, username);
      return true;
    }
  }
  else
  {
    printf("❗ Brak konta w bazie!\n");
    bool createNewAccount = getBooleanInput("Czy utworzyć nowe konto", true);

    if (createNewAccount)
    {
      printf("Trwa tworzenie konta... 😉\n");
      makeAccount(username);
      strcpy(_username, username);
      return true;
    }

    return false;
  }

  return false;
}