#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>  // For formatting output (setw, left, right)

using namespace std;

//struct for Teacher
struct Teacher{
  string name;
  string email;
  string id;
};
// Define the structure for Teacher
struct TeacherPassword {
    string teacherId;
    string password;  
};
// Structure to hold course information for a logged-in teacher
struct loginedTeacherCourses {
    string courseTitle;
    string courseCode;
    string department;
    int duration;        // Duration in weeks
    int creditHour;      // Credit hour
    string semester;
    string status;
};

// Structure to represent the logged-in teacher with their courses
struct loginedTeacher {
    string teacherId;
    string password;
    vector<loginedTeacherCourses> courses;  // A teacher can have multiple courses
};


// Define the structure for Course
struct Course {
    string courseTitle;
    string courseCode;
    string department;
    int duration;        // Duration in weeks
    int creditHour;      // Credit hour
    string semester;
    string status;
    Teacher teacher;     // Teacher as a struct inside Course
};

//Define the structure for student 
struct Student{
    string name;
    string id;
    string department;
    string email;
    string password;
    int year;
    vector<Course> courses;
};
// Global vector to store courses
vector<Course> courses;

//Global vector to store list of students based on their department
vector<Student> students;

//Global vector to store teacher password
vector<TeacherPassword> teacherPasswords;

//Current logined Teacher
loginedTeacher currentTeacher;
// Define a global variable to hold the current logged-in student's information
Student currentStudent;

//Function prototypes for the main section
void displayMainMenu();
void processMainMenu();
void adminSection();
void teacherSection();
void studentSection();

// Function prototypes for admin functionalities
void displayAdminMenu();
void processAdminMenu(bool &isInsideAdminSection);
void addCourseForAdmin();
void viewAllCourses();
void deleteCourse();
void updateCourse();
bool isCourseCodeUnique(const string& courseCode);
bool isValidInteger(int& value);
void loadCoursesFromFile();
void saveCoursesToFile();

// Function prototypes for admin functionalities
void displayAdminMenu();
void processAdminMenu();
void addCourseForAdmin();
void viewAllAssignedCourses();
void deleteCourse();
void updateCourse();
bool isCourseCodeUnique(const string& courseCode);
bool isValidInteger(int& value);
void loadCoursesFromFile();
void saveCoursesToFile();
void addStudent();


//Function prototypes for teacher functionalities
bool checkTeacherCredentials();
bool teacherLogin();
void viewAllAssignedCourses();
void displayTeacherMenu();
void processTeacherMenu(bool* isUserInsideTeacherSection);
void savePasswordsToFileForTeachers();
void loadTeacherPasswordsForTeachers();
void showAllStudents();
Teacher* savePasswordsToFileForTeachers(string teacherId);
Course* searchTeacherById(string &id);


//Function prototypes for Student functionalities
bool checkStudentCredentials();
bool teacherLogin();
bool studentLogin();
void viewMyCourses();
void viewAllCoursesForStudent();
void displayStudentMenu();
void processStudentMenu();
void addCoursesForStudent();
void dropCourse();
void viewGrades();
Student* savePasswordsToFileForStudent(string teacherId);
Student* searchStudentById(const string& studentId); 
void saveStudentsToFile();
void loadStudentsFromFile();
void rewriteStudentInfo();


//Function to generate a password
string generateRandomPassword(int length = 12) {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string password;
    for (int i = 0; i < length; ++i) {
        password += chars[rand() % chars.size()];
    }
    return password;
}

 
//Function to handle Invalid input 2
void handleInvalidInput();

 
// Main function
int main() {
    // Load existing courses from the file at the start
    loadCoursesFromFile();
    // Load existing Teacher from the file at the start
    loadTeacherPasswordsForTeachers();
    // Load students when the application starts
    loadStudentsFromFile();

    // Admin section loop
    while (true) {
       processMainMenu(); 
    }
    return -1;
}


// Display the main menu
void displayMainMenu() {
    cout << "\n--- Welcome to the Course Management System ---\n";
    cout << "Please choose your role:\n";
    cout << "1. Admin\n";
    cout << "2. Teacher\n";
    cout << "3. Student\n";
    cout << "4. Exit\n";
    cout << endl;
    cout << "Enter you choice: ";
   
}

// Process the main menu input
void processMainMenu() {
    displayMainMenu();
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            adminSection();
            break;
        case 2:
            teacherSection();
            break;
        case 3:
            studentSection();
            break;
        case 4:
            cout << "Exiting the application. Goodbye!\n";
            exit(0);
        default:
          handleInvalidInput(); 
            break;
    }
}

// Admin section 
void adminSection() { 
    bool isInsideAdminSection = true;
    while(isInsideAdminSection){
        processAdminMenu(isInsideAdminSection); 
    } 
}

// Display admin menu options
void displayAdminMenu() {
    cout << "\n------ Welcome to Admin Section ------\n";
    cout << "1. Add Course\n";
    cout << "2. View All Courses\n";
    cout << "3. Delete Course\n";
    cout << "4. Update Course\n";
    cout << "5. Add a student\n";
    cout << "6. Show all students\n";
    cout << "7. Exit Admin Section\n";
    cout << "Enter your choice: ";
}

// Handle admin menu inputs
void processAdminMenu(bool &isInsideAdminSection) {
    displayAdminMenu();
    int choice;
    cin >> choice;
    switch (choice) {
        case 1: addCourseForAdmin(); break;
        case 2: viewAllCourses(); break;
        case 3: deleteCourse(); break;
        case 4: updateCourse(); break;
        case 5: addStudent(); break;
        case 6: showAllStudents(); break;
        case 7: 
            cout << "Exiting admin section...\n";
             isInsideAdminSection = false;
            return; 
            break;
        default:
            handleInvalidInput(); 
            break;
    }
}



//Teacher Section
void teacherSection(){

    if(courses.empty()){
       cout << "There is no courses assinged.\n";
       return;
    }
    if(!teacherLogin()){
       cout << "Teacher not found or password is incorrect.\n";   
       return;     
    }
   bool isUserInsideTeacherSection = true;
   while (isUserInsideTeacherSection) {
    processTeacherMenu(& isUserInsideTeacherSection);
  } 
}


// Display admin menu options
void displayTeacherMenu() {
    cout << "\n------ Welcome to Teachers' Section ------\n";
    cout << "1. View all courses you are assigned to\n";
    cout << "2. Exit Admin Section\n";
    cout << "Enter your choice: ";
}

// Handle admin menu inputs
void processTeacherMenu(bool* isUserInsideTeacherSection) {
    displayTeacherMenu();
    int choice;
    cin >> choice;

    switch (choice) {
        case 1: viewAllAssignedCourses(); break;
        case 2: 
            *isUserInsideTeacherSection = false;
            cout << "Exiting admin section...\n";
            break;
        default:
            handleInvalidInput(); 
            break;
    }
}


//Student Section
void studentSection(){
    if(students.empty()){
      cout << "No student in the system. \n";
        return;
    }

    if(!studentLogin()){
      return;
    }
    bool isUserInsideStudentSection = true;
    while (true) {
        processStudentMenu();
    }
}
void displayStudentMenu() {
    cout << "\n------ Welcome to Students' Section ------\n";
    cout << "1. View all courses availble for you\n";
    cout << "2. Add course \n";
    cout << "3. View my courses \n";
    cout << "4. Drop a course \n";
    cout << "5. Exit Admin Section\n";
    cout << "Enter your choice: ";
}

// Handle admin menu inputs
void processStudentMenu() {
    displayStudentMenu();
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:viewAllCoursesForStudent(); break;
        case 2: addCoursesForStudent(); break;
        case 3: viewMyCourses(); break;
        case 4: dropCourse(); break;
        case 5:
            cout << "Exiting admin section...\n";
            return;
            break;
        default:
            handleInvalidInput(); 
            break;
    }
}




// Add a new course with teacher information
void addCourseForAdmin() {
    string courseTitle, courseCode, department, semester, status;
    string teacherName, teacherID, teacherEmail;
    int duration, creditHour;

    cout << "Enter Course Title: ";
    cin.ignore();
    getline(cin, courseTitle);

    cout << "Enter Course Code: ";
    cin >> courseCode;

    // Check for duplicate course code
    if (!isCourseCodeUnique(courseCode)) {
        cout << "Error: Course code already exists. Please use a unique course code.\n";
        return;
    }

    cout << "Enter Department: ";
    cin.ignore();
    getline(cin, department);

    cout << "Enter Duration (in weeks): ";
    while (!isValidInteger(duration)) {
        cout << "Please enter a valid duration (positive integer): ";
    }

    cout << "Enter Credit Hour: ";
    while (!isValidInteger(creditHour)) {
        cout << "Please enter a valid credit hour (positive integer): ";
    }

    cout << "Enter Semester: ";
    cin.ignore();
    getline(cin, semester);


     status = "assigned"; 
    // Teacher Information
    cout << "Enter Teacher Name: ";
    getline(cin, teacherName);

    cout << "Enter Teacher ID: ";
    getline(cin, teacherID);

    cout << "Enter Teacher Email: ";
    getline(cin, teacherEmail);

    // Create a new Course struct
    Course newCourse = {
        courseTitle, courseCode, department, duration, creditHour, semester, status,
        {teacherName, teacherID, teacherEmail}
    };
    courses.push_back(newCourse);
    
    string passwordForATeacher = generateRandomPassword();
    teacherPasswords.push_back({teacherID, passwordForATeacher});
    // Save courses to the file
    saveCoursesToFile();

    //Save Teacher id and password
    savePasswordsToFileForTeachers();

    cout << "Course added successfully.\n";
}

// View all available courses
void viewAllCourses() {
    cout << "\n--- All Courses ---\n";
    if (courses.empty()) {
        cout << "No courses available.\n";
        return;
    }
    int orderOfCourses = 1;
    for (const auto& course : courses) {
        cout << orderOfCourses << ". Title: " << course.courseTitle
             << ", Code: " << course.courseCode
             << ", Department: " << course.department
             << ", Duration: " << course.duration
             << " weeks, Credit Hour: " << course.creditHour
             << ", semester: " << course.semester
             << ", status: " << course.status
             << ", Teacher: " << course.teacher.name
             << " (ID: " << course.teacher.id
             << ", Email: " << course.teacher.email << ")\n";
        cout << endl;
        orderOfCourses += 1;
    }
}

// Delete a course by course code
void deleteCourse() {
    cout << "Enter Course Code to delete: ";
    string courseCode;
    cin >> courseCode;

    auto it = remove_if(courses.begin(), courses.end(),
                        [&courseCode](const Course& course) {
                            return course.courseCode == courseCode;
                        });
    if (it != courses.end()) {
        courses.erase(it, courses.end());
        saveCoursesToFile();
        cout << "Course deleted successfully.\n";
    } else {
        cout << "Course not found.\n";
    }
}

// Update course details
void updateCourse() {
    cout << "Enter Course Code to update: ";
    string courseCode;
    cin >> courseCode;

    for (auto& course : courses) {
        if (course.courseCode == courseCode) {
            cout << "Updating course details for " << course.courseTitle << "...\n";
            cout << "Enter new Course Title: ";
            cin.ignore();
            getline(cin, course.courseTitle);

            cout << "Enter new Department: ";
            getline(cin, course.department);

            cout << "Enter new Duration (in weeks): ";
            while (!isValidInteger(course.duration)) {
                cout << "Please enter a valid duration (positive integer): ";
            }

            cout << "Enter new Credit Hour: ";
            while (!isValidInteger(course.creditHour)) {
                cout << "Please enter a valid credit hour (positive integer): ";
            }

            cout << "Enter new Semester: ";
            getline(cin, course.semester);

            saveCoursesToFile();
            cout << "Course updated successfully.\n";
            return;
        }
    }
    cout << "Course not found.\n";
}
// Function to add a student to the vector
void addStudent() {
    Student newStudent;

    // Prompt admin for student details
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, newStudent.name); // Allow spaces in the name

    cout << "Enter student ID: ";
    getline(cin, newStudent.id);

    cout << "Enter student department: ";
    getline(cin, newStudent.department);

    cout << "Enter student email: ";
    getline(cin, newStudent.email);

    cout << "Enter student year (e.g., 1 for freshman, 2 for sophomore): ";
    cin >> newStudent.year;

    cin.ignore(); // Clear the input buffer

    // Generate a random password
    newStudent.password = generateRandomPassword();

    // Add the student to the global vector
    students.push_back(newStudent);

    saveStudentsToFile();

    cout << "Student added successfully! Their password is: " << newStudent.password << endl;
}



// Check if course code is unique
bool isCourseCodeUnique(const string& courseCode) {
    for (const auto& course : courses) {
        if (course.courseCode == courseCode) {
            return false;
        }
    }
    return true;
}

// Validate integer input
bool isValidInteger(int& value) {
    cin >> value;
    if (cin.fail() || value <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

// Load courses from file
void loadCoursesFromFile() {
    ifstream coursesFile("courses.txt");
    if (coursesFile.is_open()) {
        string line;
        while (getline(coursesFile, line)) {
            stringstream ss(line);
            string courseTitle, courseCode, department, semester, status, teacherName, teacherID, teacherEmail;
            int duration, creditHour;
            getline(ss, courseTitle, ',');
            getline(ss, courseCode, ',');
            getline(ss, department, ',');
            ss >> duration; ss.ignore();
            ss >> creditHour; ss.ignore();
            getline(ss, semester, ',');
            getline(ss, status, ',');
            getline(ss, teacherName, ',');
            getline(ss, teacherID, ',');
            getline(ss, teacherEmail, ',');

            courses.push_back({courseTitle, courseCode, department, duration, creditHour, semester, status,
                {teacherName, teacherID, teacherEmail}});
        }
        coursesFile.close();
    }
}

// Save courses to file
void saveCoursesToFile() {
    ofstream coursesFile("courses.txt", ios::trunc);
    if (coursesFile.is_open()) {
        for (const auto& course : courses){
            coursesFile << course.courseTitle << ","
                        << course.courseCode << ","
                        << course.department << ","
                        << course.duration << ","
                        << course.creditHour << ","
                        << course.semester << ","
                        << course.status << ","
                        << course.teacher.name << ","
                        << course.teacher.id << ","
                        << course.teacher.email << "\n";
        }
        coursesFile.close();
    }else{
        cerr << "Error: Unable to save courses to file.\n";
    }
}


//handleInvalidInput 
void handleInvalidInput(){
  cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please enter a valid number .\n";
}

// Function to save teacher-password pairs to a file
void savePasswordsToFileForTeachers() {
    ofstream file("teacher.txt", ios::out);  // Open file for appending, creates it if it doesn't exist
    if (file.is_open()) {
        for (const auto& teacher : teacherPasswords) {
            // Format: Teacher ID, Password
            file << teacher.teacherId << "," << teacher.password << "\n";
        }
        file.close();
        cout << "All passwords saved successfully.\n";
    } else {
        cerr << "Error: Unable to open file for writing.\n";
    }
}

// Function to load teacher ID and password from the file
void loadTeacherPasswordsForTeachers() {
    ifstream teachersFile("teacher.txt");  // Open teacher file for reading
    if (teachersFile.is_open()) {
        string line;
        while (getline(teachersFile, line)) {
            stringstream ss(line);
            string teacherId, password;

            // Format: Teacher ID, Password
            getline(ss, teacherId, ',');  // Extract teacher ID
            getline(ss, password);        // Extract password

            // Add the pair to the vector
            teacherPasswords.push_back({teacherId, password});
        }
        teachersFile.close();
        cout << "Teacher passwords loaded successfully.\n";
    } else {
        cerr << "Error: Unable to open file for reading.\n";
    }
}

// Function to check if teacher exists based on entered Teacher ID and Password
bool checkTeacherCredentials(const string& teacherId, const string& password) {
    for (const auto& tp : teacherPasswords) {
        if (tp.teacherId == teacherId && tp.password == password) {
            return true;
        }
    }
    return false;
}

// Function to log in the teacher
bool teacherLogin() {
    string teacherId, password;

    // Prompt for Teacher ID and Password
    cout << "Enter Teacher ID: ";
    cin >> teacherId;
    cout << "Enter Password: ";
    cin >> password;

    // Check if credentials are valid
    if (checkTeacherCredentials(teacherId, password)) {
        // Clear the currentTeacher courses list in case of previous data
        currentTeacher.courses.clear();

        // Set the teacherId and password in the currentTeacher structure
        currentTeacher.teacherId = teacherId;
        currentTeacher.password = password;

        // Loop through the courses and find all courses taught by this teacher
        for (const auto& course : courses) {
            if (course.teacher.id == teacherId) {
                // Populate loginedTeacherCourses with course details
                loginedTeacherCourses ltCourse;
                ltCourse.courseTitle = course.courseTitle;
                ltCourse.courseCode = course.courseCode;
                ltCourse.department = course.department;
                ltCourse.duration = course.duration;
                ltCourse.creditHour = course.creditHour;
                ltCourse.semester = course.semester;
                ltCourse.status = course.status;

                // Add the course to the currentTeacher's courses list
                currentTeacher.courses.push_back(ltCourse);
            }
        }

        // Check if the teacher has any courses
        if (!currentTeacher.courses.empty()) {
            cout << "Login successful! Your information and courses have been loaded." << endl;
            return true;
        } else {
            cout << "Login failed. No courses found for the given teacher ID." << endl;
            return false;
        }
    } else {
        cout << "Invalid Teacher ID or Password." << endl;
        return false;
    }
}
//Function that will show all assinged course for  a teacher 
void viewAllAssignedCourses() {
    if (currentTeacher.courses.empty()) {
        cout << "No courses assigned to you at the moment." << endl;
        return;
    }

    cout << "Assigned Courses for Teacher ID: " << currentTeacher.teacherId << endl;
    cout << "---------------------------------------------------" << endl;

    for (const auto& course : currentTeacher.courses) {
        cout << "Course Title: " << course.courseTitle << endl;
        cout << "Course Code: " << course.courseCode << endl;
        cout << "Department: " << course.department << endl;
        cout << "Duration: " << course.duration << " weeks" << endl;
        cout << "Credit Hour: " << course.creditHour << endl;
        cout << "Semester: " << course.semester << endl;
        cout << "Status: " << course.status << endl;
        cout << "---------------------------------------------------" << endl;
    }
}

//--------------------------------------------------- STUDENTS ---------------------------------------------------

void showAllStudents() {
    if (students.empty()) {
        cout << "No students found in the system.\n";
        return;
    }

    cout << "\n--- List of Students ---\n";
    for (size_t i = 0; i < students.size(); ++i) {
        cout << "Student " << i + 1 << ":\n";
        cout << "Name       : " << students[i].name << endl;
        cout << "ID         : " << students[i].id << endl;
        cout << "Department : " << students[i].department << endl;
        cout << "Email      : " << students[i].email << endl;
        cout << "Year       : " << students[i].year << endl;
        cout << "Password   : " << students[i].password << endl;

        // Display assigned course details
        if (!students[i].courses.empty()) {
            for (size_t j = 0; j < students[i].courses.size(); ++j) {
                cout << "Course " << j + 1 << ":\n";
                cout << "    Title   : " << students[i].courses[j].courseTitle << endl;
                cout << "    Code    : " << students[i].courses[j].courseCode << endl;
                cout << "    Teacher : " << students[i].courses[j].teacher.name << " ("
                     << students[i].courses[j].teacher.email << ")\n";
                cout << "    Semester: " << students[i].courses[j].semester << endl;
                cout << "    Status  : " << students[i].courses[j].status << endl;
                cout << "--------------------------\n";
            }
        } else {
            cout << "No courses assigned.\n";
        }
    }
}


// Function to save students to the file (without parameters)
void saveStudentsToFile() {
    // Open the file for writing (if it doesn't exist, it will be created)
    ofstream studentFile("student.txt", ios::out | ios::app);  // Open in append mode

    if (studentFile.is_open()) {
        // Iterate over the students vector and write each student's data
        for (const auto& student : students) {
            studentFile << student.name << ","
                        << student.id << ","
                        << student.department << ","
                        << student.email << ","
                        << student.password << ","
                        << student.year << endl;
        }
        studentFile.close();
        cout << "Student data saved successfully to: student.txt" << endl;
    } else {
        cerr << "Error: Unable to open file for writing." << endl;
    }
    rewriteStudentInfo();
}

// Function to load students from the file (without parameters)
void loadStudentsFromFile() {
    ifstream studentFile("student.txt");  // Open the file for reading

    if (studentFile.is_open()) {
        string line;
        students.clear();  // Clear the current student vector before loading new data

        while (getline(studentFile, line)) {
            stringstream ss(line);
            Student student;

            // Parse the student's details from the line
            getline(ss, student.name, ',');
            getline(ss, student.id, ',');
            getline(ss, student.department, ',');
            getline(ss, student.email, ',');
            getline(ss, student.password, ',');
            ss >> student.year;

            // Add the student to the vector
            students.push_back(student);
        }
        studentFile.close();
        cout << "Student data loaded successfully from: student.txt" << endl;
    } else {
        // If file doesn't exist, create a new one and notify the user
        ofstream studentFile("student.txt");  // Create the file
        studentFile.close();
        cout << "student.txt does not exist. A new file has been created." << endl;
    }
}

// Function to save some generic data to a file (no parameters)
void saveFile() {
    ofstream file("example.txt", ios::out | ios::app);  // Open the file for writing (create if doesn't exist)

    if (file.is_open()) {
        file << "This is a sample data\n";  // Example of saving some data to the file
        file.close();
        cout << "Data saved successfully to: example.txt" << endl;
    } else {
        cerr << "Error: Unable to open file for writing." << endl;
    }
}

// Function to load data from a generic file (no parameters)
void loadFile() {
    ifstream file("example.txt");  // Open the file for reading

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << "Loaded data: " << line << endl;
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for reading." << endl;
    }
}
// Function to check if student exists based on entered Student ID and Password
bool checkStudentCredentials(const string& studentId, const string& password) {
    for (const auto& student : students) {
        if (student.id == studentId && student.password == password) {
            return true; // Student found with matching credentials
        }
    }
    return false; // No match found
}

// Function for student login
Student* searchStudentById(const string& studentId) {
    for (auto& student : students) {
        if (student.id == studentId) {
            return &student;  // Return pointer to the student if found
        }
    }
    return nullptr;  // Return nullptr if student not found
}

// Function to perform student login
bool studentLogin() {
    string studentId, password;

    // Prompt for Student ID and Password
    cout << "Enter Student ID: ";
    cin >> studentId;
    cout << "Enter Password: ";
    cin >> password;

    // Call checkStudentCredentials to verify login
    if (checkStudentCredentials(studentId, password)) {
        // If login is successful, search and populate currentStudent
        Student* loggedInStudent = searchStudentById(studentId);
        if (loggedInStudent) {
            currentStudent = *loggedInStudent;  // Copy the student's data to currentStudent
            cout << "Login successful!\n";

            // Print out the current logged-in student's information
            cout << "Welcome " << currentStudent.name << "!\n";
            cout << "ID: " << currentStudent.id << "\n";
            cout << "Department: " << currentStudent.department << "\n";
            cout << "Email: " << currentStudent.email << "\n";
            cout << "Year: " << currentStudent.year << "\n";
            
            return true;
        } else {
            cout << "Error: Student not found.\n";
            return false;
        }
    } else {
        cout << "Invalid Student ID or Password. Please try again.\n";
        return false;
    }
}
// Function to view all courses for the logged-in student based on their department
void viewAllCoursesForStudent() {
    cout << "\nCourses available for " << currentStudent.department << " department:\n";
    
    // Print the table headers
    cout << left << setw(30) << "Course Title" 
         << setw(15) << "Course Code" 
         << setw(15) << "Duration" 
         << setw(15) << "Credit Hour" 
         << setw(15) << "Semester"
         << setw(15) << "teacher" 
         << setw(15) << "Status" << endl;
    
    cout << "--------------------------------------------------------------------------------------------------------------------------\n";
    
    // Loop through the courses and display those that match the student's department
    bool courseFound = false;
    for (const auto& course : courses) {
        if (course.department == currentStudent.department) {
            cout << left << setw(30) << course.courseTitle 
                 << setw(15) << course.courseCode 
                 << setw(15) << course.duration 
                 << setw(15) << course.creditHour 
                 << setw(15) << course.semester 
                 << setw(15) << course.teacher.name 
                 << setw(15) << course.status << endl;
            courseFound = true;
        }
    }

    if (!courseFound) {
        cout << "No courses available for your department.\n";
    }
}
void addCoursesForStudent() {
    string courseCode;
    bool courseExists = false;

    // Ask the student to enter the course code they want to add
    cout << "Enter the course code you want to add: ";
    cin >> courseCode;

    // Loop through the available courses to check if the entered course code is valid
    for (const auto& course : courses) {
        if (course.courseCode == courseCode) {
            // Check if the course matches the student's department
            if (course.department == currentStudent.department) {
                // Add the course to the student's list
                currentStudent.courses.push_back(course);
                cout << "Course " << course.courseTitle << " added successfully!\n";
                courseExists = true;
                break;
            } else {
                cout << "This course is not available for your department.\n";
                courseExists = true;
                break;
            }
        }
    }

    // If the course does not exist, notify the student
    if (!courseExists) {
        cout << "Course with code " << courseCode << " not found.\n";
    }
    saveStudentsToFile();
}

void viewMyCourses() {
    if (currentStudent.courses.empty()) {
        cout << "You have no courses assigned.\n";
        return;
    }

    // Set column widths
    const int width = 20;

    // Print table header
    cout << "\n--- Your Courses ---\n";
    cout << left << setw(width) << "Course Title" 
         << setw(width) << "Course Code" 
         << setw(width) << "Teacher Name" 
         << setw(width) << "Semester"
         << setw(width) << "Status" << endl;
    cout << string(width * 5, '-') << endl;

    // Iterate through the courses and print them in a tabular format
    for (const auto& course : currentStudent.courses) {
        cout << left << setw(width) << course.courseTitle
             << setw(width) << course.courseCode
             << setw(width) << course.teacher.name
             << setw(width) << course.semester
             << setw(width) << course.status << endl;
    }
}
void dropCourse() {
    // Check if the student has any courses assigned
    if (currentStudent.courses.empty()) {
        cout << "You have no courses to drop.\n";
        return;
    }

    string courseCode;
    cout << "Enter the course code you wish to drop: ";
    cin >> courseCode;

    // Find the course in the student's course list
    auto it = std::find_if(currentStudent.courses.begin(), currentStudent.courses.end(),
                           [&courseCode](const Course& course) {
                               return course.courseCode == courseCode;
                           });

    // If course found, remove it
    if (it != currentStudent.courses.end()) {
        currentStudent.courses.erase(it);
        cout << "Course " << courseCode << " has been successfully dropped.\n";
    } else {
        cout << "You are not enrolled in a course with code " << courseCode << ".\n";
    }
saveStudentsToFile();
     
}
void rewriteStudentInfo() {
    // Find the student in the 'students' vector by comparing the student ID
    auto it = std::find_if(students.begin(), students.end(),
                           [](const Student& student) {
                               return student.id == currentStudent.id; // Compare by student ID
                           });

    if (it != students.end()) {
        // Student found, rewrite the information
        *it = currentStudent; // Replace with the current student's details
        cout << "Your information has been updated successfully.\n";
    } else {
        // If the student is not found in the system
        cout << "Error: Student not found in the system.\n";
    }
}

