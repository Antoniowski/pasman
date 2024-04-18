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
    INIT_06 = 9,
    PASSWORD_MISMATCH = 10,
    WRONG_PASSWORD_MESSAGE = 11,
    TOO_MANY_TRIES_MESSAGE = 12,
    INIT_05 = 13,
    NOT_A_NUMBER_MESSAGE = 14,
    KEY = 15,
    EXIT_MESSAGE = 16,
    CONTINUE_MESSAGE = 17,
    CHOOSE_MESSAGE = 18,
    INSERT_PATH_MESSAGE = 19,
    ERROR_VOID_MESSAGE = 20,
    WRONG_PASS_ABORT_MESSAGE = 21,
    NEW_PATH_MESSAGE = 22,
    NEW_PASS_MESSAGE = 23,
    OLD_PASS_MESSAGE = 24,
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
    const string init_text_05 = "Insert a number. It will be used as encryption key (DON'T LOSE IT): ";
    const string init_text_06 = "Configuration completed. Welcome, ";
    const string password_mismatch_text = "Passwords doesn't match. Try again.";
    const string wrong_password_text = "Wrong password. Try again";
    const string too_many_tries_text = "Too many tries. Abort loggin";
    const string not_number_text = "Not a number. Retry";
    const string key_text = "Key: ";
    const string exit_text = "Goodbye!";
    const string continue_text = "Press Enter to continue... ";
    const string choose_option_text = "Please choose an option: ";
    const string insert_path_text = "Please enter a local path where save your data: ";
    const string error_void_insert = "Invalid entry. It cannot be empty";
    const string wrong_pass_abort_text = "Wrong password. Abort Operation";
    const string new_path_text = "Insert new path: ";
    const string new_pass_text = "Insert new password: ";
    const string old_pass_text = "Insert old password: ";
    
    
public:
    TextHandler();
    ~TextHandler();

    void selection_menu(bool&, string, bool);
    void show_selection_menu();
    void setting_selection_menu();
    void print_message(message_id);
};

#endif