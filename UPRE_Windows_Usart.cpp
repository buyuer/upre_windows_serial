#include "UPRE_Windows_Usart.hpp"

#include "vector"
#include "iostream"


using namespace UPRE;
using namespace std;



UPRE::Windows_Usart::Windows_Usart()
{
}

Windows_Usart::Windows_Usart(USART_NUM flag, int rate)
{
	this->open(flag, rate);
}

void UPRE::Windows_Usart::open(USART_NUM flag, int rate)
{
	DCB serial_opt;
	switch (flag)
	{
	case 0:serial = CreateFile(TEXT("COM0"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); break;
	case 1:serial = CreateFile(L"COM1", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); break;
	case 2:serial = CreateFile(L"COM2", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); break;
	case 3:serial = CreateFile(L"COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); break;
	case 4:serial = CreateFile(L"COM4", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); break;
	case 5:serial = CreateFile(L"COM5", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); break;
	case 6:serial = CreateFile(L"COM6", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); break;
	case 7:serial = CreateFile(L"COM7", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); break;
	case 8:serial = CreateFile(L"COM8", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); break;
	case 9:serial = CreateFile(L"COM9", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); break;
	case 10:serial = CreateFile(L"COM10", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); break;
	}
	if (serial == INVALID_HANDLE_VALUE)
	{
		cout << "open failed" << endl;
		exit(0);
	}
	if (GetCommState(serial, &serial_opt) == 0)
	{
		cout << "GetCommState failed" << endl;
		exit(0);
	}
	serial_opt.BaudRate = rate;
	serial_opt.fParity = FALSE;
	serial_opt.fBinary = TRUE;
	serial_opt.ByteSize = 8;
	serial_opt.StopBits = ONESTOPBIT;
	serial_opt.fAbortOnError = FALSE;
	serial_opt.Parity = EVENPARITY;
	if (SetCommState(serial, &serial_opt) == 0)
	{
		cout << "SetCommState failed" << endl;
	}

	cout << "OK" << endl;
}

Windows_Usart::~Windows_Usart() 
{
	CloseHandle(serial);
}

size_t Windows_Usart::Write_Data(v_uchar &data, size_t writeLengh, size_t startLocation) 
{
	DWORD writeNum;
	if (writeLengh == 0) 
	{
		writeLengh = data.size();
	}
	if (writeLengh > data.size() - startLocation) 
	{
		cout << "error : 数组越界" << endl;
		return 0;
	}
	if (WriteFile(serial, &data[startLocation], writeLengh, &writeNum, NULL)) 
	{
		return writeNum;
	}
	else 
	{
		return 0;
	}
}

size_t Windows_Usart::Read_Data(v_uchar &data, size_t readLengh, size_t startLocation) 
{
	DWORD readNum;
	if(readLengh==0)
	{
		readLengh = data.size();
    }
	if (readLengh > data.size() - startLocation)
	{
		cout << "error : 数组越界" << endl;
		return 0;
	}
	if (ReadFile(serial, &data[startLocation], readLengh, &readNum, NULL))
	{
		return readNum;
	}
	else
	{
		return 0;
	}
}

HANDLE Windows_Usart::Get_HANDLE()
{
	return serial;
}
