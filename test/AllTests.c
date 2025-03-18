#include <stdio.h>

#include "CuTest.h"

CuSuite* CuGetCodecSuite();
CuSuite* CuGetForwardPassSuite();

void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, CuGetCodecSuite());
	CuSuiteAddSuite(suite, CuGetForwardPassSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

int main(void)
{
	RunAllTests();
}
