#include<iostream>
#include<regex>
#include "../headerfiles/BankClerk.h"
#include "../DatabaseConnection/DatabaseConnector.h"
#include <cppconn/prepared_statement.h>
#include <string>
#include<sstream>
#include <mysql_driver.h>
#include <ctime>
#include <cstdlib>
#include<iomanip>
using namespace std;

BankClerk::BankClerk(DatabaseConnector* connector) : dbConnector(connector) {}
void BankClerk::ClerkDashboard(){
    int ch;
    
    cout<<"1. Add Customer "<<endl;
    cout<<"2. Delete Customer"<<endl;
    cout<<"3. Modify Customer"<<endl;
    cout<<"4. Credit Money"<<endl;
    cout<<"5. Debit Money"<<endl;
    cout<<"6. Query/Report"<<endl;
    cout<<"7. Exit"<<endl;
    cout<<"Enter Choice:";
    cin>>ch;
    switch (ch)
    {
    case 1:
            AddCustomer();
        break;
    case 2:
            DeleteCustomer();
        break;
    case 3:
            ModifyCustomer();
        break;
    case 4:
            CreditMoney();
        break;
    case 5:
            DebitMoney();
        break;
    case 6:
            Query();
        break;
    case 7:
           break;
    default:
        break;
    }

}
void BankClerk::AddCustomer(){
    DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "12345678", "Bank");
    dbConnector.connect();

    sql::Connection* connection = dbConnector.getConnection();
    sql::Statement* statement;

    try {
        // Take user input for the values to be inserted
        string customerID, name, type, address1, address2, address3, city, state, country, pincode, phoneNumber, email, pan;

        cout << "Enter customer ID: ";
        cin >> customerID;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter type: ";
        cin >> type;
        cout << "Enter address line 1: ";
        cin >> address1;
        cout << "Enter address line 2: ";
        cin >> address2;
        cout << "Enter address line 3: ";
        cin >> address3;
        cout << "Enter city: ";
        cin >> city;
        cout << "Enter state: ";
        cin >> state;
        cout << "Enter country: ";
        cin >> country;
        cout << "Enter pin code: ";
        cin >> pincode;
        cout << "Enter phone number: ";
        cin >> phoneNumber;
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter PAN: ";
        cin >> pan;

        // Build the SQL query with the provided values
        string query = "INSERT INTO Customer_Info (customerID, name, type, address1, address2, address3, city, state, country, Pincode, PhoneNumber, Email, Pan) "
                       "VALUES ('" + customerID + "', '" + name + "', '" + type + "', '" + address1 + "', '" + address2 + "', '" + address3 + "', '"
                       + city + "', '" + state + "', '" + country + "', '" + pincode + "', '" + phoneNumber + "', '" + email + "', '" + pan + "')";

        // Create a statement
        statement = connection->createStatement();

        // Execute the INSERT statement
        statement->executeUpdate(query);

// Generate auto-generated userId
srand(time(0)); // Seed the random number generator

    int userId = rand() % 10000;

        string usertype = "U"; // Assuming type is always "user"
        int loginStatus = 0; // Assuming loginStatus is always 0

        // Generate a random password
        srand(static_cast<unsigned>(time(0)));
        string password = to_string(rand() % 1000000);

        // Build the SQL query with the provided values
        string query1 = "INSERT INTO user_info ( userId,customerId, usertype, password, loginStatus) "
                       "VALUES (" + to_string(userId) + ",'" + customerID + "',  '" + usertype + "', '" + password + "', " + to_string(loginStatus) + ")";

        // Create a statement
        statement = connection->createStatement();

        // Execute the INSERT statement
        statement->executeUpdate(query1);

        // Generate auto-generated AccountNumber
srand(time(0)); // Seed the random number generator

    int AccountNumber= rand() % 10000;
        string accounttype;
        cout<<"Enter Account Type :";
        cin>>accounttype;
        string status;
        cout<<"Enter status:";
        cin>>status;
        double Balance;
        cout<<"Enter Balance:";
        cin>>Balance;
        string openingDate;
        cout<<"Enter Opening Data:";
        cin>>openingDate;
       

        string query2 = "insert into account_info(AccountNumber,Type, CustomerId, status, Balance,openingDate) values("+to_string(AccountNumber)+",'"+ accounttype+"','"+customerID+"','"+status+"',"+to_string(Balance)+",'"+openingDate+"')";
// AccountNumber int,Type varchar(10),CustomerId varchar(10), status varchar(10),Balance DOUBLE,openingDate varchar(10));

        // Create a statement 
        statement = connection->createStatement();

        // Execute the INSERT statement
        statement->executeUpdate(query2);


        cout << "Customer Added Successfully." << endl;
        ClerkDashboard();
    }
    catch (sql::SQLException& e) {
        cout << "SQL Exception: " << e.what() << endl;
    }

    // Clean up resources
    delete statement;
    delete connection;


}
void BankClerk::DeleteCustomer(){
    DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "12345678", "Bank");
    dbConnector.connect();

    sql::Connection* connection = dbConnector.getConnection();
    sql::Statement* statement;
    string customerId;
    cout<<"Enter customerId:";
    cin>>customerId;

     string query ="delete from user_info where customerId ='"+customerId+"'";
        // Create a statement
        statement = connection->createStatement();

        // Execute the INSERT statement
        statement->executeUpdate(query);

        string query1 ="delete from account_info where customerId ='"+customerId+"'";
        // Create a statement
        statement = connection->createStatement();

        // Execute the INSERT statement
        statement->executeUpdate(query1);


        string query2 ="delete from customer_info where customerId ='"+customerId+"'";

        cout<<"Customer Deleted Sucessfully!!";
        ClerkDashboard();
        // Create a statement
        statement = connection->createStatement();

        // Execute the INSERT statement
        statement->executeUpdate(query2);


}


void BankClerk::ModifyCustomer(){

  DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "12345678", "Bank");
    dbConnector.connect();

 

    string customerId;
    cout << "Enter customerId: ";
    cin >> customerId;

    string query = "SELECT * FROM customer_info WHERE customerId = '" + customerId + "'";

sql::Statement* stmt = dbConnector.getConnection()->createStatement();
sql::ResultSet* res = stmt->executeQuery(query);

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

while (res->next()) {
    for (const std::string& columnName : columnNames) {
        std::string columnValue = res->getString(columnName);
        std::cout << std::setw(nameWidth) << columnValue << " ";
    }
    std::cout << std::endl;
}
string columnname,columnvalue;
cout<<"What you want to update:";
cin>>columnname;
cout<<"Enter new data:";
cin>>columnvalue;
string query1 = "UPDATE customer_info SET " + columnname + " = '" + columnvalue + "' WHERE customerID = '" + customerId + "'";

       // Create a statement
// Assuming you have established the database connection using dbConnector
sql::Connection* connection = dbConnector.getConnection();

// Create a statement
sql::Statement* statement = connection->createStatement();

// Execute the update statement
statement->executeUpdate(query1);

// Clean up resources
delete statement;

    cout<<"Customer Details Modified Sucessfully!!"<<endl;
    ClerkDashboard();
        // Create a statement
      

}
void BankClerk::CreditMoney(){
DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "12345678", "Bank");
dbConnector.connect();

sql::Connection* connection = dbConnector.getConnection();
sql::Statement* statement;

int AccountNumber;
cout << "Enter Account Number: ";
cin >> AccountNumber;

// Check if the account number exists
string checkQuery = "SELECT * FROM account_info WHERE AccountNumber = " + to_string(AccountNumber);

// Create a statement to execute the check query
sql::Statement* checkStatement = connection->createStatement();
sql::ResultSet* checkResult = checkStatement->executeQuery(checkQuery);

// Check if the account number exists
if (!checkResult->next()) {
    cout << "Account Number doesn't exist !!" << endl;
    // Clean up resources
    delete checkResult;
    delete checkStatement;
    return;
}

double amount;
cout << "Enter the amount: ";
cin >> amount;



// Update the balance in the database
string updateQuery = "UPDATE account_info SET Balance = Balance + " + to_string(amount) + " WHERE AccountNumber = " + to_string(AccountNumber);

// Create a statement to execute the update query
sql::Statement* updateStatement = connection->createStatement();
updateStatement->executeUpdate(updateQuery);

// Clean up resources
delete checkResult;
delete checkStatement;
delete updateStatement;

cout << "Amount Credited Successfully!" << endl;
ClerkDashboard();

}
void BankClerk::DebitMoney(){

DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "12345678", "Bank");
dbConnector.connect();

sql::Connection* connection = dbConnector.getConnection();
sql::Statement* statement;

int AccountNumber;
cout << "Enter Account Number: ";
cin >> AccountNumber;
// Check the current balance
string balanceQuery = "SELECT Balance FROM account_info WHERE AccountNumber = " + to_string(AccountNumber);

// Create a statement to execute the balance query
sql::Statement* balanceStatement = connection->createStatement();
sql::ResultSet* balanceResult = balanceStatement->executeQuery(balanceQuery);

// Check if the account number exists
if (!balanceResult->next()) {
    cout << "Account Number doesn't exist!!" << endl;
    // Clean up resources
    delete balanceResult;
    delete balanceStatement;
    return;
}

double amount;
cout << "Enter the amount: ";
cin >> amount;



// Get the current balance
double currentBalance = balanceResult->getDouble("Balance");

// Check if there is sufficient balance
if (currentBalance < amount) {
    cout << "Insufficient Balance" << endl;
    // Clean up resources
    delete balanceResult;
    delete balanceStatement;
    return;
}

// Deduct the amount from the balance
double updatedBalance = currentBalance - amount;

// Update the balance in the database
string updateQuery = "UPDATE account_info SET Balance = " + to_string(updatedBalance) + " WHERE AccountNumber = " + to_string(AccountNumber);

// Create a statement to execute the update query
sql::Statement* updateStatement = connection->createStatement();
updateStatement->executeUpdate(updateQuery);

// Clean up resources
delete balanceResult;
delete balanceStatement;
delete updateStatement;

cout << "Amount Debited Successfully!" << endl;
ClerkDashboard();


}
void BankClerk::Query() {
    int ch;
    cout << "1. View All the Customers" << endl;
    cout << "2. Get the Report of a Customer's Account and Transaction" << endl;
    cout<<"Enter your choice:";
    cin >> ch;


    switch (ch) {
        case 1:
            getAllCustomers();
            break;
        case 2:
            AccountTransaction();
            break;
        default:
            break;
    }
}

void BankClerk::getAllCustomers() {
        // Establish a database connection
    DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "12345678", "Bank");
    dbConnector.connect();

    // Execute a query to retrieve all customers
    string query = "SELECT userId, customerId FROM user_info WHERE usertype = 'U'";



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
    std::cout << std::endl;
    std::cout << "Customer Information" << std::endl;

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
    ClerkDashboard();
}


void BankClerk::AccountTransaction() {
DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "12345678", "Bank");
dbConnector.connect();

// Get customer ID from user
int AccountNumber;
std::cout << "Enter Account Number: ";
std::cin >> AccountNumber;

// Create the query to retrieve account information
std::string accountQuery = "SELECT * FROM account_info WHERE AccountNumber = " + to_string(AccountNumber);

// Create a statement and execute the query to retrieve account information
sql::Statement* accountStmt = dbConnector.getConnection()->createStatement();
sql::ResultSet* accountRes = accountStmt->executeQuery(accountQuery);

// Retrieve column names from account result set metadata
sql::ResultSetMetaData* accountMetaData = accountRes->getMetaData();
int accountColumnCount = accountMetaData->getColumnCount();
std::vector<std::string> accountColumnNames;

for (int i = 1; i <= accountColumnCount; i++) {
    accountColumnNames.push_back(accountMetaData->getColumnName(i));
}

// Print account information column names
int nameWidth = 15; // Adjust the width as per your needs
std::cout << std::endl;
std::cout << "Account Information" << std::endl;
std::cout << std::left;
for (const std::string& columnName : accountColumnNames) {
    std::cout << std::setw(nameWidth) << columnName << " ";
}
std::cout << std::endl;

// Print the retrieved account information
while (accountRes->next()) {
    for (const std::string& columnName : accountColumnNames) {
        std::string columnValue = accountRes->getString(columnName);
        std::cout << std::setw(nameWidth) << columnValue << " ";
    }
    std::cout << std::endl;
}

// Clean up account resources
delete accountRes;
delete accountStmt;

// Create the query to retrieve transaction information
std::string transactionQuery = "SELECT * FROM Transaction_info WHERE AccountNumber = " + to_string(AccountNumber);

// Create a statement and execute the query to retrieve transaction information
sql::Statement* transactionStmt = dbConnector.getConnection()->createStatement();
sql::ResultSet* transactionRes = transactionStmt->executeQuery(transactionQuery);

// Retrieve column names from transaction result set metadata
sql::ResultSetMetaData* transactionMetaData = transactionRes->getMetaData();
int transactionColumnCount = transactionMetaData->getColumnCount();
std::vector<std::string> transactionColumnNames;

for (int i = 1; i <= transactionColumnCount; i++) {
    transactionColumnNames.push_back(transactionMetaData->getColumnName(i));
}

// Print transaction information column names
std::cout << std::endl;
std::cout << "Transaction Information" << std::endl;
std::cout << std::left;
for (const std::string& columnName : transactionColumnNames) {
    std::cout << std::setw(nameWidth) << columnName << " ";
}
std::cout << std::endl;

// Print the retrieved transaction information
while (transactionRes->next()) {
    for (const std::string& columnName : transactionColumnNames) {
        std::string columnValue = transactionRes->getString(columnName);
        std::cout << std::setw(nameWidth) << columnValue << " ";
    }
    std::cout << std::endl;
}

// Clean up transaction resources
delete transactionRes;
delete transactionStmt;
ClerkDashboard();

}