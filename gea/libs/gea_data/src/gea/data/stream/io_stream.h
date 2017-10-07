#ifndef __GEA_DATA_IO_STREAM_H__
#define __GEA_DATA_IO_STREAM_H__

#include <limits>

namespace gea {

// ------------------------------------------------------------------------- //
// io_ostream                                                                //
// ------------------------------------------------------------------------- //
class io_ostream {
public:
    virtual void flush() = 0;
private:
};

// ------------------------------------------------------------------------- //
// io_ostream                                                                //
// ------------------------------------------------------------------------- //
class io_istream {
public:

private:
};


} // namespace gea //

#endif // __GEA_DATA_IO_STREAM_H__ //
