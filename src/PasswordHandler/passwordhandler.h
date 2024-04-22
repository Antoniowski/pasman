#ifndef PASSWORD_HANDLER_H
#define PASSWORD_HANDLER_H

#include "../Utility/utility.h"
#include <iostream>
#include <string>
#include <fstream>
#include <tuple>
#include <vector>
#include <ctime>
#include <iomanip>
#include "../db/database.h"

typedef std::tuple<std::string,std::string, std::string> password_row;


/*
    This class is responsible to handle anything related to the passwords. It also handle the local file where
    passwords are saved.


*/



class PasswordHandler
{
private:
    std::string local_file_path;;
    std::vector<password_row> passwords;
    
public:
    PasswordHandler(std::string, int);
    PasswordHandler(Database*, int);
    ~PasswordHandler();
    void show_password(std::string);
    void show_passwords();
    void show_services();
    void add_new_password(password_row);
    void add_new_password(std::string, std::string);
    bool delete_password(std::string);
    bool edit_password(std::string, std::string);
    void save_locally(std::string, int);
    void save_locally(Database*, int);
};


#endif