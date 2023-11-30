#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <gmpxx.h>

using namespace std;

int main(int argc, char* argv[]){
    mpz_class sum = 0;
    mpz_class base_(2);
    mpz_class result_;

    std::ifstream inputFile("output");

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
        return 1;  // Return an error code
    }

    // Read and parse comma-delimited numbers
    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<int> numbers;

        while (std::getline(ss, token, ',')) {
            int number;
            std::istringstream(token) >> number;
            numbers.push_back(number);
        }

        // Process the numbers as needed
        for (int number : numbers) {
            mpz_pow_ui(result_.get_mpz_t(), base_.get_mpz_t(), number);
            sum += result_;
        }
        //cout << sum << endl << endl;
    }

    // Close the file
    inputFile.close();

    std::ofstream outputFile("binary_data.bin", std::ios::binary);

    // Check if the file is open
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
        return 1;  // Return an error code
    }

    string binaryString = "";
    string strNumber = mpz_get_str(nullptr, 10, sum.get_mpz_t());

    for(int i=0; i<strNumber.length(); i++){
        for(int j=0; j<strNumber.at(i)-'0'; j++){
            if(i % 2 == 0){
                binaryString += "0";
            }
            else{
                binaryString += "1";
            }
        }
    }

    std::vector<char> binaryData;
    for (size_t i = 0; i < binaryString.length(); i += 8) {
        // Extract a set of 8 digits
        std::string setOf8Digits = binaryString.substr(i, 8);
        unsigned long ulongValue = std::bitset<8>(setOf8Digits).to_ulong();
        binaryData.push_back(static_cast<char>(ulongValue));
    }
    
    // Write binary data to the file
    outputFile.write(binaryData.data(), binaryData.size());

    // Close the file
    outputFile.close();

    return 0;
}