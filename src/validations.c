/**
* Copyrigth (c) 2023, Iriarte Federico (fedeiria@gmail.com)
*
* This program is free software: you can redistribute it and/or modify it under the terms of the GNU
* General Public License as published by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
* even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with this program. If not, see
* <https://www.gnu.org/licenses/>.
*/

#include "../inc/validations.h"

/**
 * \brief Verifies if the received value is composed only by letters
 * \param char string String to be analyzed
 * \return int value 1 if value is composed only by letters - 0 if does not contain it
 */
int onlyWords(char *string)
{
    int i = 0;
    int value = 1;

    while(string[i] != '\0'){
        if((string[i] != ' ') && (string[i] < 'A' || string[i] > 'Z') && (string[i] < 'a' || string[i] > 'z'))
            value = 0;

        i++;
    }

    return value;
}

/**
 * \brief Verifies whether the received value is composed only by letters and numbers (No special characters)
 * \param char string String to be analyzed
 * \return int value 1 if it contains only spaces, a period, letters and numbers - 0 if it does not contain it
 */
int onlyAlphanumeric(char *string)
{
    int i = 0;
    int value = 1;

    while(string[i] != '\0'){
        if((string[i] != ' ') && (string[i] != '-') && (string[i] < 'a' || string[i] > 'z') && (string[i] < 'A' || string[i] > 'Z') && (string[i] < '0' || string[i] > '9'))
            value = 0;

        if(string[0] == '\r')
            value = 0;

        i++;
    }

    return value;
}

/**
 * \brief Verifies whether the received value is numeric
 * \param char string String to be analyzed
 * \return int value 1 if the value is numerical - 0 if does not contain it
 */
int onlyNumbers(char *string)
{
    int i = 0;
    int value = 1;

    while(string[i] != '\0'){
        if(string[i] < '0' || string[i] > '9')
            value = 0;

        i++;
    }

    return value;
}

/**
 * \brief verifies whether the received value is floating numeric
 * \param char string String to be analyzed
 * \return int value 1 if the value is numerical - 0 if does not contain it
 */
int onlyFloatingNumbers(char *string)
{
    int i = 0;
    int count = 0;
    int value = 1;

    while(string[i] != '\0'){
        if((string[i] < '0' || string[i] > '9') && (string[i] != '.'))
            value = 0;

        if(string[i] == '.')
            count++;

        if(count > 1)
            value = 0;

        i++;
    }

    return value;
}

/**
 * \brief Verifies whether the received value is a valid e-mail address
 * \param char string String to be analyzed
 * \return int value 1 if it is a valid e-mail address - 0 if it does not contain it
 */
int onlyEmail(char *string)
{
    int i = 0;
    int count = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    int value = 1;

    while(string[i] != '\0'){
        if((string[i] != '@') && (string[i] != '-') && (string[i] != '_') && (string[i] != '.') && (string[i] < 'a' || string[i] > 'z') && (string[i] < 'A' || string[i] > 'Z') && (string[i] < '0' || string[i] > '9'))
            value = 0;

        if(string[i] == '@')
            count++;

        if(string[i] == '-')
            count2++;

        if(string[i] == '_')
            count3++;

        if(string[i] == '.')
            count4++;

        if(count > 1)
            value = 0;

        if(count2 > 2)
            value = 0;

        if(count3 > 2)
            value = 0;

        if(count4 > 3)
            value = 0;

        i++;
    }

    return value;
}

/**
 * \brief Verifies whether the received value is composed only by numbers and special character (-)
 * \param char string String to be analyzed
 * \return int value 1 if it contains letters, numbers and middle script (-) - 0 if it does not contain it
 */
int onlyPhoneNumber(char *string)
{
    int i = 0;
    int count = 0;
    int value = 1;

    while(string[i] != '\0'){
        if((string[i] != '-') && (string[i] < '0' || string[i] > '9'))
            value = 0;

        if(string[i] == '-')
            count++;

        if(count > 2)
            value = 0;

        i++;
    }

    return value;
}

/**
 * \brief Requests a text from the user and returns it
 * \param char message the message to be shown
 * \param char input string where the message is loaded
 * \return void
 */
void getString(char *message, char *input)
{
    printf("%s", message);
    fflush(stdin);
    gets(input);
}

/**
 * \brief Requests a text from the user and returns it, check if it is composed by letters
 * \param char message the message to be shown
 * \param char input string where the message is loaded
 * \return int value 1 if text is composed only by letters - 0 if it is not
 */
int getStringWords(char *message, char *input)
{
    char string[MAX_LENGTH];
    int value = 0;

    getString(message, string);

    if(onlyWords(string)){
        strcpy(input, string);
        value = 1;
    }

    return value;
}

/**
 * \brief Requests a text from the user and returns it, check if it is alphanumeric
 * \param char message the message to be shown
 * \param char input string where the message is loaded
 * \return int value 1 if text is alphanumeric - 0 if it is not
 */
int getStringAlphanumeric(char *message, char *input)
{
    char string[MAX_LENGTH];
    int value = 0;

    getString(message, string);

    if(onlyAlphanumeric(string)){
        strcpy(input, string);
        value = 1;
    }

    return value;
}

/**
 * \brief Requests a text from the user and returns it, check if it is composed only by numbers
 * \param char message the message to be shown
 * \param char input string where the text is loaded
 * \return int value 1 if the text is composed only by numbers - 0 if it is not
 */
int getStringNumbers(char *message, char *input)
{
    char string[MAX_LENGTH];
    int value = 0;

    getString(message, string);

    if(onlyNumbers(string)){
        strcpy(input, string);
        value = 1;
    }

    return value;
}

/**
 * \brief Requests a text from the user and returns it, check if it is composed only by floating numbers
 * \param char message the message to be shown
 * \param char input string where the text is loaded
 * \return int value 1 if the text is composed only by floating numbers - 0 if it is not
 */
int getStringFloatingNumbers(char *message, char *input)
{
    char string[MAX_LENGTH];
    int value = 0;

    getString(message, string);

    if(onlyFloatingNumbers(string)){
        strcpy(input, string);
        value = 1;
    }

    return value;
}

/**
 * \brief Requests a text from the user and returns it, check if it is a e-mail address
 * \param char message the message to be shown
 * \param char input string where the message is loaded
 * \return int value 1 if string is a valid e-mail address - 0 if it is not
 */
int getStringEmail(char *message, char *input)
{
    char string[MAX_LENGTH];
    int value = 0;

    getString(message, string);

    if(onlyEmail(string)){
        strcpy(input, string);
        value = 1;
    }

    return value;
}

/**
 * \brief Requests a text from the user and returns it, check if it is phone number
 * \param char message the message to be shown
 * \param char input string where the message is loaded
 * \return int value 1 if string is a valid phone number - 0 if it is not
 */
int getStringPhoneNumber(char *message, char *input)
{
    char string[MAX_LENGTH];
    int value = 0;

    getString(message, string);

    if(onlyPhoneNumber(string)){
        strcpy(input, string);
        value = 1;
    }

    return value;
}

/**
 * \brief Requests a text from the user and validates it
 * \param char requestMessage the message to be shown to the user
 * \param char errorMessage message to be shown to the user in case of data type error
 * \param char errorMessageLength message to be shown to the user in case of length error
 * \param char input string where the entered text will be loaded
 * \param int minLength minimum length limit to be checked
 * \param int maxLength maximum length limit to be checked
 * \param int attempts indicates the number of retries to an error
 * \return int value 0 if the text is composed only by letters, -1 if it is not
 */
int getValidString(char *requestMessage, char *errorMessage, char *errorMessageLength, char *input, int minLength, int maxLength, int attempts)
{
    char buffer[MAX_LENGTH];
    int i;
    int value = -1;

    for(i = 0; i < attempts; i++){
        if(!getStringWords(requestMessage, buffer)){
            printf("%s", errorMessage);
            continue;
        }
        if(strlen(buffer) < minLength || strlen(buffer) > maxLength){
            printf("%s", errorMessageLength);
            continue;
        }

        firstUppercaseLetter(buffer);
        strcpy(input, buffer);
        value = 0;
        break;
    }

    return value;
}

/**
 * \brief Requests a text from the user and validate if it is alphanumeric (No special characters)
 * \param char requestMessage the message to be shown to the user
 * \param char errorMessage the message to be shown to the user in case of data type error
 * \param char errorMessageLength message to be shown to the user in case of length error
 * \param char input dtring where the entered text will be loaded
 * \param int minLength minimum length limit to be checked
 * \param int maxLength maximum length limit to be checked
 * \param int attempts indicates the number of retries to an error
 * \return int value 0 if the text is composed only by numbers, letters and blank space -1 if it is not
 */
int getValidAlphanumeric(char *requestMessage, char *errorMessage, char *errorMessageLength, char *input, int minLength, int maxLength, int attempts)
{
    char buffer[MAX_LENGTH];
    int i;
    int value = -1;

    for(i = 0; i < attempts; i++){
        if(!getStringAlphanumeric(requestMessage, buffer)){
            printf ("%s", errorMessage);
            continue;
        }
        if(strlen(buffer) < minLength || strlen(buffer) > maxLength){
            printf ("%s", errorMessageLength);
            continue;
        }

        strupr(buffer);
        strcpy(input, buffer);
        value = 0;
        break;
    }

    return value;
}

/**
 * \brief Requests a text from the user and validates if it is integer
 * \param char requestMessage the message to be shown to the user
 * \param char errorMessage the message to be shown to the user in case of data type error
 * \param char errorMessageLength the message to be shown to the user in case of error of length
 * \param int *input pointer to the place where the entered value will be loaded
 * \param int lowLimit the limit of the lowest number that can be accepted
 * \param int hiLimit the limit of the highest number that can be accepted
 * \param int attempts indicates the number of retries to an error
 * \return int value 0 if the number is composed only by integer, -1 if it is not
 */
int getValidInt(char *requestMessage, char *errorMessage, char *errorMessageLength, int *input, int lowLimit, int hiLimit, int attempts)
{
    char auxStr[MAX_LENGTH];
    int i;
    int auxInt;
    int value = -1;

    for(i = 0; i < attempts; i++){
        if(!getStringNumbers(requestMessage, auxStr)){
            printf("%s", errorMessage);
            continue;
        }

        auxInt = atoi(auxStr);

        if(auxInt < lowLimit || auxInt > hiLimit){
            printf("%s", errorMessageLength);
            continue;
        }

        *input = auxInt;
        value = 0;
        break;
    }

    return value;
}

/**
 * \brief Requests a text from the user and validates if it is long integer
 * \param char requestMessage the message to be shown to the user
 * \param char errorMessage the message to be shown to the user in case of data type error
 * \param char errorMessageLength the message to be shown to the user in case of error of length
 * \param long int *input pointer to the place where the entered value will be loaded
 * \param long int lowLimit the limit of the lowest number that can be accepted
 * \param long int hiLimit the limit of the highest number that can be accepted
 * \param int attempts indicates the number of retries to an error
 * \return int value 0 if the number is composed only by long integer, -1 If it is not
 */
int getValidLongInt(char *requestMessage, char *errorMessage, char *errorMessageLength, long int *input, long int lowLimit, long int hiLimit, int attempts)
{
    char auxStr[MAX_LENGTH];
    int i;
    int size;
    int value = -1;
    long int auxLongInt;

    for(i = 0; i < attempts; i++){
        if(!getStringNumbers(requestMessage, auxStr)){
            printf("%s", errorMessage);
            continue;
        }

        size = strlen(auxStr);

        if(size < lowLimit || size > hiLimit){
            printf("%s", errorMessageLength);
            continue;
        }

        auxLongInt = atol(auxStr);

        *input = auxLongInt;
        value = 0;
        break;
    }

    return value;
}

/**
 * \brief Requests a text from the user and validates if it is a floating numeric
 * \param char requestMessage the message to be shown to the user
 * \param char errorMessage the message to be shown to the user in case of data type error
 * \param char errorMessageLength the message to be shown to the user in case of error of length
 * \param float *input pointer to the place where the entered value will be loaded
 * \param float lowLimit the limit of the lowest number that can be accepted
 * \param float hiLimit the limit of the highest number that can be accepted
 * \param int attempts indicates the number of retries to an error
 * \return int value 0 if the number is composed only by floating numbers, -1 if it is not
 */
int getValidFloat(char *requestMessage, char *errorMessage, char *errorMessageLength, float *input, float lowLimit, float hiLimit, int attempts)
{
    char auxStr[MAX_LENGTH];
    int i;
    int value = -1;
    float auxFloat;

    for(i = 0; i < attempts; i++){
        if(!getStringFloatingNumbers(requestMessage, auxStr)){
            printf("%s", errorMessage);
            continue;
        }

        sscanf(auxStr, "%f", &auxFloat);

        if(auxFloat < lowLimit || auxFloat > hiLimit){
            printf("%s", errorMessageLength);
            continue;
        }

        *input = auxFloat;
        value = 0;
        break;
    }

    return value;
}

/**
 * \brief Requests a text from the user and validate if it is a valid e-mail address (No special characters)
 * \param char requestMessage the message to be shown to the user
 * \param char errorMessage the message to be shown to the user in case of data type error
 * \param char errorMessageLength message to be shown to the user in case of length error
 * \param char input string where the entered text will be loaded
 * \param int maxLength maximum length limit to be checked
 * \param int attempts indicates the number of retries to an error
 * \return int value 0 if the text is a valid e-mail address, -1 if it is not
 */
int getValidEmail(char *requestMessage, char *errorMessage, char *errorMessageLength, char *input, int maxLength, int attempts)
{
    char buffer[MAX_LENGTH];
    int i;
    int value = -1;

    for(i = 0; i < attempts; i++){
        if(!getStringEmail(requestMessage, buffer)){
            printf("%s", errorMessage);
            continue;
        }
        if(strlen(buffer) > maxLength){
            printf("%s", errorMessageLength);
            continue;
        }

        strcpy(input, buffer);
        value = 0;
        break;
    }

    return value;
}

/**
 * \brief Requests a text from the user and validate if it is a phone number (No special characters)
 * \param char requestMessage the message to be shown to the user
 * \param char errorMessage the message to be shown to the user in case of data type error
 * \param char errorMessageLength message to be shown to the user in case of length error
 * \param char input string where the entered text will be loaded
 * \param int minLength minimum length limit to be checked
 * \param int maxLength maximum length limit to be checked
 * \param int attempts indicates the number of retries to an error
 * \return int value 0 if the text is a valid phone number, -1 if it is not
 */
int getValidPhoneNumber(char *requestMessage, char *errorMessage, char *errorMessageLength, char *input, int minLength, int maxLength, int attempts)
{
    char buffer[MAX_LENGTH];
    int i;
    int value = -1;

    for(i = 0; i < attempts; i++){
        if(!getStringPhoneNumber(requestMessage, buffer)){
            printf("%s", errorMessage);
            continue;
        }
        if(strlen(buffer) < minLength || strlen(buffer) > maxLength){
            printf("%s", errorMessageLength);
            continue;
        }

        strcpy(input, buffer);
        value = 0;
        break;
    }

    return value;
}

/**
 * \brief Converts the first character to uppercase
 * \param char *string string to convert
 * \return void
 */
void firstUppercaseLetter(char *string)
{
    int i;
    int value = 0;

    for(i = 0; string[i] != '\0'; i++){
        string[0] = toupper(string[0]);

        if(string[i] == ' '){
            string[i + 1] = toupper(string[i + 1]);
            value = i + 1;
        }

        if(i > value)
            string[i] = tolower(string[i]);
    }
}
