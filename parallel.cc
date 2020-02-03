/*
Jeff Parker
CS 4000
2/2/20
HW1: This program is the parallel version of the program that implements
an algorithm to calculate the last six decimal digits of a sum from [i,n], i^i
*/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <omp.h>
using namespace std;

/*
Function: long calculate_power_mod1m

Purpose: This function is sent two integers, base and power and calculates an
  individual power sum mod 1000000 and returns it as a long (result)

Parameters: int base, int power are passed through by the for loop contained in
  the function calculate_pm_sum
*/
long calculate_power_mod1m(int base, int power) {
  long result = base;
  #pragma omp parallel for
  for (int i = 1; i < power; ++i) {
    result = (result * base) % 1000000;
  }
  return result;
}

/*
Function: long calculate_pm_sum

Purpose: This is the main driver function for the calculations of the algorithm.
  It initializes 4 sums which are used to help divide the work between threads
  and avoid race conditions. One thread does the first 1/4, another does the
  next 1/4 and same with the last 2. Each for loop contains a call to the function
  calculate_power_mod1m (above) which calculates and individual result.

Parameters: int lower_range (1), int upper_range(user input) define the range
  for the sum.
*/
long calculate_pm_sum(int lower_range, int upper_range) {
  long sum1 = 0;
  long sum2 = 0;
  long sum3 = 0;
  long sum4 = 0;
  #pragma omp parallel sections
    {
    #pragma omp section
      for (int i = lower_range; i <= 33*upper_range/100; ++i) {
        sum1 += calculate_power_mod1m(i, i);
      }
    #pragma omp section
      for (int i = 33*upper_range/100+1; i <= 60*upper_range/100; ++i) {
        sum2 += calculate_power_mod1m(i, i);
      }
    #pragma omp section
      for (int i = 60*upper_range/100+1; i <= 82*upper_range/100; ++i) {
        sum3 += calculate_power_mod1m(i, i);
      }
    #pragma omp section
      for (int i = 82*upper_range/100+1; i <= upper_range; ++i) {
        sum4 += calculate_power_mod1m(i, i);
      }
    }
    long sum = sum1 + sum2 + sum3 + sum4;
    return sum % 1000000;
}

int main() {
  omp_set_num_threads(4);
  int upper_bound;
  cout << "Enter upper bound: ";
  cin >> upper_bound;
  cout << "Result: " << calculate_pm_sum(1,upper_bound) << endl;
  return 1;
}
