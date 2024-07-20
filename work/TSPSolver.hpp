// TSP用Solver
#pragma once

#include <vector>
#include <utility>

namespace std {

using Distance = long long;
static constexpr Distance kInfDist = 1e10;

using DistNode = pair<Distance, int>;

// ノード間の距離を管理するクラス
static constexpr int kDistTableLimit = 1000;  // 距離テーブルのサイズはO(N^2)なので10MB程度に収まる範囲で作る

enum DistType {
   kDistEuc2D = 0,  // 2次元ユークリッド距離
};

// 距離テーブルを管理するクラス
// @note ノード数がkDistTableLimit以下ならばO(N^2)の距離テーブルを持つ
class Metrics {
  public:
   Metrics(const DistType dist_type);

   // ノードの座標情報をセットする(Euclidean 2D)
   void SetEuc2dNodes(const vector<pair<double, double>>& node_pos_list);

   // 距離を求める
   Distance GetDist(int from, int to) const;

   int GetNodeCount() const {
      return N_;
   }

   // 距離行列が対称かどうかを返す
   bool IsSymmetric() const;

  protected:
   void Init();

   DistType dist_type_;  // 距離タイプ

   int N_;  // ノード数
   vector<pair<double, double>> euc_2d_list_;

   vector<vector<Distance>> dist_table_;
};

class TSPSolver {
  public:
   TSPSolver(const Metrics& metrics);

   // 貪欲法(Nearest Neighbor)で解く
   vector<int> SolveNN();

   // 貪欲法(Kruskal)で解く
   vector<int> SolveKruskal();

   Distance CalcTourDist(const vector<int>& tour) const;

  protected:
   // 貪欲法(Nearest Neighbor)で初期化する
   // 計算量: O(N^2)
   void InitNearestNeighbor(int start_node = 0);

   // 貪欲法(Kruskal)で初期化する
   // 計算量: O(N^2 log N)
   void InitKruskal();

   int N_;  // 頂点数

   vector<int> tour_node_list_;  // 頂点の訪問順

   Metrics metrics_;
};

}  // namespace std
