// 山登り法

#include <bits/stdc++.h>
#include "State.hpp"

using SearchState = State;

namespace std {

class SolveHillClimb {
  public:
   SolveHillClimb(int seed, const SearchState& state);

   SearchState Solve(const int seed, int max_iter);

  protected:
   MoveType GetRandomMove(const vector<MoveType>& move_list) const;
   SearchState init_state_;

   mt19937_64 mt_;
};

}  // namespace std