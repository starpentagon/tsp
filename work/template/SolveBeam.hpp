// Beam search
#pragma once

#include <bits/stdc++.h>

#include "Utility.hpp"
#include "Parameter.hpp"
#include "State.hpp"
#include "SearchInfo.hpp"

namespace std {

class SolveBeam {
  public:
   SolveBeam(const State& state, OptimizeType opt_type, const Parameter& param);

   State Solve(SearchInfo& search);

  protected:
   Parameter param_;        // パラメタ
   State init_state_;       // 初期状態
   OptimizeType opt_type_;  // 最小化/最大化
};

}  // namespace std