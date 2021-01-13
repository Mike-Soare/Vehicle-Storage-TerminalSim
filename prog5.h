/***********************************************************************
 *  Title: prog5.h                                                     *
 *  Author: Mike B. Soare                                              *
 *  Date: 4/29/2020                                                    *
 *  Purpose: Header file for prog5.cpp                                 *
 ***********************************************************************/
#ifndef _PROG5_H
#define _PROG5_H

#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

struct Cost
{
    int vehicleRepairHours;
    double hourlyVehicleRepairCosts;
    double vehiclePartsCost;
    double vehicleMaterialsCost;
};

struct Vehicles
{
    string vehicleName;
    string vehicleDescription;
    bool vehicleWeapons;
    Cost vehicleInfo; //Nested structure of Cost
};

int enterVehicles(int, Vehicles []);
int deleteVehicle(int, Vehicles []);
bool moveArrayElements(string, int, Vehicles []);
void printVehicles(int, Vehicles []);
void printStatistics(int, Vehicles []);
void saveVehiclesToFile(int, Vehicles []);
float convertToFloat(string);

#endif