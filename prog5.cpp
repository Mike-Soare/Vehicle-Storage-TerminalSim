/***********************************************************************
 *  Title: prog5.cpp (Imperial Mechanic)                               *
 *  Author: Mike B. Soare                                              *
 *  Date: 4/29/2020                                                    *
 *  Purpose: Use of structures                                         *
 ***********************************************************************/
#include "prog5.h"

int main()
{
    Vehicles vehicleArray[100]; //Vehicle structure array with 100 elements
    int vehicleAmount = 0, menuChoice;
    char save;
    bool replay = true;

    cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << "\t  Welcome to the CRAZY SLICKS Shop" << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
    do
    {
        cout << endl << "Whatcha lookin\' for?" << endl << "\t1. Enter Vehicles" << endl << "\t2. Delete Vehicle" << endl << "\t3. List/ Print Vehicles" << endl << "\t4. Print Invoice of Vehicle Costs" << endl << "\t5. End Program" << endl << "Hurry up and make ya choice: ";
        cin >> menuChoice; //Main Menu

        while(menuChoice < 1 || menuChoice > 5) //Validate user choice
        {
            cout << "Ya\'s wastin\' my time" << endl << "Choose again: ";
            cin >> menuChoice;
        }

        switch(menuChoice)
        {
            case 1:
                vehicleAmount = enterVehicles(vehicleAmount, vehicleArray); //Calls enterVehicles()
                break;

            case 2:
                vehicleAmount = deleteVehicle(vehicleAmount, vehicleArray); //Calls deleteVehicle()
                break;

            case 3:
                printVehicles(vehicleAmount, vehicleArray); //Calls printVehicles()
                break;

            case 4:
                printStatistics(vehicleAmount, vehicleArray); //Calls printStatistics()
                break;

            case 5:
                cout << "-----------------------------------------------------" << endl << "Before ya go..." << endl << "Do ya wanna save ya list to a file? (y/n) ";
                cin >> save;

                switch(save) //If user wants to save current vehicleArray data to file
                {
                    case 'y':
                        saveVehiclesToFile(vehicleAmount, vehicleArray); //Calls saveVehclesToFile() if 'y'
                        break;
                    case 'n':
                        cout << "-----------------------------------------------------" << endl << "See ya later" << endl << "-----------------------------------------------------" << endl;
                }
                replay = false; //Sets replay to false | Breaks out doWhile loop
        }
    }while(replay == true); //Replay while replay is true
    
    return 0;
}