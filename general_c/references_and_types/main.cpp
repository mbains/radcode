/* 
 * File:   main.cpp
 * Author: mbains
 *
 * Created on February 9, 2014, 12:08 PM
 */

#include <cstdlib>
#include <iostream>

 
using namespace std;

/* returns just a  string*/
string str_function() {
    return string("testing");
}

/* Multiply at compile time using constant expressions! */
constexpr  int fast_multiply(int x, int y) {
    return x*y;
}

/*
 * 
 */
int main(int argc, char * argv[]) {

    int i = 42, j = 88;
    
    //const references
    const int &r1 = i; 
    const int &r2 = 42;
    const int &r3 = r1 *2;
    const int &r4 = r1*2;
    int &wr = j;    
    wr = 99;

    cout << "j: " << j << " i: " << i <<"\n";
     
    //pointers and const, pointer to const
    const double pi = 3.14;
    //double *ptr = &pi; //error  invalid conversion from ‘const double*’ to ‘double*’
    const double *cptr = &pi;
    //*cptr = 42; error
    
    //const pointer
    int errNumb = 0;
    int *const currErr = &errNumb;//const pointer that will always point to errNumb;
    //currErr++; //increment of read-only variable ‘currErr’
    
    //const pointer to a const object
    const int value = 42;
    const int *const c_ptr = &value;  
    //*c_ptr = 33; //error
    //c_ptr = NULL; //error  

    
    auto v_auto = "a string";
    cout << v_auto << endl;
    
    constexpr int cexp = fast_multiply(7,7);
    cout << "fast_multiply(7,7)= " << cexp << endl;

    decltype(str_function()) x;
    x = v_auto;
    cout << "x also is " << x << endl;
    return 0;
}

