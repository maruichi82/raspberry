#define GPFSEL4 0x3F200010
#define GPSET1  0x3F200020
#define GPCLR1  0x3F20002C
#define SYST_CLO 0x3F003004

void clear_bss()
{
    extern unsigned int __bss_start;
    extern unsigned int __bss_end;

    unsigned int *start = (unsigned int *)&__bss_start;
    unsigned int *end = (unsigned int *)&__bss_end;

    for (unsigned int *p = start; p < end; p++)
    {
        *p = 0x00;
    }
}

unsigned int get_system_count()
{
    return *(volatile unsigned int *)SYST_CLO;
}

void wait(unsigned int msec)
{
    unsigned int wait_count = msec * 1000;
    unsigned int start = get_system_count(); 
    while (get_system_count() - start < wait_count);
}

int main()
{
    clear_bss();

    *(unsigned int *)GPFSEL4 = 0x01 << (47 - 40) * 3;
    while (1)
    {
        *(volatile unsigned int *)GPCLR1 = 0x01 << 47 - 32;
        wait(500);
        *(volatile unsigned int *)GPSET1 = 0x01 << 47 - 32;
        wait(500);
    }

    return 0;
}