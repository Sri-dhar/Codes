#include <stdio.h>
#include <stdio.h>
#include <math.h>
double o_9976ab29ef2ad4ba0b2e9756d051a995(double o_c4f6455805b3f3f28dbb11f1c6192f5d, double o_fdd068638367869138e45d8bc3607c1d)
{
    double o_3bbbbccb5f2faa84460e9d51c94a3df8 = (0x0000000000000002 + 0x0000000000000201 + 0x0000000000000801 - 0x0000000000000A03);
    double o_0b3942c97441146b9232f0117ac22018 = o_c4f6455805b3f3f28dbb11f1c6192f5d;
    double o_bedba36a5b06d90c187b51137661ecef = (o_3bbbbccb5f2faa84460e9d51c94a3df8 + o_0b3942c97441146b9232f0117ac22018) / (0x0000000000000004 + 0x0000000000000202 + 0x0000000000000802 - 0x0000000000000A06);
    while ((o_0b3942c97441146b9232f0117ac22018 - o_3bbbbccb5f2faa84460e9d51c94a3df8 > 1e-6) & !!(o_0b3942c97441146b9232f0117ac22018 - o_3bbbbccb5f2faa84460e9d51c94a3df8 > 1e-6))
    {
        if ((pow(o_bedba36a5b06d90c187b51137661ecef, o_fdd068638367869138e45d8bc3607c1d) > o_c4f6455805b3f3f28dbb11f1c6192f5d) & !!(pow(o_bedba36a5b06d90c187b51137661ecef, o_fdd068638367869138e45d8bc3607c1d) > o_c4f6455805b3f3f28dbb11f1c6192f5d))
        {
            o_0b3942c97441146b9232f0117ac22018 = o_bedba36a5b06d90c187b51137661ecef;
            o_bedba36a5b06d90c187b51137661ecef = (o_3bbbbccb5f2faa84460e9d51c94a3df8 + o_0b3942c97441146b9232f0117ac22018) / (0x0000000000000004 + 0x0000000000000202 + 0x0000000000000802 - 0x0000000000000A06);
        }
        else
        {
            o_3bbbbccb5f2faa84460e9d51c94a3df8 = o_bedba36a5b06d90c187b51137661ecef;
            o_bedba36a5b06d90c187b51137661ecef = (o_3bbbbccb5f2faa84460e9d51c94a3df8 + o_0b3942c97441146b9232f0117ac22018) / (0x0000000000000004 + 0x0000000000000202 + 0x0000000000000802 - 0x0000000000000A06);
        };
    };
    return o_bedba36a5b06d90c187b51137661ecef;
};
int main()
{
    double o_57eea775627cab68ac7b59ed101755d0;
    printf("\x45"
           "n\164e\x72"
           " \164h\x65"
           " \156u\x6D"
           "b\145r\x20"
           "y\157u\x20"
           "w\141n\x74"
           " \164o\x20"
           "g\145t\x20"
           "t\150e\x20"
           "n\164h\x20"
           "r\157o\x74"
           " \157f\x3A"
           " ");
    scanf("\x25"
          "l\147",
          &o_57eea775627cab68ac7b59ed101755d0);
    printf("\x45"
           "n\164e\x72"
           " \164h\x65"
           " \166a\x6C"
           "u\145 \x6F"
           "f\040n\x20"
           ":\040");
    double o_0296e36c9009d412dc42d61e88cd8122;
    scanf("\x25"
          "l\147",
          &o_0296e36c9009d412dc42d61e88cd8122);
    double o_62c8a206469dcd8a597ca65c4e13ccc8 = o_9976ab29ef2ad4ba0b2e9756d051a995(o_57eea775627cab68ac7b59ed101755d0, o_0296e36c9009d412dc42d61e88cd8122);
    printf("\x74"
           "h\145 \x61"
           "n\163w\x65"
           "r\040i\x73"
           " \072 \x25"
           "l\147",
           o_62c8a206469dcd8a597ca65c4e13ccc8);
};
