#ifndef IMAGE_LOADER_H
#define IMAGE_H

struct image_u8;

struct image_u8 * image_u8_init();

void image_u8_free(struct image_u8 * img);

bool image_load_from_file(const char * fname, image_u8 * img);

#endif
