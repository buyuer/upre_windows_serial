/*---------------------------------使用说明-------------------------------
使用：
将UPRE_Windows_Usart.cpp文件和UPRE_Windows_Usart.hpp文件放在工程目录下，在要使
用的文件中包含UPRE_Linux_Usart.hpp文件即可。Windows_Usart类封装了串口的相关函数。
            成员函数列表：
			public：
					Windows_Usart
					~Windows_Usart
					Read_Data
					Write_Data
					Get_HANDLE
注意：
      1、Windows_Usart类定义在 UPRE 命名空间下。
      2、如果在Visual Stdio 中使用提示CreatFile函数的第一个参数有问题，可以将Visual Stdio的字符集设置为多字节字符集。
	         （1）打开项目属性
			 （2）选择常规属性页
			 （3）将“字符集”属性修改为“使用多字节字符集”

声明：UPER_Windows_Usart.hpp和UPER_Windows_Usart.cpp文件内的代码为学习之用，使用中出现的任何的问题和后果自行负责，与作者和UPRE实验室无关。  

作者：丁欣童
-------------------------------------------------------------------------*/
#ifndef _UPRE_WINDOWS_USART_HPP_ 
#define _UPRE_WINDOWS_USART_HPP_

#include "Windows.h"
#include "vector"




namespace UPRE 
{
	typedef std::vector<unsigned char> v_uchar;

	typedef enum 
	{
		COM0 = 0,
		COM1 = 1,
		COM2 = 2,
		COM3 = 3,
		COM4 = 4,
		COM5 = 5,
		COM6 = 6,
		COM7 = 7,
		COM8 = 8,
		COM9 = 9,
		COM10 = 10,
	}USART_NUM;

	class Windows_Usart 
	{
	public:
		/*--------------------------------------------------------
		@函数：Windows_Usart
		@功能：Windows_Usart类的构造函数，打开并初始化串口。
		@参数：参数一：flag为USART_NUM类型的枚举，代表要打开并初始化的串口。
		               有默认值COM1。
		       参数二：rate为串口速率，可选参数，有默认值19200。取值为任意。
		--------------------------------------------------------*/
		Windows_Usart();
		
		Windows_Usart(USART_NUM flag, int rate = 19200);
		
		void open(USART_NUM flag, int rate = 19200);
		

		/*--------------------------------------------------------
		@函数： ~Windows_Usart
		@功能：Windows_Usart类的析构函数，关闭串口。
		--------------------------------------------------------*/
		~Windows_Usart();
		
		
		/*--------------------------------------------------------
		@函数：Write_Data
		@功能：从data中向串口写入writeLengh个字节的数据。
		@参数：参数一：data为unsigned char类型的vector，为要写入的数据
		       参数二：writeLengh 要写入的字节个数。有默认值0，表示把data
		               全部写入。
		       参数三: startLocation为操作data的起始位置。默认为0，表示从data[0]开始读取。
		@返回值：返回写入进的字节数，如写入失败，则返回 -1
		--------------------------------------------------------*/
		size_t Write_Data(v_uchar &data, size_t writeLengh = 0, size_t startLocation = 0);
		
		
		/*--------------------------------------------------------
		@函数：Read_Data
		@功能：从串口读取readLengh个字节的数据存到data中。
		@参数：参数一：data为unsigned char类型的vector，读出的数据存在data
		               对象里。
		       参数二：readLengh 要读取的字节个数。有默认值0，表示读取和data
		               长度大小一样的字节数。
		       参数三: startLocation为操作data的起始位置。默认为0，表示从data[0]开始写入。
		@返回值：返回读取到的字节数。
		--------------------------------------------------------*/
		size_t Read_Data(v_uchar &data, size_t readLengh = 0, size_t startLocation = 0);
		
		
		/*--------------------------------------------------------
		@函数：Get_HANDLE
		@功能：获取当前Linux_Usart对象的串口描述符fd。
		       借助这个函数可以用WriteFile函数和ReadFile函数直接操作串口。
		@返回值：串口句柄
		--------------------------------------------------------*/
		HANDLE Get_HANDLE();
	private:
		
		/*--------------------------------------------------------
		@变量：HANDLE
		@功能：CreateFile函数返回的串口句柄。
		--------------------------------------------------------*/
		HANDLE serial;
	};
}






#endif 

