#include "sandboxrt.h"
#include "mydef.h"

static moxie_memory_map_ent *data;
static void *input;
static size_t input_length;

static void _init()
{
    data = moxie_memmap;

    while (data->addr) {
        if (strstr(data->tags, "data0,")) {
            input = data->addr;
            input_length = data->length;
            return;
        }

        data++;
    }

    abort();
}

int main()
{
    _init();

    int n = *(char *) input;
    long res = 1, pre = -1;

    if (n < 0)
        abort();

    for (int i = 0; i <= n; ++i) {
        long tmp = pre + res;
        pre = res;
        res = tmp;
    }

    void *output = MALLOC(sizeof(res));

    if (output == (void *) -1)
        abort();

    long *p = (long *) output;

    *p = res;

    setreturn(output, sizeof(res));

    return 0;
}
