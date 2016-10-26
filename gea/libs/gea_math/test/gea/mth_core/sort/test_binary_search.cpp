// gtest includes
#include <gtest/gtest.h>

// std includes
#include <algorithm>

// gea includes
#include <gea/mth_core/sort/binary_search.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// binary_search                                                             //
// ------------------------------------------------------------------------- //

TEST(gea_math, binary_search)
{
    // binary_search
    {
        typedef std::vector<int> DataSet;
        DataSet data_set = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//        DataSet::const_iterator it = binary_search(data_set.begin(), data_set.end(), [](const int& lhs, const int& rhs)->bool { return (lhs < rhs); });
    }
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
