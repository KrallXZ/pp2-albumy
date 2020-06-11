#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_ATTEMPTS 3

bool makeAccount(char *username);

bool getPassword(char username[]);

bool checkPassword(char username[], char password[]);

bool checkIfAccountExists(char username[]);

char *login();

#endif