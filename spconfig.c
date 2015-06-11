#include <memory.h>
#include <stdio.h>
#include <string.h>

#include <limits.h>
#if (CHAR_BIT != 8)
#error Not supported at this time:  `char' that is not an octet.
#else
typedef unsigned char           u8;
#endif

#define NUM_TASK_TYPES          2
static u8 conf[32];

static const char ask_HLE[] = "Simulate RSP %s from external plugin?";
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
    mask = (u8)(character & 1);
    return (mask);
}

int main(void)
{
    FILE * stream;
    size_t elements_read;
    register int i;

    for (i = 0; i < NUM_TASK_TYPES; i++)
    {
        printf(ask_HLE, MBI_types[i]);
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
        return 1;
    }
    elements_read = fwrite(conf, sizeof(conf), 1, stream);
    fclose(stream);
    if (elements_read != 1)
    {
        fputs("Disk write failed--file reset.\n", stderr);
        return 1;
    }
    return 0;
}
