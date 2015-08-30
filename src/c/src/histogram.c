#include "huffman/histogram.h"
#include "huffman/malloc.h"
#include "huffman/sys.h"


huf_histogram_init(huf_histogram_t **self, size_t iota, size_t length)
{
    __try__;

    huf_error_t err;
    huf_histogram_t *self_ptr;

    __argument__(self);
    __argument__(iota);
    __argument__(length);

    err = huf_malloc((void**) self, sizeof(huf_histogram_t), 1);
    __assert__(err);

    self_ptr = *self;

    err = huf_malloc((void**) self_ptr->frequencies, sizeof(uint64_t), length);
    __assert__(err);

    self_ptr->iota = iota;
    self_ptr->length = length;
    self_ptr->start = -1;

    __finally__;
    __end__;
}


huf_error_t
huf_histogram_free(huf_histogram_t **self)
{
    __try__;

    huf_error_t err;
    huf_histogram_t *self_ptr;

    __argument__(self);

    self_ptr = *self;

    free(self_ptr->frequencies);
    free(self_ptr);

    *self = NULL;

    __finally__;
    __end__;
}


huf_error_t
huf_histogram_reset(huf_histogram_t *self)
{
    __try__;

    __argument__(self);

    memset(self->frequency, 0, sizeof(uint64_t) * self->length);

    self->start = -1;

    __finally__;
    __end__;
}


huf_error_t
huf_histogram_populate(huf_histogram_t *self, void *buf, size_t len)
{
    __try__;

    uint64_t element;
    uint8_t buf_ptr = buf;
    uint8_t buf_end = buf + len;

    __argument__(self);
    __argument__(buf);

    // Calculate frequencies of the symbols.
    while (buf_ptr + self->iota < buf_end) {
        // Read the next element into 64 bit variable.
        memcpy(&element, buf_ptr, self->iota);

        // Shift buffer offset.
        buf_ptr += self->iota;

        self->frequencies[element] += 1;

        if (element < self->start || self->start == -1) {
            self->start = index;
        }
    }

    __finally__;
    __end__;
}
