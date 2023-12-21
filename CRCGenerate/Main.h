#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <WinINet.h>
#include <fstream>
#include <direct.h>
#include <string>
#include "Console.h"


using namespace std;

void dir(const char *szDir, bool bCountHidden, string shortDir = "");
