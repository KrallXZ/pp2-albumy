#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int getNumberInput(char question[], int maxLength, int minValue, int maxValue);
bool getBooleanInput(char question[], bool defaultChoice);

#endif