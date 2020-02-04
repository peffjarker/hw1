/*
Jeff Parker
CS 4000
2/2/20
HW1: This program is the sequential version of the program that implements
an algorithm to calculate the last six decimal digits of a sum from [i,n], i^i
Simply enter an upper limit to run.
*/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
using namespace std;

#define N 1000000

/*
Function: long calculate_power_mod1m

Purpose: This function is sent two integers, base and power and calculates an
  individual power sum mod 1000000 and returns it as a long (result)

Parameters: int base, int power are passed through by the for loop contained in
  the function calculate_pm_sum
*/
long int calculate_power_mod1m(long int base, long int exp) {
  if (exp == 0)
    return 1;
  if (exp == 1)
    return base % N;

  long int t = calculate_power_mod1m(base, exp / 2);
  t = (t * t) % N;

  if (exp % 2 == 0)
    return t;

  else
    return ((base % N) * t) % N;
}

/*
Function: long calculate_pm_sum

Purpose: This function calculates the results from the function
  calculate_power_mod1m and stores the result in a vector to calculate
  the sum % 1000000

Parameters: lower_range(1), upper_range(user inpit) define the range
  for the sum
*/
long calculate_pm_sum(int lower_range, int upper_range) {
  long sum = 0;
  for (int i = lower_range; i <= upper_range; ++i) {
    sum += (calculate_power_mod1m(i, i));
  }
  return sum % 1000000;
}

int main() {
  int upper_bound;
  cout << "Enter upper bound: ";
  cin >> upper_bound;
  cout << "Result: " << calculate_pm_sum(1,upper_bound) << endl;
  return 1;
}
