#include <catch2/catch_test_macros.hpp>

TEST_CASE("Default selection", "[ConfigGenerator]") {
	int a = 3;
	int b = 6;
	SECTION("Changing") {
		b=3;
		CHECK(a==b);
	}
	SECTION("Same") {
		CHECK_FALSE(a==b);
	}
}
