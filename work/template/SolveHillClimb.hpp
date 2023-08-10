// 山登り法
#pragma once

#include <bits/stdc++.h>

#include "Utility.hpp"
#include "State.hpp"
#include "SearchInfo.hpp"

namespace std {

class SolveHillClimb {
  public:
   SolveHillClimb(int seed, const State& state, const OptimizeType opt_type);

   State Solve(int max_iter, SearchInfo& search);

  protected:
   mt19937_64 mt_;
   State init_state_;  // 初期状態

   OptimizeType opt_type_;  // 最小化/最大化
};

}  // namespace std