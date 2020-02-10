#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    string formattedtime;
    long hour = seconds / 3600;
    long remainder = seconds % 3600;
    long minute = remainder / 60;
    long second = remainder % 60;
    std::string hour_str, minute_str, second_str;
    if (second < 10) {
        second_str = ":0" + std::to_string(second);
    }
    else {
        second_str = ":" + std::to_string(second);
    }
    if (minute < 10) {
        minute_str = ":0" + std::to_string(minute);
    }
    else {
        minute_str = ":" + std::to_string(minute);
    }
    if (hour < 10) {
        hour_str = "0" + std::to_string(hour);
    }
    else {
        hour_str = std::to_string(hour);
    }
    formattedtime = hour_str + minute_str + second_str;
    return formattedtime;
}