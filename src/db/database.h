#include <stdlib.h>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <iostream>
#include <tuple>


class Database
{
protected:

    const std::string LOGIN_CREATE_SCHEMA =     "CREATE TABLE IF NOT EXISTS LOGIN ("
                                                "USERNAME TEXT PRIMARY KEY NOT NULL,"
                                                "PASSWORD TEXT NOT NULL);";

    const std::string PATH_CREATE_SCHEMA =      "CREATE TABLE IF NOT EXISTS PATH ("
                                                "URI TEXT PRIMARY KEY NOT NULL);";

    const std::string PASSWORDS_CREATE_SCHEMA = "CREATE TABLE IF NOT EXISTS PASSWORDS ("
                                                "SERVICE TEXT PRIMARY KEY NOT NULL,"
                                                "PASSWORD TEXT NOT NULL,"
                                                "LAST_UPDATE TEXT NOT NULL);";


    //Single instance of database manager
    static Database* _instance;
    sqlite3* sqlite_db;

    Database();
    ~Database();
    bool connect();
    bool disconnect();
    void drop_table();
    void create_tables();
public:
    void full_truncate(std::string);
    void first_init();
    void init();
    bool insert(std::string, std::vector<std::string>,std::vector<std::string>);
    std::string get_values(std::string, std::string);
    std::string get_value(std::string, std::string, std::string);
    std::vector<std::tuple<std::string,std::string,std::string>> get_password_rows(std::string);


    static Database* getInstance();

    //To delete
    Database(const Database&);
    void operator=(const Database&);
};