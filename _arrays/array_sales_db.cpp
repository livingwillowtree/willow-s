#include <iostream>
#include <iomanip>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PROTOTYPES
void prepareDataTable(int* weeks, int* days, double salesTable[100][7]);
int getIntInput(int max);
double getDoubleInput();
void displayTables(int weeks, int days, double dataTable[100][7]);
void calculateSales(int weeks, int days, double salesTable[100][7], double salesPerWeek[100], double salesPerDay[7]);
void calculateTotalAndAverage(int totalDays, int weeks, double salesPerWeek[100], double* totalSales, double* averageSale);
void getExtremes(double salesTable[100][7], double salesPerWeek[100], int weeks, int days,
                 int* bestW, int* bestD, int* worstW, int* worstD, int* bestPW, int* worstPW);
void displayTableReversed(int weeks, int days, double dataTable[100][7]);


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MAIN LOGIC FLOW
int main(){
    int weeks = 0, days  = 0;
    double salesTable[100][7];
    double salesPerWeek[100] = {0}, salesPerDay[7] = {0}; 
    double totalSales = 0.0, averageSale = 0.0;
    int bestW = 0, bestD = 0, worstW = 0, worstD = 0, bestPW = 0, worstPW = 0;

    // 1. Prepare and Display the data table
    prepareDataTable(&weeks, &days, salesTable);
    std::cout << "\n\n" << std::endl;

    std::cout << "--- Table ---\n" << std::endl;
    displayTables(weeks, days, salesTable);

    // 3. Compute and Display these fuckers
    calculateSales(weeks, days, salesTable, salesPerWeek, salesPerDay);
    calculateTotalAndAverage(weeks*days, weeks, salesPerWeek, &totalSales, &averageSale);

    std::cout << std::endl;
    std::cout << "--- TOTALS ---\n" <<std::endl;
    std::cout << "Totals Per Week:" << std::endl;
    for(int i = 0; i < weeks; i++){
        std::cout << "Week " << i+1 << ": " << std::fixed << 
        std::setprecision(2) << salesPerWeek[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Totals Per Day:" << std::endl;
    for(int i = 0; i < days; i++){
        std::cout << "Day " << i+1 << ": " << std::fixed << 
        std::setprecision(2) << salesPerDay[i] << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Total: " << std::fixed << 
        std::setprecision(2) << totalSales << std::endl;
    std::cout << std::endl;
    std::cout << "Average Sale: " << std::fixed << 
        std::setprecision(2) << averageSale << std::endl;
    
    // 4. Determine and Display these fuckers
    getExtremes(salesTable, salesPerWeek, weeks, days, &bestW, &bestD, &worstW, &worstD, &bestPW, &worstPW);

    std::cout << std::endl;
    std::cout << "Highest Sale:" << std::endl;
    std::cout << "W" << bestW+1 << " D" << bestD+1 << " - " <<
        std::fixed << std::setprecision(2) << 
        salesTable[bestW][bestD] << std::endl;
    std::cout << std::endl;

    std::cout << "Lowest Sale:" << std::endl;
    std::cout << "W" << worstW+1 << " D" << worstD+1 << " - " <<
        std::fixed << std::setprecision(2) << 
        salesTable[worstW][worstD] << std::endl;
    std::cout << std::endl;

    std::cout << "Highest Sale Week:" << std::endl;
    std::cout << "W" << bestPW+1 << " - " <<
        std::fixed << std::setprecision(2) << 
        salesPerWeek[bestW] << std::endl;
    std::cout << std::endl;

    std::cout << "Lowest Sale Week:" << std::endl;
    std::cout << "W" << worstPW+1 << " - " <<
        std::fixed << std::setprecision(2) << 
        salesPerWeek[worstW] << std::endl;
    std::cout << std::endl;

    std::cout << "--- Table in Reverse ---\n" << std::endl;
    displayTableReversed(weeks, days, salesTable);
    return 0;
}

void prepareDataTable(int* weeks, int* days, double salesTable[100][7]){
    //prepare table dimensions
    std::cout << "Input Weeks.[1-100]" << std::endl;
    *weeks = getIntInput(100);
    std::cout << "Input days per week.[1-7]" << std::endl;
    *days = getIntInput(7);

    //input values
    for(int i = 0; i < *weeks; i++){
        for(int j = 0; j < *days; j++){
            std::cout << "Input sale for W" << i+1 << " D" << j+1 << std::endl;
            salesTable[i][j] = getDoubleInput();
        }
    }
}

int getIntInput(int max){
    int input = 0;

    while(true){
        std::cout << ">> ";
        std::cin >> input;

        // no 0 or above max, arrays dont like that
        if(std::cin.fail() || input < 1 || input > max){
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        break;
    }

    return input;
}

double getDoubleInput(){
    double input = 0.0;
    
    while(true){
        std::cout << ">> ";
        std::cin >> input;
        
        if(std::cin.fail() || input < 0.0){
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        break;
    }
    
    return input;
}

void displayTables(int weeks, int days, double dataTable[100][7]){
    const int width = 15;

    std::cout << std::left << std::setw(10) << "Week";
    for(int c = 0; c < days; c++){
        std::cout << std::right << std::setw(14+c) << "Day " + std::to_string(c+1);
    }
    std::cout << std::endl;

    for(int i = 0; i < weeks; i++){
        std::cout << std::left << std::setw(10) << "Week " + std::to_string(i+1); 
        for(int j = 0; j < days; j++){
            double val = dataTable[i][j];
            std::cout << std::right << std::setw(width);
            if(val > 99999)
                std::cout << std::fixed << std::setprecision(2) 
                          << std::scientific << val << " ";
            else
                std::cout << std::fixed << std::setprecision(2)
                      << val << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::defaultfloat;
}

void calculateSales(int weeks, int days, double salesTable[100][7], double salesPerWeek[100], double salesPerDay[7]){
    for(int i = 0; i < weeks; i++){
        for(int j = 0; j < days; j++){
            salesPerWeek[i] += salesTable[i][j];
            salesPerDay[j] += salesTable[i][j];
        }
    }
}

void calculateTotalAndAverage(int totalDays, int weeks, double salesPerWeek[100], double* totalSales, double* averageSale){
    for(int i = 0; i < weeks; i++){
        *totalSales += salesPerWeek[i];
    }

    *averageSale = *salesPerWeek/totalDays;
}

void getExtremes(double salesTable[100][7], double salesPerWeek[100], int weeks, int days,
                 int* bestW, int* bestD, int* worstW, int* worstD, int* bestPW, int* worstPW){
    
    double val = 0.0;
    double max = salesTable[0][0];
    double min = salesTable[0][0];

    for(int i = 1; i < weeks; i++){
        for(int j = 1; j < days; j++){
            val = salesTable[i][j];
            if(val > max){
                max = val;
                *bestW = i;
                *bestD = j;
            }
            if(val < min){
                min = val;
                *worstW = i;
                *worstD = j;
            }
        }
    }

    //reset for finding the best and worst weeks
    val = 0.0;
    max = salesPerWeek[0];
    min = salesPerWeek[0];

    for(int k = 1; k < weeks; k++){
        val = salesPerWeek[k];
        if(val > max){
            max = val;
            *bestPW = k;
        }
        if(val < min){
            min = val;
            *worstPW = k;
        }
    }
}

void displayTableReversed(int weeks, int days, double dataTable[100][7]){
    const int width = 15;

    std::cout << std::left << std::setw(10) << "Week";
    for(int c = days-1; c >= 0; c--){
        std::cout << std::right << std::setw(14+c) << "Day " + std::to_string(c+1);
    }
    std::cout << std::endl;

    for(int i = weeks-1; i >= 0; i--){
        std::cout << std::left << std::setw(10) << "Week " + std::to_string(i+1); 
        for(int j = days-1; j >= 0; j--){
            double val = dataTable[i][j];
            std::cout << std::right << std::setw(width);
            if(val > 99999)
                std::cout << std::fixed << std::setprecision(2) 
                          << std::scientific << val << " ";
            else
                std::cout << std::fixed << std::setprecision(2)
                      << val << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::defaultfloat;
}