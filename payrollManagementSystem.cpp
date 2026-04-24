#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

class Employee {
public:
    int code;
    string name, address, phone, designation;
    int day, month, year;
    char grade;
    float basic, loan;

    void input() {
        cout << "\nEnter Employee Code: ";
        cin >> code;
        cin.ignore();

        cout << "Name: ";
        getline(cin, name);

        cout << "Address: ";
        getline(cin, address);

        cout << "Phone: ";
        getline(cin, phone);

        cout << "Joining Date (DD MM YYYY): ";
        cin >> day >> month >> year;

        cout << "Designation: ";
        cin.ignore();
        getline(cin, designation);

        cout << "Grade (A-E): ";
        cin >> grade;

        cout << "Basic Salary: ";
        cin >> basic;

        cout << "Loan: ";
        cin >> loan;
    }

    void display() {
        cout << "\nCode: " << code
             << "\nName: " << name
             << "\nAddress: " << address
             << "\nPhone: " << phone
             << "\nDOJ: " << day << "/" << month << "/" << year
             << "\nDesignation: " << designation
             << "\nGrade: " << grade
             << "\nBasic Salary: " << basic
             << "\nLoan: " << loan << endl;
    }

    void save() {
        ofstream file("employee.txt", ios::app);
        file << code << "|" << name << "|" << address << "|"
             << phone << "|" << day << " " << month << " " << year
             << "|" << designation << "|" << grade
             << "|" << basic << "|" << loan << endl;
        file.close();
    }

    static vector<Employee> loadAll() {
        vector<Employee> list;
        ifstream file("employee.txt");

        Employee e;
        while (file >> e.code) {
            file.ignore();
            getline(file, e.name, '|');
            getline(file, e.address, '|');
            getline(file, e.phone, '|');
            file >> e.day >> e.month >> e.year;
            file.ignore();
            getline(file, e.designation, '|');
            file >> e.grade >> e.basic >> e.loan;
            list.push_back(e);
        }
        return list;
    }
};

// ================= MENU =================

void menu() {
    int choice;
    vector<Employee> employees;

    while (true) {
        cout << "\n===== PAYROLL SYSTEM =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Show All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Salary Slip\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Employee e;
            e.input();
            e.save();
            cout << "Saved Successfully!\n";
        }

        else if (choice == 2) {
            employees = Employee::loadAll();
            for (auto &e : employees) {
                e.display();
                cout << "------------------\n";
            }
        }

        else if (choice == 3) {
            int id;
            cout << "Enter Employee Code: ";
            cin >> id;

            employees = Employee::loadAll();
            bool found = false;

            for (auto &e : employees) {
                if (e.code == id) {
                    e.display();
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Employee Not Found!\n";
        }

        else if (choice == 4) {
            int id;
            cout << "Enter Employee Code: ";
            cin >> id;

            employees = Employee::loadAll();

            for (auto &e : employees) {
                if (e.code == id) {
                    float HRA = 0.05 * e.basic;
                    float DA = 0.05 * e.basic;
                    float PF = 0.02 * e.basic;
                    float LD = 0.15 * e.loan;

                    float net = (e.basic + HRA + DA) - (PF + LD);

                    cout << "\n===== SALARY SLIP =====\n";
                    cout << "Name: " << e.name << endl;
                    cout << "Basic: " << e.basic << endl;
                    cout << "HRA: " << HRA << endl;
                    cout << "DA: " << DA << endl;
                    cout << "PF: " << PF << endl;
                    cout << "Loan Deduction: " << LD << endl;
                    cout << "Net Salary: " << net << endl;
                }
            }
        }

        else if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid Choice!\n";
        }
    }
}

// ================= MAIN =================

int main() {
    menu();
    return 0;
}
