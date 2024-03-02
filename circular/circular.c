struct circular_buf {
    int sz
    int read;
    int write;
    char buf[0];
};

struct circular_buf *circular_init(int sz)
{
    struct circular_buf *buf = calloc(sizeof(struct array_buf) + sz);

    buf->sz = sz;
    return buf;
}

void array_push(struct array_buf *buf, char *input, int sz)
{
    int i = 0;

    while (buf->write % buf->sz != buf->read) {
        buf[buf->write++] = input[i++];
        buf->write %= buf->sz;
    }
}

void array_pop(struct array_buf *buf, char *output, int sz)
{
    int i = 0;

    while (buf->read != buf->write) {
        buf[buf->read++] = output[i++];
        buf->read %= buf->sz;
    }
}