#include "SolveSA.hpp"

#include "debug_sa.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

SolveSA::SolveSA(int seed, const State &state, OptimizeType opt_type)
    : mt_(seed), init_state_(state), opt_type_(opt_type) {
}

State SolveSA::Solve(int max_iter) {
   State cur_state(init_state_), best_state(init_state_);
   ScoreType cur_score = cur_state.CalcScore(), best_score = cur_score;

   rep(iter, max_iter) {
      State n_state(cur_state);

      auto move_list = cur_state.GetNeibours();
      auto rand_move = GetRandomElem(mt_, move_list);

      // ToDo: スコアを差分計算
      n_state.Move(rand_move);
      ScoreType n_score = n_state.CalcScore();

      ScoreType delta_improve = GetDeltaImprove(cur_score, n_score);
      bool is_next_move = CheckNextMove(delta_improve, iter, max_iter);

      if (!is_next_move) continue;

      // 遷移
      debug_sa(iter, n_score, delta_improve);

      cur_score = n_score;
      swap(cur_state, n_state);

      if (changeBetter(best_score, cur_score, opt_type_)) {
         debug_sa(iter, best_score);

         best_state = cur_state;
      }
   }

   return best_state;
}

double SolveSA::GetCurrentTemp(const int iter, const int max_iter) const {
   static const int min_temp = param_.GetSATemp().first;
   static const int max_temp = param_.GetSATemp().second;

   const double progress = 1.0 * iter / max_iter;
   const double temp = max_temp + (min_temp - max_temp) * progress;

   return temp;
}

bool SolveSA::CheckNextMove(const ScoreType delta_improve, const int iter, const int max_iter) const {
   if (delta_improve >= 0) return true;

   auto temp = GetCurrentTemp(iter, max_iter);

   // 0 < prob < 1
   double prob = exp(delta_improve / temp);

   static constexpr long long kProbScale = 1024 * 1024;
   long long prob_int = (long long)floor(kProbScale * prob);  // prob_int: [0, kProbScale)

   // debug_sa(iter, temp, delta_improve, prob);

   long long rnd = mt_() % kProbScale;
   bool move_next = rnd < prob_int;

   return move_next;
}

ScoreType SolveSA::GetDeltaImprove(const ScoreType cur_score, const ScoreType next_score) const {
   auto delta = next_score - cur_score;

   if (opt_type_ == kOptMin) {
      return -delta;
   } else {
      return delta;
   }
}
