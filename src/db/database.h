#include <stdlib.h>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <iostream>

class Database
{
protected:

    const std::string LOGIN_CREATE_SCHEMA = "CREATE TABLE IF NOT EXISTS LOGIN ("
                                            "USERNAME TEXT PRIMARY KEY NOT NULL,"
                                            "PASSWORD TEXT NOT NULL);";

    const std::string PATH_CREATE_SCHEMA = "CREATE TABLE IF NOT EXISTS PATH ("
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
    void dropTables();
    void createTables();
public:
    void first_init();
    void init();
    bool insert(std::string, std::vector<std::string>,std::vector<std::string>);

    static Database* getInstance();

    //To delete
    Database(const Database&);
    void operator=(const Database&);
};