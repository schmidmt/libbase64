#include <check.h>
#include <stdlib.h>
#include "../src/base64.h"

/* Test vectors from https://tools.ietf.org/html/rfc4648#page-12 */
const char *in_vectors[]  = {"", "f",    "fo",   "foo",  "foob",     "fooba",    "foobar"};
const size_t in_sizes[]   = {0,  1,      2,      3,      4,          5,          6};
const char *out_vectors[] = {"", "Zg==", "Zm8=", "Zm9v", "Zm9vYg==", "Zm9vYmE=", "Zm9vYmFy"};
const size_t out_sizes[]  = {0,  4,      4,      4,      8,          8,          8};



const size_t n_vectors = sizeof(in_vectors) / sizeof(in_vectors[0]);

START_TEST(rfc4648_vectors_encode_size)
{
	for (int i = 0; i < n_vectors; ++i) {
		ck_assert(Base64Encode_size(in_sizes[i]) >= out_sizes[i]);
	}
}
END_TEST

START_TEST(rfc4648_vectors_encode)
{
	char tmp[20];
	size_t size;
	for (int i = 0; i < n_vectors; ++i) {
		size = Base64Encode(tmp, in_vectors[i], in_sizes[i]);
		//ck_assert_int_eq(size, out_sizes[i]+1);
		ck_assert_str_eq(out_vectors[i], tmp);
	}
}
END_TEST

START_TEST(rfc4648_vectors_decode_size)
{
	for (int i = 0; i < n_vectors; ++i) {
		ck_assert(Base64Decode_size(out_sizes[i]) >= in_sizes[i]);
	}
}
END_TEST

START_TEST(rfc4648_vectors_decode)
{

	char tmp[20];
	size_t size;
	for (int i = 0; i < n_vectors; ++i) {
		size = Base64Decode(tmp, out_vectors[i], out_sizes[i]);
		//ck_assert_int_eq(size, in_sizes[i]+1);
		ck_assert_str_eq(in_vectors[i], tmp);
	}
}
END_TEST

Suite * base64_suite(void)
{
	Suite *s;
	TCase *tc_basic;
	
	s = suite_create("Base64");
	tc_basic = tcase_create("RFC4648");
	tcase_add_test(tc_basic, rfc4648_vectors_encode_size);
	tcase_add_test(tc_basic, rfc4648_vectors_decode_size);
	tcase_add_test(tc_basic, rfc4648_vectors_encode);
	tcase_add_test(tc_basic, rfc4648_vectors_decode);
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

	srunner_set_fork_status(sr, CK_NOFORK);
	
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
