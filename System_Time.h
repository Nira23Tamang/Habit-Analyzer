#ifndef SYSTEM_TIME
#define SYSTEM_TIME

#include <ctime>
#include <iomanip>
#include <sstream>

class System_Time
{
 public:
    System_Time(){ }

    string& current_time(string& curr_time);
};

string& System_Time:: current_time(string& curr_time)
{
        // Get the current time
        time_t currentTime = time(nullptr);

        // Convert to a tm structure
        tm* localTime = localtime(&currentTime);

        // Create a string stream to format the time
        ostringstream oss;
        oss << put_time(localTime, "%m/%d/%Y");

        // Store the formatted time in a string
        curr_time = oss.str();
        return curr_time;
}
#endif // end of declaration