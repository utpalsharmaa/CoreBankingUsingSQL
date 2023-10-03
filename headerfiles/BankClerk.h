#include<iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include "../DatabaseConnection/DatabaseConnector.h"
using namespace std;
class BankClerk {
private:
    DatabaseConnector* dbConnector;

public:
    BankClerk(DatabaseConnector* connector);
    void ClerkDashboard();
    void AddCustomer();
    void DeleteCustomer();
    void ModifyCustomer();
    void CreditMoney();
    void DebitMoney();
    void getAllCustomers();
    void AccountTransaction();
    void Query();
    void Exit();
};
