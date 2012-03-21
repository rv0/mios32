/* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
// $Id$
/*
 * This file provides tables used by the sound engine
 *
 * ==========================================================================
 *
 *  Copyright (C) 2010 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#include "MbCvTables.h"


const u16 mbCvFrqTable[128] = {
  0x0028,0x002b,0x002d,0x0030,0x0033,0x0036,0x0039,0x003d,0x0040,0x0044,0x0048,0x004c,
  0x0051,0x0056,0x005b,0x0060,0x0066,0x006c,0x0073,0x007a,0x0081,

  0x0089,0x0091,0x0099,0x00a3,0x00ac,0x00b7,0x00c1,0x00cd,0x00d9,0x00e6,0x00f4,0x0102, // c-2
  0x0112,0x0122,0x0133,0x0146,0x0159,0x016e,0x0183,0x019b,0x01b3,0x01cd,0x01e8,0x0205, // c-1
  0x0224,0x0245,0x0267,0x028c,0x02b3,0x02da,0x0307,0x0336,0x0366,0x039a,0x03d1,0x040b, // c-0
  0x0449,0x048a,0x04cf,0x0518,0x0566,0x05b8,0x060f,0x066c,0x06cd,0x0735,0x07a3,0x0817, // C-1
  0x0892,0x0915,0x099f,0x0A31,0x0Acd,0x0B71,0x0C1f,0x0Cd8,0x0D9b,0x0E6a,0x0F46,0x102e, // C-2
  0x1125,0x122a,0x133e,0x1463,0x159a,0x16e3,0x183f,0x19b0,0x1B37,0x1Cd5,0x1E8c,0x205d, // C-3
  0x224a,0x2454,0x267d,0x28c7,0x2B34,0x2Dc6,0x307e,0x3361,0x366f,0x39ab,0x3D19,0x40bc, // C-4
  0x4495,0x48a8,0x4Cfc,0x518f,0x5668,0x5B8c,0x60fe,0x66c2,0x6Cde,0x7357,0x7A34,0x8177, // C-5
  0x892a,0x9153,0x99f6,0xA31e,0xACd1,0xB718,0xC1fc,0xCD85,0xD9bc,0xE6af,0xF467         // C-6
};


const u16 mbCvEnvTable[256] = {
  0xffff, // delay=0.0020
  0xf983, // delay=0.0021
  0xe7e1, // delay=0.0022
  0xcf72, // delay=0.0025
  0xb4c4, // delay=0.0028
  0x9b1c, // delay=0.0033
  0x842b, // delay=0.0039
  0x707f, // delay=0.0046
  0x5fff, // delay=0.0053
  0x524d, // delay=0.0062
  0x46fa, // delay=0.0072
  0x3d99, // delay=0.0083
  0x35cd, // delay=0.0095
  0x2f4a, // delay=0.0108
  0x29d0, // delay=0.0122
  0x252f, // delay=0.0138
  0x213e, // delay=0.0154
  0x1dde, // delay=0.0171
  0x1af5, // delay=0.0190
  0x1870, // delay=0.0209
  0x163e, // delay=0.0230
  0x1451, // delay=0.0252
  0x12a0, // delay=0.0275
  0x1121, // delay=0.0299
  0x0fcc, // delay=0.0324
  0x0e9d, // delay=0.0350
  0x0d8d, // delay=0.0378
  0x0c99, // delay=0.0406
  0x0bbd, // delay=0.0436
  0x0af6, // delay=0.0467
  0x0a42, // delay=0.0499
  0x099d, // delay=0.0532
  0x0908, // delay=0.0567
  0x087f, // delay=0.0603
  0x0801, // delay=0.0640
  0x078d, // delay=0.0678
  0x0723, // delay=0.0717
  0x06c1, // delay=0.0758
  0x0666, // delay=0.0800
  0x0612, // delay=0.0843
  0x05c4, // delay=0.0888
  0x057c, // delay=0.0933
  0x0538, // delay=0.0981
  0x04f9, // delay=0.1029
  0x04be, // delay=0.1079
  0x0487, // delay=0.1130
  0x0453, // delay=0.1183
  0x0423, // delay=0.1237
  0x03f5, // delay=0.1293
  0x03cb, // delay=0.1350
  0x03a2, // delay=0.1408
  0x037c, // delay=0.1468
  0x0358, // delay=0.1530
  0x0336, // delay=0.1593
  0x0316, // delay=0.1657
  0x02f8, // delay=0.1723
  0x02db, // delay=0.1791
  0x02c0, // delay=0.1861
  0x02a6, // delay=0.1932
  0x028d, // delay=0.2004
  0x0276, // delay=0.2079
  0x0260, // delay=0.2155
  0x024b, // delay=0.2233
  0x0236, // delay=0.2312
  0x0223, // delay=0.2394
  0x0211, // delay=0.2477
  0x01ff, // delay=0.2562
  0x01ee, // delay=0.2649
  0x01de, // delay=0.2738
  0x01cf, // delay=0.2829
  0x01c0, // delay=0.2922
  0x01b2, // delay=0.3017
  0x01a4, // delay=0.3114
  0x0197, // delay=0.3213
  0x018b, // delay=0.3314
  0x017f, // delay=0.3418
  0x0174, // delay=0.3523
  0x0168, // delay=0.3631
  0x015e, // delay=0.3741
  0x0154, // delay=0.3854
  0x014a, // delay=0.3969
  0x0140, // delay=0.4086
  0x0137, // delay=0.4206
  0x012e, // delay=0.4328
  0x0126, // delay=0.4453
  0x011e, // delay=0.4580
  0x0116, // delay=0.4710
  0x010e, // delay=0.4843
  0x0107, // delay=0.4978
  0x0100, // delay=0.5117
  0x00f9, // delay=0.5258
  0x00f2, // delay=0.5402
  0x00ec, // delay=0.5549
  0x00e5, // delay=0.5699
  0x00df, // delay=0.5852
  0x00da, // delay=0.6009
  0x00d4, // delay=0.6168
  0x00cf, // delay=0.6331
  0x00c9, // delay=0.6497
  0x00c4, // delay=0.6667
  0x00bf, // delay=0.6840
  0x00ba, // delay=0.7017
  0x00b6, // delay=0.7197
  0x00b1, // delay=0.7381
  0x00ad, // delay=0.7569
  0x00a8, // delay=0.7761
  0x00a4, // delay=0.7957
  0x00a0, // delay=0.8157
  0x009c, // delay=0.8361
  0x0098, // delay=0.8569
  0x0095, // delay=0.8781
  0x0091, // delay=0.8998
  0x008e, // delay=0.9219
  0x008a, // delay=0.9445
  0x0087, // delay=0.9676
  0x0084, // delay=0.9911
  0x0081, // delay=1.0152
  0x007e, // delay=1.0397
  0x007b, // delay=1.0648
  0x0078, // delay=1.0903
  0x0075, // delay=1.1165
  0x0072, // delay=1.1431
  0x006f, // delay=1.1704
  0x006d, // delay=1.1982
  0x006a, // delay=1.2265
  0x0068, // delay=1.2555
  0x0065, // delay=1.2851
  0x0063, // delay=1.3154
  0x0061, // delay=1.3463
  0x005f, // delay=1.3778
  0x005c, // delay=1.4100
  0x005a, // delay=1.4429
  0x0058, // delay=1.4765
  0x0056, // delay=1.5109
  0x0054, // delay=1.5459
  0x0052, // delay=1.5818
  0x0050, // delay=1.6184
  0x004f, // delay=1.6558
  0x004d, // delay=1.6940
  0x004b, // delay=1.7331
  0x0049, // delay=1.7730
  0x0048, // delay=1.8138
  0x0046, // delay=1.8554
  0x0045, // delay=1.8981
  0x0043, // delay=1.9416
  0x0041, // delay=1.9861
  0x0040, // delay=2.0316
  0x003f, // delay=2.0781
  0x003d, // delay=2.1257
  0x003c, // delay=2.1743
  0x003a, // delay=2.2240
  0x0039, // delay=2.2748
  0x0038, // delay=2.3268
  0x0037, // delay=2.3799
  0x0035, // delay=2.4343
  0x0034, // delay=2.4899
  0x0033, // delay=2.5468
  0x0032, // delay=2.6049
  0x0031, // delay=2.6644
  0x0030, // delay=2.7253
  0x002f, // delay=2.7876
  0x002d, // delay=2.8513
  0x002c, // delay=2.9165
  0x002b, // delay=2.9832
  0x002a, // delay=3.0515
  0x0029, // delay=3.1214
  0x0029, // delay=3.1929
  0x0028, // delay=3.2661
  0x0027, // delay=3.3410
  0x0026, // delay=3.4177
  0x0025, // delay=3.4963
  0x0024, // delay=3.5767
  0x0023, // delay=3.6590
  0x0023, // delay=3.7433
  0x0022, // delay=3.8296
  0x0021, // delay=3.9180
  0x0020, // delay=4.0086
  0x001f, // delay=4.1013
  0x001f, // delay=4.1963
  0x001e, // delay=4.2937
  0x001d, // delay=4.3934
  0x001d, // delay=4.4955
  0x001c, // delay=4.6002
  0x001b, // delay=4.7075
  0x001b, // delay=4.8174
  0x001a, // delay=4.9301
  0x0019, // delay=5.0456
  0x0019, // delay=5.1639
  0x0018, // delay=5.2853
  0x0018, // delay=5.4096
  0x0017, // delay=5.5372
  0x0017, // delay=5.6679
  0x0016, // delay=5.8020
  0x0016, // delay=5.9395
  0x0015, // delay=6.0806
  0x0015, // delay=6.2252
  0x0014, // delay=6.3736
  0x0014, // delay=6.5258
  0x0013, // delay=6.6819
  0x0013, // delay=6.8421
  0x0012, // delay=7.0065
  0x0012, // delay=7.1751
  0x0011, // delay=7.3482
  0x0011, // delay=7.5258
  0x0011, // delay=7.7082
  0x0010, // delay=7.8953
  0x0010, // delay=8.0874
  0x000f, // delay=8.2847
  0x000f, // delay=8.4872
  0x000f, // delay=8.6951
  0x000e, // delay=8.9086
  0x000e, // delay=9.1279
  0x000e, // delay=9.3531
  0x000d, // delay=9.5844
  0x000d, // delay=9.8220
  0x000d, // delay=10.0660
  0x000c, // delay=10.3168
  0x000c, // delay=10.5745
  0x000c, // delay=10.8392
  0x000b, // delay=11.1113
  0x000b, // delay=11.3909
  0x000b, // delay=11.6783
  0x000a, // delay=11.9737
  0x000a, // delay=12.2773
  0x000a, // delay=12.5895
  0x000a, // delay=12.9105
  0x0009, // delay=13.2405
  0x0009, // delay=13.5799
  0x0009, // delay=13.9289
  0x0009, // delay=14.2879
  0x0008, // delay=14.6572
  0x0008, // delay=15.0370
  0x0008, // delay=15.4277
  0x0008, // delay=15.8297
  0x0008, // delay=16.2434
  0x0007, // delay=16.6690
  0x0007, // delay=17.1071
  0x0007, // delay=17.5579
  0x0007, // delay=18.0219
  0x0007, // delay=18.4996
  0x0006, // delay=18.9914
  0x0006, // delay=19.4976
  0x0006, // delay=20.0189
  0x0006, // delay=20.5557
  0x0006, // delay=21.1085
  0x0006, // delay=21.6778
  0x0005, // delay=22.2643
  0x0005, // delay=22.8683
  0x0005, // delay=23.4906
  0x0005, // delay=24.1317
  0x0005, // delay=24.7923
  0x0005, // delay=25.4731
  0x0005, // delay=26.1746
  0x0004, // delay=26.8976
  0x0004, // delay=27.6428
  0x0004 // delay=28.4110
};


const u16 mbCvLfoTable[256] = {
     0, //   0:  0.000 Hz
     1, //   1:  0.008 Hz
     3, //   2:  0.023 Hz
     6, //   3:  0.046 Hz
     8, //   4:  0.061 Hz
    10, //   5:  0.076 Hz
    12, //   6:  0.092 Hz
    14, //   7:  0.107 Hz
    16, //   8:  0.122 Hz
    18, //   9:  0.137 Hz
    21, //  10:  0.160 Hz
    23, //  11:  0.175 Hz
    25, //  12:  0.191 Hz
    28, //  13:  0.214 Hz
    30, //  14:  0.229 Hz
    33, //  15:  0.252 Hz
    35, //  16:  0.267 Hz
    38, //  17:  0.290 Hz
    40, //  18:  0.305 Hz
    43, //  19:  0.328 Hz
    45, //  20:  0.343 Hz
    48, //  21:  0.366 Hz
    51, //  22:  0.389 Hz
    54, //  23:  0.412 Hz
    56, //  24:  0.427 Hz
    59, //  25:  0.450 Hz
    62, //  26:  0.473 Hz
    65, //  27:  0.496 Hz
    68, //  28:  0.519 Hz
    71, //  29:  0.542 Hz
    74, //  30:  0.565 Hz
    77, //  31:  0.587 Hz
    80, //  32:  0.610 Hz
    83, //  33:  0.633 Hz
    87, //  34:  0.664 Hz
    90, //  35:  0.687 Hz
    93, //  36:  0.710 Hz
    97, //  37:  0.740 Hz
   100, //  38:  0.763 Hz
   104, //  39:  0.793 Hz
   107, //  40:  0.816 Hz
   111, //  41:  0.847 Hz
   115, //  42:  0.877 Hz
   118, //  43:  0.900 Hz
   122, //  44:  0.931 Hz
   126, //  45:  0.961 Hz
   130, //  46:  0.992 Hz
   134, //  47:  1.022 Hz
   138, //  48:  1.053 Hz
   142, //  49:  1.083 Hz
   146, //  50:  1.114 Hz
   150, //  51:  1.144 Hz
   154, //  52:  1.175 Hz
   159, //  53:  1.213 Hz
   163, //  54:  1.244 Hz
   168, //  55:  1.282 Hz
   172, //  56:  1.312 Hz
   177, //  57:  1.350 Hz
   181, //  58:  1.381 Hz
   186, //  59:  1.419 Hz
   191, //  60:  1.457 Hz
   196, //  61:  1.495 Hz
   201, //  62:  1.534 Hz
   206, //  63:  1.572 Hz
   211, //  64:  1.610 Hz
   216, //  65:  1.648 Hz
   221, //  66:  1.686 Hz
   227, //  67:  1.732 Hz
   232, //  68:  1.770 Hz
   237, //  69:  1.808 Hz
   243, //  70:  1.854 Hz
   249, //  71:  1.900 Hz
   254, //  72:  1.938 Hz
   260, //  73:  1.984 Hz
   266, //  74:  2.029 Hz
   272, //  75:  2.075 Hz
   278, //  76:  2.121 Hz
   284, //  77:  2.167 Hz
   291, //  78:  2.220 Hz
   297, //  79:  2.266 Hz
   304, //  80:  2.319 Hz
   310, //  81:  2.365 Hz
   317, //  82:  2.419 Hz
   324, //  83:  2.472 Hz
   331, //  84:  2.525 Hz
   337, //  85:  2.571 Hz
   345, //  86:  2.632 Hz
   352, //  87:  2.686 Hz
   359, //  88:  2.739 Hz
   367, //  89:  2.800 Hz
   374, //  90:  2.853 Hz
   382, //  91:  2.914 Hz
   389, //  92:  2.968 Hz
   397, //  93:  3.029 Hz
   405, //  94:  3.090 Hz
   413, //  95:  3.151 Hz
   422, //  96:  3.220 Hz
   430, //  97:  3.281 Hz
   438, //  98:  3.342 Hz
   447, //  99:  3.410 Hz
   456, // 100:  3.479 Hz
   465, // 101:  3.548 Hz
   474, // 102:  3.616 Hz
   483, // 103:  3.685 Hz
   492, // 104:  3.754 Hz
   502, // 105:  3.830 Hz
   511, // 106:  3.899 Hz
   521, // 107:  3.975 Hz
   531, // 108:  4.051 Hz
   541, // 109:  4.128 Hz
   551, // 110:  4.204 Hz
   561, // 111:  4.280 Hz
   572, // 112:  4.364 Hz
   582, // 113:  4.440 Hz
   593, // 114:  4.524 Hz
   604, // 115:  4.608 Hz
   615, // 116:  4.692 Hz
   626, // 117:  4.776 Hz
   638, // 118:  4.868 Hz
   650, // 119:  4.959 Hz
   661, // 120:  5.043 Hz
   673, // 121:  5.135 Hz
   686, // 122:  5.234 Hz
   698, // 123:  5.325 Hz
   710, // 124:  5.417 Hz
   723, // 125:  5.516 Hz
   736, // 126:  5.615 Hz
   749, // 127:  5.714 Hz
   762, // 128:  5.814 Hz
   776, // 129:  5.920 Hz
   790, // 130:  6.027 Hz
   804, // 131:  6.134 Hz
   818, // 132:  6.241 Hz
   832, // 133:  6.348 Hz
   847, // 134:  6.462 Hz
   861, // 135:  6.569 Hz
   876, // 136:  6.683 Hz
   892, // 137:  6.805 Hz
   907, // 138:  6.920 Hz
   923, // 139:  7.042 Hz
   939, // 140:  7.164 Hz
   955, // 141:  7.286 Hz
   971, // 142:  7.408 Hz
   988, // 143:  7.538 Hz
  1005, // 144:  7.668 Hz
  1022, // 145:  7.797 Hz
  1040, // 146:  7.935 Hz
  1057, // 147:  8.064 Hz
  1075, // 148:  8.202 Hz
  1093, // 149:  8.339 Hz
  1112, // 150:  8.484 Hz
  1131, // 151:  8.629 Hz
  1150, // 152:  8.774 Hz
  1169, // 153:  8.919 Hz
  1189, // 154:  9.071 Hz
  1209, // 155:  9.224 Hz
  1229, // 156:  9.377 Hz
  1250, // 157:  9.537 Hz
  1271, // 158:  9.697 Hz
  1292, // 159:  9.857 Hz
  1313, // 160: 10.017 Hz
  1335, // 161: 10.185 Hz
  1357, // 162: 10.353 Hz
  1380, // 163: 10.529 Hz
  1403, // 164: 10.704 Hz
  1426, // 165: 10.880 Hz
  1449, // 166: 11.055 Hz
  1473, // 167: 11.238 Hz
  1497, // 168: 11.421 Hz
  1522, // 169: 11.612 Hz
  1547, // 170: 11.803 Hz
  1572, // 171: 11.993 Hz
  1598, // 172: 12.192 Hz
  1624, // 173: 12.390 Hz
  1651, // 174: 12.596 Hz
  1678, // 175: 12.802 Hz
  1705, // 176: 13.008 Hz
  1733, // 177: 13.222 Hz
  1761, // 178: 13.435 Hz
  1790, // 179: 13.657 Hz
  1819, // 180: 13.878 Hz
  1848, // 181: 14.099 Hz
  1878, // 182: 14.328 Hz
  1909, // 183: 14.565 Hz
  1939, // 184: 14.793 Hz
  1971, // 185: 15.038 Hz
  2002, // 186: 15.274 Hz
  2035, // 187: 15.526 Hz
  2067, // 188: 15.770 Hz
  2101, // 189: 16.029 Hz
  2134, // 190: 16.281 Hz
  2169, // 191: 16.548 Hz
  2203, // 192: 16.808 Hz
  2239, // 193: 17.082 Hz
  2274, // 194: 17.349 Hz
  2311, // 195: 17.632 Hz
  2348, // 196: 17.914 Hz
  2385, // 197: 18.196 Hz
  2423, // 198: 18.486 Hz
  2462, // 199: 18.784 Hz
  2501, // 200: 19.081 Hz
  2541, // 201: 19.386 Hz
  2581, // 202: 19.691 Hz
  2622, // 203: 20.004 Hz
  2664, // 204: 20.325 Hz
  2706, // 205: 20.645 Hz
  2749, // 206: 20.973 Hz
  2793, // 207: 21.309 Hz
  2837, // 208: 21.645 Hz
  2882, // 209: 21.988 Hz
  2927, // 210: 22.331 Hz
  2973, // 211: 22.682 Hz
  3020, // 212: 23.041 Hz
  3068, // 213: 23.407 Hz
  3116, // 214: 23.773 Hz
  3165, // 215: 24.147 Hz
  3215, // 216: 24.529 Hz
  3266, // 217: 24.918 Hz
  3317, // 218: 25.307 Hz
  3369, // 219: 25.703 Hz
  3422, // 220: 26.108 Hz
  3476, // 221: 26.520 Hz
  3530, // 222: 26.932 Hz
  3586, // 223: 27.359 Hz
  3642, // 224: 27.786 Hz
  3699, // 225: 28.221 Hz
  3757, // 226: 28.664 Hz
  3816, // 227: 29.114 Hz
  3875, // 228: 29.564 Hz
  3936, // 229: 30.029 Hz
  3997, // 230: 30.495 Hz
  4060, // 231: 30.975 Hz
  4123, // 232: 31.456 Hz
  4187, // 233: 31.944 Hz
  4253, // 234: 32.448 Hz
  4319, // 235: 32.951 Hz
  4386, // 236: 33.463 Hz
  4454, // 237: 33.981 Hz
  4524, // 238: 34.515 Hz
  4594, // 239: 35.049 Hz
  4665, // 240: 35.591 Hz
  4738, // 241: 36.148 Hz
  4812, // 242: 36.713 Hz
  4886, // 243: 37.277 Hz
  4962, // 244: 37.857 Hz
  5039, // 245: 38.445 Hz
  5117, // 246: 39.040 Hz
  5197, // 247: 39.650 Hz
  5277, // 248: 40.260 Hz
  5359, // 249: 40.886 Hz
  5442, // 250: 41.519 Hz
  5526, // 251: 42.160 Hz
  5611, // 252: 42.809 Hz
  5698, // 253: 43.472 Hz
  5786, // 254: 44.144 Hz
  5876  // 255: 44.830 Hz
};


// alternative table for MIDI clock (32 entries selected with rate/8)
// Table taken from Waldorf Blofeld - Thank You guys, I like your synths!!! :-)
const u16 mbCvMclkTable[32] = {
          0, //  0: LFO disabled
    256*4*6, //  1: 16 bars
    224*4*6, //  2: 14 bars
    192*4*6, //  3: 12 bars
    160*4*6, //  4: 10 bars
    136*4*6, //  5: 9 bars
    128*4*6, //  6: 8 bars
    112*4*6, //  7: 7 bars
     96*4*6, //  8: 6 bars
     80*4*6, //  9: 5 bars
     64*4*6, // 10: 4 bars
     56*4*6, // 11: 3.5 bars
     48*4*6, // 12: 3 bars
     40*4*6, // 13: 2.5 bars
     32*4*6, // 14: 2 bars
     24*4*6, // 15: 1.5 bars
     16*4*6, // 16: 1 bar
      8*4*9, // 17: 1/2.
     16*4*4, // 18: 1/1T
      8*4*6, // 19: 1/2
      4*4*9, // 20: 1/4.
      8*4*4, // 21: 1/2T
      4*4*6, // 22: 1/4
      2*4*9, // 23: 1/8.
      4*4*4, // 24: 1/4T
      2*4*6, // 25: 1/8
      1*4*9, // 26: 1/16.
      2*4*4, // 27: 1/8T
      1*4*6, // 28: 1/16
      1*2*9, // 29: 1/32.
      1*4*4, // 30: 1/16T
      1*2*6, // 31: 1/32
};

	
const u16 mbCvSinTable[128] = {
  0x0000,
  0x0192,
  0x0324,
  0x04b6,
  0x0647,
  0x07d9,
  0x096a,
  0x0afb,
  0x0c8b,
  0x0e1b,
  0x0fab,
  0x1139,
  0x12c8,
  0x1455,
  0x15e2,
  0x176d,
  0x18f8,
  0x1a82,
  0x1c0b,
  0x1d93,
  0x1f19,
  0x209f,
  0x2223,
  0x23a6,
  0x2528,
  0x26a8,
  0x2826,
  0x29a3,
  0x2b1f,
  0x2c98,
  0x2e11,
  0x2f87,
  0x30fb,
  0x326e,
  0x33de,
  0x354d,
  0x36ba,
  0x3824,
  0x398c,
  0x3af2,
  0x3c56,
  0x3db8,
  0x3f17,
  0x4073,
  0x41ce,
  0x4325,
  0x447a,
  0x45cd,
  0x471c,
  0x4869,
  0x49b4,
  0x4afb,
  0x4c3f,
  0x4d81,
  0x4ebf,
  0x4ffb,
  0x5133,
  0x5269,
  0x539b,
  0x54ca,
  0x55f5,
  0x571d,
  0x5842,
  0x5964,
  0x5a82,
  0x5b9d,
  0x5cb4,
  0x5dc7,
  0x5ed7,
  0x5fe3,
  0x60ec,
  0x61f1,
  0x62f2,
  0x63ef,
  0x64e8,
  0x65dd,
  0x66cf,
  0x67bd,
  0x68a6,
  0x698c,
  0x6a6d,
  0x6b4a,
  0x6c24,
  0x6cf9,
  0x6dca,
  0x6e96,
  0x6f5f,
  0x7023,
  0x70e2,
  0x719e,
  0x7255,
  0x7307,
  0x73b5,
  0x745f,
  0x7504,
  0x75a5,
  0x7641,
  0x76d9,
  0x776c,
  0x77fa,
  0x7884,
  0x7909,
  0x798a,
  0x7a05,
  0x7a7d,
  0x7aef,
  0x7b5d,
  0x7bc5,
  0x7c29,
  0x7c89,
  0x7ce3,
  0x7d39,
  0x7d8a,
  0x7dd6,
  0x7e1d,
  0x7e5f,
  0x7e9d,
  0x7ed5,
  0x7f09,
  0x7f38,
  0x7f62,
  0x7f87,
  0x7fa7,
  0x7fc2,
  0x7fd8,
  0x7fe9,
  0x7ff6,
  0x7ffd
};


const u8 mbCvPatchPresetBassline[512] = {
  'B','a','s','s','l','i','n','e',' ','P','a','t','c','h',' ',' ',

  // remaining content; TODO...
};
