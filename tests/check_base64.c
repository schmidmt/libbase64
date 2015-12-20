#include <check.h>
#include <stdlib.h>
#include "../src/base64.h"

START_TEST(test_conversion)
{
	char *plain, *enc, *dec;
	size_t n, pln_len, enc_len, dec_len;

	char * tests[] = {
		"Hello World",
		"This is a very long string I guess..."
	};
	n = sizeof(tests) / sizeof(tests[0]);

	for(size_t i = 0; i < n; ++i) {
		plain = tests[i];
		pln_len = strlen(plain);

		enc_len = Base64Encode_size(pln_len);
		enc = malloc(enc_len);
		enc_len = Base64Encode(enc, plain, pln_len);
		
		dec_len = Base64Decode_size(enc);
		dec = malloc(dec_len);
		dec_len = Base64Decode(dec, enc, enc_len);

		ck_assert_str_eq(plain, dec);
	}
}
END_TEST

Suite * base64_suite(void)
{
	Suite *s;
	TCase *tc_basic;
	
	s = suite_create("Base64");
	tc_basic = tcase_create("Basic");
	tcase_add_test(tc_basic, test_conversion);
	suite_add_tcase(s, tc_basic);
	
	return s;
}

int main(int argc, char *argv[])
{
	int number_failed;
	Suite *s;
	SRunner *sr;
	
	s = base64_suite();
	sr = srunner_create(s);
	
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
