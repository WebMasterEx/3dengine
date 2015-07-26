#include "log.h"

std::ofstream Log::file;

HRESULT Log::Initialize(std::string filename) {
	file.open(filename);

	return S_OK;
}

void Log::Shutdown() {
	file.close();
}

void Log::Write(std::string str) {
	file << str << std::endl;
}