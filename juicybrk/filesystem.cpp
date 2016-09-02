#include "filesystem.h"
#include <stdio.h>
#include "gbfs.h"

namespace FileSystem
{
	static const GBFS_FILE* _gbfs = nullptr;

	void openFS(u8* gbfs)
	{
		_gbfs = (const GBFS_FILE*)gbfs;
	}

	const void* openFile(const char* filename, u32* len)
	{
		return gbfs_get_obj(_gbfs, filename, len);
	}
}
