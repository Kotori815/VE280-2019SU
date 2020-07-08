#include <iostream> 
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;


int test_1(int input) // test for triangle number
{
    double index_big; // the index of the biggest triangle number (TN) smaller than input.
    int result;

    index_big = floor(sqrt(0.25 + 2 * input)-0.5); 

    if (0.5 * (index_big + 1) * index_big == input) {result = 1;}
    else {result = 0;}
    // if the biggest TN tsmaller than input equals input, than input is TN.

    return result;
}

int test_2(int input) // test for palindrome
{
    int inversed, temp, result; // to find the inversed number from the input
    inversed = 0;
    temp = input;

    while  (temp / 10 > 0)
    {
        inversed = inversed * 10 + temp % 10;
        temp = temp / 10;   
    }
    inversed = inversed * 10 + temp % 10;
    // in this way the first x-th digit becomes the last x-th digit

    if (inversed == input) {result = 1;}
    else {result = 0;}

    return result;
}

int test_3(int input) // test for odious number
{
    int num_of_one; // directly find number of 1 in binary form
    int temp, result;

    num_of_one = 0;
    temp = input;

    while (log2(temp) != floor(log2(temp)))
    {
        num_of_one++;
        temp = temp - pow(2, floor(log2(temp)));
    }
    num_of_one++;
    //every 2^n component in the original number corresponds
    //to a "1" in the binary form, so to find number of 1 is to find 
    //number of 2^n components

    if (num_of_one % 2 == 0) {result = 0;}
    else {result = 1;}

    return result;
}

int test_4(int input) // test for extravagant number
{
    int dig_of_fac;//total digits in the prime factorization
    int dig_of_inp;//digits of the input number
    int temp, result;

    int factor, power;// temperary, show current factor and it's power

    dig_of_inp = ceil(log10(input));
    dig_of_fac = 0;
    temp = input;

    for (factor = 2; factor <= input;factor++)
    {
        power = 0;
        while (temp > 1)
        {  
            if (temp % factor ==0)
            {
                power++;
                temp = temp / factor;
            }
            else break;
        }

        if (power > 0) {dig_of_fac = dig_of_fac + ceil(log10(factor));}
        if (power > 1) {dig_of_fac = dig_of_fac + ceil(log10(power));}
    }
	
	
    if (dig_of_inp < dig_of_fac) {result = 1;}
    else {result = 0;}
	
    return result;
}

int main()
{
    int num_to_test, test_type, test_result;
    
    num_to_test = 0;
    test_type =0;

    while ((num_to_test < 1) || (num_to_test > 10000000) || (test_type < 1) || (test_type > 4))
    {
        cout << "Please enter the integer and the test number: ";
        cin >> num_to_test >> test_type;
    }
    // secure an integer input in [1,10000000] and type number in [1,4]

    switch (test_type)
    {
    case 1:
        test_result = test_1(num_to_test);
        break;

    case 2:
        test_result = test_2(num_to_test);
        break;

    case 3:
        test_result = test_3(num_to_test);
        break;
    
    case 4:
        test_result = test_4(num_to_test);
        break;

    }
    
    cout << test_result << endl;

    return 0;
    
}
