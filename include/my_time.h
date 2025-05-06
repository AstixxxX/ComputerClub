#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <regex>
#include <cmath>

class Time 
{   
public:
    Time();
    Time(int hours, int minutes);
    Time(const std::string& strTime);
    
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator>=(const Time& other) const;
    Time operator-(const Time& other) const;
    Time& operator+=(const Time& other);

    int GetHours() const;
    int GetMinutes() const;
    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& os, const Time& time);

private:
    int hours_;
    int minutes_;

    void time_alignment();
};