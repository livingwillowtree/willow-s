#include <iostream>
#include <cmath>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PROTOTYPES
int getIntInput();
int getFactorCount();
void getGCF_LCM(int num1, int num2, int* GCF, int* LCM);
void getFactorCount(int GCF, int* factorCount);
void getFactors(int GCF, int factorCount, int factors[]);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MAIN LOGIC FLOW
int main(){
    int num1 = 0, num2 = 0;
    int factorCount = 0;
    int GCF = 0, LCM = 0;

    //----------------------------------- Get the nums
    std::cout << "Input Positive Int for Num1: " << std::endl;
    num1 = getIntInput();
    std::cout << "Input Positive Int for Num2: " << std::endl;
    num2 = getIntInput();

    //------------------------------------ Get computing baby
    getGCF_LCM(num1, num2, &GCF, &LCM);
    getFactorCount(GCF, &factorCount);
    int factors[factorCount];
    getFactors(GCF, factorCount, factors);

    //------------------------------------- Display timee
    std::cout << "\n" << std::endl;
    std::cout << "Num1 : " << num1 << "\tNum2 : " << num2 << std::endl;
    std::cout << "Greatest Common Factor (GCF) : " << GCF << std::endl;
    std::cout << "Least Common Multiple (LCM)  : " << LCM << std::endl;
    std::cout << "Common Divisors              : ";
    for(int i = 0; i < factorCount; i++){
        std::cout << factors[i] << ((i<factorCount-1) ? ", " : "");
    }

    std::cout << "\n\n" << std::endl;

    return 0;
}

int getIntInput(){
    int input = 0;

    while(true){
        std::cout << ">> ";
        std::cin >> input;

        if(std::cin.fail() || input <= 0){
            std::cout << "Invalid Input. Positive Integers Only." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        break;
    }

    return input;
}

void getGCF_LCM(int num1, int num2, int* GCF, int* LCM){
    //very cool algo called Euclidean Algo, shouldnt be against the rules
    //code will figure em out naturally apparently
    int smaller = num1;
    int bigger = num2;
    int remainder = 0;
    while(true){
        remainder = bigger%smaller;
        if(remainder == 0)
            break;
        bigger = smaller;
        smaller = remainder;
    }
    *GCF = smaller;
    *LCM = (num1/(*GCF)) * num2;
}

void getFactorCount(int GCF, int* factorCount){
    int sqrtGCF = sqrt(GCF);

    for(int i = 1; i <= sqrtGCF; i++){
        if(i * i == GCF)
            (*factorCount)++;
        else if(GCF%i == 0)
            *factorCount +=2;
    }
}

void getFactors(int GCF, int factorCount, int factors[]){
    int sqrtGCF = sqrt(GCF);
    int iLeft = 0;
    int iRight = factorCount - 1;

    for(int i = 1; i <= sqrtGCF; i++){
        if(i * i == GCF){
            factors[iLeft++] = i;
        }
        else if(GCF%i == 0){
            factors[iLeft++] = i;
            factors[iRight--] = GCF/i;
        }
    }
}