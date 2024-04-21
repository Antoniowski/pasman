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
    //Connect to the local database
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
    //Disconnect from the database

    if(sqlite3_close(sqlite_db))
        return true;

    return false;
    
}

void Database::dropTables()
{
    //Delete all tables in database.

    connect();
    std::string query_basis = "DROP TABLE IF EXISTS ";
    std::vector<std::string> tables = {"LOGIN, PASSWORDS, PATH"};
    for(std::string t: tables)
    {
        sqlite3_exec(sqlite_db, (query_basis+t).c_str(), NULL, NULL, NULL);
    }
    disconnect();

}

void Database::createTables()
{
    connect();    
    sqlite3_exec(sqlite_db, LOGIN_CREATE_SCHEMA.c_str(), NULL, NULL, NULL);
    sqlite3_exec(sqlite_db, PATH_CREATE_SCHEMA.c_str(), NULL, NULL, NULL);
    sqlite3_exec(sqlite_db, PASSWORDS_CREATE_SCHEMA.c_str(), NULL, NULL, NULL);
    disconnect();
}

void Database::first_init()
{
    dropTables();
    createTables();
}

void Database::init()
{
    connect();
    
    disconnect();
}

bool Database::insert(std::string table, std::vector<std::string> colums, std::vector<std::string> values)
{
    if(colums.size() > values.size())
        return false;
    
    connect();
    
    std::string query_basis_1 = "INSERT INTO ";
    std::string query_basis_2 = ") VALUES(";
    std::string query_basis_3 = ");";
    std::string colums_string = "";
    std::string values_string = "";
    
    for(int i=0; i<colums.size(); i++)
    {
        colums_string += colums.at(i);
        values_string += "'"+values.at(i)+"'";
        if(i != colums.size()-1)
        {            
            colums_string += ", ";
            values_string += ", ";
            continue;
        }
    }
    std::string query = query_basis_1+table+"("+colums_string+query_basis_2+values_string+query_basis_3;
    std::cout << query << std::endl;
    sqlite3_exec(sqlite_db, query.c_str(), NULL,NULL,NULL);

    disconnect();
    return true;
}


//OPERATORS

/**
 * Same thing as the cloning constructor. Cannot assign a database.
 * The creation is made only with getInstance method.
*/
void Database::operator=(const Database&) = delete;