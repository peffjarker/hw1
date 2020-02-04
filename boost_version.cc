//
// File: boost_version.cc
// Author: David W. Juedes
// Purpose: Computes the last six digits of the
// sum from 1 to n (given as input) of i^i
// Uses the boost multiprecision library
// This is a "reference" implementation to test whether you are getting the
// right answer.   But, this implementation is SLOW!!!!  (
//

#include <iostream>
#include <iomanip>
#include <set>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

//
// Computes a^n using multiprecision integers (cpp_int).
// Not very efficient
//
cpp_int power(int a, int n) {
  cpp_int p = 1;

  for (int i=1;i<=n;i++) {
    p*=a;
  }
  return p;
}

int main() {
  int n;
  cin >> n;
  cpp_int sum = 0;
  for (int i=1;i<=n;i++) {
    sum+=power(i,i);
  }
  cout << " n = " << n << endl;
  cout << sum << endl;
  // Prints leading 0's
  cout << "Answer = " << setw(6) << setfill('0') << sum%1000000 << endl;
}
