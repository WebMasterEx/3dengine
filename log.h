#pragma once

#include <fstream>
#include <string>
#include <Windows.h>

class Log {
public:
	static HRESULT Initialize(std::string fileName);
	static void Shutdown();

	static void Write(std::string str);

protected:
	static std::ofstream file;
};