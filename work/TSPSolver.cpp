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

vector<int> TSPSolver::SolveNN() {
   InitNearestNeighbor();
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
