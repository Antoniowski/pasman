#include "passwordhandler.h"

PasswordHandler::PasswordHandler(std::string path, int key)
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
        std::string decrypted_row = simple_decryption(single_row, key);
        if(decrypted_row == "---"){
            password_row row;
            row = std::make_tuple(single_pass_element.at(0), single_pass_element.at(1), single_pass_element.at(2));
            this->passwords.push_back(row);
            single_pass_element.clear();
            single_row.clear();
            decrypted_row.clear();
            index++;
            continue;
        }
        single_pass_element.push_back(decrypted_row);
        single_row.clear();
        decrypted_row.clear();
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
    size_t max_cell_size = 32;

    std::cout << std::setw(max_cell_size) << std::setfill(' ') << std::left << "SERVICE"
                << std::setw(max_cell_size) << std::left << "PASSWORD"
                << std::setw(max_cell_size) << std::left << "LAST UPDATE" << std::endl;
    for(auto pass_row: this->passwords)
    {

        if(std::get<0>(pass_row) == service_name)
        {
            std::cout << std::setw(max_cell_size) << std::left << std::get<0>(pass_row)
                      << std::setw(max_cell_size) << std::left << std::get<1>(pass_row)
                      << std::setw(max_cell_size) << std::left << std::get<2>(pass_row) << std::endl << std::setfill('\0');
            break;
        }
    }

        //PAUSE
    std::cout << std::endl << "Press Enter to continue... " << std::setfill('\0');
    std::cin.ignore();
    std::cin.get();
};


void PasswordHandler::show_passwords()
{
    /*
    *  Function used to show all the saved passwords.
    */

    size_t max_cell_size = 32;

    std::cout << std::setw(max_cell_size) << std::setfill(' ') << std::left << "SERVICE" 
              << std::setw(max_cell_size) << std::left << "PASSWORD"
              << std::setw(max_cell_size) << std::left << "LAST UPDATE" << std::endl;
    for(auto pass_row: this->passwords)
    {
        std::cout << std::setw(max_cell_size) << std::left << std::get<0>(pass_row)
                  << std::setw(max_cell_size) << std::left << std::get<1>(pass_row)
                  << std::setw(max_cell_size) << std::left << std::get<2>(pass_row) << std::endl;
    }

    //PAUSE
    std::cout << std::endl << "Press Enter to continue... " << std::setfill('\0');
    std::cin.ignore();
    std::cin.get();

};

void PasswordHandler::show_services()
{
    size_t max_cell_size = 32;

    std::cout << std::setw(max_cell_size) << std::left << "SERVICES: " << std::endl;
    
    for(password_row pass_row: this->passwords)
    {
        std::cout << std::setw(max_cell_size) << std::left  << "- " << std::get<0>(pass_row) << std::endl;
    }

}

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

void PasswordHandler::save_locally(std::string path, int key)
{
    /**
     * This fuction is used to save all the changes made on the password array in the computer memory.
     * Doing so everytime the program is open all the passwords that are saved locally can be retrieved.
    */

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
        myFile << simple_encryption(std::get<0>(rows), key) << std::endl;
        myFile << simple_encryption(std::get<1>(rows), key) << std::endl;
        myFile << simple_encryption(std::get<2>(rows), key) << std::endl;
        myFile << simple_encryption("---", key) << std::endl;
    }

    myFile.close();
}

bool PasswordHandler::delete_password(std::string service_to_delete)
{
    /**
     * Function that is used to delete a password from the passwords vector.
     * Remember to save the changes to apply the operation.
    */
   
    for(std::vector<password_row>::iterator i = this->passwords.begin(); i != this->passwords.end(); ++i)
    {
        if(std::get<0>(*i) == service_to_delete)
        {
            this->passwords.erase(i);
            std:: cout << "Password deleted." << std::endl;
            return true;
        }

    };
    
    std::cout << "No service with such name" << std::endl;
    return false;
}


bool PasswordHandler::edit_password(std::string service_to_delete, std::string edit_time)
{
    /**
     * Function that is used to edit a password from the passwords vector.
     * Remember to save the changes to apply the operation.
    */
    for(std::vector<password_row>::iterator i = this->passwords.begin(); i != this->passwords.end(); ++i)
    {
        if(std::get<0>(*i) == service_to_delete)
        {
            bool pass_is_correct = false;
            while(!pass_is_correct)
            {
                std::string new_password{};
                std::string new_password_copy{}
                ;
                std::cout << "Enter the new password for " << std::get<0>(*i) << std::endl;
                std::cin >> new_password;
                std::cout << "Enter the new password again." << std::endl;
                std::cin >> new_password_copy;

                if(new_password != new_password_copy)
                {
                    std::cout << "Passwords doen't match. Try again." << std::endl;
                    new_password = "";
                    new_password_copy = "";
                    continue;
                }

                pass_is_correct = true;
                std::get<1>(*i) = new_password;
                std::get<2>(*i) = edit_time;
                std:: cout << "Password changed." << std::endl;
                return true;
            }
        }
    };
    std::cout << "No service with such name" << std::endl;
    return false;
}