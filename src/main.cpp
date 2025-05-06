#include <iostream>
#include <fstream>
#include <string>

#include "club.h"
#include "input_handler.h"

int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <log file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open()) 
    {
        std::cerr << "Failed to open log file" << std::endl;
        return 1;
    }

    int numberTables;
    std::string openTime;
    std::string closeTime;
    int costPerHour;

    std::string line;

    try 
    {
        ReadClubHeader(file, numberTables, openTime, closeTime, costPerHour, line);
        Club club(numberTables, openTime, closeTime, costPerHour);
        ReadEvents(file, club, closeTime, line);
        club.PrintReport();
    } 
    catch (...)
    {
        std::cerr << line << std::endl;
        return 1;
    } 

    return 0;
}