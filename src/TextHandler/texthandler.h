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
    INSERT_PASSWORD_MESSAGE = 4,
    INIT_01 = 5,
    INIT_02 = 6,
    INIT_03 = 7,
    INIT_04 = 8,
    INIT_05 = 9,
    PASSWORD_MISMATCH = 10
};

class TextHandler
{
private:
    const string insert_error_text = "!!! Insert a valid numeric option !!!";
    const string file_not_found_text = "File not created or not found";
    const string insert_service_text = "Insert service name: ";
    const string insert_password_text = "Insert password: ";
    const string init_text_01 = "Welcome new user. Let's configure your password manager.";
    const string init_text_02 = "Insert your username: ";
    const string init_text_03 = "Insert the password for authentication: ";
    const string init_text_04 = "Confirm the password: ";
    const string init_text_05 = "Configuration completed. Welcome, ";
    const string password_mismatch_text = "Passwords doesn't match. Try again.";


    
public:
    TextHandler();
    ~TextHandler();

    void selection_menu(bool&, string, bool);
    void print_message(message_id);
};

#endif