#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <ctime>
#include <cstdlib>

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

// Global vector to store courses
vector<Course> courses;
//Global vector to store teacher password
vector<TeacherPassword> teacherPasswords;

//Current logined Teacher
loginedTeacher currentTeacher;

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
void viewAllCourses();
void deleteCourse();
void updateCourse();
bool isCourseCodeUnique(const string& courseCode);
bool isValidInteger(int& value);
void loadCoursesFromFile();
void saveCoursesToFile();


//Function prototypes for teacher functionalities
bool checkTeacherCredentials();
bool teacherLogin();
void viewAllAssignedCourses();
void displayTeacherMenu();
void processTeacherMenu();
void savePasswordsToFileForTeachers();
void loadTeacherPasswordsForTeachers();
Teacher* savePasswordsToFileForTeachers(string teacherId);
Teacher* searchTeacherById(string id);
void populateLoginedTeacher(const Teacher &teacher); 

//Function prototypes for Student functionalities
//void viewMyCourses();
void displayStudentMenu();
void processStudentMenu();
//void addCourseForStudent();
//void dropCourseForStudent();
//vid viewGrades();


//Function to generate a password
string generateRandomPassword(int length = 12) {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+";
    string password;
    for (int i = 0; i < length; ++i) {
        password += chars[rand() % chars.size()];
    }
    return password;
}


//Function to handle Invalid input 
void handleInvalidInput();


// Main function
int main() {
    // Load existing courses from the file at the start
    loadCoursesFromFile();
    // Load existing Teacher from the file at the start
    loadTeacherPasswordsForTeachers();


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
    cout << "5. Exit Admin Section\n";
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
        case 5: 
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

   while (true) {
    processTeacherMenu();
  } 
}


// Display admin menu options
void displayTeacherMenu() {
    cout << "\n------ Welcome to Teachers' Section ------\n";
    cout << "1. View all courses\n";
    cout << "2. Exit Admin Section\n";
    cout << "Enter your choice: ";
}

// Handle admin menu inputs
void processTeacherMenu() {
    displayTeacherMenu();
    int choice;
    cin >> choice;

    switch (choice) {
        case 1: viewAllAssignedCourses(); break;
        case 2: 
            cout << "Exiting admin section...\n";
            exit(0); 
            break;
        default:
            handleInvalidInput(); 
            break;
    }
}


//Student Section
void studentSection(){
    while (true) {
        processStudentMenu();
    }
}
void displayStudentMenu() {
    cout << "\n------ Welcome to Teachers' Section ------\n";
    cout << "1. View all courses\n";
    cout << "2. Exit Admin Section\n";
    cout << "Enter your choice: ";
}

// Handle admin menu inputs
void processStudentMenu() {
    displayStudentMenu();
    int choice;
    cin >> choice;

    switch (choice) {
        case 1: viewAllAssignedCourses(); break;
        case 2: 
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
        for (const auto& course : courses) {
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
    } else {
        cerr << "Error: Unable to save courses to file.\n";
    }
}

//viewAllAssignedCourses
void viewAllAssignedCourses(){
    cout << "under contraction " << endl;
}
//handleInvalidInput 
void handleInvalidInput(){
  cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please enter a valid number .\n";
}

// Function to save teacher-password pairs to a file
void savePasswordsToFileForTeachers() {
    ofstream file("teacher.txt", ios::app);  // Open file for appending, creates it if it doesn't exist
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
    for (const auto& teacher : teacherPasswords) {
        if (teacher.teacherId == teacherId && teacher.password == password) {
            return true;  // Teacher found with correct ID and password
        }
    }
    return false;  // Teacher not found or incorrect password
}

// Function to handle teacher login
bool teacherLogin() {
    string teacherId, password;

    // Prompt for Teacher ID and Password
    cout << "Enter Teacher ID: ";
    cin >> teacherId;
    cout << "Enter Password: ";
    cin >> password;
   if(checkTeacherCredentials(teacherId, password)){
     Teacher* foundTeacher = searchTeacherById(teacherId);
     if (foundTeacher != nullptr) {
         // Populate current teacher info using the populatedLoggedInTeacher function
         populateLoginedTeacher(*foundTeacher, password);
        cout << "Your information have successfully loaded" << endl;    
      }  
        return true;
    } 
    return false;  
}


// Function to populate loginedTeacher structure
void populateLoginedTeacher(const Teacher &teacher, password) {
    // Assign teacher's details to the current logged-in teacher
    currentTeacher.teacherId = teacher.id;
    currentTeacher.password = password;
    currentTeacher.courses = teacher.courses; // Copy courses list
}

// Function to search for a teacher by teacherId
Teacher* searchTeacherById(const string& teacherId) {
    for (const auto &course : courses) {
        if (course.teacher.id == teacherId) {
            return &course.teacher; // Return pointer to the teacher
        }
    }
    return nullptr; // Return nullptr if the teacher is not found
}
