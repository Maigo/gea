#ifndef __REGEXP_H__
#define __REGEXP_H__

namespace gea {
namespace regexp {

// ------------------------------------------------------------------------- //
// Node                                                                      //
// ------------------------------------------------------------------------- //
class Graph {
public:
    // inline index
    typedef node_ref uint32_t;

    struct Node {
    public:
        inline explicit Node(char cl, char ch = 0);
        inline bool test(char c) const;
    private:
        const node_ref next;
        uint8_t _cl, _ch;
    };

private:
}

class GraphBuilder {};

// ------------------------------------------------------------------------- //
// Predefined Regular Expressions                                            //
// ------------------------------------------------------------------------- //
static const char* REGEXP_FLOAT   = "[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?";
static const char* REGEXP_INTEGER = "[+-][0-9]+";
static const char* REGEXP_
// ------------------------------------------------------------------------- //
// RegExp                                                                    //
// ------------------------------------------------------------------------- //
class RegExp {
public:
    inline RegExp(const char* pattern);

    // evaluation
    bool evaluate(const char* expression) const;
private:
    // internal state
    void construct_graph(const char* pattern);
    Graph _graph;
}

} // namespace regexp //
} // namespace gea //

#include "regexp.inl"

#endif // __REGEXP_H__ //
