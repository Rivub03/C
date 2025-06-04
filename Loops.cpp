#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <cmath>
using namespace std;

int digit_Count(long long int x) {
    int digits = 0;
    if (x == 0) {
        cout << "Number of digits = 1";
    }
    else {
        if (x < 0) {
            x = -x;
        }
        while (x != 0) {
            x /= 10;
            digits++;
        }

    }
    cout << "The number of digits are: " << digits << endl;
    return digits;
}

int reverse_Number(int x) {
    int remainder, reverse = 0;
    int original = x;  // Keep original for comparison

    while (original != 0) {  // Use original, don't modify x
        remainder = original % 10;
        reverse = reverse * 10 + remainder;
        original /= 10;
    }
    return reverse;
}

double average() {
    double x, sum = 0;
    int n = 0;
    char choice;

    do {
        cout << "Enter number " << (n + 1) << ": ";
        cin >> x;
        sum += x;
        n++;

        cout << "Do you want to enter another number? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    double average = sum / n;
    cout << fixed << setprecision(2);
    cout << "The average of " << n << " numbers is: " << average << endl;

    return average;
}

int factorial(int x) {
    int factorial = 1;
    if (x == 0) {
        cout << "0! = 1" << endl;
        return 1;
    }
    else {
        cout << x << "! = ";
        for (x; x > 0; x--) {
            factorial *= x;
        }
        cout << "Factorial of " << x << " is = " << factorial << endl;
    }
    return factorial;
}

double power(double base, int exp) {
    if (exp == 0) return 1;

    bool isNegative = (exp < 0);
    if (isNegative) exp = -exp;

    double result = 1;
    double current_power = base;
    int loopCounter = 0;

    while (exp > 0) {
        if (exp % 2 == 1) {  // If exp is odd
            result *= current_power;
        }
        current_power *= current_power;  // Square the base
        exp /= 2;  // Halve the exponent
        loopCounter++;
    }

    cout << "The number of times the loop iterated = " << loopCounter << endl;
    if (isNegative) {
        return 1.0 / result;
    }
    else {
        return result;
    }
}
double power_Optimized(double base, int exponent) {
    double result = 1;

    bool isNegative = (exponent < 0);
    if (isNegative) exponent = -exponent;  // Make n positive
    int loopCounter = 0;

    for (int i = 0; i < exponent; i++) {
        result *= base;
        loopCounter++;
    }
    cout << "The number of times the loop iterated = " << loopCounter << endl;
    if (isNegative) {
        return 1.0 / result;
    }
    else {
        return result;
    }
}

int HCF(int num1, int num2) {

    int counter = 0;
    int hcf = 1;
    int k = 2;
    while (k <= num1 && k <= num2) {
        if (num1 % k == 0 && num2 % k == 0) {
            hcf = k;
        }
        k++;
        counter++;
    }
    cout << "The number of iterations required for slow HCF: " << counter << endl;
    return hcf;
}

int HCFeuclid(int a, int b) {
    int counter = 0;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;

        counter++;
    }

    cout << "The number of iterations required for Euclid HCF: " << counter << endl;
    return a;
}

int LCM_BruteForce(int a, int b) {
    if (a == 0 || b == 0) return 0;  // LCM with 0 is 0

    int larger = max(a, b);
    int smaller = min(a, b);

    int multiple = larger;
    while (true) {
        if (multiple % smaller == 0) {
            return multiple;
        }
        multiple += larger;
    }
}

int LCM_Efficient(int a, int b) {
    if (a == 0 || b == 0) return 0;  // LCM with 0 is 0

    a = abs(a);  // Handle negative numbers
    b = abs(b);

    return (a / HCFeuclid(a, b)) * b;  // Avoid overflow by dividing first
}

bool isPrime(int x) { //brute force approach
    int counter = 0;
    if (x == 0 || x == 1) {
        return false;
    }
    else {
        for (int i = 2; i < x; i++) {
            if (x % i == 0) {
                return false;
            }
            counter++;
        }
        cout << "The number of times the loop executed: " << counter << endl;
        return true;
    }
}

bool isPrime_Optimized(int x) { // Logic: If x has a divisor > √x, it must also have a corresponding divisor < √x
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;

    int counter = 0;
    int limit = sqrt(x);

    for (int i = 2; i <= limit; i++) {
        if (x % i == 0) {
            cout << "Loop executed: " << counter << " times" << endl;
            return false;
        }
        counter++;
    }

    cout << "Loop executed: " << counter << " times" << endl;
    return true;
}

bool isPrime_HighlyOptimized(int x) { // Skip even numbers and use 6k±1 pattern
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;

    int counter = 0;

    // Check only numbers of form 6k±1 up to √x
    for (int i = 5; i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) {
            //cout << "Loop executed: " << counter << " times" << endl;
            return false;
        }
        counter++;
    }

    //cout << "Loop executed: " << counter << " times" << endl;
    return true;
}

void perfectNumber(int x) {
    bool isPerfect = false;
    int result = 0;
    for (int i = 1; i < x; i++) {
        if (x % i == 0) {
            result += i;
        }
    }
    if (result == x) {
        isPerfect = true;
    }
    if (isPerfect) {
        cout << "Perfect" << endl;
    }
    else {
        cout << "Not Perfect" << endl;
    }
}

void perfectNumber_Optimized(int x) { //Divisors come in pairs. If i divides x, then x/i also divides x.
    if (x <= 1) {
        cout << "Not Perfect" << endl;
        return;
    }

    int sum = 1;  // 1 is always a proper divisor for x > 1
    int limit = sqrt(x);

    for (int i = 2; i <= limit; i++) {
        if (x % i == 0) {
            sum += i;  // Add the divisor

            // Add the corresponding divisor (x/i), but avoid counting √x twice
            if (i != x / i && x / i != x) {
                sum += x / i;
            }
        }
    }

    if (sum == x) {
        cout << "Perfect" << endl;
    }
    else {
        cout << "Not Perfect" << endl;
    }
}

void perfectNumber_HighlyOptimized(int x) { // Skip even numbers for odd inputs
    if (x <= 1) {
        cout << "Not Perfect" << endl;
        return;
    }
    if (x == 2) {
        cout << "Not Perfect" << endl;  // 2 is not perfect
        return;
    }

    int sum = 1;

    // For odd numbers, skip even divisors (except when x is even)
    int step = (x % 2 == 0) ? 1 : 2;
    int start = (x % 2 == 0) ? 2 : 3;

    for (int i = start; i * i <= x; i += step) {
        if (x % i == 0) {
            sum += i;
            if (i != x / i) {
                sum += x / i;
            }
        }
    }

    cout << (sum == x ? "Perfect" : "Not Perfect") << endl;
}

void armstrongNumber(int x) {
    bool isArmstrong = false;
    int remainder, sum = 0, number = x;
    while (number != 0) {
        remainder = number % 10;
        number /= 10;
        sum += pow(remainder, 3);
    }
    if (sum == x) {
        isArmstrong = true;
    }

    if (isArmstrong) {
        cout << "Armstrong Number" << endl;
    }
    else {
        cout << "Not an Armstrong Number" << endl;
    }
}

bool isPalindrome(int x) {
    int reverse = reverse_Number(x);
    if (reverse == x) {
        cout << "Palindrome/Symmetric" << endl;
        return true;
    }
    else {
        cout << "Not Symmetric/Palindrome" << endl;
        return false;
    }
}

void showDigits() {
    int x, original, remainder;
    cout << "Enter a number to show its digits in separate lines: ";
    cin >> x;
    if (x == 0) {
        cout << x << endl;
    }
    original = x;
    x = reverse_Number(x);
    while (x != 0) {
        remainder = x % 10;
        x /= 10;
        cout << remainder << endl;
    }
}

void fibonacci_Sequence() {
    int n;
    cout << "Enter number of terms (n): ";
    cin >> n;
    int zero = 0, first = 1, previous = 1, current = zero + first, next;
    cout << zero << ", " << first << ", " << current << ", ";
    for (int i = 3; i < n; i++) {
        next = previous + current;
        previous = current;
        current = next;
        cout << current << ", ";
    }
    cout << endl;
}

bool if_Fibonacci_Sequence() {
    int x;
    cout << "Enter Number to check if it's in fibonacci sequence: ";
    cin >> x;
    int zero = 0, first = 1, previous = 1, current = zero + first, next, counter = 3;
    for (current; current <= x; ) {
        next = previous + current;
        if (current == x || next == x || previous == x || zero == x) {
            cout << counter << "th term of the Fibonacci sequence" << endl;
            return true;
        }
        previous = current;
        current = next;
        counter++;
    }
    cout << "Does not exist in the fibonacci sequence" << endl;
    return false;
}
void display_Divisors(int x) {
    cout << "The divisors of " << x << " are: ";
    for (int i = 1; i < x; i++) {
        if (x % i == 0) {
            cout << i << ",";
        }
    }
    cout << x << endl;
}

void printPrimes(int x1, int x2) {
    cout << "The prime numbers between " << x1 << " and " << x2 << " are: ";
    for (int i = x1; i < x2; i++) {
        if (isPrime_HighlyOptimized(i)) {
            cout << i << ",";
        }
    }
    cout << endl;
}

void sumFirst100OddSquared() {
    int sum = 0;
    for (int i = 0; i < 100; i++) {
        if (i % 2 != 0) {
            cout << i << "^2 + ";
            sum += pow(i, 2);
        }
    }
    cout << "The sum of the squares of the first 100 odd numbers is = " << sum << endl;
}

void sum() {

}

double eulerNumber(float x, int n) { // using taylor expansion to calculate e^x
    double e_x = 0;
    double base = exp(1.0);

    for (int i = 0; i <= n; i++) {
        e_x += (pow(x, i)) / (tgamma(i + 1));
    }
    return e_x;
}

int main() {

    cout << isPrime(7919);
    cout << isPrime_Optimized(7919);
    cout << isPrime_HighlyOptimized(7919);
    perfectNumber(6); perfectNumber(10); perfectNumber(496);
    armstrongNumber(0); armstrongNumber(12); armstrongNumber(370); armstrongNumber(100);
    isPalindrome(123); isPalindrome(505); isPalindrome(89); isPalindrome(77);
    showDigits(); showDigits(); showDigits();
    fibonacci_Sequence();
    cout << if_Fibonacci_Sequence(); */
        display_Divisors(100);
    printPrimes(1, 100);
    sumFirst100OddSquared();
    cout << "Calculated Euler Number e^5 = " << eulerNumber(5, 100) << "\t Real Euler Number e^5 = " << exp(5);

    return 0;

}

