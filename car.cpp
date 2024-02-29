#include<stdio.h>
#include<conio.h>
#include<windows.h>


DWORD bytesSend; 
 BOOL isSent; 
HANDLE hComm; 

char deger; 

int main() {
	
	hComm = CreateFile( "COM5",
	GENERIC_READ | GENERIC_WRITE,
	0,
	0,
	OPEN_EXISTING,
	FILE_ATTRIBUTE_NORMAL,
	0);
	
	if (hComm == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
		    printf("COM5'e erisim yok ");
		}
		
	}


DCB dcbSerialParams = {0};

dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

if (!GetCommState(hComm, &dcbSerialParams)) {
	printf("Baglanti hatasi");
	_getch();
	return EXIT_FAILURE;
}

dcbSerialParams.BaudRate = CBR_9600; 
dcbSerialParams.ByteSize = 8; 
dcbSerialParams.Parity = NOPARITY;
dcbSerialParams.StopBits = ONESTOPBIT;

if (!SetCommState(hComm, &dcbSerialParams)) {
	printf("Baglanti hatasi");
	_getch();
	return EXIT_FAILURE;
}

while (true) 
{
	
	printf("Bir yon belirtiniz: "); 
	
	deger=getch();
	
	isSent = WriteFile(hComm, &deger, sizeof(deger), &bytesSend, NULL); 
	
/*	if (!isSent) 
	{
		printf("mesaj yollanmadi");
	}
	else
	{
		printf("%c gonderildi\n",deger[0]);
	}*/
	
}
    CloseHandle(hComm);
    _getch();
    return 0;
}
