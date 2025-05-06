#include "input_handler.h"

namespace 
{
    bool IsValidClientName(const std::string& str) 
    {
        std::regex pattern("^[a-z0-9_-]+$");
        return std::regex_match(str, pattern);
    }

    void ReadPositiveInteger(std::istringstream& iss, int& value) 
    {
        std::string line;

        if (iss >> line) 
        {
            std::size_t pos;
            value = std::stoi(line, &pos);

            if (pos < line.size()) 
                throw std::invalid_argument("Invalid positive number");
        } 
        else 
            throw std::invalid_argument("Invalid positive number");
        
        if (value <= 0) 
            throw std::invalid_argument("Invalid positive number");
    }
}

void ReadClubHeader(std::ifstream& file, int& numberTables, std::string& openTime, 
 std::string& closeTime, int& costPerHour, std::string& line) 
{
    for (int i = 0; i < 3; ++i) 
    {
        std::getline(file, line);
        std::istringstream iss(line);

        if (i == 1) 
        {
            iss >> openTime >> closeTime;
            Time timeCheck1(openTime);
            Time timeCheck2(closeTime);
        } 
        else 
        {
            if (i == 0) 
                ReadPositiveInteger(iss, numberTables);
            else if (i == 2) 
                ReadPositiveInteger(iss, costPerHour);
        }
    }   
}

void ReadEvents(std::ifstream& file, Club& club, const std::string& closeTime, std::string& line) 
{
    bool clubClosed = false;

    while (std::getline(file, line)) 
    {
        std::istringstream iss(line); 

        std::string time;
        int eventId;
        std::string client;

        iss >> time;
        ReadPositiveInteger(iss, eventId);
        iss >> client;

        if (!IsValidClientName(client)) 
            throw std::invalid_argument("Invalid client name");
        
        Time timeCheck(time);

        if (timeCheck >= Time(closeTime) && !clubClosed) 
        {
            club.CloseClub();
            clubClosed = true;
        }
        
        switch (eventId)
        {
        case 1:
            club.ClientComes(client, time); 
            break;
        
        case 2:
            int tableId;
            ReadPositiveInteger(iss, tableId);
            club.ClientSitsDownAtTable(client, time, tableId); 
            break;

        case 3:
            club.ClientWaits(client, time);
            break;
        
        case 4:
            club.ClientLeaves(client, time);
            break;

        default:
            throw std::invalid_argument("Invalid Event ID");
        }
    }

    if (!clubClosed) 
        club.CloseClub();
}