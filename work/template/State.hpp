#pragma once

#include <bits/stdc++.h>

// スコア値の型
using ScoreType = long long;

// 遷移
using MoveType = int;

// 遷移のindex
using MoveIndex = int;

namespace std {
class State {
  public:
   State();

   // 終端条件かどうか
   bool IsFinished() const;

   // 状態のルールに基づく評価値を返す
   ScoreType CalcScore() const;

   // 状態の探索中の評価値を返す
   ScoreType CalcSearchScore() const;

   // 可能な遷移集合全体を返す
   vector<MoveType> GetAllMoves() const;

   // 近傍集合を返す
   vector<MoveType> GetNeibours() const;

   // 状態を遷移させる
   void Move(const MoveType& move);

   // 状態をエラー出力する
   void Output() const;

  protected:
   string GetString() const;

   int turn_;  // 遷移させた回数
};
}  // namespace std
