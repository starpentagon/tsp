#include <cassert>
#include <cmath>
#include <algorithm>

#include "TSPSolver.hpp"
#include "debug_gd.hpp"
using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
#define repp(i, s, n) for (int i = s; (i) < (int)(n); (i)++)

#define ALL(v) begin(v),end(v)
#define RALL(v) rbegin(v),rend(v)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

Metrics::Metrics(const DistType dist_type)
    : dist_type_(dist_type) {
   Init();
}

void Metrics::Init() {
   N_ = -1;
   euc_2d_list_.clear();
};

void Metrics::SetEuc2dNodes(const vector<pair<double, double>> &node_pos_list) {
   Init();

   N_ = node_pos_list.size();
   euc_2d_list_ = node_pos_list;

   if (N_ <= kDistTableLimit) {
      dist_table_.resize(N_);
      rep(i, N_) dist_table_[i].resize(N_);

      rep(i, N_) {
         auto [x1, y1] = euc_2d_list_[i];

         dist_table_[i][i] = kInfDist;

         rep(j, i) {
            auto [x2, y2] = euc_2d_list_[j];

            double x_diff = x1 - x2;
            double y_diff = y1 - y2;
            Distance dist = llround(sqrt(x_diff * x_diff + y_diff * y_diff));

            dist_table_[i][j] = dist;
            dist_table_[j][i] = dist;
         }
      }
   }
}

Distance Metrics::GetDist(int from, int to) const {
   assert(0 <= from && from < N_);
   assert(0 <= to && to < N_);

   if (N_ <= kDistTableLimit) {
      return dist_table_[from][to];
   }

   if (dist_type_ == kDistEuc2D) {
      auto [x1, y1] = euc_2d_list_[from];
      auto [x2, y2] = euc_2d_list_[to];

      double x_diff = x1 - x2;
      double y_diff = y1 - y2;

      return llround(sqrt(x_diff * x_diff + y_diff * y_diff));
   }

   assert(false);
   return -1LL;
}

bool Metrics::IsSymmetric() const {
   if (dist_type_ == kDistEuc2D) {
      return true;
   } else {
      assert(false);
      return false;
   }
}

TSPSolver::TSPSolver(const Metrics &metrics)
    : N_(metrics.GetNodeCount()), tour_node_list_(metrics.GetNodeCount()), metrics_(metrics) {
   rep(i, N_) tour_node_list_[i] = i;
}

void TSPSolver::InitNearestNeighbor(int start_node) {
   vector<bool> visited(N_, false);

   assert(0 <= start_node && start_node < N_);

   int cur_node = start_node;
   visited[start_node] = true;

   int cnt = 1;

   while (cnt < N_) {
      int min_node = -1;
      Distance min_dist = kInfDist;

      rep(i, N_) {
         if (visited[i]) continue;

         Distance dist = metrics_.GetDist(cur_node, i);

         if (chmin(min_dist, dist)) {
            min_node = i;
         }
      }

      assert(min_node != -1);
      tour_node_list_[cnt] = min_node;
      visited[min_node] = true;
      cur_node = min_node;
      cnt++;
   }
}

// UnionFindで素集合を管理するクラス
// ノードIDは1-indexed
class UnionFind {
  public:
   UnionFind(const size_t N);

   // node_1とnode_2が所属する集合を結合する(Union by size)
   // 計算量: O(almost 1)
   void Unite(size_t node_1, size_t node_2);

   // node_1とnode_2が同じ集合に入っているか
   // 計算量: O(almost 1)
   bool IsSameGroup(size_t node_1, size_t node_2) const;

   // nodeが所属する集合のサイズを返す
   // 計算量: O(almost 1)
   size_t size(size_t node) const;

   // nodeの親のnode_idを返す
   size_t root(size_t node) const;

  private:
   // ノードの数
   size_t N_;

   // parent_node_id_[i]: 親ノードのノードID, rootの場合はparent_node_id_[i] ==
   // iになる
   mutable vector<size_t> parent_node_id_;

   // tree_size_[i]: ルートノードiに含まれる集合のサイズ
   vector<size_t> tree_size_;
};

UnionFind::UnionFind(const size_t N)
    : N_(N), parent_node_id_(N + 1), tree_size_(N + 1, 1) {
   // 全ノードをrootで初期化する
   for (size_t i = 0; i <= N; i++) {
      parent_node_id_[i] = i;
   }
}

size_t UnionFind::root(size_t node) const {
   assert(1 <= node && node <= N_);

   // ルートノード以外のノードを記録し直接、親ノードをルートノードにつなぎ変える(経路圧縮)
   vector<size_t> internal_nodes;

   while (parent_node_id_[node] != node) {
      internal_nodes.push_back(node);
      node = parent_node_id_[node];
   }

   for (auto n : internal_nodes) {
      parent_node_id_[n] = node;
   }

   return node;
}

bool UnionFind::IsSameGroup(size_t node_1, size_t node_2) const {
   auto parent_1 = root(node_1);
   auto parent_2 = root(node_2);

   return parent_1 == parent_2;
}

void UnionFind::Unite(size_t node_1, size_t node_2) {
   if (IsSameGroup(node_1, node_2)) {
      // すでに同じ木の場合は何もしない
      return;
   }

   // サイズの小さい方を大きいにつなぐ
   auto size_1 = size(node_1);
   auto size_2 = size(node_2);

   size_t union_from = node_1, union_to = node_2;

   if (size_1 > size_2) {
      union_from = node_2;
      union_to = node_1;
   }
   auto parent_from = root(union_from);
   auto parent_to = root(union_to);

   parent_node_id_[parent_from] = parent_to;
   tree_size_[parent_to] = tree_size_[parent_to] + tree_size_[parent_from];
}

size_t UnionFind::size(size_t node) const {
   auto parent = root(node);
   return tree_size_[parent];
}

void TSPSolver::InitKruskal() {
   vector<pair<Distance, pair<int, int>>> edges;
   if (metrics_.IsSymmetric()) {
      edges.reserve(N_ * (N_ - 1) / 2);

      rep(i, N_) {
         rep(j, i) {
            auto dist = metrics_.GetDist(i, j);
            edges.push_back({dist, {i, j}});
         }
      }
   } else {
      edges.reserve(N_ * (N_ - 1));

      rep(i, N_) {
         rep(j, i) {
            {
               auto dist = metrics_.GetDist(i, j);
               edges.push_back({dist, {i, j}});
            }
            {
               auto dist = metrics_.GetDist(j, i);
               edges.push_back({dist, {j, i}});
            }
         }
      }
   }

   sort(ALL(edges));

   vector<int> deg(N_, 0);
   UnionFind uf(N_);

   int edge_cnt = 0;
   vector<vector<int>> adj_list(N_);

   for (auto [dist, edge] : edges) {
      auto [from, to] = edge;

      if (deg[from] >= 2 || deg[to] >= 2) continue;

      if (edge_cnt == N_ - 1) {
         adj_list[from].push_back(to);
         adj_list[to].push_back(from);
         break;
      }

      if (uf.IsSameGroup(from + 1, to + 1)) continue;

      deg[from]++;
      deg[to]++;

      uf.Unite(from + 1, to + 1);

      adj_list[from].push_back(to);
      adj_list[to].push_back(from);

      edge_cnt++;
   }

   int from = 0;
   int to = adj_list[from][0];

   tour_node_list_[0] = from;

   for (int i = 1; i < N_; i++) {
      tour_node_list_[i] = to;

      int next_node = -1;
      for (auto node : adj_list[to]) {
         if (node == from) continue;
         next_node = node;
         break;
      }

      assert(next_node != -1);

      from = to;
      to = next_node;
   }
}

vector<int> TSPSolver::SolveNN() {
   InitNearestNeighbor();
   return tour_node_list_;
}

vector<int> TSPSolver::SolveKruskal() {
   InitKruskal();
   return tour_node_list_;
}

Distance TSPSolver::CalcTourDist(const vector<int> &tour) const {
   assert(N_ == (int)tour.size());

   Distance total_dist = 0;

   for (int i = 1; i < N_; i++) {
      int cur_node = tour[i - 1];
      int next_node = tour[i];

      total_dist += metrics_.GetDist(cur_node, next_node);
   }

   total_dist += metrics_.GetDist(tour[N_ - 1], tour[0]);
   return total_dist;
}
