#include "login.h"
/** @em makeAccount Funkcja tworzaca nowego uzytkownika.
*
*@param char *username - parametr zawierający nazwe uzytkownika.
*/
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
/** @em getPassword Funkcja słuzaca do wpisania hasla.
*
*@param char username[] - parametr pobierający nazwe uzytkownika, do ktorego aktualnie chcemy się zalogowac.
*/
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
/** @em checkPassword Funkcja słuzy do sprawdzenia poprawnosci hasla.
*
*@param char username[] - parametr pobierajacy nazwe uzytkownika, do ktorego aktualnie chcemy się zalogowac.
*@param char password[] - wpisane haslo, ktorego sprawdzamy popranosc.
*/
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
/** @em checkIfAccountExists Funkcja sprawdzajaca, czy uzytkownik o podanej nazwie istnieje.
*@param char username[] - nazwa uzytkownika, ktorego istnienie jest sprawdzane.
*/
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
/** @em login Funkcja sluzaca do logowania i rejestracji uzytkownikow.
*
*/
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
