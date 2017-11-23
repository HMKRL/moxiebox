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

static long fibonacii(int n, long a, long b)
{
    if (!n)
        return a;
    else if (n == 1)
        return b;
    else if (n < 100) {
        if (fib[n] < 0)
            fib[n] = fibonacii(n - 1, b, a + b);
        return fib[n];
    } else
        return fibonacii(n - 1, b, a + b);
}

int main()
{
    _init();

    int n = *(char *) input;

    if (n < 0)
        abort();

    long res = fibonacii(n, 0, 1);

    void *output = MALLOC(sizeof(res));

    if (output == (void *) -1)
        abort();

    long *p = (long *) output;

    *p = res;

    setreturn(output, sizeof(res));

    return 0;
}
