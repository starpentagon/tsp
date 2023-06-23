#include "SetCovering.hpp"

using namespace std;
using namespace SetCoveringSolver;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

SetCovering::SetCovering()
    : N_(-1), M_(-1) {
}

void SetCovering::SetProblem(int N, int M, const vector<SetCost> &set_cost, const vector<vector<int>> &set_elem_list) {
   N_ = N;
   M_ = M;
   set_cost_ = set_cost;
   set_elem_list_ = set_elem_list;

   assert(N >= 1);
   assert(M >= 1);
   assert((int)set_cost.size() == M);
   assert((int)set_elem_list.size() == M);
#ifndef NDEBUG
   rep(m, M_) for (auto elem : set_elem_list[m]) assert(0 <= elem && elem < N);
#endif
}

pair<SetCost, vector<int>> SetCovering::SolveGreedy() const {
   vector<bool> covered_elem(N_, false);
   vector<bool> selected_set(M_, false);

   auto find_most_efficient_set = [&]() {
      auto set_additional_cost = CalcSetAdditionalCost(selected_set, covered_elem);
      int min_cost_set_index = -1;
      double min_additional_cost = (double)kCostINF;

      rep(m, M_) {
         if (chmin(min_additional_cost, set_additional_cost[m])) {
            min_cost_set_index = m;
         }
      }
      return min_cost_set_index;
   };

   int covered_cnt = 0;

   while (true) {
      auto set_index = find_most_efficient_set();

      selected_set[set_index] = true;

      for (const auto elem : set_elem_list_[set_index]) {
         if (!covered_elem[elem]) covered_cnt++;
         covered_elem[elem] = true;
      }

      if (covered_cnt == N_) break;
   }

   vector<int> select_set_list;
   SetCost total_cost = 0;

   rep(m, M_) {
      if (!selected_set[m]) continue;

      select_set_list.emplace_back(m);
      total_cost += set_cost_[m];
   }

   return {total_cost, select_set_list};
}

vector<double> SetCovering::CalcSetAdditionalCost(const vector<bool> &selected_set, const vector<bool> &covered_elem) const {
   vector<double> set_additional_cost(M_, (double)kCostINF);

   rep(m, M_) {
      if (selected_set[m]) continue;

      // 集合S[m]を追加することで新たに被覆できるノード数
      int cover_cnt = 0;

      for (const int elem : set_elem_list_[m]) {
         if (covered_elem[elem]) continue;
         cover_cnt++;
      }

      if (cover_cnt == 0) continue;

      auto c = set_cost_[m];

      double additional_cost = 1.0 * c / cover_cnt;
      set_additional_cost[m] = additional_cost;
   }

   return set_additional_cost;
}
