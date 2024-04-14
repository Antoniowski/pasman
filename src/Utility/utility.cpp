#include "./utility.h"

bool is_number(const std::string& stringa)
{
    /**
     * Check if a string is a number or not.
     * 
     * 
     * Return: bool, result of the operation
    */
    std::string::const_iterator it = stringa.begin();
    while(it != stringa.end() && std::isdigit(*it)) ++it;
    return it == stringa.end() && !stringa.empty();
}

std::string get_today_date()
{
    /**
     * 
     * Returns a string of today date in the format DD/MM/YYYY.
     * 
     * Return: string, the string containing the date.
     * 
    */
    time_t now = time(0);
    tm* time_struct = localtime(&now);
    std::string time_string ="" + std::to_string(time_struct->tm_mday) + "/" + std::to_string(1 + time_struct->tm_mon) +"/"+ std::to_string(1900 + time_struct->tm_year);
    return time_string;

}