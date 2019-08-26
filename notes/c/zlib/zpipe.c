#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <zlib.h>

#define CHUNK 16384

int def(FILE *source, FILE *dest, int level)
{
	int ret, flush;
	unsigned have;
	z_stream strm;
	unsigned char in[CHUNK];
	unsigned char out[CHUNK];

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;

	ret = deflateInit(&strm, level);
	if (ret != Z_OK)
		return ret;

	do {
		strm.avail_in = fread(in, 1, CHUNK, source);
		if (ferror(source)) {
			deflateEnd(&strm);
			return Z_ERRNO;
		}

		flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
		strm.next_in = in;

		do {
			strm.avail_out = CHUNK;
			strm.next_out  = out;

			ret = deflate(&strm, flush);

			assert(ret != Z_STREAM_ERROR);
			have = CHUNK - strm.avail_out;

			if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
				(void)deflateEnd(&strm);
				return Z_ERRNO;
			}
		} while (strm.avail_out == 0);

		assert(strm.avail_in == 0);

	} while (flush != Z_FINISH);

	assert(ret == Z_STREAM_END);

	(void)deflateEnd(&strm);

	return Z_OK;
}

int inf(FILE *source, FILE *dest)
{
	int ret;
	unsigned have;
	z_stream strm;
	unsigned char in[CHUNK];
	unsigned char out[CHUNK];

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;

	strm.avail_in = 0;
	strm.next_in = Z_NULL;

	ret = inflateInit(&strm);
	if (ret != Z_OK)
		return ret;

	do {
		strm.avail_in = fread(in, 1, CHUNK, source);
		if (ferror(source)) {
			(void)inflateEnd(&strm);
			return Z_ERRNO;
		}
		if (strm.avail_in == 0)
			break;
		strm.next_in = in;
		do {
			strm.avail_out = CHUNK;
			strm.next_out = out;

			ret = inflate(&strm, Z_NO_FLUSH);
			assert(ret != Z_STREAM_ERROR);
			switch (ret) {
				case Z_NEED_DICT:
					ret = Z_DATA_ERROR;
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					(void)inflateEnd(&strm);
					return ret;
			}

			have = CHUNK - strm.avail_out;
			if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
				(void)inflateEnd(&strm);
				return Z_ERRNO;
			}
		} while (strm.avail_out == 0);
	} while (ret != Z_STREAM_END);

	(void)inflateEnd(&strm);
	return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

#define SOURCE "jpeg.c"

int main(int argc, const char *argv[])
{
	FILE *source, *dest;
	const char *source_filename;
	char *dest_filename;

	if (argc != 2) {
		fprintf(stderr, "usage: ./zpipe filename\n");
		exit(EXIT_FAILURE);
	}

	source_filename = argv[1];

	dest_filename = malloc(strlen(source_filename) + 5 + 1);
	strcat(dest_filename, source_filename);
	strcat(dest_filename, ".zlib");

	source = fopen(SOURCE, "rb");
	if (source == NULL) {
		fprintf(stderr, "Can't open file %s", source_filename);
		exit(EXIT_FAILURE);
	}
	dest = fopen(dest_filename, "wb");
	if (dest == NULL) {
		fprintf(stderr, "Can't open file %s", dest_filename);
		fclose(source);
		exit(EXIT_FAILURE);
	}

	def(source , dest, Z_DEFAULT_COMPRESSION);

	fclose(source);
	fclose(dest);

	return 0;
}
