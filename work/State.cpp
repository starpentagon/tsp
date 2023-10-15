#include "State.hpp"
#include "debug_st.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
#define repp(i, s, n) for (int i = s; (i) < (int)(n); (i)++)

#define all(v) begin(v),end(v)
#define rall(v) rbegin(v),rend(v)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

bool operator>(const State& lhs, const State& rhs) {
   assert(false);
   return false;
}

bool operator<(const State& lhs, const State& rhs) {
   assert(false);
   return false;
}

State::State()
    : turn_(0), first_move_(kInvalidMove) {
   debug_st(turn_);
}

State State::operator=(State& state) {
   // メンバ変数をコピー
   // Note: メンバ変数を追加した場合はここに追加する
   turn_ = state.turn_;
   first_move_ = state.first_move_;

   return *this;
}

bool State::IsFinished() const {
   assert(false);
   return false;
}

ScoreType State::CalcScore() const {
   assert(false);
   return 0;
}

ScoreType State::CalcSearchScore() const {
   assert(false);
   return 0;
}

vector<MoveType> State::GetAllMoves() const {
   assert(false);
   vector<MoveType> move_list;

   return move_list;
}

vector<MoveType> State::GetNeibours() const {
   assert(false);
   vector<MoveType> move_list;

   return move_list;
}

void State::Move(const MoveType& move) {
   assert(false);
}

string State::GetString() const {
   assert(false);

   string str;
   return str;
}

void State::Output() const {
   cerr << GetString() << endl;
}
