
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);
int locateDecimalPoint(const char numString[]);
int getLength(const char numString[]);

bool add(int char1, int numerator1, int denominator1, int char2, int numerator2, int denominator2, char result[], int len)
bool subtract(int char1, int numerator1, int denominator1, int char2, int numerator2, int denominator2, char result[], int len)

bool multiply(int char1, int numerator1, int denominator1, int char2, int numerator2, int denominator2, char result[], int len)
bool divide(int char1, int numerator1, int denominator1, int char2, int numerator2, int denominator2, char result[], int len)

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
    c1 = 2;
    n1 = 5;
    d1 = 10;

    c2 = 1;
    n2 = 25;
    d2 = 100; 

    //if the c-string can hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout << "Addition Answer: "<< answer << endl;
    }    
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Divison Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

    //Test for subtract() function
    if(subtract(c1, n1, d1, c2, n2, d2, answer, 10)){
        
        cout << "Subtraction Answer: " << answer << endl;
    }

    //Test for multiply() method
    if(multiply(c1, n1, d1, c2, n2, d2, answer, 10)){
        cout << "Multiplication Answer: " << answer << endl;
    }


    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    //hard coded return value to make the main() work
    c = 0;
    int decimalPoint = locateDecimalPoint(numString);
    char character = '0';
    int powOfTen = 1;
    for (int i = decimalPoint - 1; i >= 0; i--)
    {
        character = numString[i];
        c += (character - '0') * powOfTen;
        powOfTen *= 10;
    }
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //hard coded return value to make the main() work
    numerator = 0;
    denominator = 0;
    char mantissa = '0';
    int powOfTen = 1;
    int decimalPoint = locateDecimalPoint(numString);
    int lengthOfArray = getLength(numString);
    for (int i = lengthOfArray - 1; i > decimalPoint; i--)
    {
        mantissa = numString[i];
        numerator += (mantissa - '0') * powOfTen;
        powOfTen *= 10;
    }
    denominator = powOfTen;

    return true;
}
//--

=======
int locateDecimalPoint(const char numString[])
{
    //Locates decimal point position within the character array.
    int index = 0;
    while (numString[index] != '.')
    {
        index++;
    }
    return (index);
}
//--
int getLength(const char numString[])
{
    //Returns the length of the character array.
    int index = 0;
    while (numString[index] != '\0')
    {
        index++;
    }
    return (index);
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

    // Add to array
    addToArray(charSum, fracSum, result, len);
    
    return true;
}
//--
bool subtract(int char1, int numerator1, int denominator1, int char2, int numerator2, int denominator2, char result[], int len)
{    
    // Find common denominator and scale numerators
    int commDenom = denominator1 * denominator2;
    int num1_scaled = numerator1 * denominator2;
    int num2_scaled = numerator2 * denominator1;    

    // Subtract Fractions
    int fracDiff = 0;

    if(num1_scaled < num2_scaled){
        //Borrow from char1
        num1_scaled += commDenom;
        char1-=1;
        fracDiff = num1_scaled - num2_scaled;        
    }else{
        fracDiff = num1_scaled - num2_scaled;
    }

    // Subtract characteristics
    int charDiff = char1 - char2;

    // Add to array
    addToArray(charDiff, fracDiff, result, len);
    
    return true;
}
//--
bool multiply(int char1, int numerator1, int denominator1, int char2, int numerator2, int denominator2, char result[], int len)
{
    // Convert to improper fractions
    int newNumerator1 = (char1 * denominator1) + numerator1;
    int newNumerator2 = (char2 * denominator2) + numerator2;

    // Calculate numerator
    int finalNumerator = newNumerator1 * newNumerator2;
    int finalDenominator = denominator1 * denominator2;

    // Convert back to mixed number
    int charProduct = finalNumerator / finalDenominator;
    int finalFracNum = finalNumerator % finalDenominator;

    addToArray(charProduct, finalFracNum, result, len);

    return true;
}
//--
bool divide(int char1, int numerator1, int denominator1, int char2, int numerator2, int denominator2, char result[], int len)
{
    // Check for division by zero
    if ((char2 == 0 && numerator2 == 0) || denominator2 == 0){
        return false;
    }    
    
    // Convert to improper fractions
    int newNumerator1 = (char1 * denominator1) + numerator1;
    int newNumerator2 = (char2 * denominator2) + numerator2;

    // Multiply by reciprocal
    int finalNumerator = newNumerator1 * denominator2;
    int finalDenominator = denominator1 * newNumerator2;

    // Convert back to mixed number
    int charQuotient = finalNumerator / finalDenominator;
    int fracQuotient = finalNumerator % finalDenominator;
    
    addToArray(charQuotient, fracQuotient, result, len);
    
    return true;
}

//-- Add integers to array
void addToArray(int charSum, int fracSum, char results[], int len) {
    int i = 0;

    // Reverse and add the characteristic part (before the decimal)
    if (charSum == 0) {
        results[i++] = '0';
    } else {
        int copy_of_charSum = charSum;
        // Temporary array to store the reversed characteristic part
        char reverseChar[len];
        int reverseCharIndex = 0;
        
        while (copy_of_charSum > 0) {
            reverseChar[reverseCharIndex++] = '0' + (copy_of_charSum % 10); // Get the last digit and convert it to a character
            copy_of_charSum /= 10; // Remove the last digit
        }
        
        // Copy the reversed characteristic part to the result array
        for (int j = reverseCharIndex - 1; j >= 0; j--) {
            results[i++] = reverseChar[j];
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
