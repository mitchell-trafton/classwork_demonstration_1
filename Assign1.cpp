//*******************************************
//
// Assign1.cpp
// CSCI 463
//
// Created by Mitchell Trafton (z1831076)
//
//*******************************************

#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::hex;
using std::dec;
using std::setw;
using std::setfill;

void printBinFloat (int32_t x){
    /***************************
     * takes in a 32-bit signed integer and displays the following:
     * 1) hex and binary representation
     * 2) sign bit
     * 3) the exponent (hex and decimal)
     * 4) the significand
     * 5) the full number printed in binary
     * 
     * parameters:
     * x -> 32-bit hex number to display information on
     **************************/
    //vars
    uint32_t binConvert = 0x80000000; //used for converting to binary
    uint32_t sign = (uint32_t)x >> 31;//sign bit
    int32_t exponent = (((uint32_t)x << 1) >> 24);
        exponent -= 127;
    uint32_t significand = ((uint32_t)x << 9) >> 9;

    //print hex and binary representations
    cout << "0x" << setfill('0') << setw(8) << hex << x << " = ";
    for(size_t i = 1; i <= 32; ++i){
        cout << (x & binConvert ? '1':'0');
        if (i % 4 == 0) cout << " ";
        binConvert >>= 1;
    }
    cout << endl;

    //print sign bit
    cout << "sign: " << sign << endl;

    //print exponent
    cout << setfill((exponent < 0)?'f':'0');
    cout << " exp: 0x" << setw(8) << exponent << std::dec << " (" << exponent << ")\n";

    //print significand
    cout << setfill('0');
    cout << " sig: 0x" << setw(8) << hex << significand << endl;

    //print full number in binary
    //print sign
    if (sign == 0) cout << "+";
    else cout << "-";

    //check for special cases
    //infinity
    if (exponent == 0x00000080 && significand == 0){
        cout << "inf";
        return;
    }
    //zero
    if (x == 0 || x == -2147483648){
        cout << "0";
        return;
    }

    //print value
    int cntr = 0;
    bool decimalPlaced = false; //true if decimal point has been placed
    binConvert = 0x00400000;
    //output = 1
    if (exponent == 0){
        cout << "1.";
        for (size_t i = 0; i < 23; ++i){
            cout << (significand & binConvert ? '1':'0');
            binConvert >>= 1;
        }
    }
    // output > 1
    else if (exponent > 0){
        cout << "1";
        while (cntr < 23 || cntr < exponent){
            if (cntr == exponent) {
                cout << ".";
                decimalPlaced = true;
            }
            cout << (significand & binConvert ? '1':'0');
            binConvert >>= 1;
            cntr++;
        }
        if (!decimalPlaced) cout << ".0";
    }
    //output < 1
    else{
        cout << "0.";
        if (exponent < -1){
            for (size_t i = 0; i < (exponent * -1) - 1; ++i){
                cout << "0";
            }
        }
        cout << "1";
        for (size_t i = 0; i < 23; ++i){
            cout << (significand & binConvert ? '1':'0');
            binConvert >>= 1;
        }
    }
}

int main(){
    /*
    * Asks user for hex numbers and puts them through printBinFloat() in a loop
    */
    uint32_t x; //stores user input

    while(true){
        cout << "\nEnter a hex number: ";
        cin >> hex >> x;

        //call printBinFloat() to display information on x
        printBinFloat(x);
    }
}