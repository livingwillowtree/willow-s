#include <iostream>
#include <string>
/* 
    Look at this laughable code. Globals for everything
    to avoid passing variables lmaoo.
*/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< GLOBALS

//constants
const int studentCount = 40;
const float quizW = .25;
const float actW = .20;
const float labW = .25;
const float examW = .30;

//student db
std::string studentName[studentCount];
float gwa[studentCount], quiz[studentCount], activity[studentCount], 
        laboratory[studentCount], exam[studentCount];
int sortArr[studentCount];
int arrIndex = 0;
bool isDirty = 0;

//top and lowest
float lowest = 100.0;
float highest = 0.0;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PROTOTYPES
void displayMenu();
void getChoice(char*);
void inputStudentDate();
void getFloat(float*);
void getGWA(float, float, float, float);
void displayAllStudents();
void displayTopNLowest();
void sortStudents();

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MAIN LOGIC FLOW
int main(){
    char choice = 'a';
    
    while(true){
        displayMenu();
        getChoice(&choice);
        switch(choice){
            case 'a' :
                inputStudentDate();
                break;
            case 'b' :
                displayAllStudents();
                break;
            case 'c' : 
                displayTopNLowest();
                break;
            case 'd' : 
                sortStudents();
                break;
            case 'e' :
                std::cout << "Thank You!!" << std::endl;
                return 0;
        }
    }
    return 0;
}

void displayMenu(){
    static const std::string menu = "============ STUDENT DB ===========\n\n"
                       "[a] Input Student Data\n"
                       "[b] Display All Students\n"
                       "[c] Display Top and Lowest Student Grade\n"
                       "[d] Sort the Student Grade (Ascending)\n"
                       "[e] Exit the Program\n\n";

    std::cout << menu << std::flush;
}

void getChoice(char* choice){
    while(true){
        std::cout << ">> ";
        std::cin >> *choice;
        *choice = tolower(*choice);
        if(*choice < 'a' || *choice > 'e'){
            std::cin.ignore(10000,'\n');
            continue;
        }
        std::cin.ignore(10000,'\n');
        return;
    }
}

void inputStudentDate(){
    std::string name;
    float quizG = 0.0, actG = 0.0, 
          labG = 0.0, examG = 0.0;

    std::cout << std::endl;
    std::cout << "Input Student Name" << std::endl;
    while(true){
        std::cout << ">> ";
        std::getline(std::cin, name);
        if(name.empty())
            continue;
        break;
    }

    std::cout << "Input Quiz Grade" << std::endl;
    getFloat(&quizG);
    std::cout << "Input Activity Grade" << std::endl;
    getFloat(&actG);
    std::cout << "Input Laboratory Grade" << std::endl;
    getFloat(&labG);
    std::cout << "Input Exam Grade" << std::endl;
    getFloat(&examG);
    std::cout << std::endl;
    getGWA(quizG, actG, labG, examG);

    studentName[arrIndex] = name;
    quiz[arrIndex] = quizG;
    activity[arrIndex] = actG;
    laboratory[arrIndex] = labG;
    exam[arrIndex] = examG;

    if(gwa[arrIndex] > highest)
        highest = gwa[arrIndex];
    else if(gwa[arrIndex] < lowest)
        lowest = gwa[arrIndex];

    arrIndex++;
    isDirty = 1;
}

void getFloat(float* input){
    while(true){
        std::cout << ">> ";
        std::cin >> *input;
        if(std::cin.fail() || *input < 0.0 || *input > 100.0){
            std::cout << "INVALID." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            continue;
        }
        break;
    }
}

void getGWA(float quizG, float actG, float labG, float examG){
    gwa[arrIndex] = quizG * quizW
               + actG * actW
               + labG * labW
               + examG * examW;
}

void displayAllStudents(){
    std::cout << std::endl;
    
    for(int i = 0; i < arrIndex; i++){
        std::cout << studentName[i] << " : " <<
                     gwa[i] << " (" << 
                       "[Q]" << quiz[i] << 
                     "  [A]" << activity[i] <<
                     "  [L]" << laboratory[i] <<
                     "  [E]" << exam[i] << ")" << std::endl; 
    }
    std::cout << "\n\n";
}

void displayTopNLowest(){
    std::cout << std::endl;
    std::cout << "--- TOP STUDENT GRADE [" << highest << "] ---\n\n";
    
    for(int i = 0; i < arrIndex; i++){
        if(gwa[i] == highest)
            std::cout << studentName[i] << std::endl;
    }

    std::cout << "\n\n";

    std::cout << "--- LOWEST STUDENT GRADE [" << lowest << "] ---\n\n";
    for(int i = 0; i < arrIndex; i++){
        if(gwa[i] == lowest)
            std::cout << studentName[i] << std::endl;
    }
    
    std::cout << "\n\n";
}

void sortStudents(){
    if(isDirty){
        int swaps;
        int temp;
        for(int i = 0; i < arrIndex; i++)
            sortArr[i] = i;

        do{
            swaps = 0;
            for(int i = 0; i < arrIndex-1; i++){
                if(gwa[sortArr[i]] > gwa[sortArr[i+1]]){
                    temp = sortArr[i];
                    sortArr[i] = sortArr[i+1];
                    sortArr[i+1] = temp;
                    swaps++;
                }
            }
        }
        while(swaps > 0);
        isDirty = 0;
    }
    std::cout << std::endl;
    std::cout << "--- SORTED STUDENTS ---\n\n";
    for(int i = 0; i < arrIndex; i++){
        std::cout << studentName[sortArr[i]] << " : "
                  << gwa[sortArr[i]] << std::endl;
    }

    std::cout << "\n\n";
}