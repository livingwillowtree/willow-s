/*
    Yo yo yo, decided to remake my god awful functions2 lab activity
    this time, no parallel arrays floating in the void of globals.

    everything will be either in a sturct or is a constant, which would
    prolly be also in the struct, or not, we'll see

    i will also be using getlines for input this time
    it looked cool but also a pain in the ass to sanitize

    ofc, the biggest upgrade is the dynamic VECTORS lfg

    [UPDATE] i decided to also add some features from other labs
    or not, idk, i just thought it might be good,
    thinking about it now tho, thats a lot of work

    [UPDATE] remember when I said i will add features from other labs?
    no? weird, i also dont remember saying that
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< STRUCT & GLOBALS
const double quizWeight = .25,
             activityWeight = .20,
             laboratoryWeight = .25,
             examWeight = .30;

struct Student{
    std::string name =       "";
    double quizGrade =       0.0,
           activityGrade =   0.0,
           laboratoryGrade = 0.0,
           examGrade =       0.0,
           gwa =             0.0;
};

struct Database{
    bool isDBSorted = false;
    bool isDataLatest = false;
    //--------------------------- store indices of students
    std::vector<int> topPerformers = {};
    std::vector<int> lowPerformers = {};
};

struct GradeInput{
    std::string prompt;
    double& target;
};

//----------------- haha yoink its mine now too
//                  i COULD use namespace and constexpr, but I wont
struct ErrMsgs{
    const std::string invalidChar = "Invalid character/option.\n";
    const std::string invalidNum = "Invalid number.\n";
    const std::string invalidName = "Invalid name.\n";
    const std::string invalidDouble = "Invalid double.\n";
    const std::string invalidDoubleValue = "Invalid double value.\n";

};

const ErrMsgs errmsg;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PROTOTYPES
// over engineering goes brrr
char getChar(char, char, const std::string& = "");
std::string getString(int, int, const std::string& = "");
double getDouble(double, double, const std::string& = "");
bool validateDoubleStr(const std::string&);

void displayMenu();
bool addStudent(std::vector<Student>&, bool);
double getGWA(double, double, double, double);
void displayStudents(const std::vector<Student>&);
void getTopAndLowest(const std::vector<Student>&, Database&);
void displayTopAndLowest(const std::vector<Student>&, Database&);
bool sortDatabase(std::vector<Student>&, bool);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MAIN LOGIC FLOW
int main(){
    std::vector<Student> studentDB = {};
    Database database;

    // [DEBUG] assign students directly
    studentDB.assign({{"John Doe", 88.5, 92.0, 85.75, 90.0, 88.96},
                      {"Jane Smith", 95.0, 89.5, 91.25, 93.5, 92.51},
                      {"Alex Jones", 78.25, 84.0, 80.5, 82.0, 81.09}
                    });

    bool isRunning = true;

    //default option 'exit' if user somehow bypassed input
    char choice = 'e';

    while(isRunning){
        displayMenu();

        choice = getChar('a','e');

        switch(choice){
            case 'a' : 
                database.isDBSorted = addStudent(studentDB, database.isDBSorted);
                break;
            case 'b' :
                displayStudents(studentDB);
                break;
            case 'c' :
                displayTopAndLowest(studentDB, database);
                break;
            case 'd' :
                database.isDBSorted = sortDatabase(studentDB, database.isDBSorted);
                break;
            case 'e' :
                std::cout << "Thank you!\n\n";
                isRunning = false;
                break;
        }
    }
    
    return 0;
}

char getChar(char min, char max, const std::string&){
    std::string input;
    while(true){
        std::cout << ">> ";
        std::getline(std::cin, input);
        //---------------------------------- input validation
        if(input.size() > 1 || input < "a" || input > "e"){
            std::cout << errmsg.invalidChar;
            continue;
        }
        break;
    }
    
    return input.at(0);
}

std::string getString(int min, int max, const std::string& prompt){
    std::string input;
    std::cout << prompt << " ('Quit' to cancel.)\n";
    while(true){
        std::cout << ">> ";
        std::getline(std::cin, input);
        if(input.size() < min || input.size() > max ){
            std::cout << errmsg.invalidName;
            continue;
        }
        break;
    }
    return input;
}

double getDouble(double min, double max, const std::string& prompt){
    std::string input;
    double inputDouble = 0.0;
    std::cout << prompt << " (" << min-1 << " to cancel.)\n";


    while(true){
        std::cout << ">> ";
        std::getline(std::cin, input);
        //------------------------------ check first if its a valid double
        if(!validateDoubleStr(input)){
            std::cout << errmsg.invalidDouble;
            continue;
        }
        //----------------------------- convert to double
        inputDouble = std::stod(input);
        
        //----------------------- cancel key
        if(inputDouble == min-1){
            return inputDouble;
        }

        if(inputDouble < min || inputDouble > max){
            std::cout << errmsg.invalidDoubleValue;
            continue;
        }
        
        break;
    }
    
    return inputDouble;
}

bool validateDoubleStr(const std::string& inputString){
    bool periodFound = false;
    bool isFirst = true;

    for(char c : inputString){
        //-------------------------- invalid : mid digit negative sign
        if(c == '-'){
            if(!isFirst){
                std::cout << "[MID SENTENCE]\n";
                return false;
            }
            continue;
        }
        isFirst = false;

        if(c == '.'){
            //----------------------- invalid : multiple period
            if(!periodFound) {
                periodFound = true;
            }
            else {
                return false;
            }
            continue;
        } 
        //--------------------------- invalid : non digit
        if(c < '0' || c > '9'){
            return false;
        } 
    }

    return true;
}

void displayMenu(){
    const static std::string menu = "=== Student DB ===\n\n"
                                    " [a] Add Student\n"
                                    " [b] Display All Students\n"
                                    " [c] Display Top and Bottom Performers\n"
                                    " [d] Sort Database\n"
                                    " [e] Exit\n";

    std::cout << menu << std::endl;
}

bool addStudent(std::vector<Student>& students, bool isDBSorted){
    double q, a, l, e, gwa;
    // over engineering this shit, i just didnt like having 5 if statements
    std::vector<GradeInput> gradeInput = {
        {"Input quiz grade.", q},
        {"Input activity grade.", a},
        {"Input laboratory grade.", l},
        {"Input exam grade.", e}};
    
    std::string name = getString(0, 64, "Input student name.");
    if(name == "Quit"){
        std::cout << "Process Cancelled.\n\n";
        return isDBSorted;
    }

    // they pretty much do the same, just diff prompts and var
    for(auto& input : gradeInput){
        input.target = getDouble(0.0, 100.0, input.prompt);
        if(input.target == -1){
            std::cout << "Process cancelled.\n\n";
            return isDBSorted;
        }
    }

    gwa = getGWA(q, a, l, e);

    students.push_back({name, q, a, l, e, gwa});
    return false;
}


double getGWA(double quizGrade, double activityGrade, double laboratoryGrade, double examGrade){
    return (quizGrade       * quizWeight
          + activityGrade   * activityWeight
          + laboratoryGrade * laboratoryWeight
          + examGrade       * examWeight);
}

void displayStudents(const std::vector<Student>& students){
    const static int lW = 20, rW = 8;

    // two decimal places output format
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(lW) << "Name"
              << std::right 
              << std::setw(rW) << "Quiz"
              << std::setw(rW) << "Act"
              << std::setw(rW) << "Lab"
              << std::setw(rW) << "Exam"
              << std::setw(rW) << "GWA"
              << "\n";
    
    for(const Student& student : students){
        std::cout << std::left << std::setw(lW) << student.name
              << std::right 
              << std::setw(rW) << student.quizGrade
              << std::setw(rW) << student.activityGrade
              << std::setw(rW) << student.laboratoryGrade
              << std::setw(rW) << student.examGrade
              << std::setw(rW/2) << "[" << student.gwa << "]"
              << "\n";
    }

    std::cout << "\n";
}

void getTopAndLowest(const std::vector<Student>& students, Database& database){
    if(database.isDataLatest){
        return;
    }
    
    static double highest;
    static double lowest;
    bool hitHigher = false;
    bool hitLower = false;
    int len = students.size()/2;

    lowest = students.front().gwa;
    database.lowPerformers.push_back(0);
    highest = students.back().gwa;
    database.topPerformers.push_back(students.size()-1);

    for(int i = 1; i < len; i++){
        if(students[i].gwa == lowest){
            database.lowPerformers.push_back(i);
        }
        else{
            hitHigher = true;
        }

        if(students[len - i - 1].gwa == highest){
            database.topPerformers.push_back(len - i - 1);
        }
        else{
            hitLower = true;
        }

        if(hitHigher && hitLower){
            break;
        }
    }
    
}

void displayTopAndLowest(const std::vector<Student>& students, Database& database){
    //------------------------ return if db is unsorted, making getTopnLowest unusable
    if(!database.isDBSorted){
        std::cout << "Database unsorted, unable to get data.\n\n";
        return;
    }
    getTopAndLowest(students, database);

    
    std::cout << "=== Top Performers (" << students.back().gwa << ") ===\n\n";
    for(int index : database.topPerformers){
        std::cout << students[index].name << "\n";
    }
    
    std::cout << "\n";

    std::cout << "=== Bottom Performers (" << students.front().gwa << ") ===\n\n";
    for(int index : database.lowPerformers){
        std::cout << students[index].name << "\n";
    }

    std::cout << "\n";
}

bool sortDatabase(std::vector<Student>& students, bool isDBSorted){
    if(isDBSorted){
        std::cout << "Already sorted.\n";
        return true;
    }

    Student temp;
    int swaps;
    do{
        swaps = 0;

        for(int i = 0; i < students.size()-1; i++){
            if(students[i].gwa > students[i+1].gwa){
                temp = students[i];
                students[i] = students[i+1];
                students[i+1] = temp;
                swaps++;
            }
        }
    }while(swaps > 0);

    std::cout << "Database has been sorted.\n\n";
    return true;
}