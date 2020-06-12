#include "utils.h"
/** @em getNumberInput Funkcja sluzaca do walidacji danych.
*
*@param char question[] - parametr okreslajacy etykiete wejscia
*@param int maxLength - parametr okreslajacy maksymalna dlugosc wprowadzonych danych.
*@param int minValue - parametr okreslajacy minimalna wartosc danych.
*@param int maxValue - parametr okreslajac maksymalna wartosc danych.
*/
int getNumberInput(char question[], int maxLength, int minValue, int maxValue)
{
    char *input = malloc(maxLength * sizeof(char));

    bool done = false;

    while (!done)
    {
        done = true;
        printf("%s", question);
        scanf("%s", input);
        for (int i = 0; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                done = false;
                break;
            }
        }

        if (done && atoi(input) >= minValue && atoi(input) <= maxValue)
        {
            return atoi(input);
        }

        done = false;
    }
}
/** @em getBooleanInput Funkcja sluzaca do obslugi domyslnych odpowiedzi
*
*@param char question[] - parametr okreslajacy etykiete wejscia.
*@param bool defaultChoice - parametr okreslajacy domyslna odpowiedz.
*/
bool getBooleanInput(char question[], bool defaultChoice)
{
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
