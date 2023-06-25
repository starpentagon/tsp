#include <bits/stdc++.h>

#include "XorShift.hpp"
#include "Parameter.hpp"
#include "State.hpp"
#include "Utility.hpp"

#include "debug.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
template<class T> ostream& operator<<(ostream& os, vector<T>& vec){ rep(i, vec.size()) os << vec[i] << (i+1==(int)vec.size() ? "" : " "); return os;}
// clang-format on

int main() {
   State state;

   int a = 1;
   debug(a);

   cerr << "Result="
        << "dummy"
        << " ";
   cerr << "Score=" << 0 << " ";
   cerr << endl;

   return 0;
}
