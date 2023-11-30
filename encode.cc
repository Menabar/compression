#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <gmpxx.h>

using namespace std;

mpz_class nearestLowestPowerOf2(mpz_class num){
    mpz_class seed = 1;
    mpz_class i = 0;
    for(i=0; seed<=num; i++){
        seed *= 2;
    }
    return i-1;
}

int main(int argc, char* argv[]){
    // Check an input file was given
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " <intput_file>" << endl;
        return 1;
    }

    // File path
    const string file_path = argv[1];

    // Open the file in binary mode
    ifstream file(file_path, ios::binary);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        cerr << "Error opening the file." << endl;
        return 1;
    }

    // Read file into data vector
    ifstream stream(file_path, ios::in | ios::binary);
    vector<char> data((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    // Close the file
    file.close();

    // Vector to store binary and root indices
    vector<char> binary_data;
    vector<int> indices;

    // Convert data to binary
    for(char c: data) {
        int value = c;
        //cout << "data: " << bitset<8>(value) << endl;
        for(int i=7; i>-1; i--){
            binary_data.push_back(bitset<8>(value)[i]);
        }
    }

    // Store binary
    // for(int i=0; i<binary_data.size()-1; i++){
    //     if(binary_data[i] != binary_data[i+1]){
    //         indices.push_back(i);
    //         cout << i << endl;
    //     }
    // }

    // Process data
    mpz_class total = 0;
    for(int i=0; i<binary_data.size()-1; i++){
        total++;
        if(binary_data[i] != binary_data[i+1]){
            total*=10;
        }
    }
    total++;
    // cout << total << endl;
    // cout << nearestLowestPowerOf2(total) << endl;
    // return 0;
    mpz_class base(2);
    mpz_class exp(nearestLowestPowerOf2(total));
    mpz_class mod(total + (total % 2 == 0 ? 1 : 0));
    mpz_class result;
    // Perform modular exponentiation: result = base^exp mod mod
    mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());

    //cout << total << endl;
    while(total > 0 /*&& result.get_ui() != 0*/){
        mpz_class base(2);
        mpz_class exp(nearestLowestPowerOf2(total));
        mpz_class mod(total + (total % 2 == 0 ? 1 : 0));
        mpz_class result;

        mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
        //cout << "power of 2: " << result << endl;
        cout << nearestLowestPowerOf2(total) << ",";
        if(nearestLowestPowerOf2(total) == 0){
            return 0;
        }
        total -= result;
    }
    //cout << binary_data[0];
    return 0;
}