#include "windows.h"
#include "iostream"
#include "UPRE_Windows_Usart.hpp"
#include  "cstdio"
#include "serial_test.h"
#include "string.h"

using namespace std;
using namespace UPRE;

int main(int argc,char** argv)
{
	UPRE::v_uchar data(1);
	UPRE::Windows_Usart usart;
	if (argc == 2) {
		if (!strcmp(argv[1], "COM0"))usart.open(UPRE::COM0, 460800);
		else if (!strcmp(argv[1], "COM1"))usart.open(UPRE::COM1, 460800);
		else if (!strcmp(argv[1], "COM2"))usart.open(UPRE::COM2, 460800);
		else if (!strcmp(argv[1], "COM3"))usart.open(UPRE::COM3, 460800);
		else if (!strcmp(argv[1], "COM4"))usart.open(UPRE::COM4, 460800);
		else if (!strcmp(argv[1], "COM5"))usart.open(UPRE::COM5, 460800);
		else if (!strcmp(argv[1], "COM6"))usart.open(UPRE::COM6, 460800);
		else if (!strcmp(argv[1], "COM7"))usart.open(UPRE::COM7, 460800);
		else if (!strcmp(argv[1], "COM8"))usart.open(UPRE::COM8, 460800);
		else if (!strcmp(argv[1], "COM9"))usart.open(UPRE::COM9, 460800);
		else if (!strcmp(argv[1], "COM10"))usart.open(UPRE::COM10, 460800);
		else { cout << "请输入正确的串口号，COM0--COM10，如:UPRE陀螺仪100A.exe COM3" << endl; exit(0); }
	}
	else {
		cout << "请输入要打开的串口，COM0--COM10，如:UPRE陀螺仪100A.exe COM3" << endl; exit(0);
	}

	int usart3_rec_data = 0;

	int rec[8] = {0};

	int rec_loc = 0;

	int angle = 0;

	int temperature = 0;

	float real_angle = 0.0f;

	float angle_sum = 0.0f;

	float real_temperature = 0.0f;
	
	float time = 0.0f;

	while (1) 
	{
		if (usart.Read_Data(data,1) > 0) 
		{
			usart3_rec_data = data[0];

			if(usart3_rec_data == 0x80)
			{
				rec_loc = 1;
			}
			else
			{
				if(rec_loc > 0  && rec_loc < 8)
				{
					rec[rec_loc++] = usart3_rec_data;
				}
				if(rec_loc > 0x07)
				{
					if ((rec[1] ^ rec[2] ^ rec[3] ^ rec[4]) == rec[5]) 
					{
						if ((rec[1] & 0x40) == 0x00)
						{
							angle = rec[4] | (rec[3] << 7) | (rec[2] << 14) | (rec[1] << 21);
						}
						else
						{
							angle = (rec[4] | (rec[3] << 7) | (rec[2] << 14) | (rec[1] << 21)) | 0xf0000000u;
						}

						if ((rec[6] & 0x40) == 0x00)
						{
							temperature = rec[7] | (rec[6] << 7);
						}
						else
						{
							//temperature = (rec[7] | (rec[6] << 7)) | 0xffffc0000u;
						}

						real_temperature = temperature * 0.0625f;


						real_angle = angle / 14111.4f;//166513/*14070.316f;//166516*/
													  //USART_SendData(USART6,0XFF);
													  //sprintf(str,"%d %lf\n",angle,real_angle);
													  //upre_serial_send_str(USART6,str);

						/*	static float rang_rangle = 0;
						static int tempNUM = 0;
						rang_rangle += real_angle;
							if(++tempNUM >= 10)
						{
							rang_rangle /= tempNUM;
							cout << rang_rangle << endl;
							rang_rangle = 0;
							tempNUM = 0;
						}*/
						rec_loc = 0;
						angle_sum = angle_sum + (real_angle * 0.002f) - 0.000005319f;
						
						if (real_angle >= 0)
						{
							printf("T: %f  angle: %f     angle_s:  %f\n", real_temperature, angle_sum, real_angle);
						}
						else
						{
							printf("T: %f  angle: %f     angle_s: %f\n", real_temperature, angle_sum, real_angle);
						}

						/*if (real_angle >= 0)
						{
							printf("angle: %10d  real_angle: %f  %x %x %x %x %x %x %x\n", angle, real_angle, rec[1], rec[2], rec[3], rec[4], rec[5], rec[6], rec[7]);
						}
						else
						{
							printf("angle: %10d  real_angle:%f  %x %x %x %x %x %x %x\n", angle, real_angle, rec[1], rec[2], rec[3], rec[4], rec[5], rec[6], rec[7]);
						}*/
					}
					else 
					{
						printf("error receive\n");
					}
				}
			}
		}
	}
}
