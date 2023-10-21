#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Student {
private:
    string name;
    string prn;
    double sub1Marks;
    double sub2Marks;
    double sub3Marks;
    double cgpa;

public:
    Student(const string& _name, const string& _prn, double _sub1, double _sub2, double _sub3) 
        : name(_name), prn(_prn), sub1Marks(_sub1), sub2Marks(_sub2), sub3Marks(_sub3) {
        // Calculate CGPA out of 10
        cgpa = (sub1Marks + sub2Marks + sub3Marks) / 30.0 * 10.0;
    }

    string getName() const {
        return name;
    }

    string getPRN() const {
        return prn;
    }

    double getSub1Marks() const {
        return sub1Marks;
    }

    double getSub2Marks() const {
        return sub2Marks;
    }

    double getSub3Marks() const {
        return sub3Marks;
    }

    double getCGPA() const {
        return cgpa;
    }
};

class StudentReport {
public:
    void displayStudentInfo(const Student& student) {
        cout << "Name: " << student.getName() << endl;
        cout << "PRN: " << student.getPRN() << endl;
        cout << "Subject 1 Marks: " << student.getSub1Marks() << endl;
        cout << "Subject 2 Marks: " << student.getSub2Marks() << endl;
        cout << "Subject 3 Marks: " << student.getSub3Marks() << endl;
        cout << "CGPA: " << student.getCGPA() << endl;
    }
};

class Statistics {
public:
    static double findAverageCGPA(const vector<Student>& students) {
        if (students.empty()) {
            return 0.0;
        }

        double totalCGPA = 0.0;
        for (const Student& student : students) {
            totalCGPA += student.getCGPA();
        }

        return totalCGPA / students.size();
    }
};

class StudentManager {
private:
    vector<Student> students;

public:
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    const vector<Student>& getStudents() const {
        return students;
    }

    void showReportCard() {
        if (students.empty()) {
            cout << "No student data available." << endl;
            return;
        }

        StudentReport report;
        for (const Student& student : students) {
            report.displayStudentInfo(student);
            cout << "--------------------------" << endl;
        }
    }

    void findHighestScore() {
        if (students.empty()) {
            cout << "No student data available." << endl;
            return;
        }

        auto maxStudent = max_element(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getCGPA() < b.getCGPA();
        });

        StudentReport report;
        cout << "Highest Scorer:" << endl;
        report.displayStudentInfo(*maxStudent);
    }

    void findLowestScore() {
        if (students.empty()) {
            cout << "No student data available." << endl;
            return;
        }

        auto minStudent = min_element(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getCGPA() < b.getCGPA();
        });

        StudentReport report;
        cout << "Lowest Scorer:" << endl;
        report.displayStudentInfo(*minStudent);
    }

    void findStudentByName(const string& name) {
        if (students.empty()) {
            cout << "No student data available." << endl;
            return;
        }

        auto it = find_if(students.begin(), students.end(), [&name](const Student& student) {
            return student.getName() == name;
        });

        if (it != students.end()) {
            StudentReport report;
            report.displayStudentInfo(*it);
        } else {
            cout << "Student with name '" << name << "' not found." << endl;
        }
    }

    void sortStudentsByCGPA() {
        if (students.empty()) {
            cout << "No student data available." << endl;
            return;
        }

        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getCGPA() > b.getCGPA();
        });
    }

    void inputStudentDataManually() {
        string name, prn;
        double sub1, sub2, sub3;

        cout << "Enter Student Name: ";
        cin >> name;
        cout << "Enter PRN: ";
        cin >> prn;
        cout << "Enter Subject 1 Marks: ";
        cin >> sub1;
        cout << "Enter Subject 2 Marks: ";
        cin >> sub2;
        cout << "Enter Subject 3 Marks: ";
        cin >> sub3;

        Student student(name, prn, sub1, sub2, sub3);
        addStudent(student);
        cout << "Student data added successfully." << endl;
    }

    void importStudentDataFromFile() {
        string filename;
        cout << "Enter the filename to import data from: ";
        cin >> filename;

        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open the file." << endl;
            return;
        }

        string name, prn;
        double sub1, sub2, sub3;
        while (file >> name >> prn >> sub1 >> sub2 >> sub3) {
            Student student(name, prn, sub1, sub2, sub3);
            addStudent(student);
        }

        file.close();
        cout << "Data imported successfully." << endl;
    }

    void saveStudentDataToFile() {
        if (students.empty()) {
            cout << "No student data available to save." << endl;
            return;
        }

        string filename;
        cout << "Enter the filename to save data to: ";
        cin >> filename;

        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to create or open the file." << endl;
            return;
        }

        for (const Student& student : students) {
            file << student.getName() << " " << student.getPRN() << " "
                 << student.getSub1Marks() << " " << student.getSub2Marks() << " " << student.getSub3Marks() << endl;
        }

        file.close();
        cout << "Data saved successfully." << endl;
    }
};

int main() {
    StudentManager manager;
    int choice;

    do {
        cout << "====== Student Grading System Menu ======" << endl;
        cout << "1. Add Student Data Manually" << endl;
        cout << "2. Import Student Data from File" << endl;
        cout << "3. Show Class Report Card" << endl;
        cout << "4. Find Highest Scorer" << endl;
        cout << "5. Find Lowest Scorer" << endl;
        cout << "6. Find Student by Name" << endl;
        cout << "7. Sort Students by CGPA" << endl;
        cout << "8. Save Student Data to File" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.inputStudentDataManually();
                break;
            case 2:
                manager.importStudentDataFromFile();
                break;
            case 3:
                manager.showReportCard();
                break;
            case 4:
                manager.findHighestScore();
                break;
            case 5:
                manager.findLowestScore();
                break;
            case 6:
                {
                    string searchName;
                    cout << "Enter the name to search: ";
                    cin >> searchName;
                    manager.findStudentByName(searchName);
                }
                break;
            case 7:
                manager.sortStudentsByCGPA();
                cout << "Students sorted by CGPA." << endl;
                break;
            case 8:
                manager.saveStudentDataToFile();
                break;
            case 0:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
