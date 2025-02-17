#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "../include/codec/nnf.h"
#include "../include/neuralnet/model.h"
#include "CuTest.h"


int equals(float a, float b) {
    float epsilon = 0.0001f; 
    return fabs(a - b) < epsilon;
}


void TestDecoding(CuTest* tc) {
    int ret;
    char *testFileName = "test_data.nnf";
    char *input = "3\n\n"
                  "2, 5\n\n"
                  "0.2, 0.5, 0.6, 0.7, 0.9\n"
                  "0.1, 0.3, 0.4, 0.6, 0.8\n\n"
                  "0.5, 0.8\n\n"
                  "5, 3\n\n"
                  "0.8, 0.3, 0.7\n"
                  "0.7, 0.9, 0.1\n"
                  "0.3, 0.7, 0.2\n"
                  "0.5, 0.4, 0.6\n"
                  "0.3, 0.5, 0.9\n\n"
                  "0.9, 0.6, 0.7, 0.1, 0.6";
    
    FILE *f = fopen(testFileName, "w");
    CuAssertPtrNotNull(tc, f);
    ret = fwrite(input, sizeof(char), strlen(input), f);
	CuAssertTrue(tc, ret != -1);
    ret = fclose(f);
    CuAssertTrue(tc, ret != -1);


    Model model;
    ret = fromFile(testFileName, &model);
    CuAssertTrue(tc, ret != -1);

    CuAssertTrue(tc, countLayers(model) == 3);
    CuAssertTrue(tc, model->layer_n == 3);
    
    Layer curr = model->input;
    CuAssertTrue(tc, curr->n == 2);
    CuAssertTrue(tc, curr->w == 5);
    CuAssertTrue(tc, equals(curr->weight[0][0], 0.2));
    CuAssertTrue(tc, equals(curr->weight[0][1], 0.5));
    CuAssertTrue(tc, equals(curr->weight[0][2], 0.6));
    CuAssertTrue(tc, equals(curr->weight[0][3], 0.7));
    CuAssertTrue(tc, equals(curr->weight[0][4], 0.9));

    CuAssertTrue(tc, equals(curr->weight[1][0], 0.1));
    CuAssertTrue(tc, equals(curr->weight[1][1], 0.3));
    CuAssertTrue(tc, equals(curr->weight[1][2], 0.4));
    CuAssertTrue(tc, equals(curr->weight[1][3], 0.6));
    CuAssertTrue(tc, equals(curr->weight[1][4], 0.8));

    CuAssertTrue(tc, equals(curr->bias[0], 0.5));
    CuAssertTrue(tc, equals(curr->bias[1], 0.8));

    curr = curr->next;
    CuAssertTrue(tc, curr->n == 5);
    CuAssertTrue(tc, curr->w == 3);
    CuAssertTrue(tc, equals(curr->weight[0][0], 0.8));
    CuAssertTrue(tc, equals(curr->weight[0][1], 0.3));
    CuAssertTrue(tc, equals(curr->weight[0][2], 0.7));

    CuAssertTrue(tc, equals(curr->weight[1][0], 0.7));
    CuAssertTrue(tc, equals(curr->weight[1][1], 0.9));
    CuAssertTrue(tc, equals(curr->weight[1][2], 0.1));

    CuAssertTrue(tc, equals(curr->weight[2][0], 0.3));
    CuAssertTrue(tc, equals(curr->weight[2][1], 0.7));
    CuAssertTrue(tc, equals(curr->weight[2][2], 0.2));

    CuAssertTrue(tc, equals(curr->weight[3][0], 0.5));
    CuAssertTrue(tc, equals(curr->weight[3][1], 0.4));
    CuAssertTrue(tc, equals(curr->weight[3][2], 0.6));

    CuAssertTrue(tc, equals(curr->weight[4][0], 0.3));
    CuAssertTrue(tc, equals(curr->weight[4][1], 0.5));
    CuAssertTrue(tc, equals(curr->weight[4][2], 0.9));

    CuAssertTrue(tc, equals(curr->bias[0], 0.9));
    CuAssertTrue(tc, equals(curr->bias[1], 0.6));
    CuAssertTrue(tc, equals(curr->bias[2], 0.7));
    CuAssertTrue(tc, equals(curr->bias[3], 0.1));
    CuAssertTrue(tc, equals(curr->bias[4], 0.6));

    curr = curr->next;
    CuAssertTrue(tc, curr->n == 3);

    remove(testFileName);

}


CuSuite* CuGetCodecSuite(void) {
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, TestDecoding);
    return suite;
}

