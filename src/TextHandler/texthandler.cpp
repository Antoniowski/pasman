#include "texthandler.h"

TextHandler::TextHandler(){};
TextHandler::~TextHandler(){};

void TextHandler::selection_menu(bool &pending_save, string username, bool first_run)
{
    string save_warning = "";
    size_t max_dim = 25;

    if(pending_save)
        save_warning = "(!)";
        
    //if (first_run)
    cout << left << setw(max_dim) << "Welcome to your password manager, " << username << "!" <<  endl;
    
    cout 
    << left << setw(max_dim) << "What do you need?" << endl << endl << setfill('.')
    << left << setw(max_dim) << "1." 
    << right << setw(max_dim) << "Show passwords" << endl
    << left << setw(max_dim) << "2."
    << right << setw(max_dim) << "Add password" << endl
    << left << setw(max_dim) << "3."
    << right << setw(max_dim) << "Edit password" << endl
    << left << setw(max_dim) << "4."
    << right << setw(max_dim) << "Delete password" << endl
    << left << setw(max_dim) << "5."
    << right << setw(max_dim) << "Save locally" << save_warning << endl
    << left << setw(max_dim) << "6."
    << right << setw(max_dim) << "Settings" << endl
    << left << setw(max_dim) << "7." 
    << right << setw(max_dim) << "Exit" << endl << endl << setfill('\0');

}

void TextHandler::show_selection_menu()
{
    size_t max_dim = 25;

    cout << left << setw(max_dim) << "What do you need?" << endl << endl << setfill('.')
    << left << setw(max_dim) << "1." 
    << right << setw(max_dim) << "All" << endl
    << left << setw(max_dim) << "2."
    << right << setw(max_dim) << "Select service" << endl << setfill('\0');
}

void TextHandler::setting_selection_menu()
{
    size_t max_dim = 25;

    cout << setfill('.')
    << left << setw(max_dim) << "1." 
    << right << setw(max_dim) << "Change username" << endl
    << left << setw(max_dim) << "2." 
    << right << setw(max_dim) << "Change login password" << endl
    << left << setw(max_dim) << "3."
    << right << setw(max_dim) << "Change save path" << endl 
    << left << setw(max_dim) << "4."
    << right << setw(max_dim) << "Go back" << endl << setfill('\0');
    
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
        cout << this->init_text_05;
        break;
    case INIT_06:
        cout << this->init_text_06 << endl;
        break;
    case PASSWORD_MISMATCH:
        cout << this->password_mismatch_text << endl;
        break;
    case WRONG_PASSWORD_MESSAGE:
        cout << this->wrong_password_text << endl;
        break;
    case TOO_MANY_TRIES_MESSAGE:
        cout << this->too_many_tries_text << endl;
        break;
    case NOT_A_NUMBER_MESSAGE:
        cout << this->not_number_text << endl;
        break;
    case KEY:
        cout << this->key_text;
        break;
    case EXIT_MESSAGE:
        cout << this->exit_text << endl;
        break;
    case CONTINUE_MESSAGE:
        cout << this->continue_text;
        break;
    case CHOOSE_MESSAGE:
        cout << this->choose_option_text << endl;
        break;
    case INSERT_PATH_MESSAGE:
        cout << this->insert_path_text;
        break;
    default:
        break;
    }
}




