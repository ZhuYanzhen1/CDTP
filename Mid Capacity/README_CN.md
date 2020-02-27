## 中容量通信协议
src="https://raw.githubusercontent.com/ZhuYanzhen1/CDTP/master/Pic/Package%20Contents_cn.jpg" alt="PID Frame" title="PID Frame" style="zoom: 50%;" />
  + Package Contents_cn
  + 帧头、帧尾均为0xff的定长数据包
  + PID域用于包标识，自带翻转校验
  + 为了确保数据帧中出现的0xff不干扰帧头桢尾，加入调整帧
  + 数据帧中所有的0xff均替换为0x00，并在调整帧中相应位置1
  + 包校验长度若不等于12，说明数据错误