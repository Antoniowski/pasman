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
    ADD_PSW_MESSAGE_1 = 3,
    ADD_PSW_MESSAGE_2 = 4
};

class TextHandler
{
private:
    const string insert_error_text = "!!! Insert a valid numeric option !!!";
    const string file_not_found_text = "File not created or not found";
    const string add_psw_text_1 = "Insert service name: ";
    const string add_psw_text_2 = "Insert password: ";

    
public:
    TextHandler();
    ~TextHandler();

    void welcome_text(bool&);
    void print_message(int);
};

#endif