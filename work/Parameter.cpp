#include "Parameter.hpp"

using namespace std;

Parameter::Parameter()
    :                      // デフォルトパラメタ
      sa_max_temp_(3000),  // SA: 最大温度
      sa_min_temp_(0),     // SA: 最小温度
      beam_width_(3),      // Beam Search: ビーム幅
      beam_depth_(10)      // Beam Search: 探索深さ
{
}

pair<int, int> Parameter::GetSATemp() const {
   return {sa_min_temp_, sa_max_temp_};
}

void Parameter::SetSATemp(int min_temp, int max_temp) {
   sa_min_temp_ = min_temp;
   sa_max_temp_ = max_temp;
}

int Parameter::GetBeamDepth() const {
   return beam_depth_;
}

int Parameter::GetBeamWidth() const {
   return beam_width_;
}

void Parameter::SetBeamDepth(int depth) {
   beam_depth_ = depth;
}

void Parameter::SetBeamWidth(int width) {
   beam_width_ = width;
}
