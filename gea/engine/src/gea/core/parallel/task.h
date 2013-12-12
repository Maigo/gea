#ifndef __GEA_TASK_H__
#define __GEA_TASK_H__

namespace gea {
namespace prl {

struct task_context {

};

struct task_item_header {
    uintptr_t m_binary;

//    uint16_t m_size_task;
//    uint16_t m_size_dma_list;
//
//    uint16_t m_size_stack;
//    uint16_t m_size_scratch;
//
//    uint8_t m_task_type;
//    uint8_t m_task_id;

    // pad to 16 byte
    uint8_t m_pad[
        16 - sizeof(uintptr_t)];
};

template <int N>
struct task_item : public task_item_header {
    union {
        uint64_t dma_list[N / 8 - sizeof(task_item_header) / 8];
        uint64_t workarea[N / 8 - sizeof(task_item_header) / 8];
    };
};
typedef task_item<16> task_item16;
typedef task_item<32> task_item32;
typedef task_item<64> task_item64;

typedef void (*task_entry_func)(task_item_header *task, task_context *context);

} // namespace prl //
} // namespace gea //

#endif // __GEA_TASK_H__ //
