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

#include "../inc/init.h"

void init()
{
    char start;
    int option, emergencyOption;
    ArrayList *pArrayList = al_newArrayList();

    mechatronic_createBinaryFile(pArrayList);
    mechatronic_loadTextFile(MECHATRONIC_USER_CONFIG, pArrayList);

    start = 's';
    emergencyOption = 0;

    while(start == 's'){
        option = mechatronic_showMainMenu();

        switch(option){
            case 1:
                mechatronic_newMechatronicObject(pArrayList, emergencyOption);
                break;
            case 2:
                emergencyOption = mechatronic_emergencySwitch(pArrayList);
                break;
            case 3:
                mechatronic_generalEventsReport(pArrayList);
                break;
            case 4:
                mechatronic_emergencyEventsReport(pArrayList);
                break;
            case 5:
                mechatronic_userConfig(pArrayList);
                break;
            case 6:
                start = 'n';
                break;
        }
    }

    al_deleteArrayList(pArrayList);
}
