#include "DatabaseConnector.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include<iostream>
//#include "../DatabaseConnection/DatabaseConnector.h"
using namespace std;

DatabaseConnector::DatabaseConnector(const std::string& host, const std::string& user, const std::string& password, const std::string& database) {
    driver = sql::mysql::get_mysql_driver_instance();
    connection = driver->connect("tcp://127.0.0.1:3306", "root", "12345678");
    connection->setSchema("Bank");
}
DatabaseConnector::~DatabaseConnector() 
{
    delete connection;
}

void DatabaseConnector::connect() 
{
    // Additional connection logic, if needed
    // For example, setting connection properties or handling exceptions
}

void DatabaseConnector::disconnect() {
    // Additional disconnection logic, if needed
}
// 
sql::Connection* DatabaseConnector::getConnection() {
    return connection;
}
