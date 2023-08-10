#include <bits/stdc++.h>

#include "XorShift.hpp"
#include "Utility.hpp"
#include "Parameter.hpp"
#include "SearchInfo.hpp"
#include "State.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
#define repp(i, s, n) for (int i = s; (i) < (int)(n); (i)++)

#define all(v) begin(v),end(v)
#define rall(v) rbegin(v),rend(v)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }

template<class T> ostream& operator<<(ostream& os, vector<T>& vec){ rep(i, vec.size()) os << vec[i] << (i+1==(int)vec.size() ? "" : " "); return os;}
// clang-format on

int main() {
   cerr << "Result="
        << "dummy"
        << " ";
   cerr << "Score=" << 0 << " ";
   cerr << endl;

   return 0;
}
