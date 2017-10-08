#pragma once
#include "allocator_linked.h"

namespace gea {

// ------------------------------------------------------------------------- //
// allocator_linked                                                          //
// ------------------------------------------------------------------------- //
inline linked_allocator::header::header() : next(nullptr), prev(nullptr) {}
inline void linked_allocator::header::link_after(header *h) {
    this->prev = h;
    h->next = this;
}
inline void linked_allocator::header::link_before(header *h) {
    h->prev = this;
    this->next = h;
}
inline void linked_allocator::header::insert_after(header *h) {
    // link outgoing
    this->next = h->next;
    this->prev = h;
    // link incoming
    h->next->prev = this;
    h->next = this;
}
inline void linked_allocator::header::insert_before(header *h) {
    // link outgoing
    this->prev = h->prev;
    this->next = h;
    // link incoming
    h->prev->next = this;
    h->prev = this;
}

inline void linked_allocator::header::remove() const {
    this->prev->next = this->next;
    this->next->prev = this->prev;
}

// ------------------------------------------------------------------------- //

} // namespace gea //
