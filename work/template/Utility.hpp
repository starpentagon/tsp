// 共通処理を宣言/定義する

#include <bits/stdc++.h>
#include "XorShift.hpp"

namespace std {

// 最適化のタイプ(最小化/最大化)
enum OptimizeType {
   kOptMin,  // 最小化
   kOptMax   // 最大化
};

static const long long INF = 100100100100L;  // 十分大きな数

long long GetWorstValue(const OptimizeType opt_type) {
   if (opt_type == kOptMin)
      return INF;
   else
      return -INF;
}

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
