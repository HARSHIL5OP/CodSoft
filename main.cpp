#include <iostream>
#include<conio.h>
#include <mysql.h>
#include <errmsg.h> // for error
#include <windows.h> // for system pause and sleep
#include <sstream> // for giving int value in query
#include <vector>
#include<iomanip>
#include <ctime>  // For time functions
#include <string>

using namespace std;

const int width = 120;
const char* HOST = "localhost";
const char* USER = "root";
const char* PASSWORD = "harshil@2004";
const char* DB = "library_management_system";

void printDecor() {
    for (int i = 0; i < width; i++) {
        cout << "-";
    }
    cout << "\n";
}

void printCentered(string message) {
    int messageLength = message.length();
    int padding = (width - messageLength) / 2;
    cout << setfill('-') << setw(padding) << "" << message << setw(padding + messageLength % 2) << "" << "\n";
}

bool adminLogin(string usn, string pass, MYSQL* con) {
    string query = "select * from adminCredentials where username = '" + usn + "' and password = '" + pass + "'";
    if (mysql_query(con, query.c_str())) { // returns false / 0 on success and true / 1 on failure
        cout << "Error in Executing Query : " << mysql_error(con) << endl;
        return false;
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        cout << "Error retrieving result set: " << mysql_error(con) << endl;
        return false;
    } else {
        if (mysql_num_rows(result) > 0) {
            return true;
        } else {
            return false;
        }
    }
}

void addBook(const string& bookName, int quantity, MYSQL* con) {
    stringstream ss;
    ss << "INSERT INTO books (bookName, quantity) VALUES ('" << bookName << "', " << quantity << ")";
    string query = ss.str();
    
    if (mysql_query(con, query.c_str())) {
        cout << "Error in Adding Book: " << mysql_error(con) << endl;
    } else {
        cout << "Book Added Successfully" << endl;
    }
}

void removeBook(const string& bookName, MYSQL* con) {
    string query = "SELECT bookName, quantity FROM books WHERE bookName = '" + bookName + "'";

    if (mysql_query(con, query.c_str())) {
        cout << "Error in Executing Query: " << mysql_error(con) << endl;
        return;
    } else {
        MYSQL_RES* result = mysql_store_result(con);
        if (result == NULL) {
            cout << "Error retrieving result set: " << mysql_error(con) << endl;
            return;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        if (row == NULL) {
            cout << "No Book Found" << endl;
            Sleep(1000);
            mysql_free_result(result);
            return;
        }

        int quantity = atoi(row[1]); // Convert quantity to integer
        if (quantity > 1) {
            quantity--; 
            stringstream ss;
            ss << "UPDATE books SET quantity = " << quantity << " WHERE bookName = '" << bookName << "'";
            string updateQuery = ss.str();

            if (mysql_query(con, updateQuery.c_str())) {
                cout << "Error in Updating Quantity: " << mysql_error(con) << endl;
            } else {
                cout << "One Book Removed" << endl;
            }
        } else if(quantity<=1) {
            string query="delete from books where bookName='"+bookName+"'";
            if(mysql_query(con,query.c_str())){
            	cout<<"Error in Deleting Query : "<<mysql_error(con)<<endl;
			}
			else{
				cout<<"Deleted"<<endl;
				cout<<"No More Books of name : "<<bookName<<endl;
			}
        }

        mysql_free_result(result); // Free the result set
      
    }
}



void showBooks(MYSQL* con) {
    string query = "select bookName, quantity from books";
    if (mysql_query(con, query.c_str())) {
        cout << "Error in Loading Query : " << mysql_error(con) << endl;
        return;
    } else {
        MYSQL_RES* result = mysql_store_result(con);
        if (result == NULL) {
            cout << "Error Fetching Data: " << mysql_error(con) << endl;
            return;
        }

        if (mysql_num_rows(result) == 0) {
            cout << "No Data Found" << endl;
            mysql_free_result(result);
            return;
        }

        vector<vector<string> > books;

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            vector<string> book;
            book.push_back(row[0] ? row[0] : "");
            book.push_back(row[1] ? row[1] : "");
            books.push_back(book);
        }
        mysql_free_result(result);

        cout << "Book Details \n\n";

        cout << left << setw(30) << setfill(' ') << "Book Name" << setw(10) << setfill(' ') << "Quantity" << endl;
        printDecor();
        for (size_t i = 0; i < books.size(); ++i) {
            cout << left << setw(30) << setfill(' ') << books[i][0]
                 << setw(10) << setfill(' ') << books[i][1] << endl;
        }
    }
}


void addStudent(const string& studentId, const string& studentName,const string& studentPhn, MYSQL* con) {
    string query="insert into students (studentId,studentName,studentPhn) values ('"+studentId+"','"+studentName+"','"+studentPhn+"')";
    
    if (mysql_query(con, query.c_str())) {
        cout << "Error in Adding Student: " << mysql_error(con) << endl;
    } else {
    	cout << "Student Added Successfully" << endl;
        Sleep(2000);
    }
}

void removeStudent(const string& studentId, MYSQL* con) {
    string query = "SELECT * FROM students WHERE studentId = '" + studentId + "'";
    if (mysql_query(con, query.c_str())) {
        cout << "Error in Executing Query: " << mysql_error(con) << endl;
        return;
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (!result) {
        cout << "Error in Fetching Data: " << mysql_error(con) << endl;
        return;
    }
    if (mysql_num_rows(result) == 0) {
        	cout << "No Student Found" << endl;
       	 	mysql_free_result(result);
        	return;
    	}
    MYSQL_ROW row = mysql_fetch_row(result);
    
    mysql_free_result(result);

    string deleteQuery = "DELETE FROM students WHERE studentId = '" + studentId + "'";
    if (mysql_query(con, deleteQuery.c_str())) {
        cout << "Error in Deleting Student: " << mysql_error(con) << endl;
    } else {
        cout << "Student Record Deleted Successfully" << endl;
    }
}

void showStudents(MYSQL* con) {
    string query = "select * from students";
    if (mysql_query(con, query.c_str())) {
        cout << "Error in Loading Query : " << mysql_error(con) << endl;
        return;
    } else {
        MYSQL_RES* result = mysql_store_result(con);
        if (result == NULL) {
            cout << "Error Fetching Data: " << mysql_error(con) << endl;
            return;
        }

        if (mysql_num_rows(result) == 0) {
            cout << "No Data Found" << endl;
            mysql_free_result(result);
            return;
        }

        vector<vector<string> > students;

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            vector<string> student;
            student.push_back(row[0] ? row[0] : "");
            student.push_back(row[1] ? row[1] : "");
            student.push_back(row[2] ? row[2] : "");
            students.push_back(student);
        }
        mysql_free_result(result);

        cout << "Student Details \n\n";

        cout << left << setw(10) << setfill(' ') << "ID" << setw(25) << setfill(' ') << "Name" << setw(15) << setfill(' ') << "Phone" << endl;
        printDecor();
        for (size_t i = 0; i < students.size(); ++i) {
            cout << left << setw(10) << setfill(' ') << students[i][0]
                 << setw(25) << setfill(' ') << students[i][1]
                 << setw(15) << setfill(' ') << students[i][2] << endl;
        }
    }
}

string checkForStudent(const string& studentName,MYSQL* con){
	string query = "SELECT studentId FROM students WHERE studentName = '" + studentName + "'";
	if (mysql_query(con, query.c_str())) {
        cout << "Error in Executing Query: " << mysql_error(con) << endl;
        return "";
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (!result) {
        cout << "Error in Fetching Data: " << mysql_error(con) << endl;
        return "";
    }
    if (mysql_num_rows(result) == 0) {
        	cout << "No Student Found" << endl;
       	 	mysql_free_result(result);
        	return "";
    }
    MYSQL_ROW row;
    row=mysql_fetch_row(result);
    string studentId=row[0];
    
    return studentId;
    
}

int checkForBook(const string& bookName,MYSQL* con){
	string query = "SELECT * FROM books WHERE bookName = '" + bookName + "'";
	if (mysql_query(con, query.c_str())) {
        cout << "Error in Executing Query: " << mysql_error(con) << endl;
        return 0;
    }
    MYSQL_RES* result = mysql_store_result(con);
    if (!result) {
        cout << "Error in Fetching Data: " << mysql_error(con) << endl;
        return 0;
    }
    if (mysql_num_rows(result) == 0) {
        	cout << "No Book Found" << endl;
       	 	mysql_free_result(result);
        	return 0;
    }
    MYSQL_ROW row;
	row = mysql_fetch_row(result);
    
    if(atoi(row[1])<1){
    	cout<<"No Book Found"<<endl;
		return 0;
	}
    
    return 1;
}

void issueBook(const string& bookName,const string& studentId,const string& studentName,MYSQL* con){
	string query="insert into issue (bookName,studentId,studentName,issueDate) values ('"+bookName+"','"+studentId+"','"+studentName+"',curdate())";
	
	if(mysql_query(con,query.c_str())){
		cout<<"FAILED"<<mysql_error(con)<<endl;
		return;
	}
	else{
		cout<<"BOOK Issued"<<endl;
		string query="update books set quantity = quantity - 1 where bookName = '"+bookName+"'";
		if(mysql_query(con,query.c_str())){
			cout<<"Failed to Update Quantity : "<<mysql_error(con)<<endl;
			return;
		}
		else{
			cout<<"Book Quantity Decreased by 1"<<endl;
		}
	}
}




tm stringToTm(const string& dateStr) {
    tm tm = {};
    stringstream ss(dateStr);
    ss >> tm.tm_year;
    ss.ignore(1, '-'); // Ignore the dash
    ss >> tm.tm_mon;
    ss.ignore(1, '-'); // Ignore the dash
    ss >> tm.tm_mday;
    tm.tm_year -= 1900; // tm_year is years since 1900
    tm.tm_mon -= 1; // tm_mon is 0-based
    tm.tm_isdst = -1; // Not set by get_time, but required by mktime
    return tm;
}


int daysBetween(const string& date1, const string& date2) {
    // Convert strings to tm structures
  	tm tm1 = stringToTm(date1);
    tm tm2 = stringToTm(date2);

    // Convert tm structures to time_t
   	time_t time1 = mktime(&tm1);
   	time_t time2 = mktime(&tm2);

   	// Calculate the difference in seconds
   	double difference = difftime(time2, time1);

   	// Convert the difference from seconds to days
   	return difference / (60 * 60 * 24);
}
		
string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}		
		
void checkFine(MYSQL* con){
	
    string query = "select * from issue";
    if (mysql_query(con, query.c_str())) {
        cout << "Error in Loading Query : " << mysql_error(con) << endl;
        return;
    } else {
        MYSQL_RES* result = mysql_store_result(con);
        if (result == NULL) {
            cout << "Error Fetching Data: " << mysql_error(con) << endl;
            return;
        }

        if (mysql_num_rows(result) == 0) {
            cout << "No Data Found" << endl;
            mysql_free_result(result);
            return;
        }
		

		string currentDate;
		string query="select curdate()";
		if(mysql_query(con,query.c_str())){
			cout<<"ERROR EXECUING QUERY : "<<mysql_error(con);
		}
		else{
			MYSQL_RES* result=mysql_store_result(con);
			MYSQL_ROW row=mysql_fetch_row(result);
			currentDate=row[0];
			cout<<currentDate<<"\n\n";
		}
 		
    	cout << "Fine Details \n\n";
    	cout<<"Fine is 30/- Per Day After 7 Days of Issue \n\n";
		
        vector<vector<string> > students;

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            vector<string> student;
            student.push_back(row[0] ? row[0] : "");
            student.push_back(row[1] ? row[1] : "");
            student.push_back(row[2] ? row[2] : "");
            student.push_back(row[2] ? row[3] : "");
            student.push_back(row[2] ? row[4] : "");
             student.push_back(currentDate);
            int daysDiff = daysBetween(row[4], currentDate);
            student.push_back(intToString(daysDiff));
            if(daysDiff>7){
            	student.push_back(intToString((daysDiff-7)*30));
			}
			else{
				student.push_back(intToString(0));
			}
            students.push_back(student);
        }
        mysql_free_result(result);
		
		printDecor();
        cout << left << setw(10) << setfill(' ') << "Issue ID" 
		<< setw(30) << setfill(' ') << "Book Name" 
		<< setw(15) << setfill(' ') << "Student Id" 
		<< setw(20) << setfill(' ') << "Student Name" 
		<< setw(15) << setfill(' ') << "Issue Date"
		<<setw(15) << setfill(' ')<< "Current Date"
		<<setw(10)<<setfill(' ')<< "Days"
		<<setw(15)<<setfill(' ')<< "Fine"
		<< endl;
        printDecor();
        for (size_t i = 0; i < students.size(); ++i) {
            cout << left << setw(10) << setfill(' ') << students[i][0]
                 << setw(30) << setfill(' ') << students[i][1]
                 << setw(15) << setfill(' ') << students[i][2] 
                 << setw(20) << setfill(' ') << students[i][3]
				 << setw(15) << setfill(' ') << students[i][4]  
				 << setw(15) << setfill(' ') << students[i][5]  
				 << setw(10) << setfill(' ') << students[i][6]  
				 << setw(10) << setfill(' ') << students[i][7]
				 << endl;
        }
    }


}


void returnBook(const string& studentName, const string& bookName, MYSQL* con) {
    string studentId = checkForStudent(studentName, con);
    if (studentId.empty()) {
        cout << "No Student with Name: " << studentName << endl;
        return;
    }

    // Check if the student has issued the book
    string checkIssueQuery = "SELECT issueDate FROM issue WHERE studentId = '" + studentId + "' AND bookName = '" + bookName + "'";
    if (mysql_query(con, checkIssueQuery.c_str())) {
        cout << "Error in Checking Issue Status: " << mysql_error(con) << endl;
        return;
    }

    MYSQL_RES* issueResult = mysql_store_result(con);
    if (issueResult == NULL) {
        cout << "Error in Retrieving Issue Data: " << mysql_error(con) << endl;
        return;
    }

    if (mysql_num_rows(issueResult) == 0) {
        cout << "No Record of Issued Book for this Student" << endl;
        mysql_free_result(issueResult);
        return;
    }

    MYSQL_ROW issueRow = mysql_fetch_row(issueResult);
    string issueDate = issueRow ? issueRow[0] : "";
    mysql_free_result(issueResult);

    // Calculate fine if any (30 INR per day after 7 days)
    time_t now = time(0);
    tm* nowTm = localtime(&now);

    int year, month, day;
    sscanf(issueDate.c_str(), "%d-%d-%d", &year, &month, &day);
    tm issueTm = {0};
    issueTm.tm_year = year - 1900;
    issueTm.tm_mon = month - 1;
    issueTm.tm_mday = day;

    double seconds = difftime(mktime(nowTm), mktime(&issueTm));
    int days = seconds / (60 * 60 * 24);
    int fine = (days > 7) ? (days - 7) * 30 : 0;

    // Return the book
    string returnQuery = "DELETE FROM issue WHERE studentId = '" + studentId + "' AND bookName = '" + bookName + "'";
    if (mysql_query(con, returnQuery.c_str())) {
        cout << "Error in Returning Book: " << mysql_error(con) << endl;
        return;
    }

    // Update the book quantity
    string updateQuery = "UPDATE books SET quantity = quantity + 1 WHERE bookName = '" + bookName + "'";
    if (mysql_query(con, updateQuery.c_str())) {
        cout << "Error in Updating Book Quantity: " << mysql_error(con) << endl;
    } else {
        cout << "Book Returned Successfully" << endl;
        if (fine > 0) {
            cout << "Fine: " << fine << " INR" << endl;
        }
    }
}

void adminPanel(MYSQL* con) {
    bool exit = false;
    string bookName,studentId,studentName,studentPhn,issueDate;
    int quantity;
    
    while (!exit) {
        system("cls");
        int ch;
        printDecor();
        printCentered("Welcome To Admin Panel");
        printDecor();
        cout << "1) Add Book" << endl;
        cout << "2) Delete Book" << endl;
        cout << "3) Show All Books" << endl;
        cout << "4) Add Student" << endl;
        cout << "5) Delete Student" << endl;
        cout << "6) Show All Students" << endl;
        cout << "7) Issue a Book for Student"<<endl;
        cout << "8) Return Book from Student"<<endl;
        cout << "9) Check for Fines"<<endl;
        cout << "10) Exit" << endl;
        cout << "Enter Choice : ";
        cin >> ch;
        
        switch (ch) {
            case 1:
                cin.ignore(); // Ignore any remaining newline characters
                cout << "Enter Book Name : ";
                getline(cin, bookName); // Use getline to read the book name
                cout << "Enter Quantity  : ";
                cin >> quantity;
                addBook(bookName, quantity, con);
                Sleep(2000);
                break;
            case 2:
            	cin.ignore();
            	cout<<"Enter Book Name : ";
            	getline(cin,bookName);
            	removeBook(bookName,con);
            	  Sleep(3000);
            	break;
            case 3:
            	showBooks(con);
            	cout<<endl;
            	system("pause");
            	break;
            case 4:
            	cout<<  "Enter Student Id        : ";
            	cin>>studentId;
            	cin.ignore();
                cout << "Enter Student Name      : ";
                getline(cin,studentName);
                cout << "Enter Student Phone No. : ";
                getline(cin,studentPhn);
                addStudent(studentId,studentName,studentPhn,con);
            	break;
            case 5:
            	cout<<  "Enter Student Id   : ";
            	cin>>studentId;
                removeStudent(studentId,con);
                Sleep(2000);
            	break;
            case 6:
            	showStudents(con);
            	cout<<endl;
            	system("pause");
            	break;
            case 7:
            	cout<<"Enter Student Name : ";
            	cin.ignore();
            	getline(cin,studentName);
            	studentId=checkForStudent(studentName,con);
            	if(studentId != ""){
            		cout<<"Enter Book Name    : ";
            		getline(cin,bookName);
            		if(checkForBook(bookName,con)){
            			issueBook(bookName,studentId,studentName,con);		
					}
						
				}
				
            	
            	Sleep(2000);
            	break;
             case 8:
        cout << "Enter Student Name: ";
        cin.ignore();
        getline(cin, studentName);
        cout << "Enter Book Name: ";
        getline(cin, bookName);
        returnBook(studentName, bookName, con);
        Sleep(2000);
        break;
            case 9:
            	checkFine(con);
            	system("pause");
            	break;
            case 10:
                cout << "Logged Out";
                exit = true;
                Sleep(1000);
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                Sleep(2000);
                break;
        }
    }
}

void admin(MYSQL* con) {
    string usn, pass;
    cout << "Enter Username : ";
    cin >> usn;
    cout << "Enter Password : ";
    cin >> pass;
    if (adminLogin(usn, pass, con)) {
        cout << "Login Success as Admin" << endl;
        Sleep(2000);
        adminPanel(con);
    } else {
        cout << "Username or Password Incorrect" << endl << "Try Again !" << endl;
        Sleep(2000);
    }
}

int main() {
    MYSQL* con = mysql_init(NULL);
    if (!con) {
        cout << "Error: mysql_init failed!" << endl;
        return 1;
    }

    if (mysql_real_connect(con, HOST, USER, PASSWORD, DB, 3306, NULL, 0) == NULL) {
        cout << "Error: mysql_real_connect failed!" << endl;
        cout << "Error: " << mysql_error(con) << endl;
        mysql_close(con);
        return 1;
    } else {
        cout << "Database Connection Established Successfully !!" << endl;
    }

    Sleep(2000);
    bool exit = false;
    while (!exit) {
        system("cls");
        int ch;
        printDecor();
        printCentered("Welcome To Library Management System");
        printDecor();
        cout << "1) Admin" << endl;
        cout << "2) Exit" << endl;
        cout << "Enter Choice : ";
        cin >> ch;
        
        switch (ch) {
            case 1:
                admin(con);
                break;
            case 2:
                cout << "Exited" << endl;
                exit = true;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                Sleep(2000);
                break;
        }
    }

    mysql_close(con);
    return 0;
}

