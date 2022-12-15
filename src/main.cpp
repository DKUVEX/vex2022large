#include "tasks.h"

using namespace vex;
using namespace std;

void autonomous(void) {
  chState = ctrl_AUTONOMOUS;

  intake(100);
  fwState = fw_HSPD;
  //测试直到小车一秒走1块 左转一秒180度 右转1秒180度
  // 第一次前进长度还没确定

  mov_fwd(525);
  rotate_left(371);
  index(120);
  delay(3000);
  index(0);
  rotate_right(371);
  mov_fwd(525);
  rotate_left(454);
  index(120);
  delay(3000);
  index(0);
  rotate_right(604);
  mov_fwd(1000);
  rotate_right(500);
  mov_fwd(1200);
  intake(0);
  fwState = fw_OFF;
  
  
  //runAuton();
  //oneminute310p();
  // drift(50, 0, 1, 0.8);
  // drift(-100, 0, 1, 0.8);
  // mov_fwd(1000);

}
//gps 9、17
//motor 16
void usercontrol(void) {
  bool lastL1 = false;
  chState = ctrl_DEFAULT;
  sol.set(0);
  while (1) {

    if(BB) fwState = fw_OFF;
    else if(L2 && R1) fwState = fw_HSPD;
    else if(L2 && R2) fwState = fw_LSPD;
    // cout<<"here";
    if(fwState == fw_LSPD && kCount > 0) {
      // kick(1);
      // cout<<"kcount "<<kCount<<endl;
      index(120);
      intake(-100);
      vexDelay(100);
      if (kCount == 1)
      {
        kCount -= 1;
        index(0);
        intake(0);
      }
    }
    else if(fwState == fw_HSPD && ifSpeedOK && kCount > 0){
      // cout<<"kcount "<<kCount<<endl;
      index(120);
      intake(-100);
      vexDelay(100);
      if (kCount == 1)
      {
        kCount -= 1;
        index(0);
        intake(0);
      }
      // kick(1);
    }
    intake(-100*(R2-R1)*!L2);
    // cout<<R2<<" "<<R1<<endl;
    roller(100*BY);
    // extend(100*UP);
    lastL1 = L1;
    // cout<<Hor.rotation(deg)<<"  "<<Ver.rotation(deg)<<endl;
    //printScreen(10,140,"x:%.2f y:%.2f v4gyro:%.2f v5gyro:%.2f",omniPos[0], omniPos[1], -v4gyro.rotation(),-Gyro.rotation());

    vexDelay(10);
  }
}
void longpress()
{
  if(UP)
  {
    delay(2000);
    if (UP)
    {
      extend(100);
      delay(5000);
    }
  }
  extend(0);
}
int main() {
  vexDelay(200);
  task GP1(positioning);
  task GP2(GPSpositioning);
  task GP(posConfig);
  task BS(base);
  task FW(flywheelContorl);
  task LA(launch);
  task LP(longpress);

  vexDelay(200);
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  while (true) {
    vexDelay(100);
  }
}
