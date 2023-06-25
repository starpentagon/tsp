// 焼きなまし法

#include <bits/stdc++.h>

#include "Utility.hpp"
#include "State.hpp"
#include "Parameter.hpp"
#include "SearchInfo.hpp"

namespace std {

class SolveSA {
  public:
   SolveSA(int seed, const State& state, OptimizeType opt_type, const Parameter& param);

   State Solve(int max_iter, SearchInfo& search);

  protected:
   // 遷移を行うかチェックする
   bool CheckNextMove(const ScoreType delta_improve, const int iter, const int max_iter) const;

   // 現在の温度を取得する
   double GetCurrentTemp(const int iter, const int max_iter) const;

   // Current/Nextスコアから改善量を求める
   ScoreType GetDeltaImprove(const ScoreType cur_score, const ScoreType next_score) const;

   Parameter param_;  // パラメタ

   mutable mt19937_64 mt_;
   State init_state_;

   OptimizeType opt_type_;  // 最小化/最大化
};

}  // namespace std