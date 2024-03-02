#include <string.h>

struct array_buf {
    int sz
    int cur;
    char buf[0];
}

struct array_buf *array_init(int sz)
{
    struct array_buf *buf = calloc(sizeof(struct array_buf) + sz);
    buf->sz = sz;
    return buf;
}

void array_push(struct array_buf *buf, char *input, int sz)
{
    if (buf->cur + sz > buf->sz)
        sz = buf->sz - cur;
    memcpy(buf->buf + buf->cur, input, sz);
    buf->cur += sz;
}

void array_pop(struct array_buf *buf, char *output, int sz)
{
    if (sz > buf->cur)
        sz = buf->cur
    memcpy(output, buf->buf, sz);
    memmove(buf->buf, buf->buf + sz);
    buf->cur -= sz;
}
