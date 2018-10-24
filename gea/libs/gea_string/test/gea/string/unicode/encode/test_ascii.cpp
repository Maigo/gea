// gtest includes
#include <gtest/gtest.h>

// gea includes
#include <gea/string/unicode/encode/ascii.h>

namespace gea {
namespace uni {
namespace ascii {

// ------------------------------------------------------------------------- //
// charset_ascii                                                             //
// ------------------------------------------------------------------------- //

TEST(gea_string_unicode_encode, ascii_validate_string)
{
	struct data_type { const char8_t* s; ascii::error_code res; };
	const data_type data_set[] = {
		{ "zupEfT\0hCfzGj61", ascii::ASCII_OK },
		{ "LUJKn8sPjnYX50gd", ascii::ASCII_OK },
		{ "VthcveXx""\x12""\x20""\x41wwww", ascii::ASCII_OK },
		{ "", ascii::ASCII_OK },

		{ "\xFF", ascii::ASCII_INVALID_CODEPOINT}
	};

	for (const data_type &data : data_set) {
		const uint8_t* s = reinterpret_cast<const uint8_t*>(data.s);
		EXPECT_EQ(ascii::validate_string(s), data.res);
	}
}

} // namespace ascii //
} // namespace mth //
} // namespace gea //
