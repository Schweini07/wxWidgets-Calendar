#include "clock.h"

#include <ctime>
#include <map>
#include <string>

std::map<char, std::string> Clock::getDateAsStrings()
{
    time_t rawtime = time(&rawtime);
    tm *time_struct = localtime(&rawtime);

    int weekday_as_int = time_struct->tm_wday;
    std::string weekday;

    switch (weekday_as_int)
    {
        case 1:
            weekday = "Monday";
            break;
        case 2:
            weekday = "Tuesday";
            break;
        case 3:
            weekday = "Wednesday";
            break;
        case 4:
            weekday = "Thursday";
            break;
        case 5:
            weekday = "Friday";
            break;
        case 6:
            weekday = "Saturday";
            break;
        case 7:
            weekday = "Sunday";
            break;
        
        default:
            break;
    }

    int month_as_int = time_struct->tm_mon+1;
    std::string month;

    switch (month_as_int)
    {
        case 1:
            month = "January";
            break;
        case 2:
            month = "February";
            break;
        case 3:
            month = "March";
            break;
        case 4:
            month = "April";
            break;
        case 5:
            month = "May";
            break;
        case 6:
            month = "June";
            break;
        case 7:
            month = "July";
            break;
        case 8:
            month = "August";
            break;
        case 9:
            month = "September";
            break;
        case 10:
            month = "October";
            break;
        case 11:
            month = "November";
            break;
        case 12:
            month = "December";
            break;

    
        default:
            break;
    }

    std::map<char, std::string> date {{'d', weekday}, {'m', month}, {'y', std::to_string(time_struct->tm_year+1900)}};

    return date;
}

tm* Clock::getTimeStruct()
{
    time_t rawtime = time(&rawtime);
    tm *time_struct = localtime(&rawtime);

    return time_struct;
}

std::string Clock::getTimeString()
{
    std::string str;

    if (time_struct->tm_hour < 10) str += "0";
    str += std::to_string(time_struct->tm_hour) + ":";
    if (time_struct->tm_min < 10) str += "0";
    str += std::to_string(time_struct->tm_min) + ":";
    if (time_struct->tm_sec < 10) str += "0";
    str += std::to_string(time_struct->tm_sec);

    return str;
}

std::string Clock::getDateString()
{
    return std::to_string(time_struct->tm_mday) + "." + std::to_string(time_struct->tm_mon+1) + "." + std::to_string(time_struct->tm_year+1900);
}

void Clock::updateTime()
{
    time_struct = getTimeStruct();
}