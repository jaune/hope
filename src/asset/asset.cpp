#include "asset.h"

#include "../core/core.h"
#include "../console.h"

#include <stdio.h>
#include <map>
#include "assets_generated.h"

#if defined(_MSC_VER) && _MSC_VER >= 1400
#define _CRT_SECURE_NO_WARNINGS // suppress warnings about fopen()
#pragma warning(push)
#pragma warning(disable:4996)   // suppress even more warnings about fopen()
#endif

namespace hope {
namespace asset {

	static std::map<std::string, Asset> kAssetMap;


	void* loadFile(const char* path) {
		FILE* file = fopen(path, "rb");
		if (file == NULL) {
			::hope::console::log("fopen failed: %s\n", path);
			return NULL;
		}
		if (fseek(file, 0L, SEEK_END) != 0){
			fclose(file);
			::hope::console::log("fseek failed\n");
			return NULL;
		}
		size_t file_size = ftell(file);
		if (file_size == -1) {
			::hope::console::log("ftell failed\n");
			fclose(file);
			return NULL;
		}
		rewind(file);

		void* buffer = new char[file_size];

		size_t read = fread(buffer, file_size, 1, file);
		if (read != 1) {
			::hope::console::log("fread failed (%i / %i)\n", read, file_size);
			return NULL;
		}

		fclose(file);

		::hope::console::log("loadFile (%s)\n", path);

		return buffer;
	}

	int32_t load() {
		void* headers_buffer = loadFile("assets.headers.bin");
		if (headers_buffer == NULL) {
			return 45;
		}

		const ::hope::asset::fbs::Assets* assets = ::hope::asset::fbs::GetAssets(headers_buffer);

		void* content_buffer = loadFile("assets.content.bin");
		if (content_buffer == NULL) {
			return 46;
		}

		flatbuffers::uoffset_t i = 0, length = assets->assets()->size();
		for (; i < length; i++) {
			const ::hope::asset::fbs::Asset* assetHeader = assets->assets()->Get(i);

//			SDL_Log("===> %s ", assetHeader->identifier()->c_str());

			void* asset_content = (char*)content_buffer + assetHeader->position();

			::hope::asset::Asset assetData;
			assetData.pointer = asset_content;
			assetData.size = (size_t)assetHeader->size();
			kAssetMap[assetHeader->identifier()->c_str()] = assetData;
		}
		
		return 0;
	}

	Asset get(const char* key) {
		return kAssetMap.at(key);
	}

	Asset get(const std::string& key) {
		return kAssetMap.at(key);
	}

} /* namespace asset */
} /* namespace hope */