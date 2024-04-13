#ifndef PASSWORD_HANDLER_H
#define PASSWORD_HANDLER_H
#include <iostream>
#include <string>
#include <fstream>
#include <tuple>
#include <vector>
#include <ctime>
#include <iomanip>

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
    PasswordHandler(std::string);
    ~PasswordHandler();
    void show_password(std::string);
    void show_passwords();
    void add_new_password(password_row);
    void add_new_password(std::string, std::string);
    void delete_password(std::string);
    void edit_password(std::string);
    void save_locally(std::string);
};


#endif