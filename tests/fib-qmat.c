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

static void mat_mul(long x[][2], long y[][2], long z[][2])
{
    long tmp[2][2] = {{0, 0}, {0, 0}};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j] += x[i][k] * y[k][j];
            }
        }
    }

    memcpy(z, tmp, 4 * sizeof(long));
}

static void mat_pow(long dst[][2], long src[][2], size_t n)
{
    if (n == 1) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                dst[i][j] = src[i][j];
            }
        }
        return;
    }
    if (n % 2 == 0) {
        long tmp[2][2];
        mat_pow(tmp, src, n >> 1);
        mat_mul(tmp, tmp, dst);
        return;
    } else {
        long tmp1[2][2], tmp2[2][2];
        mat_pow(tmp1, src, n >> 1);
        mat_pow(tmp2, src, (n >> 1) + 1);
        mat_mul(tmp1, tmp2, dst);
        return;
    }
}

static long fibonacci(int n)
{
    if (!n)
        return 0;

    long mat[2][2] = {{1, 1}, {1, 0}}, res[2][2];
    mat_pow(res, mat, n);

    return res[0][1];
}

int main()
{
    _init();

    int n = *(char *) input;
    long res = 0;

    if (n < 0)
        abort();

    res = fibonacci(n);

    void *output = MALLOC(sizeof(res));

    if (output == (void *) -1)
        abort();

    long *p = (long *) output;

    *p = res;

    setreturn(output, sizeof(res));

    return 0;
}
