#include "Main.h"
#include "crc.h"

#define GetCurrentDir _getcwd

char cCurrentPath[FILENAME_MAX];

ofstream myfile;

int main()
{
	long time = timeGetTime();
	
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return errno;
	}

	CConsole *console = new CConsole();
	console->SetColor(10);
	console->PrintLog("Building Patch list of Current Directory...\n");
	myfile.open ("Patch.txt");
	dir(cCurrentPath, false);
	myfile.close();
	
	printf("Time: %u\n", timeGetTime() - time);
	system("PAUSE");
	return 0;
}

//Straight nigger rigged like a G
void dir(const char *szDir, bool bCountHidden = false, string shortDir)
{		
	CConsole *console = new CConsole();
	char path[MAX_PATH];
	char temp[MAX_PATH];
	char shortd[256];
	char cFile[256];
	Boolean_T errors;
	char sHash[50];
	DWORD crc;
	bool is_CRC =0;
	WIN32_FIND_DATA fd;
	DWORD dwAttr = FILE_ATTRIBUTE_DIRECTORY;
	if( !bCountHidden) dwAttr |= FILE_ATTRIBUTE_HIDDEN;
	sprintf_s( path, "%s\\*", szDir);

	string Dir = shortDir;
	if(Dir.find("SAVE") != string::npos  || 
		Dir.find("updates") != string::npos  ||
		Dir.find("CONDUCT") != string::npos  ||
		Dir.find("svn") != string::npos  ||
		Dir.find("FRIENDS") != string::npos ||
		Dir.find("MUTES") != string::npos)
	{
		return;
	}

	HANDLE hFind = FindFirstFile( path, &fd);

	if(hFind != INVALID_HANDLE_VALUE)	
	{		
		do
		{
			if( !(fd.dwFileAttributes & dwAttr))

				if(fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
				{
					Dir=fd.cFileName;
					if( Dir.find("Patch.txt") != string::npos 
						|| Dir.find("CRCGen") != string::npos
						|| Dir.find("Uninstall") != string::npos
						|| Dir.find(".lnk") != string::npos)
					{
						continue;
					}
					if(shortDir == "")
					{		


						errors = crc32file(fd.cFileName, &crc);
						sprintf(sHash,"%08lX",crc);
						printf("File : %s  || Hash : %08lX \n",fd.cFileName, crc);

						myfile << fd.cFileName << "*";
						myfile << sHash << "*";
						myfile << fd.nFileSizeLow << "\n";
					}
					else
					{
						//New Subdirectory file
						sprintf_s(cFile,"%s\\%s",szDir,fd.cFileName);
						errors = crc32file(cFile, &crc);

						sprintf(sHash,"%08lX",crc);
						printf("File : %s  || Hash : %08lX \n",fd.cFileName, crc);
						myfile << shortDir << "\\" << fd.cFileName << "*";
						myfile << sHash << "*";
						myfile << fd.nFileSizeLow << "\n";
					}
				}
		} while( FindNextFile( hFind, &fd));
		FindClose( hFind);

		// directories
		hFind = FindFirstFile( path, &fd);

		if(hFind != INVALID_HANDLE_VALUE)	
		{	
			do
			{
				if(fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
				{
					if(fd.cFileName[0] != '.')
					{
						//New Subdirectory exists
						sprintf_s(temp,"%s\\%s\\",szDir,fd.cFileName);
						//printf("%s \n",temp);

						if(shortDir == "")
							sprintf_s(shortd, "%s", fd.cFileName);
						else
							sprintf_s(shortd, "%s\\%s", shortDir.c_str(), fd.cFileName);

						dir(temp,false,shortd);
					}
				}
			} while( FindNextFile( hFind, &fd));
			FindClose( hFind);
		}
	}	
	
}