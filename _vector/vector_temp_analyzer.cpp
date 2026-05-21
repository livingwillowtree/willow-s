#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <vector>

// for input validation
const double MIN_REALISTIC = 0.0;
const double MAX_REALISTIC = 60.0;

// for extreme heat count, anything beyond is extreme
const double EXTREME_HEAT_BOUNDS = 40.0;

// for cateegorization,from PAGASA
const double MIN_NORMAL = 25.0;
const double MAX_NORMAL = 35.0;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PROTOTYPES
int getInt(const std::string& = "");
void fillVector(std::vector<double>&, int);
double getDouble(const std::string& = "");

double computeAverage(const std::vector<double>&);
void sortVector(std::vector<double>&);
int countExtremeHeat(const std::vector<double>&);
void categorizeTemperatures(const std::vector<double>&, std::vector<std::string>&);

void displayVector(const std::vector<double>&);
void displayCategories(const std::vector<double>&, const std::vector<std::string>&);

bool promptReplay(const std::string& = "");

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MAIN LOGIC FLOW
int main(){
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "==============================================\n"
              << "= Temperature Monitoring and Analysis System =\n"
              << "==============================================\n\n";
    int numReadings;

    std::vector<double> temperatures;
    std::vector<double> sortedTemperatures;
    std::vector<std::string> categories;

    double averageTemperature;
    double highestTemp;
    double lowestTemp;
    int extremeHeatCount;
    
    bool running = true;
    while(running){
        numReadings = getInt("\tGive the number of readings for today.\n");
        
        temperatures = {};
        categories = {};
        
        fillVector(temperatures, numReadings);

        sortedTemperatures.assign(temperatures.begin(), temperatures.end());

        sortVector(sortedTemperatures);

        averageTemperature = computeAverage(temperatures);
        //------------------- get the extremes using the sorted vector
        highestTemp = sortedTemperatures.back();
        lowestTemp = sortedTemperatures.front();

        extremeHeatCount = countExtremeHeat(sortedTemperatures);

        categorizeTemperatures(sortedTemperatures, categories);

        std::cout << "\n";

        std::cout << "--- Recorded Readings --- \n";
        displayVector(temperatures);
        std::cout << "\n\n";

        std::cout << "--- Statistical Analysis ---\n";
        std::cout << "Average Temperature : " << averageTemperature << " °C";
        std::cout << "\n";

        std::cout << "Highest Recorded Temperature : " << highestTemp << " °C";
        std::cout << "\n";

        std::cout << "Lowest Recorded Temperature : " << lowestTemp << " °C";
        std::cout << "\n";

        std::cout << "Number of Readings Above 40 °C : " << extremeHeatCount;
        std::cout << "\n\n"; 

        std::cout << "--- Sorted Record ---\n";
        displayVector(sortedTemperatures);
        std::cout << "\n\n";

        std::cout << "--- Temperature Categorization ---\n";
        displayCategories(sortedTemperatures, categories);
        std::cout << "\n\n";

        running = promptReplay("Would you like to repeat the process? (Y/n)\n");

        if(!running){
            std::cout << "Thank You!";
        }

        std::cout << "\n\n";
    }

    return 0;
}

int getInt(const std::string& prompt){
    int input = 0;
    
    std::cout << prompt;

    while(true){
        std::cout << ">> ";
        std::cin >> input;
        if(std::cin.fail() || input <= 0.0){
            std::cout << "Invalid input.\n";
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            continue;
        }

        return input;
    }
}

double getDouble(const std::string& prompt){
    double input = 0.0;

    std::cout << prompt;
    while(true){
        std::cout << ">> ";
        std::cin >> input;

        if(std::cin.fail()|| input < MIN_REALISTIC || input > MAX_REALISTIC){
            std::cout << "Invalid input.\n";
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            continue;
        }
        return input;
    }
}

void fillVector(std::vector<double>& temperatures, int numReadings){
    for(int i = 1; i <= numReadings; i++){
        temperatures.push_back(getDouble("Reading " + std::to_string(i) + "\n"));
    }
}

void sortVector(std::vector<double>& sortedTemps){
    int swaps = 0;
    int n = sortedTemps.size();
    double tmp;

    do{
        swaps = 0;

        for(int i = 0; i < n-1; i++){
            if(sortedTemps[i] > sortedTemps[i+1]){
                tmp = sortedTemps[i+1];
                sortedTemps[i+1] = sortedTemps[i];
                sortedTemps[i] = tmp;
                swaps++;
            }
        }
        n--;

    }while(swaps > 0);
}

double computeAverage(const std::vector<double>& temperatures){
    double sum = 0.0;
    double average = 0.0;
    for(double temp : temperatures){
        sum += temp;
    }

    average = sum/(double)temperatures.size();
    return average;
}


int countExtremeHeat(const std::vector<double>& sortedTemps){
    int count = 0;
    //------------------- start counting from highest temp, its faster that way
    for(int i = sortedTemps.size() - 1; i >= 0; i--){
        if(sortedTemps[i] > EXTREME_HEAT_BOUNDS) count++;
    } 
    return count;
}

void categorizeTemperatures(const std::vector<double>& sortedTemps, std::vector<std::string>& categories){
    for(double temp : sortedTemps){
        if(temp < MIN_NORMAL){
            categories.push_back("Cold");
        }
        else if(temp <= MAX_NORMAL){
            categories.push_back("Normal");
        }
        else {
            categories.push_back("Hot");
        }
    }
}

void displayVector(const std::vector<double>& vector){
    std::cout << std::fixed << std::setprecision(2);

    for(int i = 0; i < vector.size(); i ++){
        std::cout << vector[i] << " °C" 
                  << ((i == vector.size()-1) ? "" : ", ");
    }
}

void displayCategories(const std::vector<double>& sortedTemps, const std::vector<std::string>& categories){
    std::cout << std::fixed << std::setprecision(2);

    for(int i = 0; i < sortedTemps.size(); i++){
        std::cout << sortedTemps[i] << " °C -> " << categories[i] << "\n";
    }
}

bool promptReplay(const std::string& prompt){
    char input;

    std::cout << prompt;
    while(true){
        std::cout << ">> ";
        std::cin >> input;

        input = std::tolower(input);
        if(input != 'y' && input != 'n'){
            std::cout << "Y or N only.\n";
            std::cin.ignore(10000,'\n');
            continue;
        }

        if(input == 'y'){
            return true;
        }
        else{
            return false;
        }
    }
}