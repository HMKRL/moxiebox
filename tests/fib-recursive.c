#include "sandboxrt.h"
#include "mydef.h"

static moxie_memory_map_ent *data;
static void *input;
static size_t input_length;
static long fib[100];

static void _init()
{
    memset(fib, -1, 100 * sizeof(long));

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

static long fibonacii(int n)
{
    if (!n)
        return n;
    else if (n == 1 || n == 2)
        return 1;
    else if (n < 100) {
        if (fib[n] < 0)
            fib[n] = fibonacii(n - 1) + fibonacii(n - 2);
        return fib[n];
    } else
        return fibonacii(n - 1) + fibonacii(n - 2);
}

int main()
{
    _init();

    int n = *(char *) input;

    if (n < 0)
        abort();

    long res = fibonacii(n);

    void *output = MALLOC(sizeof(res));

    if (output == (void *) -1)
        abort();

    long *p = (long *) output;

    *p = res;

    setreturn(output, sizeof(res));

    return 0;
}
