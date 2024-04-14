#include "texthandler.h"

TextHandler::TextHandler(){};
TextHandler::~TextHandler(){};

void TextHandler::selection_menu(bool &pending_save)
{
    string save_warning = "";
    if(pending_save)
        save_warning = "(!)";
    size_t max_dim = 25;
    cout << left << setw(max_dim) << "Welcome to your Password Manager" << endl
    << left << setw(max_dim) << "What do you need?" << endl << endl << setfill('.')
    << left << setw(max_dim) << "1." 
    << right << setw(max_dim) << "Show passwords" << endl
    << left << setw(max_dim) << "2."
    << right << setw(max_dim) << "Add password" << endl
    << left << setw(max_dim) << "3."
    << right << setw(max_dim) << "Edit passwords" << endl
    << left << setw(max_dim) << "4."
    << right << setw(max_dim) << "Delete passwords" << endl
    << left << setw(max_dim) << "5."
    << right << setw(max_dim) << "Save locally" << save_warning << endl
    << left << setw(max_dim) << "6." 
    << right << setw(max_dim) << "Exit" << endl << endl << setfill(' ');

}

void TextHandler::print_message(int id)
{
    switch (id)
    {
    case 0:
        break;
    case 1:
        cout << this->insert_error_text << endl;
        break;
    case 2:
        cout << this->file_not_found_text << endl;
        break;
    case 3:
        cout << this->insert_service_text << endl;
        break;
    case 4:
        cout << this->insert_password_text << endl;
        break;
    default:
        break;
    }
}




