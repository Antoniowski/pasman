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

void Database::drop_table()
{
    //Delete all tables in database.

    connect();
    std::string query_basis = "DROP TABLE IF EXISTS ";
    std::vector<std::string> tables = {"LOGIN", "PASSWORDS", "PATH"};
    for(std::string t: tables)
    {
        sqlite3_exec(sqlite_db, (query_basis+t+";").c_str(), NULL, NULL, NULL);
    }
    disconnect();

}

void Database::create_tables()
{
    connect();    
    sqlite3_exec(sqlite_db, LOGIN_CREATE_SCHEMA.c_str(), NULL, NULL, NULL);
    sqlite3_exec(sqlite_db, PATH_CREATE_SCHEMA.c_str(), NULL, NULL, NULL);
    sqlite3_exec(sqlite_db, PASSWORDS_CREATE_SCHEMA.c_str(), NULL, NULL, NULL);
    disconnect();
}

void Database::first_init()
{
    drop_table();
    create_tables();
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

std::string Database::get_value(std::string column, std::string table, std::string where_condition)
{
    std::string query_1 = "SELECT ";
    std::string queey_2 = " FROM ";
    std::string query_3 = " WHERE ";
    std::string query;
    if(where_condition != "")
    {
        query = query_1 + column + queey_2 + table + query_3 + where_condition + ";";
        std::cout << query;
    }else{
        query = query_1 + column + queey_2 + table + ";";
        std::cout << query << std::endl;
    }

    connect();
    sqlite3_stmt* statement;
    const void* result;
    int rc = sqlite3_prepare_v2(sqlite_db, query.c_str(),query.length(),&statement, nullptr);
    if(rc != SQLITE_OK)
    {
        disconnect();
        return "Error\n";
    }

    std::string x = "";
    while ((rc = sqlite3_step(statement)) == SQLITE_ROW)
    {
        result = sqlite3_column_text(statement, 0);
        std::string string_result(static_cast<char const *>(result));
        x = string_result;
    }
    sqlite3_finalize(statement);
    disconnect();
    return x;
}


//OPERATORS

/**
 * Same thing as the cloning constructor. Cannot assign a database.
 * The creation is made only with getInstance method.
*/
void Database::operator=(const Database&) = delete;