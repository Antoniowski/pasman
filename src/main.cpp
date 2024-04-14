#include "./TextHandler/texthandler.h"
#include "./PasswordHandler/passwordhandler.h"
#include "./Utility/utility.h"
#include <stdio.h>


using namespace std;

const string resource_path = "./resources/";

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

void init_procedure()
{

}

void auth_procedure()
{

}


struct status
{
    bool pending_save = false;
    bool exit = false;
    bool init = false;
    bool first_run = true;
};

int main()
{
    TextHandler txt_handler = TextHandler();
    PasswordHandler pass_handler = PasswordHandler(resource_path+"pass.txt");
    string scelta{};
    status status;

    if(status.init == true)
    {

    }

    system("clear");
    txt_handler.print_message(message_id::WELCOME_MESSAGE);
   
    while (status.exit == false)
    {
        if(!status.first_run)
        {
            system("clear");
        }

        status.first_run = false;
        txt_handler.selection_menu(status.pending_save);
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