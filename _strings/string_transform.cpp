#include <iostream>
#include <string>
//------------------other libs are banned

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< FUNCTION PROTOTYPES
void countVowels(std::string original, int* vowelCount, int vowelPos[]);
void countWords(std::string original, int* wordCount);
void capitalize(int vowelCount, int vowelPos[], std::string* uppercased);
void reverse(std::string* reversed);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MAIN LOGIC FLOW
int main(){
    std::string original = "", uppercased = "", reversed = "";
    int vowelCount = 0, wordCount = 0;

    std::cout << "Enter A Sentence.(Must end with a period)" << std::endl;

    while(true){
        std::cout << ">> ";
        std::getline(std::cin, original);

        //must be at least a char and a period, whats stopping them 
        //from doing a symbol? a space? no one, but its a pain in the ass
        //so this does it
        if(original.length() < 2 || original[original.length()-1] != '.'){
            std::cout << "Invalid Input." << std::endl;
            continue;
        }

        break;
    }

    //-----------------------create an array to hold the vowel
    //                       positions so we dont have to check again
    int vowelPos[1000] = {0};
    uppercased = original;
    reversed = original;
    countVowels(original, &vowelCount, vowelPos);
    countWords(original, &wordCount);
    capitalize(vowelCount, vowelPos, &uppercased);
    reverse(&reversed);

    std::cout << "\n\n";
    std::cout << "--- RESULTS ---\n\n";
    std::cout << "Original:          " << original << std::endl;
    std::cout << "Vowel Count:       " << vowelCount << std::endl;
    std::cout << "Word Count:        " << wordCount << std::endl;
    std::cout << "Uppercased Vowels: " << uppercased << std::endl;
    std::cout << "Reversed:          " << reversed << std::endl;

    return 0;
}

void countVowels(std::string original, int* vowelCount, int vowelPos[]){
    for(int i = 0; i < original.length(); i++){
        char c = original[i];
        //--------------------manual checking :(
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'){
            //--------------------------store index then increment count
            vowelPos[*vowelCount] = i; 
            (*vowelCount)++;
        }
    }

    return;
}

void countWords(std::string original, int* wordCount){
    //should be fine to ignore the first char since it can still count if the first word is a letter
    for(int i = 1; i < original.length(); i++){
        char c = original[i];
        //this would count trailing space(blah .), but our code is
        //already being held tby the hope of the user being decent
        //so this wouldnt matter much :)
        if(c == ' ' && original[i-1] != ' ')
            (*wordCount)++;
    }
    //--------------account for the last word not detectable
    (*wordCount)++;

}

void capitalize(int vowelCount, int vowelPos[], std::string* uppercased){
    for(int i = 0; i < vowelCount; i++){
        char *c = &((*uppercased)[vowelPos[i]]);
        *c = std::toupper(*c);//works for english only, but no libs, so this is the best we have
    }
    return;
}

void reverse(std::string* reversed){
    int l = (*reversed).length() - 2;
    std::string copy = *reversed;
    //---------------------------cool array reversing trick also works on strings nice
    //---------------------------again, no other libs
    for(int i = l; i >= 0; i--){
        (*reversed)[i] = copy[l-i];
    }
}