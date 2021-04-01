#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <vector>
#include <fstream>
#include <TlHelp32.h>

#include <WinInet.h>
#include <urlmon.h>
#include <Psapi.h>

#include "inject.h"

using namespace std;

#pragma comment(lib, "WinInet.lib")
#pragma comment(lib, "urlmon.lib") 
#pragma comment(lib, "psapi.lib") 