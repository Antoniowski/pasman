#include "passwordhandler.h"

PasswordHandler::PasswordHandler(std::string path)
{
    this->local_file_path = path;

    std::fstream pass_wordfile;
    pass_wordfile.open(this->local_file_path, std::ios::in | std::ios::out);

    if(!pass_wordfile)
    {
        std::cout << "File not created or not exists" << std::endl;
        return;
    }

    if(!pass_wordfile.is_open())
        return;

    
    std::string single_row = "";
    std::vector<std::string> single_pass_element;
    unsigned int index = 0;
    while(pass_wordfile >> single_row)
    {
        if(single_row == "---"){
            password_row row;
            row = std::make_tuple(single_pass_element.at(0), single_pass_element.at(1), single_pass_element.at(2));
            this->passwords.push_back(row);
            single_pass_element.clear();
            single_row.clear();
            index++;
            continue;
        }
        single_pass_element.push_back(single_row);
        single_row.clear();
    }

    pass_wordfile.close();
    

};

PasswordHandler::~PasswordHandler(){};

void PasswordHandler::show_password(std::string service_name)
{
    /**
     *   Function used to show a single password.
     *   The passord is search by name and if it's found the method will print a row with: name of service, password
     *   and creation date.
     * 
     *   Params:
     *      service_name: string = string containing the service name of the serached password.
    */
    for(auto pass_row: this->passwords)
    {
        size_t max_cell_size = 32;

        std::cout << std::setw(max_cell_size) << std::left << "SERVICE"
                  << std::setw(max_cell_size) << std::left << "PASSWORD"
                  << std::setw(max_cell_size) << std::left << "CREATION DATE" << std::endl;

        if(std::get<0>(pass_row) == service_name)
        {
            std::cout << std::setw(max_cell_size) << std::left << std::get<0>(pass_row)
                      << std::setw(max_cell_size) << std::left << std::get<1>(pass_row)
                      << std::setw(max_cell_size) << std::left << std::get<2>(pass_row) << std::endl;
            break;
        }
    }
};


void PasswordHandler::show_passwords()
{
    /*
    *  Function used to show all the saved passwords.
    */

    size_t max_cell_size = 32;

    std::cout << std::setw(max_cell_size) << std::left << "SERVICE"
              << std::setw(max_cell_size) << std::left << "PASSWORD"
              << std::setw(max_cell_size) << std::left << "CREATION DATE" << std::endl;
    for(auto pass_row: this->passwords)
    {
        std::cout << std::setw(max_cell_size) << std::left << std::get<0>(pass_row)
                  << std::setw(max_cell_size) << std::left << std::get<1>(pass_row)
                  << std::setw(max_cell_size) << std::left << std::get<2>(pass_row) << std::endl;
    }

    //PAUSE
    std::cin.ignore();
    std::cin.get();

};

void PasswordHandler::add_new_password(password_row new_password_row)
{
    /**
     * 
     * Function that adds a new password to the password array.
     * 
     * Params:
     *  new_password_row: password_row = a tuple containing all the info that need to be added (service name, password, creation date).
     * 
    */

   this->passwords.push_back(new_password_row);
};

void PasswordHandler::add_new_password(std::string service_name, std::string password)
{
    /**
     * 
     * Function that adds a new password to the password array.
     * 
     * Params:
     *  service_name: string = string rappresenting the name of service to which the password is related.
     *  password: string = string of the password.
    */

   time_t now = time(0);
   char* time_string = ctime(&now);
   password_row new_pass = std::make_tuple(service_name, password,time_string);
   this->passwords.push_back(new_pass);
};

void PasswordHandler::save_locally(std::string path)
{
    std::fstream myFile;
    myFile.open(path, std::ios::out);

    if(!myFile)
    {
        std::cout << "File not created or not found";
        return;
    }

    if(!myFile.is_open())
        return;

    for(password_row rows: this->passwords)
    {
        myFile << std::get<0>(rows) << std::endl;
        myFile << std::get<1>(rows) << std::endl;
        myFile << std::get<2>(rows) << std::endl;
        myFile << "---" << std::endl;
    }

    myFile.close();
}