
namespace gea {
namespace mth {

// state functions
inline bool half::is_zero() const {
	return (m_bits & ~HALF_SIGN_MASK) == 0;
}
inline bool half::is_finite() const {
	uint16_t exp = HALF_EXP_F(m_bits);
	return exp < 31;
}
inline bool half::is_negative() const {
	return (m_bits & HALF_SIGN_MASK) != 0;
}
inline bool half::is_normalized() const {
	uint16_t exp = HALF_EXP_F(m_bits);
	return 0 < exp && exp < 31;
}
inline bool half::is_denormalized() const {
	uint16_t exp  = HALF_EXP_F (m_bits);
	uint16_t frac = HALF_FRAC_F(m_bits);
	return exp == 0 && frac != 0;
}
inline bool half::is_infinity() const {
	uint16_t exp  = HALF_EXP_F (m_bits);
	uint16_t frac = HALF_FRAC_F(m_bits);
	return exp == 31 && frac == 0;
}
inline bool half::is_nan() const {
	uint16_t exp  = HALF_EXP_F (m_bits);
	uint16_t frac = HALF_FRAC_F(m_bits);
	return exp == 31 && frac != 0;
}

// internal represenation access functions
inline uint16_t &half::bits() { return m_bits; }

// compression functions
inline bool half::can_pack(const float &f) {
	return HALF_MIN <= f && f <= HALF_MAX;
}

// segment access functions
inline const uint16_t half::HALF_SIGN_F(const uint16_t &x) { return ((x & HALF_SIGN_MASK) >> HALF_SIGN_SHIFT); }
inline const uint16_t half::HALF_EXP_F (const uint16_t &x) { return ((x & HALF_EXP_MASK ) >> HALF_EXP_SHIFT ); }
inline const uint16_t half::HALF_FRAC_F(const uint16_t &x) { return ((x & HALF_FRAC_MASK) >> HALF_FRAC_SHIFT); }

inline float half::overflow() const {
    volatile float f = 1e10;

	for (int i=0; i<10; ++i)	// this will overflow before	
		f *= f;					// the for-loop terminates
	return f;
}

} // namespace mth //
} // namespace gea //
