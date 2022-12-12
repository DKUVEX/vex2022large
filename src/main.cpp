#include "tasks.h"

using namespace vex;
using namespace std;

void autonomous(void) {
  chState = ctrl_AUTONOMOUS;
  //runAuton();
  //oneminute310p();
  // drift(50, 0, 1, 0.8);
  // drift(-100, 0, 1, 0.8);
  mov_fwd(1000);
}

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

  vexDelay(200);
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  while (true) {
    vexDelay(100);
  }
}
