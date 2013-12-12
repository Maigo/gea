#ifndef __GEA_STRING_PARSER_H__
#define __GEA_STRING_PARSER_H__

// STL includes
#include <string>

#include <gea/engine/utility/utility.h>

namespace gea {

class Token {
public:


private:
    std::string _str_token;
};


class Tokenizer : public ModeBase<8>, private StateBase {
public:
//    enum Modes { }

    Tokenizer(ModeBase::mode_t mode = ModeBase::EMPTY) {}

private:
    enum States { NORMAL = 0, QUOTE };

    //static const char[] DOMAIN_WHITESPACE = {' ', '\t', '\n'};
    //static const char[] DOMAIN_PARATHESIS;

};

} // namespace gea //

#endif // __GEA_STRING_PARSER_H__ //
