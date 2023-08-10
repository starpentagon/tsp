// 共通処理を宣言/定義する
#pragma once

#include <bits/stdc++.h>
#include "XorShift.hpp"

namespace std {
using ll = long long;

// 2次元座標
using Coord = pair<ll, ll>;

// 2点間の距離
ll CalcSquareDist(const Coord& p1, const Coord& p2);            // 二乗距離
double CalcEuclidDist(const Coord& p1, const Coord& p2);        // ユークリッド距離
ll CalcManhattanDist(const Coord& p1, const Coord& p2);         // マンハッタン距離
ll CalcChebyshevDist(const Coord& p1, const Coord& p2);         // チェビシェフ距離
double CalcLpDist(const Coord& p1, const Coord& p2, double p);  // Lp距離

// 最適化のタイプ(最小化/最大化)
enum OptimizeType {
   kOptMin,  // 最小化
   kOptMax   // 最大化
};

// 最小化/最大化に合わせて最も悪い値を返す
static constexpr ll kInfVal = numeric_limits<ll>::max();

ll GetWorstValue(const OptimizeType opt_type);

// 最小化/最大化に合わせて値を更新する
template <class T>
bool changeBetter(T& a, const T& b, const OptimizeType opt_type) {
   if (opt_type == kOptMin) {
      // 最小化
      if (a > b) {
         a = b;
         return true;
      } else {
         return false;
      }
   } else {
      // 最大化
      if (a < b) {
         a = b;
         return true;
      } else {
         return false;
      }
   }
}

// 要素 vec[i]が真になる要素のindexを取得する
template <class T>
vector<int> GetTrueIndex(const vector<T>& vec) {
   vector<int> index_list;

   for (int i = 0; i < (int)index_list.size(); i++) {
      if (vec[i]) index_list.emplace_back(i);
   }
   return index_list;
}

// 集合からランダムに要素を選択する(mt19937_64版)
template <class T>
T GetRandomElem(mt19937_64& mt, const vector<T>& list) {
   assert(!list.empty());
   auto ind = mt() % list.size();
   return list[ind];
}

// 集合からランダムに要素を選択する(XorShift版)
template <class T>
T GetRandomElem(const vector<T>& list) {
   assert(!list.empty());
   auto ind = XorShift() % list.size();
   return list[ind];
}

}  // namespace std
