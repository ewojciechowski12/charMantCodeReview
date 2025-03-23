
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

void addToArray(int charSum,int fracSum, char result[], int len);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "123.456"; 
    int c, n, d;

    //if both conversions from c-string to integers can take place
    if(characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout<<"c: "<<c<<endl;
        cout<<"n: "<<n<<endl;
        cout<<"d: "<<d<<endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout<<"Error on input"<<endl;
    }

    //room for 9 characters plus the null terminating character
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    //initialize the values
    c1 = 1;
    n1 = 1;
    d1 = 10;

    c2 = 2;
    n2 = 2;
    d2 = 10; 

    //if the c-string can hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Addition Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    //hard coded return value to make the main() work
    c = 123;
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //hard coded return value to make the main() work
    numerator = 456;
    denominator = 1000;
    return true;
}
//--
bool add(int char1, int numerator1, int denominator1, int char2, int numerator2, int denominator2, char result[], int len)
{    
    // Find common denominator and scale numerators
    int commDenom = denominator1 * denominator2;
    int num1_scaled = numerator1 * denominator2;
    int num2_scaled = numerator2 * denominator1;

    // Add characteristics
    int charSum = char1 + char2;

    // Add fractions
    int fracSum = num1_scaled + num2_scaled;

    // Normalize result
    charSum += fracSum / commDenom; // Add whole part from fraction sum
    fracSum %= commDenom;

    cout << "Integer part: " << charSum << endl;
    cout << "Fraction part: " << fracSum << " / " << commDenom << endl;  

    addToArray(charSum, fracSum, result, len);
    
    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers
    return true;
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to multiply the two numbers
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    result[0] = '0';
    result[1] = '.';
    result[2] = '5';
    result[3] = '6';
    result[4] = '2';
    result[5] = '5';
    result[6] = '\0';
    
    return true;
}

//-- Add integers to aray
void addToArray(int charSum, int fracSum, char results[], int len) {
    int i = 0;

    // Reverse and add the characteristic part (before the decimal)
    if (charSum == 0) {
        results[i++] = '0';
    } else {
        int temp = charSum;
        // Temporary array to store the reversed characteristic part
        char tempArr[len];
        int tempIndex = 0;
        
        while (temp > 0) {
            tempArr[tempIndex++] = '0' + (temp % 10); // Get the last digit and convert it to a character
            temp /= 10; // Remove the last digit
        }
        
        // Copy the reversed characteristic part to the result array
        for (int j = tempIndex - 1; j >= 0; j--) {
            results[i++] = tempArr[j];
        }
    }

    // Add the decimal point
    results[i++] = '.';

    // Reverse and add the fractional part (after the decimal)
    if (fracSum == 0) {
        results[i++] = '0';
    } else {
        int temp = fracSum;
        // Temporary array to store the reversed fractional part
        char tempArr[len];
        int tempIndex = 0;

        while (temp > 0) {
            tempArr[tempIndex++] = '0' + (temp % 10); // Get the last digit and convert it to a character
            temp /= 10; // Remove the last digit
        }

        // Copy the reversed fractional part to the result array
        for (int j = tempIndex - 1; j >= 0; j--) {
            results[i++] = tempArr[j];
        }
    }

    // Add the null terminator at the end
    results[i] = '\0';
}
