# Tests

### CuTest docs

https://github.com/asimjalis/cutest

### Run tests

``` console
make tests
```

### Add a test

``` c
// SamplePackageTest.c

int x = 10;

void TestDecoding(CuTest* tc) {
    CuAssertTrue(tc, x == 10);
}

CuSuite* CuGetSamplePackageSuite(void) {
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, TestDecoding);
    return suite;
}
```

``` c
// AllTests.c

+ CuSuite* CuGetSamplePackageSuite();

void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

  + CuSuiteAddSuite(suite, CuGetSamplePackageSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}
```
