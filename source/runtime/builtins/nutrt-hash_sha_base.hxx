//
// nutrt-hash_sha_func.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

namespace coconut {
	namespace runtime {
		namespace builtins {

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool hash_sha_hex(std::istream & in_binary, hash::sha_base * h)
{
	bool result = false;
	std::size_t blocksize = 256;
	std::size_t chunksize = 0;
	std::streampos insize = 0;
	char * buffer = nullptr;
	in_binary.seekg(0, in_binary.end);
	insize = in_binary.tellg();
	in_binary.clear();
	in_binary.seekg(0, in_binary.beg);
	if (insize) {
		if (insize >= 1024 * 1024) {
			blocksize = 1024;
		} else if (insize >= 1024 * 512) {
			blocksize = 512;
		}
		buffer = new char[blocksize];
		if (buffer != nullptr) {
			std::memset(buffer, 0, blocksize);
			while (!in_binary.eof()) {
				in_binary.read(buffer, static_cast<std::streamsize>(blocksize));
				std::streamsize cnt = in_binary.gcount();
				if (cnt) {
					chunksize = static_cast<std::size_t>(cnt);
					h->add(buffer, chunksize);
					result = true;
				}
			}
			delete [] buffer;
			buffer = nullptr;
		}
	}
	return result;
}

}}} /* EONS */

/* EOF */