#include "texthandler.h"

TextHandler::TextHandler(){};
TextHandler::~TextHandler(){};

void TextHandler::selection_menu(bool &pending_save, string username, bool first_run)
{
    string save_warning = "";
    size_t max_dim = 25;

    if(pending_save)
        save_warning = "(!)";
        
    if (first_run)
        cout << left << setw(max_dim) << "Welcome to your password Manager, " << username <<  endl;

    cout 
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

void TextHandler::print_message(message_id id)
{
    switch (id)
    {
    case WELCOME_MESSAGE:
        cout << R"(
      ___         ___           ___           ___           ___           ___     
     /\  \       /\  \         /\__\         /\  \         /\  \         /\  \    
    /::\  \     /::\  \       /:/ _/_       |::\  \       /::\  \        \:\  \   
   /:/\:\__\   /:/\:\  \     /:/ /\  \      |:|:\  \     /:/\:\  \        \:\  \  
  /:/ /:/  /  /:/ /::\  \   /:/ /::\  \   __|:|\:\  \   /:/ /::\  \   _____\:\  \ 
 /:/_/:/  /  /:/_/:/\:\__\ /:/_/:/\:\__\ /::::|_\:\__\ /:/_/:/\:\__\ /::::::::\__\
 \:\/:/  /   \:\/:/  \/__/ \:\/:/ /:/  / \:\~~\  \/__/ \:\/:/  \/__/ \:\~~\~~\/__/
  \::/__/     \::/__/       \::/ /:/  /   \:\  \        \::/__/       \:\  \      
   \:\  \      \:\  \        \/_/:/  /     \:\  \        \:\  \        \:\  \     
    \:\__\      \:\__\         /:/  /       \:\__\        \:\__\        \:\__\    
     \/__/       \/__/         \/__/         \/__/         \/__/         \/__/                       
    )" << endl;
        break;
    case INSERT_ERROR_MESSAGE:
        cout << this->insert_error_text << endl;
        break;
    case FILE_NOT_FOUND_MESSAGE:
        cout << this->file_not_found_text << endl;
        break;
    case INSERT_SERVICE_MESSAGE:
        cout << this->insert_service_text << endl;
        break;
    case INSERT_PASSWORD_MESSAGE:
        cout << this->insert_password_text << endl;
        break;
    case INIT_01:
        cout << this->init_text_01 << endl;
        break;
    case INIT_02:
        cout << this->init_text_02;
        break;
    case INIT_03:
        cout << this->init_text_03;
        break;
    case INIT_04:
        cout << this->init_text_04;
        break;
    case INIT_05:
        cout << this->init_text_05 << endl;
        break;
    case PASSWORD_MISMATCH:
        cout << this->password_mismatch_text << endl;
    default:
        break;
    }
}




