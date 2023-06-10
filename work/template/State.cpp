#include "State.hpp"

using namespace std;

State::State()
    : turn_(0) {
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

void State::Move(const MoveType& move) {
   assert(false);
}
