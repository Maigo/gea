
namespace gea {
namespace regexp {

// ------------------------------------------------------------------------- //
// Node                                                                      //
// ------------------------------------------------------------------------- //
inline Node::Node(char cl, char ch) : _cl(cl), _ch(ch) {
    if (_ch < _cl) _ch = _cl;
}
inline bool Node::test(char c) const {
    return (_cl <= c && c <= _ch);
}

} // namespace regexp //
} // namespace gea //
