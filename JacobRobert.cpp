//
// An example from the web
// To make it work on voyager it must be compiled as such:
//
// g++ -Wall -o mysql_test -I/usr/include/mysql-cppconn-8/mysql -I/usr/include/mysql-cppconn-8/jdbc mysql_test.cpp -L/usr/lib64 -lmysqlcppconn 
//

// To use c++ libraries
#include <iostream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

// To use lambda anonymous functions in c++ programming 
#include <boost/lambda/lambda.hpp> 

// To create MySQL connections
#include "mysql_connection.h"

// To use SQL statements in c++
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#define HOST "voyager.cs.bgsu.edu"
#define USER "mcjacob"
#define PASS "G5N3b7"
#define DB "CMS4620"

using namespace std;

int main(void)
{
	cout << endl;
	cout << "Running Cemetary Management System \n";
       
	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;
		
		/* Create a connection */
		driver = get_driver_instance();

		//cout << "hello" << endl;
		con = driver->connect(HOST, USER, PASS);

		// Connect to the MySQL test database
		con->setSchema(DB);

		stmt = con->createStatement();

		while (selection != 3) {
			int selection;
			cout << "Select Option\n 1) Search by First Name\n 2) Display Section/Lot\n 3) Quit\n\n";
			cin >> selection;

			if (selection < 1 || selection > 3) {
				cout << "Please enter a your choice as a number between 1 and 3\n";
			}

			// replace with your statement
			if(selection == 1) {
				//First Name Search
				string fname;
				cout << "Enter the First Name of the interred you wish to search for.\n";
				cin >> fname;

				res = stmt->executeQuery("SELECT 'Hello World!' AS _message"); 
				while (res->next()){
					cout << "\t... MySQL replies: " << res->getString("_message") << endl;
					cout << "\t... say it again, MySQL" << endl;
					cout << "\t....MySQL replies: " << res->getString(1) << endl;
				}
			}
			else if(selection == 2) {
				//Section/Lot
				
				int section;
				cout << "Sections:\n 1) N/A\n 2) BC E\n 3) BC W\n 4) NC A\n 5) NC B\n 6) NC C\n 7) NC D\n 8) NC E\n";
				cout << "9) NC E Row B\n 10) NC E Row D\n 11) NC E Row E\n 13) O/C\n 14) OC\n 15) OS\n 16) OS Memory Garden\n\n Which Section would you like to view?\n";
				cin >> section

				res = stmt->executeQuery("SELECT 'Hello World!' AS _message"); 
				while (res->next()){
					cout << "\t... MySQL replies: " << res->getString("_message") << endl;
					cout << "\t... say it again, MySQL" << endl;
					cout << "\t....MySQL replies: " << res->getString(1) << endl;
				}

			}

			// Release unused resources
			delete res;
			delete stmt;
			delete con;
		}
	}
	catch (sql::SQLException &e) {
		/*
		 * MySQL Connector/C++ throws three different exceptions:
		 * - sql::MethodNotImplementedException (derived from sql::SQLException)
		 *   - sql::InvalidArgumentException (derived from sql::SQLException)
		 *   - sql::SQLException (derived from std::runtime_error)
		 **/
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;

		/* what() (derived from std::runtime_error) fetches error message */
		cout << "# ERR: " << e.what();
		//cout << " (MySQL error code: " << e.getErrorCode();
		////cout << ", SQLState: " << e.getSQLState() << " )" << endl;

		return EXIT_FAILURE;
	}

	cout << "Done." << endl;
	return EXIT_SUCCESS;
}
