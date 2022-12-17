#include "tasks.h"

using namespace vex;
using namespace std;

void autonomous(void) {
  chState = ctrl_AUTONOMOUS;


  intake(-100);
  fwState = fw_HSPD;
  //测试直到小车一秒走1块 左转一秒180度 右转1秒180度
  // 第一次前进长度还没确定
  // delay(10000);
  rotate_left(210);
  mov_bwd(300);
  roller(-100);
  delay(100);
  roller(0);
  rotate_right(210);
  
  mov_fwd(400);
  rotate_left(375);
  delay(2500);
  index(120);
  intake(-100);
  delay(3000);
  index(0);
  intake(100);

  rotate_right(400);
  // mov_fwd(1000);
  crash();

  delay(1000);
  mov_fwd(1500, 3);
  rotate_left(484);
  delay(8000);
  index(120);
  intake(-100);
  delay(5000);
  index(0);
  intake(100);
  rotate_right(1000);
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
      cout<<"here"<<endl;
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
    roller(100*(BY-RIGHT));
    // roller(-100*RIGHT);
    index(-100*DOWN);
    extend(100*UP);
    lastL1 = L1;
    // cout<<Hor.rotation(deg)<<"  "<<Ver.rotation(deg)<<endl;
    //printScreen(10,140,"x:%.2f y:%.2f v4gyro:%.2f v5gyro:%.2f",omniPos[0], omniPos[1], -v4gyro.rotation(),-Gyro.rotation());

    vexDelay(10);
  }
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
