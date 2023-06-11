// Beam search

#include <bits/stdc++.h>

#include "Utility.hpp"
#include "Parameter.hpp"
#include "State.hpp"

namespace std {

class SolveBeam {
  public:
   SolveBeam(const State& state, OptimizeType opt_type);

   State Solve();

  protected:
   Parameter param_;        // パラメタ
   State init_state_;       // 初期状態
   OptimizeType opt_type_;  // 最小化/最大化
};

}  // namespace std