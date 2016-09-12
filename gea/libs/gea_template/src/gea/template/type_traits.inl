
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// type_traits                                                               //
// ------------------------------------------------------------------------- //

// value types
template <class T, T v>
struct integral_constant {
    typedef T value_type;
    static const T value = v;
};

// primary type categories
// is_void
template <class T> struct is_void : false_type{};
template <>        struct is_void<void> : true_type{};

// is_same
template <class T0, class T1> struct is_same : false_type {};
template <class T>            struct is_same<T, T> : true_type{};

// type properties
// is_const
template <class T> struct is_const : false_type {};
template <class T> struct is_const<const T> : true_type{};


// ------------------------------------------------------------------------- //

} // namespace gea //
} // namespace mth //
