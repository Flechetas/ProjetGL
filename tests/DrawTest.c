#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "CuTest.h"
#include "draw/draw.h"
#include "log.h"

void TestSpiralInitialisation(CuTest *tc) {
    initSpiralPoints();

    Point *blue_points = getBluePoints();
    Point *red_points = getRedPoints();
    int blen = getBlen();
    int rlen = getRlen();

    log_trace("blen = %d, rlen = %d", blen, rlen);
    CuAssertTrue(tc, blen > 0);
    CuAssertTrue(tc, rlen > 0);
    freePoints();
}

CuSuite* CuGetDrawSuite() {
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestSpiralInitialisation);
    return suite;
}