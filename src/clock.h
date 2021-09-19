#ifndef _CLOCK_
#define _CLOCK_

#include <map>
#include <string>
#include <ctime>

class Clock
{
    public:
        std::map<char, std::string> getDateAsStrings();
        tm* getTimeStruct();
        std::string getTimeString();
        std::string getDateString();
        // TODO: int getWeekInYear();
        void updateTime();
    private:
        tm* time_struct = getTimeStruct();
};

#endif