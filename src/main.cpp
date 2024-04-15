#include "./TextHandler/texthandler.h"
#include "./PasswordHandler/passwordhandler.h"
#include "./Utility/utility.h"
#include <stdio.h>


using namespace std;


struct status
{
    bool pending_save = false;
    bool exit = false;
    bool init = true;
    bool first_run = true;
};

const string resource_path = "./resources/";
string user{};
string pass{};
int key = 0;

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
    ph.edit_password(service_to_edit, get_today_date());
    save_status = true;
}

void delete_procedure(TextHandler& th, PasswordHandler& ph, bool& save_status)
{
    string service_to_delete{};
    th.print_message(message_id::INSERT_SERVICE_MESSAGE);
    cin >> service_to_delete;
    ph.delete_password(service_to_delete);
    save_status = true;
}

void save_procedure(TextHandler& th, PasswordHandler& ph, bool& save_status)
{
    ph.save_locally(resource_path+"pass.txt");
    save_status = false;
}

void init_procedure(TextHandler& th)
{
    bool password_is_good = false;
    string username;
    string password;
    string password_cp;
    string enc_key;
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

    fstream conf_file;
    conf_file.open(resource_path+"config.txt", ios::out);
    conf_file << simple_encryption("username="+username, key) << endl;
    conf_file << simple_encryption("password="+password, key) << endl;
    conf_file << simple_encryption("key="+enc_key, key) << endl;
    conf_file.close();
}

bool auth_procedure(TextHandler& th)
{
    string inserted_pass{};
    th.print_message(message_id::INSERT_PASSWORD_MESSAGE);
    cin >> inserted_pass;
    if(inserted_pass == pass)
        return true;
    
    return false;
}

bool login_procedure(TextHandler& th)
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
    
    fstream my_conf;
    my_conf.open(resource_path+"config.txt", ios::in);
    my_conf >> user;
    user = simple_decryption(user, key);
    user = user.substr(user.find("=")+1, user.length()-1);
    my_conf >> pass;
    pass = simple_decryption(pass, key);
    pass = pass.substr(pass.find("=")+1, pass.length()-1);
    my_conf.close();

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

int main()
{
    TextHandler txt_handler = TextHandler();
    PasswordHandler pass_handler = PasswordHandler(resource_path+"pass.txt");
    string scelta{};
    status status;

    status.init = !file_exists(resource_path+"config.txt");

    if(status.init == true)
    {
        init_procedure(txt_handler);
        status.init = false;
    }else
    {
        login_procedure(txt_handler);
    }
    
    /*
        System specific:
            "clear" - linux, unix
            "cls" - windows
    */
    system("clear");
   
    while (status.exit == false)
    {
        system("clear");

        txt_handler.print_message(message_id::WELCOME_MESSAGE);
        txt_handler.selection_menu(status.pending_save, user, status.first_run);
        
        if(status.first_run)
            status.first_run = false;
        
        cout << "Insert a value to select what to do." << endl;
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
            pass_handler.show_passwords();
            break;
        case 2:
            add_procedure(txt_handler, pass_handler, status.pending_save);
            break;           
        case 3:
            edit_procedure(txt_handler, pass_handler, status.pending_save);
            break;
        case 4:
            delete_procedure(txt_handler, pass_handler, status.pending_save);
            break;
        case 5:
            save_procedure(txt_handler, pass_handler, status.pending_save);
            break;
        case 6:
            status.exit = true;
            break;
        default:
            break;
        }
    }

    
    
    return 0;
}