#include "SolveGreedy.hpp"
#include "debug_gd.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
#define repp(i, s, n) for (int i = s; (i) < (int)(n); (i)++)

#define all(v) begin(v),end(v)
#define rall(v) rbegin(v),rend(v)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

SolveGreedy::SolveGreedy(const State &state, OptimizeType opt_type)
    : init_state_(state), opt_type_(opt_type) {
}

State SolveGreedy::Solve() {
   State cur_state(init_state_);

   while (!cur_state.IsFinished()) {
      auto best_move = GetGreedyMove(cur_state);
      cur_state.Move(best_move);
   }

   return cur_state;
}

MoveType SolveGreedy::GetGreedyMove(const State &cur_state) const {
   const auto move_list = cur_state.GetAllMoves();
   assert(!move_list.empty());

   ScoreType best_search_score = GetWorstValue(opt_type_);

   vector<MoveType> best_move_list;

   for (const auto &move : move_list) {
      State n_state(cur_state);
      ScoreType n_search_score = n_state.CalcSearchScore();

      if (best_search_score == n_search_score) {
         best_move_list.emplace_back(move);
      } else if (changeBetter(best_search_score, n_search_score, opt_type_)) {
         best_move_list.clear();
         best_move_list.emplace_back(move);
      }
   }

   assert(!best_move_list.empty());
   auto best_move = GetRandomElem(best_move_list);
   return best_move;
}
