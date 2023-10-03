#include<iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include "../DatabaseConnection/DatabaseConnector.h"
using namespace std;
class Customer {
private:
    DatabaseConnector* dbConnector;

public:
    Customer(DatabaseConnector* connector);
    void CustomerDashboard();
    void ViewDetails();
    void TransferMoney();
    void Query();
    void Exit();
};
