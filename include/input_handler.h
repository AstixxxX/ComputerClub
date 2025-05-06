#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

#include "time.h"
#include "club.h"

void ReadClubHeader(std::ifstream& file, int& numberTables, std::string& openTime, 
 std::string& closeTime, int& costPerHour, std::string& line);

void ReadEvents(std::ifstream& file, Club& club, const std::string& closeTime, std::string& line);