#include <cstdio>
#include <iostream>
//#include <filesystem>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include "sha1.h"

int main(int argc, char** argv) {
	using namespace std;
	try {
		if (argc < 4) {
			cerr << "Usage: " << argv[0] << 
				" {threshold_size} {large_blob_storage_dir} {large_blob_public_url} [filenames...]" << endl;
			exit(1);
		}
		string sThresholdSize(argv[1]);
		string_view sLargeBlobStorageDir(argv[2]);
		string_view sLargeBlobPublicURL(argv[3]);
		vector<string_view> filenames;
		for (int i = 4; i < argc; ++i) filenames.push_back(string_view(argv[i]));

		size_t thresholdSize = [&sThresholdSize]() {size_t res = 0; istringstream s(sThresholdSize); s >> res; return res; }();

		// TODO: Ensure that the blob storage directory exists.

		// Read the file from standard input
		string sBuffer;
		fseek(stdin, 0L, SEEK_END);
		size_t sz = ftell(stdin);
		rewind(stdin);
		sBuffer.resize(sz); // This can be LARGE
		fread(sBuffer.data(), 1, sz, stdin);
		if (ferror(stdin)) return true;


		// Is the file a candidate for storage?
		bool doStore = false;
		if (sBuffer.size() > thresholdSize) doStore = true;

		// If not, just re-write the file to standard output.
		if (!doStore) {
			fwrite(sBuffer.data(), 1, sBuffer.size(), stdout);
		}
		// If the file will be extracted,
		// 1) Calculate the SHA-1 hash.
		// 2) Write the blob to the storage directory, under path_to_storage_dir/SHA-1_hash.
		// 3) Print the blob reference string to standard output.
		else {
			SHA1_CTX context;
			uint8_t digest[20];
			char outputHash[80];
			SHA1_Init(&context);
			SHA1_Update(&context, reinterpret_cast<uint8_t*>(sBuffer.data()), sBuffer.size());
			SHA1_Final(&context, digest);
			digest_to_hex(digest, outputHash);

			string blob_filepath(sLargeBlobStorageDir);
			blob_filepath += "/";
			blob_filepath += outputHash;

			string blob_pubURL(sLargeBlobPublicURL);
			blob_pubURL += "/";
			blob_pubURL += outputHash;
			// Checking for pre-existing file here. If the file already existed and had data, then
			// ftell will be nonzero.
			std::unique_ptr<FILE, decltype(&fclose)> pFile(fopen(blob_filepath.c_str(), "a+b"), &fclose);
			fseek(pFile.get(), 0L, SEEK_END);
			size_t currentPos = ftell(pFile.get());
			if (currentPos == 0) // Only write if the file is empty.
				fwrite(sBuffer.data(), 1, sBuffer.size(), pFile.get());
			fprintf(stdout, "BLOB-CONVERTED: %s\n", blob_pubURL.data());
		}
	}
	catch (std::exception &e) {
		cerr << e.what() << endl;
		exit(1);
	}
	catch (...) {
		cerr << "An unrecognized exception has occurred." << endl;
		exit(1);
	}
	return 0;
}