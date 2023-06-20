#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <sstream>
#include <stdexcept>

using namespace std;

char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "12345";

void displayInsertedData(MYSQL* obj) {
    MYSQL_RES* result;
    MYSQL_ROW row;

    string sql_query = "SELECT id, name, email FROM students";

    if (mysql_query(obj, sql_query.c_str())) {
        throw runtime_error("Error executing SELECT query: " + string(mysql_error(obj)));
    }

    result = mysql_store_result(obj);
    if (result) {
        cout << endl << "Students are:" << endl << endl;
        while ((row = mysql_fetch_row(result))) {
            cout << " " << row[0] << " " << row[1] << " " << row[2] << endl;
        }
        mysql_free_result(result);
    } else {
        cout << "No students found" << endl;
    }
}

void registerStudent(MYSQL* obj) {
    string username, email;
    cin.ignore(); // Ignore the newline character from previous input
    cout << "Username: ";
    getline(cin, username);
    cout << "Email: ";
    getline(cin, email);

    string sql_query = "INSERT INTO students(name,email) VALUES ('" + username + "', '" + email + "')";

    if (mysql_query(obj, sql_query.c_str())) {
        throw runtime_error("Failed to register student: " + string(mysql_error(obj)));
    } else {
        cout << "Student registered successfully" << endl;
    }
}

void deleteStudent(int userId, MYSQL* obj) {
    stringstream ss;
    ss << userId;
    string userIdStr = ss.str();

    string sql_query = "DELETE FROM students WHERE id = " + userIdStr;

    if (mysql_query(obj, sql_query.c_str())) {
        throw runtime_error("Failed to delete student: " + string(mysql_error(obj)));
    } else {
        if (mysql_affected_rows(obj) > 0) {
            cout << "Student deleted successfully" << endl;
        } else {
            cout << "No student found with ID: " << userId << endl;
        }
    }
}

void updateStudent(int userId, MYSQL* obj) {
    string name, email;
    cin.ignore(); // Ignore the newline character from previous input
    cout << "Enter new name: ";
    getline(cin, name);
    cout << "Enter new email: ";
    getline(cin, email);
    
    stringstream ss;
    ss << userId;
    string userIdStr = ss.str();

    string sql_query = "UPDATE students SET name='" + name + "', email='" + email + "' WHERE id=" +userIdStr;

    if (mysql_query(obj, sql_query.c_str())) {
        throw runtime_error("Failed to update student: " + string(mysql_error(obj)));
    } else {
        if (mysql_affected_rows(obj) > 0) {
            cout << "Student updated successfully" << endl;
        } else {
            cout << "No student found with ID: " << userId << endl;
        }
    }
}

void welcome(){
 cout <<endl<< "    1. Display students" << endl;
        cout << "    2. Insert student" << endl;
        cout << "    3. Delete student" << endl;
        cout << "    4. Update student" << endl;
        cout << "    0. Exit" << endl;	
}

int main() {
    MYSQL* obj; // one to manage mysql session

    int id;
    string names;
    string email;
    bool exit = false;

    try {
        if (!(obj = mysql_init(0))) {
            throw runtime_error("ERROR: Mysql object could not be created");
        }

        if (!mysql_real_connect(obj, HOST, USER, PASS, "revision", 3306, NULL, 0)) {
            throw runtime_error("Failed to connect to the database: " + string(mysql_error(obj)));
        }

        cout << "Connected to the database successfully!" << endl << endl;

        int choice;
        welcome();

        cin >> choice;
        
        while(choice!=0){
        	switch (choice) {
            case 1:
                displayInsertedData(obj);
                break;
            case 2:
                registerStudent(obj);
                break;
            case 3:
                int userId;
                cout << "Enter the ID of the student to delete: ";
                cin >> userId;
                deleteStudent(userId, obj);
                break;
            case 4:
                int updateId;
                cout << "Enter the ID of the student to update: ";
                cin >> updateId;
                updateStudent(updateId, obj);
                break;
            default:
                cout << endl << "Invalid choice" << endl;
                break;
        }
        
       welcome();

        cin >> choice;
		}
		
cout<<endl<<"Good Byee!!!"<<endl<<endl;		

    } catch (const exception& e) {
        cout << "An exception occurred: " << e.what() << endl;
    }

    return 0;
}
