#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_
#include "types.h"

namespace FileSystem
{
	void openFS(u8* gbfs);

	const void* openFile(const char* filename, u32* len = nullptr);
	//void closeFile();
}

#endif
