
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cdecode.h"
#include "matchtemplat.h"
#include "recognize.h"

int main(int argc, char **argv) {

    double matchValue = logoMatchTemplat(argv[1], argv[2], argv[3], 0, 0, atoi(argv[4]), atoi(argv[5]));
    
    printf("matchvalue is: %f\n", matchValue);
    return 0;
}


