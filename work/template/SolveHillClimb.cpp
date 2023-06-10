#include "SolveHillClimb.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

SolveHillClimb::SolveHillClimb(int seed, const SearchState &state)
    : mt_(seed), init_state_(state) {
}

SearchState SolveHillClimb::Solve(const int seed, int max_iter) {
   SearchState cur_state(init_state_), best_state(init_state_);
   ScoreType best_score = best_state.CalcScore();

   rep(i, max_iter) {
      SearchState n_state(cur_state);

      auto move_list = cur_state.GetNeibours();
      auto rand_move = GetRandomMove(move_list);

      // ToDo: スコアを差分計算
      n_state.Move(rand_move);
      ScoreType n_score = n_state.CalcScore();

      if (chmax(best_score, n_score)) {
         best_state = n_state;
         swap(cur_state, n_state);
      }
   }

   return best_state;
}

MoveType SolveHillClimb::GetRandomMove(const vector<MoveType> &move_list) const {
   int L = move_list.size();
   assert(L > 0);

   int ind = move_list.size() % L;
   return move_list[ind];
}
