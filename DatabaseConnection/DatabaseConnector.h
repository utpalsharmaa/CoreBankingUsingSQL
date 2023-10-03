#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <string>

class DatabaseConnector {
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* connection;

public:
    DatabaseConnector(const std::string& host, const std::string& user, const std::string& password, const std::string& database);
    ~DatabaseConnector();

    void connect();                           
    void disconnect();
    sql::Connection* getConnection();       
};

#endif
