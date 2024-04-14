#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

enum message_id: unsigned int
{
    WELCOME_MESSAGE = 0,
    INSERT_ERROR_MESSAGE = 1,
    FILE_NOT_FOUND_MESSAGE = 2,
    INSERT_SERVICE_MESSAGE = 3,
    INSERT_PASSWORD_MESSAGE = 4
};

class TextHandler
{
private:
    const string insert_error_text = "!!! Insert a valid numeric option !!!";
    const string file_not_found_text = "File not created or not found";
    const string insert_service_text = "Insert service name: ";
    const string insert_password_text = "Insert password: ";


    
public:
    TextHandler();
    ~TextHandler();

    void selection_menu(bool&);
    void print_message(int);
};

#endif