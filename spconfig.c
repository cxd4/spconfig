#include <memory.h>
#include <stdio.h>
#include <string.h>

/*
 * Since we are bypassing the conventional C startup code for the entry point
 * `main`, we cannot any longer safely approach the normal `return 0;` method
 * of exiting main() as a proper function.  We require exit() or _exit() to
 * guarantee proper C termination--exit() from <stdlib.h> is a safer bet.
 */
#include <stdlib.h>

#include <limits.h>
#if (CHAR_BIT == 8) & (UCHAR_MAX == 255)
typedef unsigned char           u8;
#else
#error Not supported at this time:  `char` that is not an octet.
#endif

#define NUM_TASK_TYPES          2
static u8 conf[32];

static const char* MBI_types[] = {
    "graphics",
    "audio",
#if (NUM_TASK_TYPES > 2)
    "video",
    "JPEG",
    "HVQM",
#endif
};

#include <assert.h>
static u8 read_bit(void)
{
    u8 mask;
    unsigned int bits;
    int character;

    puts("  0, No; 1, Yes");
    do {
        character = getchar();
    } while (character == '\n');
    assert(character >= 0);
    bits = (unsigned int)character;
    mask = (u8)(bits & 1);
    return (mask);
}

int main(void)
{
    FILE * stream;
    size_t elements_read;
    register int i;

    for (i = 0; i < NUM_TASK_TYPES; i++)
    {
        printf("Simulate RSP %s from external plugin?", MBI_types[i]);
        conf[i] = read_bit();
    }

    if (conf[0] | conf[1])
        { /* branch */ }
    else
    {
        printf("Force semaphore locking (won't work on some emulators)?");
        if (read_bit())
            memset(&conf[16], 0xFF, 8 * sizeof(u8));
    }

    stream = fopen("rsp_conf.bin", "wb");
    if (stream == NULL)
    {
        fputs("File write permission failure.\n", stderr);
        exit(EXIT_FAILURE);
    }
    elements_read = fwrite(conf, sizeof(conf), 1, stream);
    fclose(stream);
    if (elements_read != 1)
    {
        fputs("Disk write failed--file reset.\n", stderr);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
