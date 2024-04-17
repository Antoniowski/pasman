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

std::string simple_encryption(std::string string_to_encrypt, int key)
{
    /**
     * Simple encryption function that uses a key to transform the string param into an ecnrypted
     * string.
     * 
     * Params:
     *  - string_to_encrypt (string): string that will be encrypted.
     *  - key (int): integer used to change the ascii value.
     * 
     * Return:
     *  string: the encrypted string
    */

    for(std::string::iterator iter = string_to_encrypt.begin(); iter != string_to_encrypt.end(); ++iter)
    {

        *iter += key;
    }

    return string_to_encrypt;
}

std::string simple_decryption(std::string string_to_decrypt, int key)
{
    /**
     * Simple decryption function that uses a key to transform the encrypt string to its original form.
     * 
     * Params:
     *  - string_to_decrypt (string): string that will be decrypted.
     *  - key (int): integer used to change the ascii value.
     * 
     * Return:
     *  string: the decrypted string
    */

    for(std::string::iterator iter = string_to_decrypt.begin(); iter != string_to_decrypt.end(); ++iter)
    {
        *iter -= key;
    }
    return string_to_decrypt;
}

bool file_exists(const std::string& file_path)
{
    /**
     * It checks the existence of the file specified by the inserted path.
     * 
     * Params:
     *  - file_path(string): the path to the file that need to be checked/
     * 
     * Returns:
     *  bool: result of the operation
    */

    if (FILE *file = fopen(file_path.c_str(), "r")) {
        fclose(file);
        return true;
    } 

    return false;  

}

void pause()
{
    /**
     * Simple altenativee fucntion to pause the program execustion without using
     * the system() method.
    */ 
   
    std::cin.ignore();
    std::cin.get();
}

bool endsWith(const std::string& fullString, const std::string& ending) 
{ 
    // Check if the ending string is longer than the full 
    // string 
    if (ending.size() > fullString.size()) 
        return false; 
  
    // Compare the ending of the full string with the target 
    // ending 
    return fullString.compare(fullString.size() - ending.size(), 
                              ending.size(), 
                              ending) == 0; 
} 