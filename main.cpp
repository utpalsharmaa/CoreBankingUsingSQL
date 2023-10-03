#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <stdlib.h>
#include "headerfiles/Customer.h"
#include "headerfiles/BankClerk.h"
#include "DatabaseConnection/DatabaseConnector.h"
using namespace std;
int main()
{
    DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "12345678", "Bank");
    dbConnector.connect();
    Customer loginManager(&dbConnector);
    BankClerk AdminLogin(&dbConnector);

    int userid;
    string password;
    bool validLogin = false;

    do {
        cout << "Enter user id: ";
        cin >> userid;
        cout << "Enter the password: ";
        cin >> password;

        string query = "SELECT * FROM user_info WHERE userId = " + to_string(userid) + " AND password = '" + password + "' ";
        sql::Connection* connection = dbConnector.getConnection();
        
        // Create a statement
        sql::Statement* statement = connection->createStatement();
        
        // Execute a query
        sql::ResultSet* resultSet = statement->executeQuery(query);
        
        // Check if the login is valid
        if (resultSet->next()) {
            string role = resultSet->getString("userType");
            if (role == "U") {
                cout<<"Customer Login Sucessfull!!"<<endl;
                loginManager.CustomerDashboard();
            }
            else if (role == "A") {
                cout<<"Bank Clerk Login Sucessfull !!"<<endl;
                AdminLogin.ClerkDashboard();
                
            }
            validLogin = true;
        }
        else {
            cout << "Invalid user ID or password. Please try again." << endl;
        }
        
        // Clean up resources
        delete resultSet;
        delete statement;
    } while (!validLogin);

    // ...

    return 0;
}
