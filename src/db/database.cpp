/*\
    Class used to abstract the database and its logics.
    Every operation to do on the database will be filtered by the database class.
*/
#include "database.h"

Database* Database::_instance = nullptr;

Database::Database()
{
}

/**
 * Cannot create a database object. A new database class can be only be created
 * by using the getInstance method.
 * 
 */

Database::Database(const Database& database) = delete;

Database::~Database()
{

}


Database* Database::getInstance()
{
    if(_instance == nullptr)
        _instance = new Database();

    return _instance;
}

bool Database::connect()
{
    int rc;
    rc = sqlite3_open("./src/db/db_resources/localdata.db", &sqlite_db);
    if(rc)
    {
        return true;
    }

    return false;
}

bool Database::disconnect()
{
    if(sqlite3_close(sqlite_db))
        return true;

    return false;
    
}

void Database::first_init()
{
    connect();    
    sqlite3_exec(sqlite_db, LOGIN_CREATE_SCHEMA.c_str(), NULL, NULL, NULL);
    sqlite3_exec(sqlite_db, PATH_CREATE_SCHEMA.c_str(), NULL, NULL, NULL);
    sqlite3_exec(sqlite_db, PASSWORDS_CREATE_SCHEMA.c_str(), NULL, NULL, NULL);
    disconnect();
}


//OPERATORS

/**
 * Same thing as the cloning constructor. Cannot assign a database.
 * The creation is made only with getInstance method.
*/
void Database::operator=(const Database&) = delete;