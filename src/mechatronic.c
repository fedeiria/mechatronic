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

#include "../inc/mechatronic.h"

int humidityThreshold;
float temperatureEngineOn;
float temperatureEngineOff;

/**
 * \brief Allocates dynamic memory for a variable of type Mechatronic
 * \param -
 * \return Pointer *value pointer to Mechatronic with dynamic memory
 *                  - (NULL) if error [if can't allocate memory]
 */
Mechatronic *new_mechatronic(void)
{
    Mechatronic *this = NULL;

    this = (Mechatronic*)malloc(sizeof(Mechatronic));

    if(this == NULL)
        mechatronic_showErrorMessage();

    return this;
}

/**
 * \brief Set datetime to the structure Date
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \param int value option selected by user
 * \return void
 */
void mechatronic_setDate(Mechatronic *this)
{
    time_t now;
    struct tm *date = NULL;
    time(&now);

    date = localtime(&now);

    if(date != NULL){
        this->today.day = date->tm_mday;
        this->today.month = date->tm_mon + 1;
        this->today.year = date->tm_year + 1900;
        this->today.hour = date->tm_hour;
        this->today.minutes = date->tm_min;
        this->today.seconds = date->tm_sec;
    }
    else
        mechatronic_showErrorMessage();
}

/**
 * \brief Set the engine start temperature
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setTemperatureEngineOn(Mechatronic *this)
{
    this->temperatureEngineOn = temperatureEngineOn;
}

/**
 * \brief Set the engine off temperature
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setTemperatureEngineOff(Mechatronic *this)
{
    this->temperatureEngineOff = temperatureEngineOff;
}

/**
 * \brief Set the humidity threshold
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setHumidityThreshold(Mechatronic *this)
{
    this->humidityThreshold = humidityThreshold;
}

/**
 * \brief Set the employee ID
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setIdEmployee(Mechatronic *this)
{
    this->idEmployee = ID_EMPLOYEE;
}

/**
 * \brief Set the name and surname of the user
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setNameSurname(Mechatronic *this)
{
    strcpy(this->nameSurname, EMPLOYEE_NAME);
}

/**
 * \brief Read temperature input by the user
 * \return Read temperature
 */
float mechatronic_newAmbientTemperatureRead(void)
{
    float temperatureRead;

    mechatronic_showSetAmbientTemperatureReadMessage();
    getValidFloat("\nVALOR DE TEMPERATURA AMBIENTE SENSADO: ", "\nERROR!, solo se permite el ingreso de numeros\n\n", "\nERROR!, valor fuera de rango. El valor ingresado debe ser >= -20 y <= 60\n\n", &temperatureRead, -20, 60, 1000);

    return temperatureRead;
}

/**
 * \brief Set temperature input by the user
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \param Float value enter by the user
 * \return void
 */
void mechatronic_setAmbientTemperatureRead(Mechatronic *this, float value)
{
    this->ambientTemperatureRead = value;
}

/**
 * \brief Read ambient humidity input by the user
 * \return Read humidity
 */
int mechatronic_newAmbientHumidityRead(void)
{
    int humidityRead;

    mechatronic_showSetAmbientHumidityReadMessage();
    getValidInt("\nVALOR DE HUMEDAD SENSADO: ", "\nERROR!, solo se permite el ingreso de numeros\n\n", "\nERROR!, valor fuera de rango. El valor ingresado debe ser >= 0 y <= 100\n\n", &humidityRead, 0, 100, 1000);

    return humidityRead;
}

/**
 * \brief Set ambient humidity input by the user
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \param Int value enter by the user
 * \return void
 */
void mechatronic_setAmbientHumidityRead( Mechatronic *this, int value)
{
    this->humidityTemperatureRead = value;
}

/**
 * \brief Set emergency event type
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setEmergencyEventType(Mechatronic *this)
{
    strcpy(this->eventType, EMERGENCY);
}

/**
 * \brief Set event type
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setEventType(Mechatronic *this)
{
    if(this != NULL)
    {
        if(this->ambientTemperatureRead > this->temperatureEngineOn && this->humidityTemperatureRead >= this->humidityThreshold)
        {
            strcpy(this->eventType, BOOT_BY_TEMPERATURE);
        }
        else if(this->ambientTemperatureRead < this->temperatureEngineOff)
        {
            strcpy(this->eventType, STOP_BY_TEMPERATURE);
        }
        else if(this->humidityTemperatureRead > this->humidityThreshold)
        {
            strcpy(this->eventType, BOOT_BY_HUMIDITY);
        }
        else if(this->humidityTemperatureRead <= this->humidityThreshold)
        {
            strcpy(this->eventType, STOP_BY_HUMIDITY);
        }
    }
    else
    {
        printf("\nError!, no hay espacio en memoria RAM.\n\n");
        system("pause");
    }
}

/**
 * \brief Set a new mechatronic structure
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \param Int emergencyOption value determining whether an emergency stop has occurred
 * \return void
 */
void mechatronic_newMechatronicObject(ArrayList *pArrayList, int emergencyOption)
{
    if(pArrayList != NULL && emergencyOption != 1){
        Mechatronic *this = new_mechatronic();
        mechatronic_setDate(this);
        mechatronic_setIdEmployee(this);
        mechatronic_setNameSurname(this);
        mechatronic_setTemperatureEngineOn(this);
        mechatronic_setTemperatureEngineOff(this);
        mechatronic_setHumidityThreshold(this);
        mechatronic_setAmbientTemperatureRead(this, mechatronic_newAmbientTemperatureRead());
        mechatronic_setAmbientHumidityRead(this, mechatronic_newAmbientHumidityRead());
        mechatronic_setEventType(this);
        mechatronic_confirmNewMechatronicData(pArrayList, this);
        printf("\n");
        system("pause");
    }
    else if(pArrayList != NULL && emergencyOption == 1){
        mechatronic_showWelcomeMessage();
        printf("No se puede utilizar este menu debido a que se ha ejecutado un evento de tipo '%s'.\n\n", EMERGENCY);
        system("pause");
    }
    else
        mechatronic_showErrorMessage();
}

/**
 * \brief Set a mechatronic emergency structure
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_newMechatronicEmergencyObject(ArrayList *pArrayList)
{
    if (pArrayList != NULL){
        Mechatronic *this = new_mechatronic();
        mechatronic_setDate(this);
        mechatronic_setIdEmployee(this);
        mechatronic_setNameSurname(this);
        mechatronic_setTemperatureEngineOn(this);
        mechatronic_setTemperatureEngineOff(this);
        mechatronic_setHumidityThreshold(this);
        mechatronic_setAmbientTemperatureRead(this, EMERGENCY_AMBIENT_TEMPERATURE);
        mechatronic_setAmbientHumidityRead(this, EMERGENCY_AMBIENT_HUMIDITY);
        mechatronic_setEmergencyEventType(this);
        mechatronic_printNewMechatronicData(this);
        al_add(pArrayList, this);
        mechatronic_saveBinaryFile(pArrayList, this);
        mechatronic_createTextFile(pArrayList, this);
    }
    else
        mechatronic_showErrorMessage();
}

/**
 * \brief Confirmation screen
 * \param ArrayList *pArrayList pointer to the array list
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_confirmNewMechatronicData(ArrayList *pArrayList, Mechatronic *this)
{
    int option;

    do{
        mechatronic_showWelcomeMessage();
        mechatronic_printNewMechatronicData(this);
        printf("\n1 - CONFIRMAR DATOS\n2 - CANCELAR OPERACION\n3 - MODIFICAR DATOS\n");
        getValidInt("\nINGRESE OPCION: ", "\nERROR!, la opcion debe ser numerica\n\n", "\nERROR!, ingrese una opcion entre 1 y 3\n\n", &option, 1, 3, 100);

        if(option == 1){
            al_add(pArrayList, this);
            printf("\n****** DATOS GUARDADOS ******\n");
        }
        else if(option == 2)
            printf("\n****** OPERACION CANCELADA ******\n");

        else
            mechatronic_editNewMechatronicData(pArrayList, this);

    }while(option == 3);

    mechatronic_saveBinaryFile(pArrayList, this);
    mechatronic_createTextFile(pArrayList, this);
}

/**
 * \brief Screen to modify the data
 * \param ArrayList *pArrayList pointer to the array list
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_editNewMechatronicData(ArrayList *pArrayList, Mechatronic *this)
{
    int option;

    mechatronic_showModifyMechatronicMessage();
    mechatronic_printNewMechatronicData(this);
    printf("\n1 - MODIFICAR DATOS COMPLETOS\n\n2 - MODIFICAR LECTURA DE TEMPERATURA AMBIENTE\n\n3 - MODIFICAR LECTURA DE HUMEDAD\n\n4 - SALIR SIN MODIFICAR\n\n");
    getValidInt("\nINGRESE OPCION: ", "\nERROR!, la opcion debe ser numerica\n\n", "\nERROR!, ingrese una opcion entre 1 y 4\n\n", &option, 1, 4, 100);

    if(option == 1){
        mechatronic_showModifyMechatronicMessage();
        mechatronic_setAmbientTemperatureRead(this, mechatronic_newAmbientTemperatureRead());
        mechatronic_setAmbientHumidityRead(this, mechatronic_newAmbientHumidityRead());
        printf("\nDATOS MODIFICADOS\n\n");
        system("pause");
    }
    else if(option == 2){
        mechatronic_showModifyMechatronicMessage();
        mechatronic_setAmbientTemperatureRead(this, mechatronic_newAmbientTemperatureRead());
        printf("\nDATO MODIFICADO\n\n");
        system("pause");
    }
    else if(option == 3){
        mechatronic_showModifyMechatronicMessage();
        mechatronic_setAmbientHumidityRead(this, mechatronic_newAmbientHumidityRead());
        printf("\nDATO MODIFICADO\n\n");
        system("pause");
    }
    else
        option = 4;
}

/**
 * \brief Display to confirm an emergency stop
 * \param ArrayList *pArrayList pointer to the array list
 * \return int opcion selected by the user
 */
int mechatronic_emergencySwitch(ArrayList *pArrayList)
{
    int option;

    mechatronic_showEmergencySwitchMessage();
    printf("\nEJECUTAR PARADA DE EMERGENCIA?\n\n1 - CONFIRMAR\n\n2 - CANCELAR\n");
    getValidInt("\nINGRESE OPCION: ", "\nERROR!, la opcion debe ser numerica\n", "\nERROR!, ingrese una opcion entre 1 y 2\n", &option, 1, 2, 100);

    if(option == 1){
        mechatronic_newMechatronicEmergencyObject(pArrayList);
        printf("\nPARADA DE EMERGENCIA EJECUTADA\n\n");
        system("pause");
    }
    else{
        option = 2;
        printf("\nOPERACION CANCELADA\n\n");
        system("pause");
    }

    return option;
}

/**
 * \brief Displays the data of a mechatronic type structure
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_printNewMechatronicData(Mechatronic *this)
{
    printf("\nID OPERARIO: %d\n\nNOMBRE OPERARIO: %s\n\nTIPO DE EVENTO: %s\n\nTEMPERATURA AMBIENTE SENSADA: %.2f\n\nHUMEDAD AMBIENTE SENSADA: %d\n", this->idEmployee, this->nameSurname, this->eventType, this->ambientTemperatureRead, this->humidityTemperatureRead);
    printf("\n-----------------------------------------------\n");
}

/**
 * \brief Displays the general events report
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_generalEventsReport(ArrayList *pArrayList)
{
    int i;
    Mechatronic *this = NULL;

    mechatronic_showWelcomeMessage();
    printf("************** INFORME GENERAL DE EVENTOS ***********\n\n");

    if(pArrayList != NULL){
        for(i = 0; i < al_len(pArrayList); i++){
            this = al_get(pArrayList, i);

            if(this != NULL)
                mechatronic_printEventList(this);
            else
                mechatronic_showErrorMessage();
        }

        if(i == 0) {
            printf("El programa no tiene registros almacenados.\n\n");
            system("pause");
        }
        else {
            printf("Cantidad total de eventos registrados: %d\n\n", i);
            system("pause");
        }
    }
    else
        mechatronic_showErrorMessage();
}

/**
 * \brief Displays the emergency report
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_emergencyEventsReport(ArrayList *pArrayList)
{
    int i, j = 0;
    Mechatronic *this = NULL;

    mechatronic_showWelcomeMessage();
    printf("*************** INFORME DE EMERGENCIAS **************\n\n");

    if(pArrayList != NULL){
        for(i = 0; i < al_len(pArrayList); i++){
            this = al_get(pArrayList, i);

            if(this != NULL){
                if(!strcmp(this->eventType, EMERGENCY)){
                    mechatronic_printEventList(this);
                    j++;
                }
            }
        }
        if(i == 0){
            printf("El programa no tiene registros almacenados.\n\n");
            system("pause");
        }
        else{
            printf("Cantidad total de eventos '%s' registrados: %d\n\n", EMERGENCY, j);
            system("pause");
        }
    }
    else
        mechatronic_showErrorMessage();
}

/**
 * \brief Displays all data of a mechatronic type structure
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_printEventList(Mechatronic *this)
{
    printf("ID OPERARIO: %d\n\nNOMBRE OPERARIO: %s\n\nTIPO DE EVENTO: %s\n\nTEMPERATURA AMBIENTE SENSADA: %.2f\n\nHUMEDAD AMBIENTE SENSADA: %d\n\nTEMPERATURA CONFIGURADA MOTOR ENCENDIDO: %.2f\n\nTEMPERATURA CONFIGURADA MOTOR APAGADO: %.2f\n\nUMBRAL HUMEDAD : %d\n", this->idEmployee, this->nameSurname, this->eventType, this->ambientTemperatureRead, this->humidityTemperatureRead, this->temperatureEngineOn, this->temperatureEngineOff, this->humidityThreshold);
    printf("\n---------------------------------------------------\n\n");
}

/**
 * \brief Creates a binary file with the information of the mechatronic structures. If the file exists, add information to the end of the file
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_createBinaryFile(ArrayList *pArrayList)
{
    int i;
    int size;
    int length;
    FILE *file = NULL;
    Mechatronic *this = NULL;

    if(pArrayList != NULL){
        file = fopen(MECHATRONIC_BINARY_FILE, "rb");

        if(file == NULL){
            file = fopen(MECHATRONIC_BINARY_FILE, "wb");

            if(file == NULL){
                system("cls");
                printf("\nERROR!, no se pudo leer/crear el archivo: %s.\nNo hay datos cargados.\n", MECHATRONIC_BINARY_FILE);
                system("pause");
            }
        }
        else{
            fseek(file, 0, SEEK_END);
            size = ftell(file);
            length = size / sizeof(Mechatronic);
            rewind(file);

            for(i = 0; i < length; i++){
                this = new_mechatronic();
                fread(this, sizeof(Mechatronic), 1, file);
                al_add(pArrayList, this);
            }
        }
    }
    else
        mechatronic_showErrorMessage();

    fclose(file);
}

/**
 * \brief Saves the information in the binary file. If the file exists, add information to the end of the file
 * \param ArrayList *pArrayList pointer to the array list
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_saveBinaryFile(ArrayList *pArrayList, Mechatronic *this)
{
    int i;
    FILE *file = NULL;

    file = fopen(MECHATRONIC_BINARY_FILE, "wb");

    if(file != NULL){
        for(i = 0; i < al_len(pArrayList); i++){
            this = al_get(pArrayList, i);

            if(this != NULL)
                fwrite(this, sizeof(Mechatronic), 1, file);
            else
                mechatronic_showErrorMessage();
        }
    }
    else{
        system("cls");
        printf("\nERROR!, no se pudo abrir el archivo: %s.\nDatos sin guardar.\n", MECHATRONIC_BINARY_FILE);
        system("pause");
    }

    fclose(file);
}

/**
 * \brief Creates a text file with the information of the mechatronic structures
 * \param ArrayList *pArrayList pointer to the array list
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_createTextFile(ArrayList *pArrayList, Mechatronic *this)
{
    int i;
    FILE *file = NULL;

    file = fopen(MECHATRONIC_OUTPUT_FILE, "w");

    if(file != NULL){
        fprintf(file, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t******************** LISTADO DE EVENTOS ********************\n\n\n");
        fprintf(file, "FECHA EVENTO\t\t\tID OPERARIO\t\tNOMBRE OPERARIO\t\t\t\t\tTIPO DE EVENTO\t\t\t\t\tTEMPERATURA AMBIENTE SENSADA\t\t\tHUMEDAD AMBIENTE SENSADA\t\t\tTEMPERATURA CONFIGURADA MOTOR ENCENDIDO\t\tTEMPERATURA CONFIGURADA MOTOR APAGADO\t\tUMBRAL HUMEDAD\t\t\t\t\t\t\n");
        fprintf(file, "-------------\t\t\t-----------\t\t---------------\t\t\t\t\t-----------------\t\t\t\t----------------------------\t\t\t------------------------\t\t\t---------------------------------------\t\t-------------------------------------\t\t--------------\n\n");

        for(i = 0; i < al_len(pArrayList); i++){
            this = al_get(pArrayList, i);

            if(this != NULL)
                fprintf(file, "%02d/%02d/%d %02d:%02d:%02d\t\t%d\t\t%s\t\t\t%25s\t\t\t\t%.2f\t\t\t\t\t\t%d\t\t\t\t\t\t%.2f\t\t\t\t\t\t%.2f\t\t\t\t\t\t%d\n", this->today.day, this->today.month, this->today.year, this->today.hour, this->today.minutes, this->today.seconds, this->idEmployee, this->nameSurname, this->eventType, this->ambientTemperatureRead, this->humidityTemperatureRead, this->temperatureEngineOn, this->temperatureEngineOff, this->humidityThreshold);
            else
                mechatronic_showErrorMessage();
        }
    }
    else{
        system("cls");
        printf("\nERROR!, no se pudo crear el archivo: %s\n", MECHATRONIC_OUTPUT_FILE);
        system("pause");
    }

    fclose(file);
}

/**
 * \brief Load configuration file information
 * \param char *filename file to read
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_loadTextFile(char *fileName, ArrayList *pArrayList)
{
    char auxTemperatureOn[MAX_STRING_CHARS], auxTemperatureOff[MAX_STRING_CHARS], auxHumidity[MAX_STRING_CHARS], stringFile[MAX_STRING_CHARS];
    int i, j = 0, k = 0, l = 0;
    FILE *file = NULL;

    mechatronic_showLoadConfigUserFileMessage();
    file = fopen(fileName, "r");

    if(file == NULL){
        mechatronic_showWelcomeMessage();
        printf("No se pudo leer el archivo '%s'. El archivo no existe o su nombre fue modificado.\n\n", MECHATRONIC_USER_CONFIG);

        file = fopen(fileName, "w");

        if(file != NULL){
            humidityThreshold = INITIAL_HUMIDITY_THRESHOLD;
            temperatureEngineOn = INITIAL_ENGINE_START_TEMPERATURE;
            temperatureEngineOff = INITIAL_ENGINE_IDLE_TEMPERATURE;

            printf("A continuacion, se creara el archivo con los siguientes valores de temperatura por defecto:\n\n");
            printf("- Temperatura inicial motor encendido: %.2f grados\n", temperatureEngineOn);
            printf("- Temperatura inicial motor apagado: %.2f grados\n", temperatureEngineOff);
            printf("- Temperatura inicial umbral de humedad: %d%%\n\n", humidityThreshold);

            fprintf(file, "temperatureEngineOn=%.2f\n", temperatureEngineOn);
            fprintf(file, "temperatureEngineOff=%.2f\n", temperatureEngineOff);
            fprintf(file, "humidityThreshold=%d", humidityThreshold);

            system("pause");
        }
        else{
            system("cls");
            mechatronic_showWelcomeMessage();
            printf("ERROR!, no se pudo crear el archivo: %s\n\n", MECHATRONIC_USER_CONFIG);
            system("pause");
            exit(0);
        }
    }
    else{
        // limpio los arrays
        memset(&auxTemperatureOn, 0, sizeof(auxTemperatureOn));
        memset(&auxTemperatureOff, 0, sizeof(auxTemperatureOff));
        memset(&auxHumidity, 0, sizeof(auxHumidity));

        // leo y cargo cada linea del archivo
        while(!feof(file)){
            fscanf(file, "%[^\n]\n", auxTemperatureOn);
            fscanf(file, "%[^\n]\n", auxTemperatureOff);
            fscanf(file, "%[^\n]\n", auxHumidity);
        }

        // declaro variables para leer la longitud de cada linea del archivo
        int lengthTempOnRead, lengthTempOffRead, lengthHumidityRead;

        lengthTempOnRead = strlen(auxTemperatureOn);
        lengthTempOffRead = strlen(auxTemperatureOff);
        lengthHumidityRead = strlen(auxHumidity);

        if((lengthTempOnRead > MAX_STRING_CHARS) || (lengthTempOffRead > MAX_STRING_CHARS) || (lengthHumidityRead > MAX_STRING_CHARS)){
            printf("\nNo se puede leer el archivo '%s'. Revise su configuracion y vuelva a reintentar.\n\n", MECHATRONIC_USER_CONFIG);
            system("pause");
            exit(0);
        }
        else{
            memset(&stringFile, 0, sizeof(stringFile));

            // Recorro el array de la primera linea del archivo en busca del valor de 'temperatura motor encendido'
            for(i = 0; i < MAX_STRING_CHARS; i++){
                if(auxTemperatureOn[i] >= '0' && auxTemperatureOn[i] <= '9'){
                    stringFile[j] = auxTemperatureOn[i];
                    j++;
                }
                else if(auxTemperatureOn[i] == '.'){
                    break;
                }
            }

            temperatureEngineOn = atof(stringFile);
            memset(&stringFile, 0, sizeof(stringFile));

            // Recorro el array de la segunda linea del archivo en busca del valor de 'temperatura motor apagado'
            for(i = 0; i < MAX_STRING_CHARS; i++){
                if(auxTemperatureOff[i] >= '0' && auxTemperatureOff[i] <= '9'){
                    stringFile[k] = auxTemperatureOff[i];
                    k++;
                }
                else if(auxTemperatureOff[i] == '.'){
                    break;
                }
            }

            temperatureEngineOff = atof(stringFile);
            memset(&stringFile, 0, sizeof(stringFile));

            // Recorro el array de la tercera linea del archivo en busca del valor de 'umbral de humedad'
            for(i = 0; i < MAX_STRING_CHARS; i++){
                if(auxHumidity[i] >= '0' && auxHumidity[i] <= '9'){
                    stringFile[l] = auxHumidity[i];
                    l++;
                }
                else if(auxHumidity[i] == '.'){
                    break;
                }
            }

            humidityThreshold = atoi(stringFile);

            mechatronic_showWelcomeMessage();
            printf("Archivo '%s' cargado con exito.\n\n", MECHATRONIC_USER_CONFIG);
            printf("- Temperatura inicial motor encendido: %.2f grados\n", temperatureEngineOn);
            printf("- Temperatura inicial motor apagado: %.2f grados\n", temperatureEngineOff);
            printf("- Temperatura inicial umbral de humedad: %d%%\n\n", humidityThreshold);
            system("pause");
        }
    }

    fclose(file);
}

/**
 * \brief Calls the loadtextfile function
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_userConfig(ArrayList *pArrayList)
{
    mechatronic_loadTextFile(MECHATRONIC_USER_CONFIG, pArrayList);
}

/**
 * \brief Message to be displayed when starting the program
 * \return void
 */
void mechatronic_showWelcomeMessage(void)
{
    system("cls");
    printf("\n*****************************************************\n");
    printf("|          SISTEMA DE CONTROL MECATRONICO           |\n");
    printf("*****************************************************\n\n");
}

/**
 * \brief Shows a menu with options
 * \param void
 * \return int option returns the value entered by the user
 */
int mechatronic_showMainMenu(void)
{
    int option;

    do{
        mechatronic_showWelcomeMessage();
        printf("*****************************************************\n");
        printf("|                   MENU PRINCIPAL                  |\n");
        printf("*****************************************************\n\n");
        printf("1 - INGRESO DE DATOS\n\n");
        printf("2 - INTERRUPTOR DE EMERGENCIA\n\n");
        printf("3 - INFORME GENERAL DE EVENTOS\n\n");
        printf("4 - INFORME DE EMERGENCIAS\n\n");
        printf("5 - ARCHIVO DE CONFIGURACION\n\n");
        printf("6 - SALIR\n\n");
        printf("-----------------------------------------------------\n");

        getValidInt("\nINGRESE OPCION: ", "\nERROR!, solo se permite el ingreso de numeros\n", "\nERROR!, seleccione una opcion entre 1 y 6\n", &option, 1, 6, 100);

    }while(!option);

    return option;
}

/**
 * \brief Message to be displayed when the program failed
 * \return void
 */
void mechatronic_showErrorMessage(void)
{
    mechatronic_showWelcomeMessage();
    printf("************ MENSAJE DE ERROR ************\n");
    printf("\nError al asignar memoria RAM.\n");
    exit(0);
}

/**
 * \brief Message to be displayed to the user
 * \return void
 */
void mechatronic_showEmergencySwitchMessage(void)
{
    system("cls");
    printf("\n************ PARADA DE EMERGENCIA ************\n");
}

/**
 * \brief Message to be displayed to the user
 * \return void
 */
void mechatronic_showLoadConfigUserFileMessage(void)
{
    system("cls");
    printf("\n************ ARCHIVO DE CONFIGURACION DE USUARIO ************\n");
}

/**
 * \brief Message to be displayed to the user
 * \return void
 */
void mechatronic_showSetAmbientTemperatureReadMessage(void)
{
    system("cls");
    printf("\n************ NUEVA LECTURA DE TEMPERATURA AMBIENTE ************\n");
}

/**
 * \brief Message to be displayed to the user
 * \return void
 */
void mechatronic_showSetAmbientHumidityReadMessage(void)
{
    system("cls");
    printf("\n************ NUEVA LECTURA DE HUMEDAD AMBIENTE ************\n");
}

/**
 * \brief Message to be displayed to the user
 * \return void
 */
void mechatronic_showModifyMechatronicMessage(void)
{
    system("cls");
    printf("\n************ MODIFICAR DATOS ************\n");
}
