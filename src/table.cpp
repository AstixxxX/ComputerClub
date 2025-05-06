#include "table.h"

Table::Table(int costPerHour) : vacant_(true), income_(0), costPerHour_(costPerHour) {}

bool Table::AddClient(const std::string& client, const std::string& strTime) 
{
    if (IsVacant()) 
    {
        lastStartTime_ = Time(strTime);
        client_ = client;
        vacant_ = false;
        return true;
    }

    return false;
}

bool Table::DeleteClient(const std::string& strTime) 
{
    if (!IsVacant()) 
    {
        Time diffTime = (Time(strTime) - lastStartTime_);
        workTime_ += diffTime;
        income_ += costPerHour_ * (diffTime.GetHours() + 1);
        vacant_ = true;
        return true;
    }

    return false;
}

int Table::GetIncome() const
{
    return income_;
}

std::string Table::GetClient() const 
{
    return client_;
}

bool Table::IsVacant() const 
{
    return vacant_;
}

Time Table::GetWorkTime() const 
{
    return workTime_;
}