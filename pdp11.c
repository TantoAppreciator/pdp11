#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MEMSIZE (64 * 1024)
typedef char byte;
typedef unsigned int Length;
typedef short word;
typedef word address;
byte mem[MEMSIZE];
void b_write(address adr, byte val);
byte b_read(address adr);
void w_write(address adr, word val);
word w_read(address adr);
void test_mem();
int main()
{
    test_mem();
    return 0;
}
void test_mem()
{
    address a;
    byte b0, b1, bres;
    word w, wres;

    // пишем байт, читаем байт
    fprintf(stderr, "Пишем и читаем байт по четному адресу\n");
    a = 0;
    b0 = 0x12;
    b_write(a, b0);
    bres = b_read(a);
    // тут полезно написать отладочную печать a, b0, bres
    fprintf(stderr, "a=%06o b0=%hhx bres=%hhx\n", a, b0, bres);
    assert(b0 == bres);
    // аналогично стоит проверить чтение и запись по нечетному адресу

    // пишем слово, читаем слово
    fprintf(stderr, "Пишем и читаем слово\n");
    a = 2; // другой адрес
    w = 0x3456;
    w_write(a, w);
    wres = w_read(a);
    // тут полезно написать отладочную печать a, w, wres
    fprintf(stderr, "a=%06o w=%04x wres=%04x\n", a, w, wres);
    assert(w == wres);

    // пишем 2 байта, читаем 1 слово
    fprintf(stderr, "Пишем 2 байта, читаем слово\n");
    a = 4; // другой адрес
    w = 0xa1b2;
    // little-endian, младшие разряды по меньшему адресу
    b0 = 0xb2;
    b1 = 0xa1;
    b_write(a, b0);
    b_write(a + 1, b1);
    wres = w_read(a);
    // тут полезно написать отладочную печать a, w, wres
    fprintf(stderr, "a=%06o b1=%02hhx b0=%02hhx wres=%04x\n", a, b1, b0, wres);
    assert(w == wres);

    // еще тесты
}
void b_write(address adr, byte val)
{
    mem[adr] = val;
}
byte b_read(address adr)
{
    return mem[adr];
}
void w_write(address adr, word val)
{
}
word w_read(address adr)
{
    byte b1 = mem[adr];
    byte b2 = mem[adr + 1];
    word w = b2;
    w = w << 8;
    w = (0xFF & b1);
    return w;
}