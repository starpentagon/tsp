#include "Parameter.hpp"

using namespace std;

Parameter::Parameter()
    :                      // デフォルトパラメタ
      sa_max_temp_(3000),  // SA: 最大温度
      sa_min_temp_(0)      // SA: 最小温度
{
}

pair<int, int> Parameter::GetSATemp() const {
   return {sa_min_temp_, sa_max_temp_};
}

void Parameter::SetSATemp(int min_temp, int max_temp) {
   sa_min_temp_ = min_temp;
   sa_max_temp_ = max_temp;
}
