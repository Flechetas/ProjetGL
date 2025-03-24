#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "CuTest.h"
#include "log.h"
#include "neuralnet/model.h"
#include "neuralnet/layer.h"

void TestModelStructure(CuTest *tc) {
    log_info("Starting test on model structure");
    log_info("Testing initialisation");
    Model m = createModelRandom(5, 2, 8, 8, 8, 2);
    CuAssertTrue(tc, m != NULL);

    log_info("Testing structural correctness");
    Layer l = firstLayer(m);
    while(l->next != NULL) {
        CuAssertTrue(tc, l->w == l->next->n);
        l = l->next;
    }

    log_info("Testing weight initialisation");
    l = firstLayer(m);
    while(l->next != NULL) {
        for (int i = 0; i < l->n; i++) {
            for (int j = 0; j < l->w; j++) {
                bool cond = (l->weight[i][j] <= 1 && l->weight[i][j] >= -1);
                CuAssertTrue(tc, cond);
            }
        }
        l = l->next;
    }
}

CuSuite* CuGetModelSuite() {
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestModelStructure);
    return suite;
}