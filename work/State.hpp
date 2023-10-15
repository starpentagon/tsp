#pragma once

#include <bits/stdc++.h>

// スコア値の型
using ScoreType = long long;

// 遷移
using MoveType = int;
static constexpr MoveType kInvalidMove = -1;  // 無効な遷移

// 遷移のindex
using MoveIndex = int;

namespace std {

class State {
  public:
   State();
   State operator=(State& state);

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

   // root局面から最初の遷移を取得する
   MoveType GetFirstMove() const {
      return first_move_;
   }

   // root局面から最初の遷移を設定する
   void SetFirstMove(const MoveType& move) {
      first_move_ = move;
   }

  protected:
   string GetString() const;

   int turn_;             // 遷移させた回数
   MoveType first_move_;  // 文脈ありゲームでroot局面から最初の遷移を記録する(文脈なしゲームの場合は不要)
};

// Beam search用の比較演算子
bool operator>(const State& lhs, const State& rhs);
bool operator<(const State& lhs, const State& rhs);

}  // namespace std
