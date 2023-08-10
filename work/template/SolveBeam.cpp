#include "SolveBeam.hpp"
#include "debug_bm.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
#define repp(i, s, n) for (int i = s; (i) < (int)(n); (i)++)

#define all(v) begin(v),end(v)
#define rall(v) rbegin(v),rend(v)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

SolveBeam::SolveBeam(const State &state, OptimizeType opt_type, const Parameter &param)
    : init_state_(state), opt_type_(opt_type), param_(param) {
}

State SolveBeam::Solve(SearchInfo &search) {
   int beam_depth = param_.GetBeamDepth();
   int beam_width = param_.GetBeamWidth();

   using P = pair<ScoreType, State>;

   vector<P> cur_state_list;
   cur_state_list.emplace_back(init_state_.CalcSearchScore(), init_state_);

   rep(d, beam_depth) {
      vector<P> n_state_list;

      if (search.IsTerminate()) break;

      for (const auto &[cur_score, cur_state] : cur_state_list) {
         const auto &move_list = cur_state.GetAllMoves();

         for (const auto &move : move_list) {
            State n_state(cur_state);
            n_state.Move(move);

            if (d == 0) n_state.SetFirstMove(move);

            n_state_list.emplace_back(n_state.CalcSearchScore(), n_state);
         }
      }

      if ((int)n_state_list.size() > beam_width) {
         // bool operator>(const State &lhs, const State &rhs)が必要
         nth_element(n_state_list.begin(), n_state_list.begin() + beam_width, n_state_list.end(), std::greater<>());
         n_state_list.resize(beam_width);
      }

      swap(cur_state_list, n_state_list);

      assert(!cur_state_list.empty());
      const auto &cur_state = cur_state_list.front().second;
      if (cur_state.IsFinished()) break;
   }

   State best_state(init_state_);
   ScoreType best_search_score = GetWorstValue(opt_type_);

   for (const auto &[search_score, state] : cur_state_list) {
      if (changeBetter(best_search_score, search_score, opt_type_)) {
         best_state = state;
      }
   }

   return best_state;
}
