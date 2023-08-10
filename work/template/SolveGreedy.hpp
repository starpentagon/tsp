// 貪欲法
#pragma once

#include <bits/stdc++.h>

#include "Utility.hpp"
#include "State.hpp"

namespace std {

class SolveGreedy {
  public:
   SolveGreedy(const State& state, OptimizeType opt_type);

   State Solve();

  protected:
   // 最も一時評価(SearchScore)の良い子局面への遷移を返す
   MoveType GetGreedyMove(const State& cur_state) const;

   State init_state_;       // 初期状態
   OptimizeType opt_type_;  // 最小化/最大化
};

}  // namespace std