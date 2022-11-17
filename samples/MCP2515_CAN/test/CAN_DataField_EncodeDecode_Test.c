#include <stdio.h>
#include <string.h>

/* CAN Field Data type
    0 - 68 bit (8 bytes)

    https://gregstoll.com/~gregstoll/floattohex/
    https://www.web-dev-qa-db-ja.com/ja/c/float%E3%81%8B%E3%82%89%E3%83%90%E3%82%A4%E3%83%88%E9%85%8D%E5%88%97%E3%81%AB%E5%A4%89%E6%8F%9B%E3%81%99%E3%82%8Bc%E9%96%A2%E6%95%B0/1047028374/
*/
typedef unsigned char ___u64Byte;

void double2Bytes(double double_variable, ___u64Byte  bytes_temp[8]) {
    union {
        double d;
        ___u64Byte bytes[8];
    } thing;
    thing.d = double_variable;
    memcpy(bytes_temp, thing.bytes, 8);
}

int main(void) {
    /* Variables */
    double double_var = 135.355414;
    ___u64Byte bytes_temp[8];

    /* Encode */
    double2Bytes(double_var, bytes_temp);

    printf("\ndouble double_var = %lf", double_var);
    printf("\nfun res = ");
    for (int i = 0; i < 8; i++)
        printf("%02x", bytes_temp[i]);
    printf("\n");



    /* Decode */

    return 0;
}
