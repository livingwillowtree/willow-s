#include <iostream>
#include <cmath>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PROTOTYPES
int getIntInput(int);
void fillMatrix(int, int*);
void sumDiagonals(int&, int&, int, int*);
void avrgPrimes(float&, int, int*);
bool isPrime(int);
void printMatrix(int, int*);
void printTransposed(int, int*);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MAIN LOGIC FLOW
int main(){
    int matrixSideLen = 0;
    int diagonalSum = 0;
    int aDiagonalSum = 0;
    float primesAverage = 0.0;

    std::cout << "--- NUM MATRIX LAB --- \n\n" << std::endl;

    std::cout << "Enter the side len of the square matrix: " << std::endl;
    matrixSideLen = getIntInput(1);

    //------------------------------------ PREPARE MATRIX
    // yo forget 2d arrays, look at this clean ass 1d array
    int* arr = new int[matrixSideLen * matrixSideLen];
    fillMatrix(matrixSideLen, arr);

    //------------------------------------ CALCULATE
    sumDiagonals(diagonalSum, aDiagonalSum, matrixSideLen, arr);
    avrgPrimes(primesAverage, matrixSideLen, arr);

    //------------------------------------ PRINT NOWWWW
    std::cout << "\n" << std::endl;
    printMatrix(matrixSideLen, arr);
    std::cout << std::endl;
    std::cout << "Sum of Diagonal      : " << diagonalSum << std::endl;
    std::cout << "Sum of Anti-diagonal : " << aDiagonalSum << std::endl;
    std::cout << "Average of Primes    : " << primesAverage << std::endl;
    std::cout << std::endl;
    printTransposed(matrixSideLen, arr);
    std::cout << std::endl;

    delete[] arr;

    return 0;
}

int getIntInput(int min){
    int input = 0;
    while(true){
        std::cout << ">> ";
        std::cin >> input;
        if(std::cin.fail() || input < min){
            std::cout << "Invalid input." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            continue;
        }
        return input;
    }
}

void fillMatrix(int sideLen, int* arr){
    // yeah yeah i know i can do a single for loop since its 1d now
    // but i did these when i had a 2d, shut up, i aint refactoring these
    for(int i = 0; i < sideLen; i++){
        for(int j = 0; j < sideLen; j++){
            std::cout << "Enter val for R" << i+1 << 
                         " C" << j+1 << ": " << std::endl;
            *(arr + (i * sideLen) + j) = getIntInput(0);
        }
    }
}

void sumDiagonals(int& diagonalSum, int& aDiagonalSum, int sideLen, int* arr){
    //--------------------------------its a square matrix, its symmetrical, duh
    for(int i = 0; i < sideLen; i++){
        //---------------------------------------00, 11, 22
        diagonalSum += *(arr + (i * sideLen) + i);// arr[i][i], in case you dont get it
        //---------------------------------------20, 11, 02
        aDiagonalSum += *(arr + ((sideLen - i -1) * sideLen) + i);// arr[s-i-1][i], in case you dont get it
    }
}

void avrgPrimes(float& primesAverage, int sideLen, int* arr){
    
    int primesSum = 0;
    int primeCount = 0;
    int val;
    //-----------------------------------fine, nested loop for readability >:[
    for(int i = 0; i < sideLen; i++){
        for(int j = 0; j < sideLen; j++){
            val = *(arr + (i * sideLen) + j);// arr[i][j] in case you dont get it, why do i even explain
            if(isPrime(val)){
                primesSum += val;
                primeCount++;
            }
        }
    }
    if(primeCount == 0)
        return;

    primesAverage = (float)primesSum/primeCount;
}

bool isPrime(int num){
    // prime must be greater than 1
    if(num <= 1)
        return false;
    // 'easy catch' 2 and 3
    if(num > 1 && num < 4)
        return true;
    // 'easy catch' even nums
    if(num%2 == 0)
        return false;
    
    //optimization, root n trick 
    int sqrtNum = std::sqrt(num);

    for(int i = 3; i <= sqrtNum; i += 2){
        if(num%i == 0)
            return false;
    }
    return true;
}

void printMatrix(int sideLen, int* arr){
    std::cout << "--- Original Matrix ---\n" << std::endl;
    for(int i = 0; i < sideLen; i++){
        for(int j = 0; j < sideLen; j++)
            std::cout << *(arr + (i * sideLen) + j) << " ";
        std::cout << std::endl;
    }
}

void printTransposed(int sideLen, int* arr){
    std::cout << "--- Transposed Matrix ---\n" << std::endl;
    for(int i = 0; i < sideLen; i++){
        for(int j = 0; j < sideLen; j++)
            std::cout << *(arr + (j * sideLen) + i) << " ";
        std::cout << std::endl;
    }
}