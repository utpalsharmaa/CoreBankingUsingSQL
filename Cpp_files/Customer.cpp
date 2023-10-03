#include<iostream>
#include<regex>
#include <iomanip>
#include "../headerfiles/Customer.h"
#include "../DatabaseConnection/DatabaseConnector.h"
#include <cppconn/prepared_statement.h>
#include <string>
#include<sstream>
using namespace std;

Customer::Customer(DatabaseConnector* connector) : dbConnector(connector) {}
void Customer::CustomerDashboard(){
    int ch;
    cout<<"1. View Customer Details"<<endl;
    cout<<"2. Transfer Money"<<endl;
    cout<<"3. Query"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<"Enter Choice:";

    cin>>ch;

    switch(ch){
        case 1:
              ViewDetails();
              break;
        case 2:
              TransferMoney();
              break;
        case 3:
              Query();
              break;
        case 4:
              break;
        default:
              break;
    }
    
    
}

void Customer::ViewDetails(){
   DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "12345678", "Bank");
    dbConnector.connect();

    // Get customer ID from user
    std::string customerId;
    std::cout << "Enter customer ID: ";
    std::cin >> customerId;

    // Create the query
    std::string query = "SELECT * FROM customer_info WHERE customerId = '" + customerId + "'";

    // Create a statement and execute the query
    sql::Statement* stmt = dbConnector.getConnection()->createStatement();
    sql::ResultSet* res = stmt->executeQuery(query);

    // Retrieve column names from result set metadata
    sql::ResultSetMetaData* metaData = res->getMetaData();
    int columnCount = metaData->getColumnCount();
    std::vector<std::string> columnNames;

    for (int i = 1; i <= columnCount; i++) {
        columnNames.push_back(metaData->getColumnName(i));
    }

    int nameWidth = 15; // Adjust the width as per your needs

    std::cout << std::left;
    for (const std::string& columnName : columnNames) {
        std::cout << std::setw(nameWidth) << columnName << " ";
    }
    std::cout << std::endl;

    // Print the retrieved data
    while (res->next()) {
        for (const std::string& columnName : columnNames) {
            std::string columnValue = res->getString(columnName);
            std::cout << std::setw(nameWidth) << columnValue << " ";
        }
        std::cout << std::endl;
    }

    // Clean up resources
    delete res;
    delete stmt;
    CustomerDashboard();

}
void Customer::TransferMoney(){

DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "12345678", "Bank");
dbConnector.connect();

sql::Connection* connection = dbConnector.getConnection();
sql::Statement* statement;

string debitCustomerId;
cout << "Enter Debit Customer ID: ";
cin >> debitCustomerId;

int debitAccountNumber;
cout << "Enter your Account Number: ";
cin >> debitAccountNumber;

int creditAccountNumber;
cout << "Enter Credit Account Number: ";
cin >> creditAccountNumber;

double amount;
cout << "Enter the amount: ";
cin >> amount;

// Get the current balance of the debit account
string debitBalanceQuery = "SELECT Balance FROM account_info WHERE customerId = '" + debitCustomerId + "'";

// Create a statement to execute the debit balance query
sql::Statement* debitBalanceStatement = connection->createStatement();
sql::ResultSet* debitBalanceResult = debitBalanceStatement->executeQuery(debitBalanceQuery);

double debitCurrentBalance = 0.0;

if (debitBalanceResult->next()) {
    debitCurrentBalance = debitBalanceResult->getDouble("Balance");
} else {
    cout << "Debit Customer ID doesn't exist" << endl;
    // Clean up resources
    delete debitBalanceResult;
    delete debitBalanceStatement;
    return;
}

// Check if there is sufficient balance in the debit account
if (debitCurrentBalance < amount) {
    cout << "Insufficient Balance in the Debit Account" << endl;
    // Clean up resources
    delete debitBalanceResult;
    delete debitBalanceStatement;
    return;
}

// Deduct the amount from the debit account
string debitUpdateQuery = "UPDATE account_info SET Balance = Balance - " + std::to_string(amount) + " WHERE customerId = '" + debitCustomerId + "'";

// Create a statement to execute the debit update query
sql::Statement* debitUpdateStatement = connection->createStatement();
debitUpdateStatement->executeUpdate(debitUpdateQuery);

// Credit the amount to the credit account
string creditUpdateQuery = "UPDATE account_info SET Balance = Balance + " + std::to_string(amount) + " WHERE AccountNumber = " + std::to_string(creditAccountNumber);

// Create a statement to execute the credit update query
sql::Statement* creditUpdateStatement = connection->createStatement();
creditUpdateStatement->executeUpdate(creditUpdateQuery);

// Clean up resources
delete debitBalanceResult;
delete debitBalanceStatement;
delete debitUpdateStatement;
delete creditUpdateStatement;

srand(time(0)); // Seed the random number generator

    int TransactionID= rand() % 10000;


        string Transcationtype;
        cout<<"Enter Transcation Type :";
        cin>>Transcationtype;
        
        string query2 = "insert into Transaction_info(TransID,Type, AccountIDSrc, AccountIDDst, Amount,AccountNumber) values("+to_string(TransactionID)+",'"+ Transcationtype+"',"+to_string(debitAccountNumber)+","+to_string(creditAccountNumber)+","+to_string(amount)+","+to_string(debitAccountNumber)+")";
// AccountNumber int,Type varchar(10),CustomerId varchar(10), status varchar(10),Balance DOUBLE,openingDate varchar(10));

        // Create a statement 
        statement = connection->createStatement();

        // Execute the INSERT statement
        statement->executeUpdate(query2);
cout << "Money Transfred Sucessfully!!"<<endl;
CustomerDashboard();


}
void Customer::Query(){

    DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "12345678", "Bank");
    dbConnector.connect();

    // Get customer ID from user
    int AccountNumber;
    std::cout << "Enter Account Number: ";
    std::cin >> AccountNumber;

    // Create the query
    std::string query = "SELECT * FROM Transaction_info WHERE AccountNumber = " +to_string(AccountNumber )+ "";

    // Create a statement and execute the query
    sql::Statement* stmt = dbConnector.getConnection()->createStatement();
    sql::ResultSet* res = stmt->executeQuery(query);

    // Retrieve column names from result set metadata
    sql::ResultSetMetaData* metaData = res->getMetaData();
    int columnCount = metaData->getColumnCount();
    std::vector<std::string> columnNames;

    for (int i = 1; i <= columnCount; i++) {
        columnNames.push_back(metaData->getColumnName(i));
    }

    int nameWidth = 15; // Adjust the width as per your needs
    // Print transaction information column names
    std::cout << std::endl;
    std::cout << "Transaction Information" << std::endl;

    std::cout << std::left;
    for (const std::string& columnName : columnNames) {
        std::cout << std::setw(nameWidth) << columnName << " ";
    }
    std::cout << std::endl;

    // Print the retrieved data
    while (res->next()) {
        for (const std::string& columnName : columnNames) {
            std::string columnValue = res->getString(columnName);
            std::cout << std::setw(nameWidth) << columnValue << " ";
        }
        std::cout << std::endl;
    }

    // Clean up resources
    delete res;
    delete stmt;
    CustomerDashboard();


}

