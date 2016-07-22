#ifndef _MATCH_TEMPLAT_H_
#define _MATCH_TEMPLAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cdecode.h"

typedef struct Roi_s {
    int x, y, w, h;
} Roi;

double matchtemplat(JpegDecode *tmp, JpegDecode *msk, JpegDecode *img, Roi roi);

#endif

