#include "my_time.h"

Time::Time() : hours_(0), minutes_(0) {}

Time::Time(int hours, int minutes) : hours_(hours), minutes_(minutes)
{
    time_alignment();
}

Time::Time(const std::string& strTime) 
{
    std::regex time_format("^([01][0-9]|2[0-3]):([0-5][0-9])$");

    if (!std::regex_match(strTime, time_format))
        throw std::invalid_argument("Invalid time format");
    else
    {
        hours_ = std::stoi(strTime.substr(0, 2));
        minutes_ = std::stoi(strTime.substr(3, 2));
    }
}

int Time::GetHours() const 
{
    return hours_;
}

int Time::GetMinutes() const 
{
    return minutes_;
}

std::string Time::toString() const 
{
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours_ << ":" << std::setw(2) << std::setfill('0') << minutes_;
    return oss.str();
}

bool Time::operator<(const Time& other) const 
{
    if (hours_ < other.hours_) 
        return true;
    else if (hours_ == other.hours_) 
        return minutes_ < other.minutes_;
    else 
        return false;
}

bool Time::operator>(const Time& other) const 
{
    if (hours_ > other.hours_) 
        return true;
    else if (hours_ == other.hours_) 
        return minutes_ > other.minutes_;
    else 
        return false;
}

bool Time::operator>=(const Time& other) const 
{
    if (hours_ > other.hours_) 
        return true;
    else if (hours_ == other.hours_) 
        return minutes_ >= other.minutes_;
    else 
        return false;
}

Time& Time::operator+=(const Time& other) 
{
    hours_ += other.hours_;
    minutes_ += other.minutes_;
    time_alignment();
    return *this;
}

Time Time::operator-(const Time& other) const 
{
    int totalMinutes1 = hours_ * 60 + minutes_;
    int totalMinutes2 = other.hours_ * 60 + other.minutes_;
    int diffMinutes = totalMinutes1 - totalMinutes2;

    if (diffMinutes < 0) 
        diffMinutes = 0;
    
    return Time(diffMinutes / 60, diffMinutes % 60);
}

std::ostream& operator<<(std::ostream& os, const Time& time) 
{
    os << std::setw(2) << std::setfill('0') << time.hours_ << ":" << std::setw(2) << std::setfill('0') << time.minutes_;
    return os;
}

void Time::time_alignment() 
{
    if (minutes_ >= 60) 
    {
        hours_ += minutes_ / 60;
        minutes_ %= 60;
    } 
    else if (minutes_ < 0) 
    {
        hours_ -= (std::abs(minutes_) / 60) + 1;
        minutes_ = 60 - (std::abs(minutes_) % 60);
    }

    if (hours_ < 0) 
    {
        hours_ = 0;
        minutes_ = 0;
    }
}