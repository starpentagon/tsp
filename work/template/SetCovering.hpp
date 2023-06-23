#pragma once
#include <bits/stdc++.h>

// 集合被覆問題を解く
namespace std {
namespace SetCoveringSolver {

using SetCost = long long;
static const SetCost kCostINF = numeric_limits<SetCost>::max();

class SetCovering {
  public:
   // @param N: 要素数
   // @param M: 集合数
   // @param set_list[i]: 集合iが含む要素リスト(M x N行列), 要素番号は0-indexedであること
   SetCovering();

   void SetProblem(int N, int M, const vector<SetCost>& set_cost, const vector<vector<int>>& set_elem_list);

   // 貪欲法で解く
   // @retval (cost, 用いる集合リスト)
   // @note 近似度 H_N(=1+1/2+...+1/N)が保証される。H_10=2.93, H_30=3.99, H_50=4.50, H_100=5.19
   // 計算量: O(TMK) <= O(N^2 M), T: 反復回数<=N, K: 集合に含まれる最大要素数<=N
   pair<SetCost, vector<int>> SolveGreedy() const;

   SetCost GetSetCost(const int set_index) const {
      assert(0 <= set_index && set_index < M_);
      return set_cost_[set_index];
   }

   void SetSetCost(const int set_index, const SetCost cost) {
      assert(0 <= set_index && set_index < M_);
      set_cost_[set_index] = cost;
   }

  protected:
   // 集合の追加コストを求める
   // 計算量: O(MK), K: 集合に含まれる最大要素数
   vector<double> CalcSetAdditionalCost(const vector<bool>& selected_set, const vector<bool>& covered_elem) const;

   int N_;                              // 要素数
   int M_;                              // 集合数
   vector<SetCost> set_cost_;           // set_list_[i]: 集合iが含む要素リスト
   vector<vector<int>> set_elem_list_;  // set_elem_list_[i]: 集合iが含む要素リスト
};

}  // namespace SetCoveringSolver
}  // namespace std