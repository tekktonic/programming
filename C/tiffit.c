#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tiff.h>
#include <tiffio.h>
#include <stdint.h>

#ifndef IMAGE_WIDTH
#define IMAGE_WIDTH 640
#endif
#ifndef IMAGE_HEIGHT
#define IMAGE_HEIGHT 480
#endif
#ifndef BYTESPP
#define BYTESPP 4
#endif

char *extension(char *string) {
	return strrchr(string, '.') + 1;
}

void slurp_data(FILE *src, char *data, size_t data_size) {
	for(size_t point = 0; point < data_size; point++) {
		if (feof(src))
			fseek(src, 0, SEEK_SET);
		
		data[point] = (char) getc(src);
	}

}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "No arguments given\n");
		exit(0);
	}
	
	size_t databuf_size = ((IMAGE_WIDTH * BYTESPP) * (IMAGE_HEIGHT));
	char *databuf = _TIFFmalloc(databuf_size);
	size_t databuf_point = 0;

	char *line = _TIFFmalloc(IMAGE_WIDTH * BYTESPP);

	
	TIFF *tiffile = TIFFOpen("tiffany.tiff", "w");
	FILE *fp = fopen("pdg.txt", "r");

	TIFFSetField(tiffile, TIFFTAG_IMAGEWIDTH, IMAGE_WIDTH);
	TIFFSetField(tiffile, TIFFTAG_IMAGELENGTH, IMAGE_HEIGHT);
	TIFFSetField(tiffile, TIFFTAG_SAMPLESPERPIXEL, BYTESPP);
	TIFFSetField(tiffile, TIFFTAG_BITSPERSAMPLE, 8);
	TIFFSetField(tiffile, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
	TIFFSetField(tiffile, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	TIFFSetField(tiffile, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

	TIFFSetField(tiffile, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tiffile, IMAGE_WIDTH));

	slurp_data(fp, databuf, databuf_size);

	int row = 0;
	for (size_t pos = 0; row <= IMAGE_HEIGHT && pos < databuf_size; pos += (IMAGE_WIDTH * BYTESPP), row++) {
		memcpy(line, databuf+pos, IMAGE_WIDTH * BYTESPP);
		for (size_t i = 0; i < IMAGE_WIDTH * BYTESPP; i++){ // brighten the image a bit
			if ((0xff - line[i]) <= 0x0A) // just brighten it a touch
				line[i] = 0xFF;
			else
				line[i] += 0x0A;
		}
		for (size_t i = 3; i < IMAGE_WIDTH * BYTESPP; i += BYTESPP) // remove transparency, RGBA so data[3] is the first Alpha byte
			line[i] = 0xff;
		TIFFWriteScanline(tiffile, line, row, 0);
	}

	TIFFClose(tiffile);
	_TIFFfree(line);
	_TIFFfree(databuf);
}
