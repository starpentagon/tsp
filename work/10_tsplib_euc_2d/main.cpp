#pragma GCC target("arch=skylake-avx512")
#pragma GCC optimize("O3")

#include <bits/stdc++.h>
#include "../TSPSolver.hpp"

using namespace std;

#ifdef LOCAL
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) ;
#endif

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
#define repp(i, s, n) for (int i = s; (i) < (int)(n); (i)++)

#define ALL(v) begin(v),end(v)
#define RALL(v) rbegin(v),rend(v)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }

template<class T> istream& operator>>(istream& is, vector<T>& vec){ rep(i, vec.size()) is >> vec[i]; return is;}
template<class T> ostream& operator<<(ostream& os, vector<T>& vec){ rep(i, vec.size()) os << vec[i] << (i+1==(int)vec.size() ? "" : " "); return os;}
// clang-format on

using ll = long long;
using ull = unsigned long long;

Metrics LoadProblem();

int main() {
   chrono::system_clock::time_point start = chrono::system_clock::now();

   auto metrics = LoadProblem();
   TSPSolver solver(metrics);

   // auto tour = solver.SolveNN();
   auto tour = solver.SolveKruskal();
   Distance total_dist = solver.CalcTourDist(tour);

   chrono::system_clock::time_point end = chrono::system_clock::now();
   long long elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();

   cerr << "tour=";

   for (auto node : tour) {
      cerr << (node + 1) << "-";
   }

   cerr << " ";

   cerr << "distance=" << total_dist << " ";
   cerr << "e_time_micro_sec=" << elapsed << " ";

   cerr << endl;

   return 0;
}

Metrics LoadProblem() {
   string file_name;
   cin >> file_name;

   ifstream ifs(file_name);
   assert(!ifs.fail() && ifs.is_open());

   int N;
   ifs >> N;

   vector<pair<double, double>> node_pos_list(N);

   rep(i, N) {
      double x, y;
      ifs >> x >> y;

      node_pos_list[i] = {x, y};
   }

   Metrics metrics(kDistEuc2D);
   metrics.SetEuc2dNodes(node_pos_list);

   return metrics;
}
