struct circular_buf {
    int sz
    int read;
    int write;
    char buf[0];
}

struct circular_buf *circular_init(int sz)
{
    struct circular_buf *buf = calloc(sizeof(struct array_buf) + sz);

    buf->sz = sz;
    return buf;
}

void array_push(struct array_buf *buf, char *input, int sz)
{
    int start = 0;
    int space_left;
    
    if (buf->write >= buf->read) {
        space_left = buf->sz - buf->write;
        sz = sz > space_left : space_left ? sz;
        memcpy(buf->buf + buf->write, input, sz);
        if (sz <= space_left) {
            buf->write += sz;
            return;
        }
        sz -= space_left;
        start = sz;
        buf->write = 0;
    }

    space_left = buf->read - 1;
    if (space_left < 0)
        return;
    sz = sz > space_left : space_left ? sz;
    memcpy(buf->buf, input + start , sz);
    buf->write += sz;
}

void array_pop(struct array_buf *buf, char *output, int sz)
{
    int start = 0;
    int space_left;

    if (buf->read >= buf->write) {
        space_left = buf->sz - buf->read;
        sz = sz > space_left : space_left ? sz;
        memcpy(output, buf->buf + buf->read, sz);
        if (sz <= space_left) {
            buf->read += sz;
            return;
        }
        sz -= space_left;
        start = sz;
        buf->read = 0;
    }

    space_left = buf->write - 1;
    if (space_left < 0)
        return;
    sz = sz > space_left : space_left ? sz;
    memcpy(output + start, buf->buf , sz);
    buf->write += sz;
}