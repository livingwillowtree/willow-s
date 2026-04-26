#include <iostream>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PROTOTYPES
int getIntInput();
void manualEnd(int initialBalance);
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MAIN LOGIC FLOW
int main(){
    int initialBalance = 0, withdrawal = 0;
    std::cout << "[======== ATM MF ========]\n\n" << std::endl;

    std::cout << "Give initial account balance." << std::endl;
    initialBalance = getIntInput();

    while(initialBalance > 0){
        std::cout << "Give withdrawal amount.[-1 to stop]" << std::endl;
        withdrawal = getIntInput();
        //"The loop will process the withdrawals until any of the conditions occur:
        //▪ The withdrawal amount is 0
        //▪ The account balance becomes 0
        //▪ The user chooses to stop withdrawing money"
        // need i say more why we have 2 sentinels? 
        // sentinel
        if(withdrawal == -1 || withdrawal == 0){
            manualEnd(initialBalance);
            break;
        }
        if(withdrawal < -1){
            std::cout << "Invalid amount." << std::endl;
            continue;
        }
        if(withdrawal > initialBalance){
            std::cout << "Insufficient balance!!" << std::endl;
            continue;
        }
        initialBalance -= withdrawal;
        std::cout << "Remaining Balance: " << initialBalance << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Thank You!!" << std::endl;
    return 0;
}

int getIntInput(){
    int input = 0;

    while(true){
        std::cout << ">> ";
        std::cin >> input;
        if(std::cin.fail()){
            std::cout << "Invalid Input." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        break;
    }

    return input;
}

void manualEnd(int initialBalance){
    std::cout << "Transaction ended." << std::endl;

    std::cout << "Remaining balance: " << initialBalance << std::endl;
}