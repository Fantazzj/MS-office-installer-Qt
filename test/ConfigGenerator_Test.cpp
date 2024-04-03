#include <catch2/catch_test_macros.hpp>

TEST_CASE("Check basic tests", "[check]" ) {
	int a = 3;
	int b = 6;
	SECTION("Changing") {
		b = 3;
		CHECK(a == b);
	}
	SECTION("Same") {
		CHECK_FALSE(a == b);
	}
}

TEST_CASE("Require basic tests", "[require]" ) {
	int a = 3;
	int b = 6;
	SECTION("Changing") {
		b = 3;
		REQUIRE(a == b);
	}
	SECTION("Same") {
		REQUIRE_FALSE(a == b);
	}
}
