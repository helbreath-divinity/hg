#include "Main.h"

void CConsole::SetColor(int iColor)
{
	HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hHandle,iColor);
}

void CConsole::PrintLog(char *szBuf, ...)
{
	char szBuffer[0x8000];
	va_list vaArgs;
	va_start(vaArgs,szBuf);
	vsprintf(szBuffer,szBuf,vaArgs);
	va_end(vaArgs);

	printf("[%s] %s",__TIMESTAMP__,szBuffer);

}

void CConsole::PrintCurrentFile(char *File)
{
	printf("[%s] %s\n",__TIMESTAMP__,File);
}

void CConsole::PrintRecieve(char *szBuffer, int iLen)
{
	printf("[%s]: ",__TIMESTAMP__);
	for(int i=0; i < iLen; i++)
		printf("%X ",szBuffer[i]);
	printf("\n");
}