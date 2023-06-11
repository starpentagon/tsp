// パラメタ管理
#include <bits/stdc++.h>

namespace std {

class Parameter {
  public:
   Parameter();

   // -- SA --
   // 最小/最大温度
   pair<int, int> GetSATemp() const;
   void SetSATemp(int min_temp, int max_temp);

  protected:
   // -- SA --
   int sa_max_temp_;  // 最大温度
   int sa_min_temp_;  // 最大温度
};

}  // namespace std