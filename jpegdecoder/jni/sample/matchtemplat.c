#include "matchtemplat.h"

#include <math.h>

double matchtemplat(JpegDecode *tmp, JpegDecode *msk, JpegDecode *img, Roi roi) {

    long double varianceTmpImg = 0;
    long double tmpSquare = 0;
    long double imgSquare = 0;

    int roiXstart = roi.x;
    int roiXend   = roi.x + roi.w;
    int roiYstart = roi.y;
    int roiYend   = roi.y + roi.h;

    int i, j;
    for (i=roiYstart; i<roiYend; i++) {
        for (j=roiXstart; j<roiXend; j++) {
        
            unsigned int tmpPixe = tmp->getPixe(tmp, i, j);
            unsigned int mskPixe = msk->getPixe(msk, i, j);
            unsigned int imgPixe = img->getPixe(img, i, j);

            unsigned int andPixe = (mskPixe & imgPixe);
            int subPixe = (tmpPixe - andPixe);

            varianceTmpImg += (long double)(subPixe * subPixe);

            tmpSquare += (long double)(tmpPixe * tmpPixe);
            imgSquare += (long double)(andPixe * andPixe);
        }
    }

    fprintf(stdout, "variance: %Lf\n", varianceTmpImg);
    fprintf(stdout, "tmpSquar: %Lf\n", tmpSquare);
    fprintf(stdout, "imgsquar: %Lf\n", imgSquare);

    long double tigSquare = tmpSquare * imgSquare;
    fprintf(stdout, "tigSquar: %Lf\n", tigSquare);
    long double denominator = sqrtl(tigSquare);
    fprintf(stdout, "denominator: %Lf\n", denominator);

    double match_value = varianceTmpImg / denominator;

    return match_value;
}
