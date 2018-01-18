#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main(int argc, char **argv)
{
    png_byte png_header[8];
    int img_w, img_h;

    png_bytep *rows;

    png_structp png;
    png_infop png_info;

    FILE *fp = fopen(argv[1], "rb");
    fread(png_header, 1, 8, fp);
    if (png_sig_cmp(png_header, 0, 8))
    {
	exit(1);
    }

    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    png_info = png_create_info_struct(png);

    if (setjmp(png_jmpbuf(png)))
	exit(2);

    png_init_io(png, fp);
    png_set_sig_bytes(png, 8);
    png_read_info(png, png_info);

    img_w = png_get_image_width(png, png_info);
    img_h = png_get_image_height(png, png_info);
    printf("Some number %d\n", img_h);
    png_read_update_info(png, png_info);

    printf("debug!\n\n");
    rows = malloc(sizeof(png_bytep) * img_h);

    for (int y = 0; y < img_h; ++y)
    {
	rows[y] = malloc(png_get_rowbytes(png, png_info));
    }
    png_read_image(png, rows);
    fclose(fp);
}
