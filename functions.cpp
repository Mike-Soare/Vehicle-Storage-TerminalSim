/***********************************************************************
 *  Title: functions.cpp                                               *
 *  Author: Mike B. Soare                                              *
 *  Date: 4/29/2020                                                    *
 *  Purpose: Functions file for prog5.cpp                              *
 ***********************************************************************/
#include "prog5.h"

/************************************************************************
 *  Function Name: enterVehicles()                                      *
 *  Parameters: int vehicleAmount | Vehicles structure array            *
 *  Returns: vehicleAmount to main                                      *
 *  Purpose: Prompts user to enter vehicles from file to array |        *
 *           Enter vehicles to array manually                           *
 ************************************************************************/
int enterVehicles(int vehicleAmt, Vehicles vehicleArray[])
{
    int userChoice;
    char replay, weapons;
    string fileName, temp;
    ifstream inFile;

    cout << "-----------------------------------------------------" << endl << "What\'d you wanna do?" << endl << "\t1. Load my vehicles from a file" << endl << "\t2. Enter one vehicle manually" << endl << "Choose what ya want here: ";
    cin >> userChoice;
    cin.ignore();

    while(userChoice < 1 || userChoice > 2) //Validate user choice
    {
        cout << "-----------------------------------------------------" << endl << "Whadya doin\' thas notta choice" << endl << "Choose again: ";
        cin >> userChoice;
        cin.ignore();
    }

    switch(userChoice)
    {
        case 1:
            if(vehicleAmt >= 100) //Checks if current vehicleAmount is 100 or more | Breaks loop if so
            {
                cout << "-----------------------------------------------------" << endl << "Ya\'s garage\'s filled up!" << endl << "Do something about it." << endl << "-----------------------------------------------------" << endl;
                break;
            }
            
            cout << "-----------------------------------------------------" << endl << "What\'s the name of ya file? (ex: whatever.txt)" << endl << "Give it here: ";
            getline(cin, fileName);

            inFile.open(fileName.c_str()); //Opens user file

            if(inFile.is_open())
            {
                while(getline(inFile, temp, '#') && vehicleAmt != 100) //Extracts line under # is reached
                {
                    vehicleArray[vehicleAmt].vehicleName = temp; //Extracts vehicle name

                    getline(inFile, vehicleArray[vehicleAmt].vehicleDescription, '#'); //Extracts vehicle description
                    
                    getline(inFile, temp, '#');
                    vehicleArray[vehicleAmt].vehicleWeapons = convertToFloat(temp); //Extracts vehicle weapons value and calls convertToFloat to change to int

                    getline(inFile, temp, '#');
                    vehicleArray[vehicleAmt].vehicleInfo.vehicleRepairHours = convertToFloat(temp); //Extracts vehicle repair hours value and calls convertToFloat to change to int

                    getline(inFile, temp, '#');
                    vehicleArray[vehicleAmt].vehicleInfo.hourlyVehicleRepairCosts = convertToFloat(temp); //Extracts vehicle repair costs and calls convertToFloat to change to int

                    getline(inFile, temp, '#');
                    vehicleArray[vehicleAmt].vehicleInfo.vehiclePartsCost = convertToFloat(temp); //Extracts vehicle parts cost and calls convertToFloat to change to int

                    getline(inFile, temp, '#');
                    vehicleArray[vehicleAmt].vehicleInfo.vehicleMaterialsCost = convertToFloat(temp); //Extracts vehicle supplies cost and calls convertToFloat to change to int
                    
                    vehicleAmt++; //Increment vehicleAmount by 1 for each vehicle extracted

                    if(vehicleAmt == 100) //Breaks while loop is vehicleAmount reaches 100
                    {
                        cout << "-----------------------------------------------------" << endl << "I can\'t take anymore." << endl << "-----------------------------------------------------" << endl;
                        break;
                    }
                }
                inFile.close(); //File closes

                cout << "-----------------------------------------------------" << endl << "All ya\'s vehicles from " << fileName << " been imported." << endl << "-----------------------------------------------------" << endl;
            }
            else
            {
                cout << "-----------------------------------------------------" << endl << fileName << "\'s not workin\'... fix it." << endl << "-----------------------------------------------------" << endl;
                break;
            }
            break;

        case 2:
            if(vehicleAmt >= 100) //Checks if current vehicleAmount is 100 or more | Breaks loop if so
            {
                cout << "-----------------------------------------------------" << endl << "Ya\'s garage is currently filled up!" << endl << "Do something about it." << endl << "-----------------------------------------------------" << endl;
                break;
            }

            for(vehicleAmt; vehicleAmt < 100; ) //For loop iterating through
            {
                cout << "-----------------------------------------------------" << endl << "Vehicle Name: ";
                getline(cin, vehicleArray[vehicleAmt].vehicleName); //Prompts user for vehicle name

                cout << endl << "Vehicle Description: ";
                getline(cin, vehicleArray[vehicleAmt].vehicleDescription); //Prompts user for vehicle description

                cout << endl << "Does this vehicle have weapons? (y/n): ";
                cin >> weapons; //Prompts user for vehicle weapons

                if(weapons == 'y')
                    vehicleArray[vehicleAmt].vehicleWeapons = true; //Set equal to 1 if 'y'
                else
                    vehicleArray[vehicleAmt].vehicleWeapons = false;

                cout << endl << "How many hours do ya spend repairing the " << vehicleArray[vehicleAmt].vehicleName << "?" << endl << "Number of Hours: ";
                cin >> vehicleArray[vehicleAmt].vehicleInfo.vehicleRepairHours;//Prompts user for vehicle repair hours

                cout << endl << "What is the cost per hour for repairing the " << vehicleArray[vehicleAmt].vehicleName << "?" << endl << "Cost Per Hour: ";
                cin >> vehicleArray[vehicleAmt].vehicleInfo.hourlyVehicleRepairCosts; //Prompts user for hourly repair costs

                cout << endl << "How much money do ya spend on part for the " << vehicleArray[vehicleAmt].vehicleName << "?" << endl << "Part Cost: ";
                cin >> vehicleArray[vehicleAmt].vehicleInfo.vehiclePartsCost; //Prompts user for vehicle part cost
                
                cout << endl << "How much money do ya spend on supplies for the " << vehicleArray[vehicleAmt].vehicleName << "?" << endl << "Supplies Cost: ";
                cin >> vehicleArray[vehicleAmt].vehicleInfo.vehicleMaterialsCost; //Prompts user for supplies cost

                cout << "-----------------------------------------------------" << endl << "The " << vehicleArray[vehicleAmt].vehicleName << " has been added." << endl;
                
                vehicleAmt++; //Increment vehicleAmount by 1

                cout << "-----------------------------------------------------" << endl << "Wanna add another vehicle? (y/n): ";
                cin >> replay;

                if(replay == 'n') //Breaks loop if 'n'
                    break;

                cin.ignore();
            }
    }
    return vehicleAmt; //Return vehicleAmount to main function
}

/************************************************************************
 *  Function Name: deleteVehicle()                                      *
 *  Parameters: int vehicleAmount | Vehicles structure array            *
 *  Returns: vehicleAmount to main                                      *
 *  Purpose: Prompts user for vehicle name to delete | Returns vehicle  *
 *                                                     amount to main   *
 ************************************************************************/
int deleteVehicle(int vehicleAmt, Vehicles vehicleArray[])
{
    string name;
    bool deleted;

    cout << "-----------------------------------------------------" << endl << "These are the bad boys ya currently got:" << endl;

    for(int keepTrack = 0; keepTrack < vehicleAmt; keepTrack++) //Prints out all vehicle names in vehicleArray
        cout << vehicleArray[keepTrack].vehicleName << endl;

    cin.ignore();

    cout << "-----------------------------------------------------" << endl << "Which one do you wanna let go?" << endl << "Vehicle Name: ";
    getline(cin, name); //Prompts user for vehicle name to delete

    deleted = moveArrayElements(name, vehicleAmt, vehicleArray); //Call moveArrayElements

    if(deleted == true) //If returned boolean value is true run the following
    {
        cout << "-----------------------------------------------------" << endl << "Ya got rid of " << name << "." << endl << "-----------------------------------------------------";
        vehicleAmt--; //Decrement vehicleAmount by 1 if deleted
    }
    else
        cout << "-----------------------------------------------------" << endl << "Ya messed up somewhere." << endl << "-----------------------------------------------------";

    return vehicleAmt;
}

/************************************************************************
 *  Function Name: moveArrayElements()                                  *
 *  Parameters: string name | int vehicleAmount | Vehicles structure    *
 *                                                array                 *
 *  Returns: flag boolean value                                         *
 *  Purpose: Locates name in vehicle array | Moves vehicle array |      *
 *           Returns true/ false                                        *
 ************************************************************************/
bool moveArrayElements(string vehicleRemoveName, int vehicleAmt, Vehicles vehicleArray[])
{
    bool flag;

    for(int count = 0; count < vehicleAmt; count++) //Iterates through every element in vehicleArray
    {
        if(vehicleRemoveName == vehicleArray[count].vehicleName) //If user input matches vehicleArray element name | Run the following
        {
            for(; count < vehicleAmt; count++) 
                vehicleArray[count] = vehicleArray[count + 1]; //Sets current array element to element on its right
            
            flag = true; //Set flag true
            break; //Breaks loop
        }
        if(vehicleRemoveName != vehicleArray[count].vehicleName)
            flag = false;
    }
    return flag;
}

/************************************************************************
 *  Function Name: printVehicles()                                      *
 *  Parameters: int VehicleAmount | Vehicles structure array            *
 *  Returns: None                                                       *
 *  Purpose: Prints current vehicles in array to screen or file         *
 ************************************************************************/
void printVehicles(int vehicleAmt, Vehicles vehicleArray[])
{
    int userChoice;
    ofstream outFile;
    string fileName;

    cout << "-----------------------------------------------------" << endl << "What do ya wanna do?" << endl << "\t1. Print Vehicles to Screen" << endl << "\t2. Print Vehicles to File" << endl << "Whatcha gonna choose: ";
    cin >> userChoice;

    while(userChoice < 1 || userChoice > 2) //Validate user choice
    {
        cout << "-----------------------------------------------------" << endl << "Ya\'s wastin\' my time" << endl << "Choose again: ";
        cin >> userChoice;
    }

    cin.ignore();

    switch(userChoice)
    {
        case 1: //Print data to screen
            for(int count = 0; count < vehicleAmt; count++) //Iterates through vehicleArray | Prints data to screen
            {
                cout << "-----------------------------------------------------" << endl << "Vehicle " << count + 1 << ":" << endl;
                cout << "\tName: " << vehicleArray[count].vehicleName << endl;
                cout << "\tDescription: " << vehicleArray[count].vehicleDescription << endl;
                cout << "\tWeapons? ";

                if(vehicleArray[count].vehicleWeapons == 1) //If boolean value is 1 print out "yes" | Else "no"
                    cout << "yes" << endl;
                else
                    cout << "no" << endl;

                cout << "\tNumber of Hours to Repair Vehicle: " << vehicleArray[count].vehicleInfo.vehicleRepairHours << endl;
                cout << "\tCost Per Hour: $" << vehicleArray[count].vehicleInfo.hourlyVehicleRepairCosts << endl;
                cout << "\tCost of Parts: $" << vehicleArray[count].vehicleInfo.vehiclePartsCost << endl;
                cout << "\tCost of Supplies: $" << vehicleArray[count].vehicleInfo.vehicleMaterialsCost << endl << "-----------------------------------------------------" << endl << endl;
            }
            break;
        
        case 2:
            cout << "-----------------------------------------------------" << endl << "What\'s the file name you wanna write to?" << endl << "Give it here: ";
            getline(cin, fileName); //Prompts user for fileName

            outFile.open(fileName.c_str(), ios::app); //Opens user fileName
            
            for(int count = 0; count < vehicleAmt; count++) //Iterates through inputting data to user fileName
            {
                outFile << "-----------------------------------------------------" << endl << "Vehicle " << count + 1 << ":" << endl;
                outFile << "\tName: " << vehicleArray[count].vehicleName << endl;
                outFile << "\tDescription: " << vehicleArray[count].vehicleDescription << endl;
                outFile << "\tWeapons? ";

                if(vehicleArray[count].vehicleWeapons == 1) //If boolean value is 1 input "yes" | Else "no"
                    outFile << "yes" << endl;
                else
                    outFile << "no" << endl;

                outFile << "\tNumber of Hours to Repair Vehicle: " << vehicleArray[count].vehicleInfo.vehicleRepairHours << endl;
                outFile << "\tCost Per Hour: $" << vehicleArray[count].vehicleInfo.hourlyVehicleRepairCosts << endl;
                outFile << "\tCost of Parts: $" << vehicleArray[count].vehicleInfo.vehiclePartsCost << endl;
                outFile << "\tCost of Supplies: $" << vehicleArray[count].vehicleInfo.vehicleMaterialsCost << endl << "-----------------------------------------------------" << endl << endl;
            }
            outFile.close(); //Close file

            cout << "-----------------------------------------------------" << endl << "Ya vehicles been entered into " << fileName << "." << endl << "-----------------------------------------------------";

            break;
    }
}

/************************************************************************
 *  Function Name: printStatistics()                                    *
 *  Parameters: int vehicleAmount | Vehicles structure array            *
 *  Returns: None                                                       *
 *  Purpose: Prints cost of each vehicle for repairs | Prints total     *
 *           repair costs for all vehicles                              *
 ************************************************************************/
void printStatistics(int vehicleAmt, Vehicles vehicleArray[])
{
    unsigned long long int cost = 0, total = 0; //Very large positive value for calculations

    cout << "-----------------------------------------------------" << endl << "COST OF EACH VEHICLE:" << endl << endl;
    cout << "VEHICLE\t\tCOST" << endl << "-------\t\t----" << endl;

    for(int count = 0; count < vehicleAmt; count++) //For loop calculating cost for each vehicle | Adds cost of each vehicle to total
    {
        cost = (vehicleArray[count].vehicleInfo.vehicleRepairHours * vehicleArray[count].vehicleInfo.hourlyVehicleRepairCosts) + vehicleArray[count].vehicleInfo.vehiclePartsCost + vehicleArray[count].vehicleInfo.vehicleMaterialsCost;
        total += cost;
        cout << vehicleArray[count].vehicleName << ":\t$" << cost << endl;
    }
    cout << "-----------------------------------------------------" << endl << "TOTAL COST:\t$" << total << endl << "-----------------------------------------------------";
}

/************************************************************************
 *  Function Name: saveVehicleToFile()                                  *
 *  Parameters: int vehicleAmount | Vehicles structure array            *
 *  Returns: None                                                       *
 *  Purpose: Activated after user chooses 5 prompt on main menu |       *
 *           Saves current vehicleArray contents to file                *
 ************************************************************************/
void saveVehiclesToFile(int vehicleAmt, Vehicles vehicleArray[])
{
    char userChoice;
    string fileName;
    ofstream outFile;

    cout << "-----------------------------------------------------" << endl << "Ya sure you wanna save ya vehicles? (y/n): ";
    cin >> userChoice;
    cin.ignore();
    
    switch(userChoice)
    {
        case 'y':
            cout << "-----------------------------------------------------" << endl << "What\'s the name of the file you wanna save your vehicles to?" << endl << "Give it here: ";
            getline(cin, fileName); //Prompts user for fileName

            outFile.open(fileName.c_str(), ios::app); //Opens user fileName

            for(int count = 0; count < vehicleAmt; count++) //For loop iterating through vehicle array | Inputs data from array following a '#' sign
                outFile << vehicleArray[count].vehicleName << "#" << vehicleArray[count].vehicleDescription << "#" << vehicleArray[count].vehicleWeapons << "#" << vehicleArray[count].vehicleInfo.vehicleRepairHours << "#" << vehicleArray[count].vehicleInfo.hourlyVehicleRepairCosts << "#" << vehicleArray[count].vehicleInfo.vehiclePartsCost << "#" << vehicleArray[count].vehicleInfo.vehicleMaterialsCost << "#";

            outFile.close(); //Close file

            cout << "-----------------------------------------------------" << endl << "Ya\'s vehicles been saved to " << fileName << "." << endl << "-----------------------------------------------------";

            break; //Break loop
        
        case 'n':
            break;
    }
}

/************************************************************************
 *  Function Name: convertToFloat()                                     *
 *  Parameters: string temp                                             *
 *  Returns: float x                                                    *
 *  Purpose: Takes in string parameter | converts string containing     *
 *                                       value to float variable        *
 ************************************************************************/
float convertToFloat(string s)
{
    istringstream i(s);

    float x;

    if(!(i >> x))
        x = 0;

    return x;
}