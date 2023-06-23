#include "SteinerTree.hpp"

using namespace std;
using namespace SteinerTreeSolver;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

SteinerTree::SteinerTree(int N)
    : N_(N), M_(0), adj_list_(N + 1, vector<AdjInfo>()) {
}

void SteinerTree::AddEdge(int u, int v, EdgeWeight w) {
   adj_list_[u].emplace_back(v, w);
   adj_list_[v].emplace_back(u, w);

   edge_list_.emplace_back(u, v, w);
}

// ワーシャル・フロイド法で全点対間最短路を求める
// @note 負の重みが存在しても正しく動く
// @param min_weight_list[i][j] : node i->jの最短路。1-indexedのためi=0, j=0にはINFが入る
// @retval true 負の閉路が存在, false 負の閉路が存在しない
// @note 最短路の重みが負の無限大になるノードはmin_weight_list[node][node]が負のもの
// @note 計算量: O(N^3)
// 非連結成分には INF = numeric_limits<long long>::max() が設定される
pair<bool, vector<vector<long long>>> AllShortestPathWarshallFloyd(const vector<vector<pair<int, long long>>>& adj_list) {
   // dp[k][i][j]: ノード1からkまでを使ってiからjまで移った時の最小重み
   // -> dp[i][j]のみで管理可能
   int L = (int)adj_list.size();
   int N = L - 1;
   constexpr long long INF = numeric_limits<long long>::max();

   vector<vector<long long>> min_weight_list(L, vector<long long>(L, INF));

   // 初期化
   for (int node = 1; node <= N; node++) {
      min_weight_list[node][node] = 0;

      for (const auto& [to, weight] : adj_list[node]) {
         min_weight_list[node][to] = weight;
      }
   }

   for (int node_k = 1; node_k <= N; node_k++) {
      for (int node_i = 1; node_i <= N; node_i++) {
         for (int node_j = 1; node_j <= N; node_j++) {
            if (min_weight_list[node_i][node_k] == INF || min_weight_list[node_k][node_j] == INF) {
               // 重み < 0の可能性があり直後の更新がinf > inf - dで成立し意図しない挙動になるため明示的にスキップ
               continue;
            }

            long long weight = min_weight_list[node_i][node_k] + min_weight_list[node_k][node_j];

            min_weight_list[node_i][node_j] = min(min_weight_list[node_i][node_j], weight);
         }
      }
   }

   bool negative_loop = false;

   for (int node = 1; node <= N; node++) {
      if (min_weight_list[node][node] < 0) {
         negative_loop = true;
      }
   }

   return {negative_loop, min_weight_list};
}

// ノード間の最短経路を求める(重み付き用)
// @param start, node: 最短経路を求めるノード
// @param min_weight_list: startから各ノードの最短距離が格納されたテーブル
// @retval node_path: startノードからendノードまでの最短経路順に並べたノードリスト
// @note 計算量: O(E)
// Unverified
vector<int> FindShortestPath(const int start, const int end, const vector<vector<pair<int, long long>>>& adj_list, const vector<long long>& min_weight_list) {
   int N = (int)adj_list.size() - 1;

   // to -> fromの逆順隣接リストを作る
   using Edge = pair<int, long long>;
   vector<vector<Edge>> rev_adj_list(N + 1, vector<Edge>());

   for (int from = 1; from <= N; from++) {
      for (auto [to, weight] : adj_list[from]) {
         rev_adj_list[to].emplace_back(from, weight);
      }
   }

   vector<int> back_path;
   vector<bool> visited(N + 1, false);
   constexpr long long INF = numeric_limits<long long>::max();

   int node = end;

   back_path.push_back(node);
   visited[node] = true;

   while (node != start) {
      for (auto [from, weight] : rev_adj_list[node]) {
         if (visited[from] || min_weight_list[from] == INF) continue;

         if (min_weight_list[node] == min_weight_list[from] + weight) {
            back_path.push_back(from);
            node = from;
            visited[from] = true;
            break;
         }
      }
   }

   reverse(back_path.begin(), back_path.end());
   return back_path;
}

// ノード間の最短経路を求める(重みなし用)
// @param start, node: 最短経路を求めるノード
// @param min_weight_list: startから各ノードの最短距離が格納されたテーブル
// @retval node_path: startノードからendノードまでの最短経路順に並べたノードリスト
// @note 計算量: O(E)
vector<int> FindShortestPath(const int start, const int end, const vector<vector<int>>& adj_list, const vector<long long>& min_weight_list) {
   int N = (int)adj_list.size() - 1;

   using Edge = pair<int, long long>;
   vector<vector<Edge>> weight_adj_list(N + 1, vector<Edge>());

   for (int node = 1; node <= N; node++) {
      for (auto to : adj_list[node]) {
         weight_adj_list[node].emplace_back(to, 1);
      }
   }

   return FindShortestPath(start, end, weight_adj_list, min_weight_list);
}

vector<EdgeInfo> SteinerTree::SolveByShortestPath(const vector<int>& terminal_node_list) const {
   auto [neg_loop, node_min_dist_tbl] = AllShortestPathWarshallFloyd(adj_list_);
   return SolveByShortestPath(terminal_node_list, node_min_dist_tbl);
}

vector<vector<EdgeWeight>> SteinerTree::AllShortestPath() const {
   auto [neg_loop, node_min_dist_tbl] = AllShortestPathWarshallFloyd(adj_list_);
   return node_min_dist_tbl;
}

vector<EdgeInfo> SteinerTree::SolveByShortestPath(const vector<int>& terminal_node_list, const vector<vector<EdgeWeight>>& node_min_dist_tbl) const {
   assert(terminal_node_list.size() >= 2);
   constexpr long long INF = numeric_limits<long long>::max();

   vector<bool> terminal_node(N_, false);      // ターミナルノード
   vector<bool> steiner_tree_node(N_, false);  // シュタイナー木に採用済のノード
   vector<EdgeInfo> steiner_tree_edge;

   int steiner_terminal_cnt = 0;

   for (auto t : terminal_node_list) {
      terminal_node[t] = true;
   }

   // fromノードから最も近いターミナルノードを求める
   auto GetNearestTerminal = [&](int from) {
      auto min_dist = INF;
      int min_terminal = -1;

      for (const auto t : terminal_node_list) {
         if (t == from) continue;

         auto dist = node_min_dist_tbl[from][t];
         if (chmin(min_dist, dist)) {
            min_terminal = t;
         }
      }

      return min_terminal;
   };

   // fromノードからもっとも近いシュタイナー木のノードを求める
   auto GetNearestSteinerNode = [&](int from) {
      auto min_dist = INF;
      int min_node = -1;

      for (int n = 1; n <= N_; n++) {
         if (!steiner_tree_node[n]) continue;
         if (n == from) continue;

         auto dist = node_min_dist_tbl[from][n];
         if (chmin(min_dist, dist)) {
            min_node = n;
         }
      }

      return min_node;
   };

   auto SelectSteinerNode = [&](int n) {
      if (steiner_tree_node[n]) return;
      steiner_tree_node[n] = true;
      if (terminal_node[n]) steiner_terminal_cnt++;
   };

   auto AddShortestPath = [&](int from, int to) {
      assert(!steiner_tree_node[from]);

      auto path_vec = FindShortestPath(from, to, adj_list_, node_min_dist_tbl[from]);
      int L = path_vec.size();

      for (int i = 1; i < L; i++) {
         int u = path_vec[i - 1];
         int v = path_vec[i];
         EdgeWeight w = node_min_dist_tbl[u][v];

         SelectSteinerNode(u);
         SelectSteinerNode(v);

         steiner_tree_edge.emplace_back(u, v, w);
      }
   };

   // ターミナル集合Tからt1, t2を選び最短パスを木に追加する
   auto t1 = terminal_node_list[0];
   auto t2 = GetNearestTerminal(t1);

   AddShortestPath(t1, t2);

   for (auto t : terminal_node_list) {
      if (steiner_tree_node[t]) continue;

      // ターミナルノードから一番近いシュタイナー木ノードを求め最短パスを木に追加する
      auto n = GetNearestSteinerNode(t);
      AddShortestPath(t, n);
   }

   return steiner_tree_edge;
}
