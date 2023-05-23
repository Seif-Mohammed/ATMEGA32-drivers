#ifndef STDTYPE_H
#define STDTYPE_H
typedef unsigned char        u8;
typedef signed char          s8;
typedef unsigned short int   u16;
typedef signed short         s16;
typedef unsigned int         u32;
typedef signed int           s32;
typedef float                f32;
typedef double               f64;
/*ERROR INDICATION*/
#define STD_TYPES_OK  1
#define STD_TYPES_NOK 0
/**/
#define STD_TYPE_NULL ((void *) 0)
#endif
