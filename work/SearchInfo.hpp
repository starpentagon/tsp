#pragma once

#include <bits/stdc++.h>

// 探索情報を管理するクラス
class SearchInfo {
  public:
   SearchInfo();

   // 最善解の更新情報を記録する
   void BestUpdate() {
      best_update_iter_.emplace_back(iter_);
   }

   // 探索開始
   void SearchStart();

   // 探索回数上限を設定する
   void SetTerminateIter(const int iter) {
      terminate_iter_ = iter;
   }

   // 探索時間上限(ms)を設定する
   void SetTerminateTime(const int ms) {
      terminate_time_ = ms;
   }

   // 探索終了条件が成立しているかチェックする
   const bool IsTerminate() const;

   // 探索ノード数を取得する
   int GetIter() const {
      return iter_;
   }

   void AddIter() {
      iter_++;
   }

   // 平均更新間隔を取得する
   int GetMeanUpdateInterval() const;

   // 最大更新間隔を取得する
   int GetMaxUpdateInterval() const;

  protected:
   int iter_;                           // 探索回数数
   std::vector<int> best_update_iter_;  // 最善解を更新時の探索回数数の履歴

   std::chrono::system_clock::time_point start_time_;  // 探索開始時間

   int terminate_iter_;  // 探索回数上限
   int terminate_time_;  // 探索時間上限(ms)
};
