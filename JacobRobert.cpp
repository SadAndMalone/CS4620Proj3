//
// An example from the web
// To make it work on voyager it must be compiled as such:
//
// g++ -Wall -o JacobRobert -I/usr/include/mysql-cppconn-8/mysql -I/usr/include/mysql-cppconn-8/jdbc JacobRobert.cpp -L/usr/lib64 -lmysqlcppconn 
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
#define USER "rjmoon"
#define PASS "ftyHcW"
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

		int selection = 0;

		while (selection != 3) {
			cout << "Select Option\n 1) Search by First Name\n 2) Display Section/Lot\n 3) Quit\n\n";
			cin >> selection;


			if (selection < 1 || selection > 3) {
				cout << "Please enter a your choice as a number between 1 and 3\n";
			}

			if(selection == 3) {
				cout << "Goodbye\n\n";
				return EXIT_SUCCESS;
			}

			// replace with your statement
			else if(selection == 1) {
				//First Name Search
				string fname;
				cout << "Enter the First Name of the owner you wish to search for.\n";
				cin >> fname;

				//Query to find all owners with first name provided by user
				res = stmt->executeQuery("SELECT First_Name, Last_Name, Address_Street, Address_City, Address_State, Address_ZIP FROM OWNER WHERE First_Name = '" + fname + "'"); 

				cout << "\n Owner Information \n";
				while (res->next()){
					cout << "Name:\t" << res->getString(1) << " " <<  res->getString(2) << endl;
					cout << "Address:\t" << res->getString(3) << endl << res->getString(4) << ", " << res->getString(5) << " " << res->getString(6) << endl << endl;
				}
				string lname;
				cout << "Enter the last name of the owner you are looking for.\n";
				cin >> lname;

				//Query to find all owned graves by the owner being search for.
				res = stmt->executeQuery("SELECT Grave_Number, Style, Lot_Name, Section_Name FROM GRAVE LEFT JOIN LOT ON LOT.Lot_ID = GRAVE.Lot_ID LEFT JOIN SECTION ON SECTION.Section_ID = LOT.Section_ID WHERE GRAVE.Owner_ID IN (SELECT Owner_ID FROM OWNER WHERE First_Name = '" + fname + "' AND Last_Name = '" + lname + "')");

				cout << "Graves Owned by " << fname << " " << lname << endl;
				while (res->next()) {
					cout << "\tGrave Number:\t" << res->getString(1) << endl;
					cout << "\tGrave Style:\t" << res->getString(2) << endl;
					cout << "\tLot:\t\t" << res->getString(3) << endl;
					cout << "\tSection:\t" << res->getString(4) << endl << endl;
				}

							
			}
			else if(selection == 2) {
				//Section/Lot
				
				string section;
				cout << "Sections:\n 1) N/A\t\t 9) NC E Row B\n 2) BC E\t 10) NC E Row D\n 3) BC W\t 11) NC E Row E\n 4) NC A\t 13) O/C\n 5) NC B\t 14) OC\n 6) NC C\t 15) OS\n 7) NC D\t 16) OS Memory Garden\n 8) NC E\n";
				cout<< "Which section would you like to view?\n";
				cin >> section;

				//Query to find lot names in section entered by user
				res = stmt->executeQuery("SELECT lot_Name FROM LOT JOIN SECTION ON LOT.Section_ID = SECTION.Section_ID where Section_Name = '" + section + "'"); 
				
				cout << " Lots in Section " << section << endl;
				while (res->next()){
					cout << res->getString(1) << endl; 
				}
				string lotname;
				cout << "Enter the lot you are looking for.\n";
				cin >> lotname;

				//Query to find the status of all graves in the lot entered by user.
				res = stmt->executeQuery("SELECT Grave_Number, Style, First_Name, Last_Name FROM OWNER JOIN GRAVE ON OWNER.Owner_ID = GRAVE.Owner_ID JOIN LOT ON GRAVE.Lot_ID = LOT.Lot_ID WHERE Lot_Name = '" + lotname + "'");

				cout << "Graves In Lot " << lotname << endl;
				while (res->next()) {
					cout << "\tGrave Number:\t" << res->getString(1) << endl;
					cout << "\tGrave Style:\t" << res->getString(2) << endl;
					cout << "\tFirst Name:\t" << res->getString(3) << endl;
					cout << "\tLast Name:\t" << res->getString(4) << endl << endl;
				}
			}

		}
		// Release unused resources
		delete res;
		delete stmt;
		delete con;
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
