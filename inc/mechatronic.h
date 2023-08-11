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

#ifndef MECHATRONIC_H_INCLUDED
#define MECHATRONIC_H_INCLUDED

#include <time.h>
#include "arraylist.h"
#include "validations.h"

// LONGITUD CARACTERES
#define MAX_EVENTS_CHARS 31
#define MAX_STRING_CHARS 1024
#define MAX_EMPLOYEE_NAME_CHARS 61

// ID OPERARIO
#define ID_EMPLOYEE 32765881

// NOMBRE OPERARIO
#define EMPLOYEE_NAME "Federico Iriarte"

// VALORES INICIALES TEMPERATURA MOTOR
#define INITIAL_ENGINE_IDLE_TEMPERATURE 15
#define INITIAL_ENGINE_START_TEMPERATURE 25

// VALOR INICIAL UMBRAL DE HUMEDAD
#define INITIAL_HUMIDITY_THRESHOLD 70

// VALORES ESTADO EMERGENCIA
#define EMERGENCY_AMBIENT_HUMIDITY 888
#define EMERGENCY_AMBIENT_TEMPERATURE 999.00

// TIPOS DE EVENTOS
#define EMERGENCY "Emergencia"
#define STOP_BY_HUMIDITY "Parada por humedad"
#define BOOT_BY_HUMIDITY "Arranque por humedad"
#define STOP_BY_TEMPERATURE "Parada por temperatura"
#define BOOT_BY_TEMPERATURE "Arranque por temperatura"

// ARCHIVOS
#define MECHATRONIC_OUTPUT_FILE "data.txt"
#define MECHATRONIC_BINARY_FILE "data.bin"
#define MECHATRONIC_USER_CONFIG "config.ini"

typedef struct{

    int day;
    int month;
    int year;
    int hour;
    int minutes;
    int seconds;

}Date;

typedef struct{

    Date today;
    char eventType[MAX_EVENTS_CHARS];
    int idEmployee;
    char nameSurname[MAX_EMPLOYEE_NAME_CHARS];
    float ambientTemperatureRead;
    int humidityTemperatureRead;
    float temperatureEngineOn;
    float temperatureEngineOff;
    int humidityThreshold;

}Mechatronic;

/**
 * \brief Allocates dynamic memory for a variable of type Mechatronic
 * \param -
 * \return Pointer *value pointer to Mechatronic with dynamic memory
 *                  - (NULL) if error [if can't allocate memory]
 */
Mechatronic *new_mechatronic(void);

/**
 * \brief Set datetime to the structure Date
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \param int value option selected by user
 * \return void
 */
void mechatronic_setDate(Mechatronic *this);

/**
 * \brief Set the engine start temperature
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setTemperatureEngineOn(Mechatronic *this);

/**
 * \brief Set the engine off temperature
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setTemperatureEngineOff(Mechatronic *this);

/**
 * \brief Set the humidity threshold
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setHumidityThreshold(Mechatronic *this);

/**
 * \brief Set the employee ID
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setIdEmployee(Mechatronic *this);

/**
 * \brief Set the name and surname of the user
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setNameSurname(Mechatronic *this);

/**
 * \brief Read temperature input by the user
 * \return Read temperature
 */
float mechatronic_newAmbientTemperatureRead(void);

/**
 * \brief Set temperature input by the user
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \param Float value enter by the user
 * \return void
 */
void mechatronic_setAmbientTemperatureRead(Mechatronic *this, float value);

/**
 * \brief Read ambient humidity input by the user
 * \return Read humidity
 */
int mechatronic_newAmbientHumidityRead(void);

/**
 * \brief Set ambient humidity input by the user
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \param Int value enter by the user
 * \return void
 */
void mechatronic_setAmbientHumidityRead( Mechatronic *this, int value);

/**
 * \brief Set emergency event type
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setEmergencyEventType(Mechatronic *this);

/**
 * \brief Set event type
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_setEventType(Mechatronic *this);

/**
 * \brief Set a new mechatronic structure
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \param Int emergencyOption value determining whether an emergency stop has occurred
 * \return void
 */
void mechatronic_newMechatronicObject(ArrayList *pArrayList, int emergencyOption);

/**
 * \brief Set a mechatronic emergency structure
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_newMechatronicEmergencyObject(ArrayList *pArrayList);

/**
 * \brief Confirmation screen
 * \param ArrayList *pArrayList pointer to the array list
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_confirmNewMechatronicData(ArrayList *pArrayList, Mechatronic *this);

/**
 * \brief Screen to modify the data
 * \param ArrayList *pArrayList pointer to the array list
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_editNewMechatronicData(ArrayList *pArrayList, Mechatronic *this);

/**
 * \brief Display to confirm an emergency stop
 * \param ArrayList *pArrayList pointer to the array list
 * \return int opcion selected by the user
 */
int mechatronic_emergencySwitch(ArrayList *pArrayList);

/**
 * \brief Displays the data of a mechatronic type structure
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_printNewMechatronicData(Mechatronic *this);

/**
 * \brief Displays the general events report
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_generalEventsReport(ArrayList *pArrayList);

/**
 * \brief Displays the emergency report
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_emergencyEventsReport(ArrayList *pArrayList);

/**
 * \brief Displays all data of a mechatronic type structure
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_printEventList(Mechatronic *this);

/**
 * \brief Creates a binary file with the information of the mechatronic structures. If the file exists, add information to the end of the file
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_createBinaryFile(ArrayList *pArrayList);

/**
 * \brief Saves the information in the binary file. If the file exists, add information to the end of the file
 * \param ArrayList *pArrayList pointer to the array list
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_saveBinaryFile(ArrayList *pArrayList, Mechatronic *this);

/**
 * \brief Creates a text file with the information of the mechatronic structures
 * \param ArrayList *pArrayList pointer to the array list
 * \param Mechatronic *this pointer to the structure Mechatronic
 * \return void
 */
void mechatronic_createTextFile(ArrayList *pArrayList, Mechatronic *this);

/**
 * \brief Load configuration file information
 * \param char *filename file to read
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_loadTextFile(char *fileName, ArrayList *pArrayList);

/**
 * \brief Calls the loadtextfile function
 * \param ArrayList *pArrayList pointer to the array list
 * \return void
 */
void mechatronic_userConfig(ArrayList *pArrayList);

/**
 * \brief Message to be displayed when starting the program
 * \return void
 */
void mechatronic_showWelcomeMessage(void);

/**
 * \brief Shows a menu with options
 * \param void
 * \return int option returns the value entered by the user
 */
int mechatronic_showMainMenu(void);

/**
 * \brief Message to be displayed when the program failed
 * \return void
 */
void mechatronic_showErrorMessage(void);

/**
 * \brief Message to be displayed to the user
 * \return void
 */
void mechatronic_showEmergencySwitchMessage(void);

/**
 * \brief Message to be displayed to the user
 * \return void
 */
void mechatronic_showLoadConfigUserFileMessage(void);

/**
 * \brief Message to be displayed to the user
 * \return void
 */
void mechatronic_showSetAmbientTemperatureReadMessage(void);

/**
 * \brief Message to be displayed to the user
 * \return void
 */
void mechatronic_showSetAmbientHumidityReadMessage(void);

/**
 * \brief Message to be displayed to the user
 * \return void
 */
void mechatronic_showModifyMechatronicMessage(void);

#endif // MECHATRONIC_H_INCLUDED
