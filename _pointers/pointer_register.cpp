#include <iostream>
#include <string>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< CONSTANTS
const double TAX_RATE = 0.12;
const double SR_PWD_DISCOUNT = .20;
const double STUDENT_DISCOUNT = .10;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PROTOTYPES
void displayMenu();
int getIntInput();
int getMenuInput();
void handleOrders(double* subTotal);
void handleDiscount(double* discount);
void handleFinalCalcs(double subTotal, double discount, double* afterTax, double* discountAmount, double* finalTotal);
void handlePayment(double finalTotal, double* change, double* totalPayment);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MAIN LOGIC FLOW
int main(){
    displayMenu();

    double subTotal = 0.0;
    double discount = 0.0;
    double discountAmount = 0.0;
    double afterTax = 0.0;
    double finalTotal = 0.0;
    double totalPayment = 0.0;
    double change = 0.0;

    handleOrders(&subTotal);
    if(subTotal == 0){
        std::cout << "Cancelling... Thank you!!" << std::endl;
        return 0;
    }
    
    handleDiscount(&discount);

    handleFinalCalcs(subTotal, discount, &afterTax, &discountAmount, &finalTotal);
    
    std::cout << "=====================\n"
                 "=       TOTAL:      =\n"
                 "=====================\n\n" << std::flush;
    std::cout << "Subtotal:            " << subTotal << std::endl;
    std::cout << "After Tax:           " << afterTax << std::endl;
    std::cout << "Discount:            " << discountAmount << std::endl;
    std::cout << "Final Amount to pay: " << finalTotal << std::endl;

    handlePayment(finalTotal, &change, &totalPayment);

    std::cout << std::endl;
    std::cout << "Total Amount Paid:    " << totalPayment << std::endl;
    std::cout << "Change:               " << change << std::endl;
    std::cout << std::endl;
    std::cout << "Thank you!" << std::endl;

    return 0;
}

void displayMenu(){
    std::string menuString = "=====================\n"
                             "=        MENU       =\n"
                             "=====================\n"
                             "   a. Burger - 120   \n"
                             "   b. Pizza  - 250   \n"
                             "   c. Fries  - 80    \n"
                             "   d. Pasta  - 200   \n"
                             "   e. Soda   - 50    \n";
    std::cout << menuString << std::flush;
    
    return;
}
//<<<<<<<<<<<<<<<<<< INT INPUTS
int getIntInput(){
    int input = 0;

    while(true){
        std::cout << ">> ";
        std::cin >> input;
        if(std::cin.fail() || input < 0){
            std::cout << "Invalid input. Positive integers only." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        return input;
    }
    return 0;
}

//<<<<<<<<<<<<<<<<<< MENU INPUTS
int getMenuInput(){
    char input = 'a';
    while(true){
        std::cout << ">> ";
        
        std::cin >> input;
        input = std::tolower(input);
        
        //------------------clear cin buffer
        std::cin.ignore(10000, '\n');

        switch(input){
            case 'a': 
                std::cout << "Chose: Burger" << std::endl;
                return 120;
            case 'b': 
                std::cout << "Chose: Pizza" << std::endl;
                return 250;
            case 'c': 
                std::cout << "Chose: Fries" << std::endl;
                return 80;
            case 'd': 
                std::cout << "Chose: Pasta" << std::endl;
                return 200;
            case 'e': 
                std::cout << "Chose: Soda" << std::endl;
                return 50;
            case 'x':
                return 0;
            default:
                std::cout << "Please choose from the options.(a-e or x)" << std::endl;
                break;//dont return, loop back
        }
    }
    
    return 0;

}

void handleOrders(double* subTotal){
    int numItems = 0;
    int itemPrice = 0;

    std::cout << "Please indicate the number of items you want to order.(0 to cancel)" << std::endl;
    numItems = getIntInput();
    if(numItems == 0) return;

    std::cout << std::endl;
    std::cout << "Now please identify your chosen items.(a-e, x to cancel)" << std::endl;
    for(int i = 0; i < numItems; i++){
        itemPrice = getMenuInput();
        if(itemPrice == 0){
            *subTotal = 0;
            return;
        }
        *subTotal += itemPrice;
    }

    return;
}

void handleDiscount(double* discount){
    int type = 0;
    std::cout << "Discount Card?([1]Senior/PWD - 20%, [2]Student - 10%, [Any]None - 0%)" << std::endl;
    type = getIntInput();
    if(type == 1) *discount = SR_PWD_DISCOUNT;
    else if(type == 2) *discount = STUDENT_DISCOUNT;
    else *discount = 0.0;
    return;
}

void handleFinalCalcs(double subTotal, double discount, double* afterTax, double* discountAmount, double* finalTotal){
    *afterTax = subTotal + subTotal*TAX_RATE;
    
    *discountAmount = *afterTax * discount;
    *finalTotal = *afterTax - *discountAmount;

    return;
}

void handlePayment(double finalTotal, double* change,  double* totalPayment){
    double input;

    std::cout << std::endl;
    std::cout << "Please pay up." << std::endl;

    while(true){
        std::cout << ">> ";
        std::cin >> input;
        if(std::cin.fail() || input < 0){
            std::cout << "Invalid input. Positive numbers only." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        *totalPayment += input;

        if(*totalPayment < finalTotal){
            std::cout << "Insufficient amount!" << std::endl;
            std::cout << "You still owe: " << finalTotal - *totalPayment << std::endl;
            continue;
        }

        break;
    }

    *change = *totalPayment - finalTotal;

    return;
}