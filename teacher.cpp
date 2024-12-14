#include "libs.h"

Teacher::Teacher(const string& username, const string& password)
    : User(username, password) {}

Teacher::Teacher(ifstream& inFile) {
    getline(inFile, username);
    getline(inFile, password);
}

void Teacher::displayMenu() const {
    cout << "Teacher Menu: \n"; 
    cout << "1. View Courses\n";
    cout << "2. View Students in Course\n";
    cout << "3. Add Student to Course\n";
    cout << "4. Remove Student from Course\n";
    cout << "5. Assign Grade to Student\n";
    cout << "6. View Student`s Grades\n";
    cout << "7. Exit\n";
}

void Teacher::saveToFile(ofstream& outFile) const {
    outFile << username << '\n';
    outFile << password << '\n';
}

void Teacher::viewCourses(const string& fileName) const {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Cannot open file.\n";
        return;
    }

    string courseName;
    cout << "Courses:\n";
    while (getline(inFile, courseName)) {
        if (courseName == "END") break; // Закінчення списку курсів
        cout << "- " << courseName << '\n';
    }
}

void Teacher::viewStudentsInCourse(const string& fileName) const {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Cannot open file.\n";
        return;
    }

    string courseName, studentName, targetCourse;
    cout << "Enter course name: ";
    cin.ignore();
    getline(cin, targetCourse);

    while (getline(inFile, courseName)) {
        if (courseName == targetCourse) {
            cout << "Students in " << targetCourse << ":\n";
            while (getline(inFile, studentName) && studentName != "END") {
                cout << "- " << studentName << '\n';
            }
            return;
        }
        else {
            // Пропускаємо студентів курсу
            while (getline(inFile, studentName) && studentName != "END");
        }
    }
    cout << "Course not found.\n";
}

void Teacher::addStudentToCourse(const string& fileName) {
    string courseName, studentName;
    cout << "Enter course name: ";
    cin.ignore();
    getline(cin, courseName);
    cout << "Enter student name: ";
    getline(cin, studentName);

    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Cannot open file.\n";
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cerr << "Error: Cannot open temporary file.\n";
        return;
    }

    string currentCourse, student;
    bool found = false;
    while (getline(inFile, currentCourse)) {
        tempFile << currentCourse << '\n';
        if (currentCourse == courseName) {
            found = true;
            while (getline(inFile, student) && student != "END") {
                tempFile << student << '\n';
            }
            tempFile << studentName << '\n'; // Додаємо нового студента
            tempFile << "END\n";
        }
        else {
            while (getline(inFile, student) && student != "END") {
                tempFile << student << '\n';
            }
            tempFile << "END\n";
        }
    }

    if (!found) {
        tempFile << courseName << '\n';
        tempFile << studentName << '\n';
        tempFile << "END\n";
    }

    inFile.close();
    tempFile.close();
    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());
    cout << "Student added successfully.\n";
}

void Teacher::removeStudentFromCourse(const string& fileName) {
    string courseName, studentName;
    cout << "Enter course name: ";
    cin.ignore();
    getline(cin, courseName);
    cout << "Enter student name: ";
    getline(cin, studentName);

    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Cannot open file.\n";
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cerr << "Error: Cannot open temporary file.\n";
        return;
    }

    string currentCourse, student;
    while (getline(inFile, currentCourse)) {
        tempFile << currentCourse << '\n';
        if (currentCourse == courseName) {
            while (getline(inFile, student) && student != "END") {
                if (student != studentName) {
                    tempFile << student << '\n';
                }
            }
            tempFile << "END\n";
        }
        else {
            while (getline(inFile, student) && student != "END") {
                tempFile << student << '\n';
            }
            tempFile << "END\n";
        }
    }

    inFile.close();
    tempFile.close();
    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());
    cout << "Student removed successfully.\n";
}

void Teacher::assignGradeToStudent(const string& fileName) {
    string courseName, studentName;
    int grade;

    cout << "Enter course name: ";
    cin.ignore();
    getline(cin, courseName);

    cout << "Enter student name: ";
    getline(cin, studentName);

    cout << "Enter grade: ";
    cin >> grade;

    ofstream outFile(fileName, ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open " << fileName << " for writing.\n";
        return;
    }

    outFile << courseName << "|" << studentName << "|" << grade << "\n";
    outFile.close();

    cout << "Grade assigned successfully to " << studentName << " in course " << courseName << ".\n";
}
