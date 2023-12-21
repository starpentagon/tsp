#include "SearchInfo.hpp"

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
#define repp(i, s, n) for (int i = s; (i) < (int)(n); (i)++)

#define ALL(v) begin(v),end(v)
#define RALL(v) rbegin(v),rend(v)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

using namespace std;

SearchInfo::SearchInfo()
    : iter_(0), terminate_iter_(numeric_limits<int>::max()), terminate_time_(numeric_limits<int>::max()) {
   start_time_ = chrono::system_clock::now();
}

void SearchInfo::SearchStart() {
   start_time_ = chrono::system_clock::now();
}

const bool SearchInfo::IsTerminate() const {
   if (iter_ >= terminate_iter_) {
      return true;
   }

   auto e_time = chrono::system_clock::now() - start_time_;
   int e_time_ms = chrono::duration_cast<chrono::milliseconds>(e_time).count();

   if (e_time_ms >= terminate_time_) {
      return true;
   }

   return false;
}

int SearchInfo::GetMeanUpdateInterval() const {
   int size = (int)best_update_iter_.size();
   if (size < 2) {
      return 0;
   }

   int sum_interval = 0;

   for (int i = 1; i < size; i++) {
      int interval = best_update_iter_[i] - best_update_iter_[i - 1];
      sum_interval += interval;
   }

   return sum_interval / (size - 1);
}

// 最大更新間隔を取得する
int SearchInfo::GetMaxUpdateInterval() const {
   int size = (int)best_update_iter_.size();
   if (size < 2) {
      return 0;
   }

   int max_interval = -1;

   for (int i = 1; i < size; i++) {
      int interval = best_update_iter_[i] - best_update_iter_[i - 1];
      chmax(max_interval, interval);
   }

   return max_interval;
}
