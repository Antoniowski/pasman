#include "./TextHandler/texthandler.h"
#include "./PasswordHandler/passwordhandler.h"
#include <stdio.h>


using namespace std;

const string resource_path = "./resources/";

bool is_number(const std::string& stringa)
{
    std::string::const_iterator it = stringa.begin();
    while(it != stringa.end() && std::isdigit(*it)) ++it;
    return it == stringa.end() && !stringa.empty();
}

void add_procedure(TextHandler& th, PasswordHandler& ph, bool& save_status)
{
    password_row new_row = make_tuple("", "", "");
    string value;
    th.print_message(message_id::ADD_PSW_MESSAGE_1);
    cin >> value;
    get<0>(new_row) = value;
    th.print_message(message_id::ADD_PSW_MESSAGE_2);
    cin >> value;
    get<1>(new_row) = value;

    time_t now = time(0);
    tm* time_struct = localtime(&now);
    string time_string ="" + to_string(time_struct->tm_mday) + "/" + to_string(1 + time_struct->tm_mon) +"/"+ to_string(1900 + time_struct->tm_year);
    get<2>(new_row) = time_string;
    ph.add_new_password(new_row);
    save_status = true;

}


int main()
{
    system("clear");
    TextHandler txt_handler = TextHandler();
    PasswordHandler pass_handler = PasswordHandler(resource_path+"pass.txt");
    string scelta{};
    bool pending_save = false;
    bool exit = false;
   
    while (exit == false)
    {
        txt_handler.welcome_text(pending_save);
        cout << "Insert a value to select what to do.\n";
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
        {
            add_procedure(txt_handler, pass_handler, pending_save);
            break;           
        }
        case 4:
            pass_handler.save_locally(resource_path+"pass.txt");
            pending_save = false;
            break;
        case 5:
            exit = true;
            break;
        default:
            break;
        }
    }

    
    
    return 0;
}