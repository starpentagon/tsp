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

template<class T> istream& operator>>(istream& is, vector<T>& vec){ rep(i, vec.size()) is >> vec[i]; return is;}
template<class T> ostream& operator<<(ostream& os, vector<T>& vec){ rep(i, vec.size()) os << vec[i] << (i+1==(int)vec.size() ? "" : " "); return os;}
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
