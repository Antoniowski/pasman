//Written by Antonio "Antoniowski" Romano
#include "./TextHandler/texthandler.h"
#include "./PasswordHandler/passwordhandler.h"
#include "./Utility/utility.h"
#include <stdio.h>

#ifdef _WIN32
    #define CLEAR "cls"
#elif _WIN64
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

using namespace std;
struct status
{
    bool pending_save = false;
    bool exit = false;
    bool init = true;
    bool first_run = true;
};

const string PASS_FILE_NAME = "pass.txt";
const string CONFIG_FILE_NAME = "config.txt";
const string PATH_FILE_NAME = "path.txt";
string user{};
string pass{};
int key = 0;

void show_procedure(TextHandler& th, PasswordHandler& ph)
{
    system(CLEAR);
    th.print_message(message_id::WELCOME_MESSAGE);
    th.print_message(message_id::CHOOSE_MESSAGE);
    th.show_selection_menu();
    th.print_message(message_id::INSERT_CHOICE_MESSAGE);
    
    bool good_choice = false;
    string choice{};
    while (!good_choice)
    {
        
        cin >> choice;
        if(!is_number(choice))
        {
            th.print_message(message_id::NOT_A_NUMBER_MESSAGE);
            choice = "";
            continue;
        }
        switch (stoi(choice))
        {
            case 1:
                system(CLEAR);
                th.print_message(message_id::WELCOME_MESSAGE);
                ph.show_passwords();
                good_choice = true;
                break;
            case 2:
            {
                string c{};
                
                system(CLEAR);
                th.print_message(message_id::WELCOME_MESSAGE);
                ph.show_services();
                th.print_message(message_id::INSERT_SERVICE_MESSAGE);
                cin >> c;
                
                system(CLEAR);
                th.print_message(message_id::WELCOME_MESSAGE);
                ph.show_password(c);
                good_choice = true;
                break;
            }
            case 3:
                good_choice =true;
                break;
            default:
                th.print_message(message_id::INSERT_ERROR_MESSAGE);
                break;
        }
    }
}

void add_procedure(TextHandler& th, PasswordHandler& ph, bool& save_status)
{
    password_row new_row = make_tuple("", "", "");
    string value;
    th.print_message(message_id::INSERT_SERVICE_MESSAGE);
    cin >> value;
    get<0>(new_row) = value;
    th.print_message(message_id::INSERT_PASSWORD_MESSAGE);
    cin >> value;
    get<1>(new_row) = value;
    get<2>(new_row) = get_today_date();
    ph.add_new_password(new_row);
    save_status = true;

}

void edit_procedure(TextHandler& th, PasswordHandler& ph, bool& save_status)
{
    string service_to_edit{};
    th.print_message(message_id::INSERT_SERVICE_MESSAGE);
    cin >> service_to_edit;
    save_status = ph.edit_password(service_to_edit, get_today_date());
}

void delete_procedure(TextHandler& th, PasswordHandler& ph, bool& save_status)
{
    string service_to_delete{};
    th.print_message(message_id::INSERT_SERVICE_MESSAGE);
    cin >> service_to_delete;
    save_status = ph.delete_password(service_to_delete);
}

void save_procedure(TextHandler& th, PasswordHandler& ph, bool& save_status, Database* database)
{
    ph.save_locally(key);
    save_status = false;
}

bool auth_procedure(TextHandler& th)
{
    string inserted_pass{};
    th.print_message(message_id::INIT_03);
    cin >> inserted_pass;
    if(inserted_pass == pass)
        return true;
    
    return false;
}

void setting_procedure(TextHandler& th, PasswordHandler& ph, Database* database)
{
    system(CLEAR);
    th.print_message(message_id::WELCOME_MESSAGE);
    bool good_choose = false;
    th.setting_selection_menu();
    while (!good_choose)
    {
        th.print_message(message_id::CHOOSE_MESSAGE);
        string choose{};
        cin >> choose;

        if(!is_number(choose))
        {
            th.print_message(message_id::NOT_A_NUMBER_MESSAGE);
            continue;
        }

        switch (stoi(choose))
        {
        case 1:
            {
                string new_user = "";
                th.print_message(message_id::INIT_02);
                cin >> new_user;

                if(new_user == "")
                {
                    th.print_message(message_id::ERROR_VOID_MESSAGE);
                    break;
                }
                user = new_user;
                database->full_truncate("LOGIN");
                database->insert("LOGIN",
                                {"USERNAME", "PASSWORD"},
                                {simple_encryption(user, key),
                                 simple_encryption(pass, key)});
                good_choose = true;
            }
            break;
        case 2:
            {
                if(!auth_procedure(th))
                {
                    th.print_message(message_id::WRONG_PASS_ABORT_MESSAGE);
                    break;
                }

                string new_pass{};
                string new_pass_cp{};
                th.print_message(message_id::NEW_PASS_MESSAGE);
                cin >> new_pass;
                th.print_message(message_id::INIT_04);
                cin >> new_pass_cp;
                if(new_pass != new_pass_cp)
                {
                    th.print_message(message_id::PASSWORD_MISMATCH);
                    break;
                }

                pass = new_pass;
                database->full_truncate("LOGIN");
                database->insert("LOGIN",
                                {"USERNAME", "PASSWORD"},
                                {simple_encryption(user, key),
                                 simple_encryption(pass, key)});
                good_choose = true;
            }
            break;
        case 3:
            good_choose = true;
            break;
        default:
            th.print_message(message_id::INSERT_ERROR_MESSAGE);
            good_choose = false;
            break;
        }
    }    
}

void init_procedure(TextHandler& th, Database*& db)
{
    bool password_is_good = false;
    string username;
    string password;
    string password_cp;
    string enc_key;
    string path = "";
    while(!password_is_good)
    {
        th.print_message(message_id::INIT_01);
        th.print_message(message_id::INIT_02);
        cin >> username;
        user = username;
        th.print_message(message_id::INIT_03);
        cin >> password;
        th.print_message(message_id::INIT_04);
        cin >> password_cp;
        if(password != password_cp)
        {
            th.print_message(message_id::PASSWORD_MISMATCH);
            username = "";
            password = "";
            password_cp = "";
            continue;
        }
        pass = password;
        password_is_good = true;
        bool good_key = false;
        while(!good_key)
        {
            th.print_message(message_id::INIT_05);
            cin >> enc_key;
            if(!is_number(enc_key))
            {
                th.print_message(message_id::NOT_A_NUMBER_MESSAGE);
                enc_key = "";
                continue;
            }

            good_key = true;
            key = stoi(enc_key);
        }   
        th.print_message(message_id::INIT_06);
    }
    db->insert(
        "LOGIN", 
        {"USERNAME","PASSWORD"}, 
        {simple_encryption(username, key), simple_encryption(password, key)});
}



void login_procedure(TextHandler& th, Database* db)
{
    bool is_key_number = false;
    string k;
    while (!is_key_number)
    {
        th.print_message(message_id::KEY);
        cin >> k;

        if(!is_number(k))
        {
            th.print_message(message_id::NOT_A_NUMBER_MESSAGE);
            continue;
        }

        is_key_number = true;
        key = stoi(k);
    }
    
    user = db->get_value("USERNAME", "LOGIN", "");
    user = simple_decryption(user, key);
    pass = db->get_value("PASSWORD", "LOGIN", "");
    pass = simple_decryption(pass, key);

    int tries = 0;
    bool loggin_success = false;
    while(tries < 4 && loggin_success == false)
    {
        if(auth_procedure(th))
        {
            loggin_success = true;
            continue;
        }
        tries++;
        
        if(tries < 4)
            th.print_message(message_id::WRONG_PASSWORD_MESSAGE);
    }

    if(!loggin_success)
    {
        th.print_message(message_id::TOO_MANY_TRIES_MESSAGE);
        exit(0);
    }
}

//MAIN PROGRAM 

int main()
{
    Database* db = Database::getInstance();
    TextHandler txt_handler = TextHandler();
    status status;

    status.init = !file_exists("exfls");

    if(status.init == true)
    {
        db->first_init();
        init_procedure(txt_handler, db);
        status.init = false;
        fstream ex_file;
        ex_file.open("exfls", ios::out);
        ex_file.close();
    }else
    {
        login_procedure(txt_handler, db);
    }
    
    string scelta{};
    PasswordHandler pass_handler = PasswordHandler(db, key);
    /*
        System specific:
            "clear" - linux, unix
            "cls" - windows
    */
    system(CLEAR);
   
    while (status.exit == false)
    {
        system(CLEAR);

        txt_handler.print_message(message_id::WELCOME_MESSAGE);
        txt_handler.selection_menu(status.pending_save, user, status.first_run);
        
        if(status.first_run)
            status.first_run = false;
        
        txt_handler.print_message(message_id::INSERT_CHOICE_MESSAGE);
        cin >> scelta;

        if(!is_number(scelta))
        {
            txt_handler.print_message(message_id::INSERT_ERROR_MESSAGE);
            continue;
        }

        int scelta_num = stoi(scelta);

        switch (scelta_num)
        {
        case 1:
            show_procedure(txt_handler, pass_handler);
            break;
        case 2:
            add_procedure(txt_handler, pass_handler, status.pending_save);
            break;           
        case 3:
            system(CLEAR);
            txt_handler.print_message(message_id::WELCOME_MESSAGE);
            pass_handler.show_services();
            edit_procedure(txt_handler, pass_handler, status.pending_save);
            break;
        case 4:            
            system(CLEAR);
            txt_handler.print_message(message_id::WELCOME_MESSAGE);
            pass_handler.show_services();
            delete_procedure(txt_handler, pass_handler, status.pending_save);
            break;
        case 5:
            save_procedure(txt_handler, pass_handler, status.pending_save, db);
            break;
        case 6:
            setting_procedure(txt_handler, pass_handler, db);
            break;
        case 7:
            status.exit = true;
            break;
        default:
            break;
        }
    }
    
    system(CLEAR);
    txt_handler.print_message(message_id::EXIT_MESSAGE);
    return 0;
}