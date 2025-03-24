#include <stdio.h>

#include "CuTest.h"
#include "log.h"

CuSuite* CuGetCodecSuite();
CuSuite* CuGetForwardPassSuite();
CuSuite* CuGetDrawSuite();

void RunAllTests(void)
{
	log_set_level(1);

	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, CuGetCodecSuite());
	CuSuiteAddSuite(suite, CuGetForwardPassSuite());
	CuSuiteAddSuite(suite, CuGetDrawSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

int main(void)
{
	RunAllTests();
}
