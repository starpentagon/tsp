#include "SolveHillClimb.hpp"
#include "debug_hc.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
#define repp(i, s, n) for (int i = s; (i) < (int)(n); (i)++)

#define all(v) begin(v),end(v)
#define rall(v) rbegin(v),rend(v)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

SolveHillClimb::SolveHillClimb(int seed, const State &state, const OptimizeType opt_type)
    : mt_(seed), init_state_(state), opt_type_(opt_type) {
}

State SolveHillClimb::Solve(int max_iter, SearchInfo &search) {
   State cur_state(init_state_), best_state(init_state_);
   ScoreType best_score = best_state.CalcScore();

   rep(i, max_iter) {
      search.AddIter();
      if (search.IsTerminate()) {
         break;
      }

      State n_state(cur_state);

      auto move_list = cur_state.GetNeibours();
      auto rand_move = GetRandomElem(mt_, move_list);

      // ToDo: スコアを差分計算
      n_state.Move(rand_move);
      ScoreType n_score = n_state.CalcScore();

      if (changeBetter(best_score, n_score, opt_type_)) {
         best_state = n_state;
         swap(cur_state, n_state);
      }
   }

   return best_state;
}
