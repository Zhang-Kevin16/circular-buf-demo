#define _GNU_SOURCE
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define PAGE_SIZE 4096
#define ROUND_UP(N, S) ((((N) + (S) - 1) / (S)) * (S))

struct mirror_buf {
    int sz;
    int cur;
    char *buf;
};

struct mirror_buf *mirror_init(int sz)
{
    void *page1;
    void *page2;
    int fd = memfd_create("test", 0);
    struct mirror_buf *buf = malloc(sizeof(*buf));
    
    sz = ROUND_UP(sz, 4096);
    ftruncate(fd, sz);
    page1 = mmap(NULL, sz * 2, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    page2 = page1 + sz;
    munmap(page1, sz * 2);
    page1 = mmap(page1, sz, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0);
    page2 = mmap(page2, sz, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0);
    printf("%p %p\n", page1, page2);
    buf->sz = sz;
    buf->cur = 0;
    buf->buf = page1;
    return buf;
}

void mirror_push(struct mirror_buf *buf, char *input, int sz)
{
    sz = sz > buf->sz ? buf->sz : sz;

    memcpy(buf->buf + buf->cur, input, sz);
    buf->cur = (buf->cur + sz) % buf->sz;
}

void mirror_pop(struct mirror_buf *buf, char *output, int sz)
{
    sz = sz > buf->sz ? buf->sz : sz;

    memcpy(output, buf->buf + buf->cur, sz);
    buf->cur = (buf->cur + sz) % buf->sz;
}

char *mirror_cont_buf(struct mirror_buf *buf, int sz)
{
    return buf->buf + buf->cur;
}

int main()
{
    struct mirror_buf *buf = mirror_init(4096);

    sprintf(buf->buf, "%s", "hello world");
    printf("%s\n", buf->buf + 4096);
    return 0;
}