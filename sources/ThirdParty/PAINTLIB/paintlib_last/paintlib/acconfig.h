@BOTTOM@

// Byte order in a 32 bit word
#ifdef WORDS_BIGENDIAN
#define MSB_FIRST  // Motorola et al.
#else
#define LSB_FIRST // Intel et al.
#endif

#undef PL_SUPPORT_TGA
#undef PL_SUPPORT_BMP
#undef PL_SUPPORT_TIFF
#undef PL_SUPPORT_PICT
#undef PL_SUPPORT_JPEG
#undef PL_SUPPORT_PNG
#undef PL_SUPPORT_GIF
#ifdef _WINDOWS
  #define PL_SUPPORT_WEMF
#endif
#undef PL_SUPPORT_PCX
#undef PL_SUPPORT_PGM
#undef PL_SUPPORT_PPM
#undef PL_SUPPORT_PSD

//#ifdef _WINDOWS
//#define PIXEL_BGRA_ORDER  // MS Windows ordering
//#else
#define PIXEL_RGBA_ORDER // GNU/Linux (at least)
//#endif

// The following lines can be used to define maximum memory useage
// for a single BITMAP. If we need more, we assume something went wrong.
// If MAX_BITMAP_SIZE isn't defined, the code doesn't check for huge
// bitmaps and just tries to allocate the memory. This can take a
// long time.
// #ifndef MAX_BITMAP_SIZE
// #define MAX_BITMAP_SIZE 8L*1024*1024
// #endif

