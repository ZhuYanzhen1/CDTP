#include "decrypt.h"
#include "string.h"
#include "ioctrl.h"
void Comm_Received_CallBack(unsigned char Receive_Buffer[])
{
	unsigned char Buffer_Data_Counter=0;
	unsigned char Buffer_Flag=0;
	while(1)
	{
		if(Buffer_Flag == 0 && Receive_Buffer[Buffer_Data_Counter] == 0xff)
			Buffer_Flag = 1;
		else if(Buffer_Flag == 1 && Receive_Buffer[Buffer_Data_Counter] == 0xff)
			break;
		Buffer_Data_Counter++;
	}
	Buffer_Data_Counter++;
	if(Buffer_Data_Counter == 12)   //if the package had been broken
  {
    unsigned char Data_Buffer[8];
    unsigned char PID_Bit = Receive_Buffer[1]>>4;  //Get The PID Bit
    if(PID_Bit == ((~(Receive_Buffer[1] & 0x0f)) & 0x0f) )  //PID Verify Success
    {
      unsigned char Temp_Var = 0x00 ;
      while(1)     //Memory Copy
      {
        Data_Buffer[Temp_Var] = Receive_Buffer[2+Temp_Var];
        Temp_Var++;
        if(Temp_Var == 8)
					break;
      }
      if(Receive_Buffer[10] != 0x00)   //Some Byte had been replace
      {
        unsigned char Temp_Filter = 0x00;
				Temp_Var = 0;
        while(1)
        {
          if(((Receive_Buffer[10] & (Temp_Filter|(0x01<<Temp_Var)))>>Temp_Var) == 1)  //This Byte Need To Adjust
             Data_Buffer[Temp_Var] = 0xff;    //Adjust to 0xff
          Temp_Var++;
          if(Temp_Var == 8)
            break;
        }
			}
      Receive_CallBack(PID_Bit, Data_Buffer);
    }
	}
}
