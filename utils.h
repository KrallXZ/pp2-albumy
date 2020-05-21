#include <stdio.h>
#include <stdbool.h>

bool getBooleanInput(char question[], bool defaultChoice)
{
  getchar();
  char input[128];
  while (true)
  {
    printf("%s %s: ", question, defaultChoice ? "[T]/N" : "T/[N]");
    fgets(input, 128, stdin);
    char choice = input[0];

    if (choice == '\n')
    {
      return defaultChoice;
    }

    if (choice == 'T' || choice == 't')
    {
      return true;
    }

    if (choice == 'N' || choice == 'n')
    {
      return false;
    }
  };
}