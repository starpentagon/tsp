#pragma once
#include <bits/stdc++.h>

namespace std {
namespace SteinerTreeSolver {

using EdgeWeight = long long;
using AdjInfo = pair<int, EdgeWeight>;         // to, weight
using EdgeInfo = tuple<int, int, EdgeWeight>;  // node1, node2, weight

// 最小シュタイナー木を求める
// @note ノードは1-indexed
class SteinerTree {
  public:
   SteinerTree(int N);

   void AddEdge(int u, int v, EdgeWeight w);

   // Prim法ベースによるシュタイナー木の構成(全点対最短路を計算)
   // @note: ターミナルは2点以上あること
   // 計算量: O(N^3 + NT)
   // @note 厳密解は保証されないが経験的に良い解が得られる。
   // @note 開始点がterminal_node_list[0]で固定されている。ランダムに変えると改善する可能性がある。
   vector<EdgeInfo> SolveByShortestPath(const vector<int>& terminal_node_list) const;

   // Prim法ベースによるシュタイナー木の構成(全点対最短路を事前計算版)
   // @note: ターミナルは2点以上あること
   // 計算量: O(NT)
   // @note 厳密解は保証されないが経験的に良い解が得られる。
   // @note 開始点がterminal_node_list[0]で固定されている。ランダムに変えると改善する可能性がある。
   vector<EdgeInfo> SolveByShortestPath(const vector<int>& terminal_node_list, const vector<vector<EdgeWeight>>& node_min_dist_tbl) const;

   // 全点対最短路を求める
   // 計算量: O(N^3)
   vector<vector<EdgeWeight>> AllShortestPath() const;

  protected:
   int N_;
   int M_;

   vector<vector<AdjInfo>> adj_list_;  // 隣接リスト
   vector<EdgeInfo> edge_list_;        // 辺リスト
};
}  // namespace SteinerTreeSolver
}  // namespace std
