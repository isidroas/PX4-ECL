/****************************************************************************
 *
 *   Copyright (c) 2020 Estimation and Control Library (ECL). All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name ECL nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdint.h>

static constexpr float SAMPLING_RES = 10;
static constexpr float SAMPLING_MIN_LAT = -90;
static constexpr float SAMPLING_MAX_LAT = 90;
static constexpr float SAMPLING_MIN_LON = -180;
static constexpr float SAMPLING_MAX_LON = 180;

static constexpr int LAT_DIM = 19;
static constexpr int LON_DIM = 37;


// Magnetic declination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.074,
static constexpr const int16_t declination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ {  26024, 24278, 22533, 20788, 19042, 17297, 15552, 13806, 12061, 10316,  8571,  6825,  5080,  3335,  1589,  -156, -1901, -3646, -5392, -7137, -8882,-10628,-12373,-14118,-15864,-17609,-19354,-21100,-22845,-24590,-26336,-28081,-29827, 31260, 29515, 27769, 26024, },
/* LAT: -80 */ {  22594, 20457, 18513, 16736, 15093, 13553, 12088, 10676,  9300,  7949,  6616,  5297,  3988,  2683,  1376,    58, -1282, -2651, -4058, -5507, -6998, -8532,-10106,-11723,-13384,-15100,-16883,-18752,-20732,-22847,-25119,-27552,-30122, 30068, 27444, 24931, 22594, },
/* LAT: -70 */ {  14964, 13569, 12447, 11490, 10626,  9799,  8960,  8076,  7125,  6107,  5037,  3942,  2855,  1797,   773,  -238, -1273, -2373, -3567, -4860, -6234, -7658, -9101,-10540,-11964,-13378,-14804,-16285,-17900,-19800,-22296,-26060, 30855, 24206, 19629, 16838, 14964, },
/* LAT: -60 */ {   8371,  8135,  7864,  7599,  7354,  7108,  6806,  6379,  5769,  4954,  3956,  2844,  1721,   685,  -205,  -970, -1700, -2516, -3507, -4690, -6008, -7369, -8686, -9896,-10963,-11865,-12583,-13080,-13252,-12802,-10717, -3626,  4744,  7550,  8351,  8494,  8371, },
/* LAT: -50 */ {   5446,  5487,  5438,  5356,  5290,  5259,  5230,  5108,  4771,  4116,  3113,  1844,   499,  -693, -1582, -2164, -2570, -3005, -3671, -4658, -5880, -7146, -8286, -9193, -9802,-10055, -9875, -9132, -7636, -5285, -2386,   359,  2467,  3890,  4764,  5240,  5446, },
/* LAT: -40 */ {   3926,  4021,  4035,  3997,  3944,  3915,  3924,  3918,  3750,  3225,  2215,   781,  -786, -2116, -3002, -3475, -3676, -3744, -3899, -4429, -5370, -6432, -7323, -7876, -8003, -7648, -6777, -5402, -3686, -1974,  -508,   715,  1756,  2616,  3268,  3696,  3926, },
/* LAT: -30 */ {   2959,  3047,  3084,  3078,  3026,  2953,  2898,  2867,  2744,  2277,  1258,  -248, -1859, -3131, -3895, -4261, -4360, -4173, -3744, -3484, -3797, -4525, -5232, -5603, -5500, -4934, -3987, -2778, -1556,  -599,    86,   688,  1307,  1903,  2406,  2763,  2959, },
/* LAT: -20 */ {   2317,  2365,  2390,  2402,  2367,  2279,  2177,  2104,  1960,  1475,   437, -1038, -2522, -3604, -4164, -4304, -4123, -3588, -2735, -1914, -1595, -1920, -2567, -3052, -3107, -2764, -2136, -1315,  -526,   -25,   245,   550,   985,  1454,  1868,  2168,  2317, },
/* LAT: -10 */ {   1923,  1919,  1906,  1913,  1893,  1816,  1713,  1628,  1445,   903,  -143, -1512, -2794, -3648, -3946, -3745, -3187, -2414, -1567,  -800,  -314,  -321,  -777, -1288, -1514, -1435, -1126,  -623,  -116,   135,   193,   357,   721,  1147,  1530,  1809,  1923, },
/* LAT:   0 */ {   1711,  1680,  1632,  1632,  1629,  1568,  1473,  1367,  1115,   500,  -530, -1755, -2823, -3435, -3464, -2987, -2228, -1444,  -784,  -241,   180,   308,    45,  -372,  -635,  -696,  -598,  -332,   -35,    63,    11,   104,   438,   868,  1277,  1587,  1711, },
/* LAT:  10 */ {   1579,  1589,  1554,  1577,  1610,  1569,  1458,  1280,   907,   192,  -825, -1905, -2748, -3112, -2933, -2343, -1570,  -853,  -328,    58,   387,   546,   396,    75,  -165,  -274,  -293,  -207,   -97,  -132,  -263,  -233,    62,   504,   975,  1374,  1579, },
/* LAT:  20 */ {   1404,  1554,  1619,  1717,  1808,  1795,  1650,  1355,   814,   -42, -1087, -2048, -2663, -2794, -2484, -1891, -1182,  -527,   -58,   257,   518,   671,   589,   347,   144,    27,   -58,  -115,  -189,  -373,  -604,  -662,  -434,     4,   537,  1050,  1404, },
/* LAT:  30 */ {   1115,  1483,  1745,  1971,  2134,  2149,  1969,  1552,   827,  -203, -1329, -2221, -2655, -2610, -2221, -1647,  -992,  -371,    99,   411,   646,   798,   785,   638,   486,   363,   214,    13,  -261,  -631,  -998, -1160, -1006,  -586,   -14,   594,  1115, },
/* LAT:  40 */ {    772,  1360,  1854,  2246,  2495,  2541,  2329,  1799,   888,  -346, -1599, -2485, -2822, -2682, -2241, -1651,  -998,  -366,   150,   521,   796,  1001,  1102,  1095,  1018,   873,   614,   216,  -312,  -915, -1438, -1688, -1578, -1165,  -566,   109,   772, },
/* LAT:  50 */ {    498,  1248,  1928,  2482,  2846,  2951,  2721,  2065,   918,  -594, -2038, -2972, -3279, -3093, -2605, -1960, -1249,  -548,    74,   585,  1009,  1371,  1658,  1834,  1857,  1677,  1246,   554,  -328, -1230, -1917, -2213, -2095, -1654, -1013,  -273,   498, },
/* LAT:  60 */ {    327,  1184,  1990,  2680,  3178,  3384,  3162,  2338,   801, -1191, -2937, -3931, -4187, -3925, -3350, -2601, -1771,  -925,  -112,   644,  1342,  1978,  2528,  2931,  3101,  2929,  2311,  1218,  -184, -1508, -2392, -2713, -2551, -2051, -1347,  -533,   327, },
/* LAT:  70 */ {    137,  1081,  1981,  2778,  3386,  3669,  3396,  2216,  -106, -2900, -4875, -5688, -5679, -5179, -4396, -3451, -2418, -1344,  -263,   803,  1834,  2805,  3679,  4394,  4853,  4904,  4324,  2891,   728, -1379, -2693, -3148, -2988, -2448, -1686,  -802,   137, },
/* LAT:  80 */ {   -418,   510,  1370,  2066,  2447,  2230,   913, -1969, -5415, -7544, -8221, -8024, -7346, -6393, -5276, -4058, -2777, -1460,  -127,  1208,  2527,  3812,  5042,  6182,  7178,  7940,  8290,  7875,  6051,  2482, -1017, -2761, -3164, -2858, -2192, -1344,  -418, },
/* LAT:  90 */ { -30388,-28643,-26898,-25152,-23407,-21661,-19916,-18171,-16425,-14680,-12935,-11190, -9444, -7699, -5954, -4209, -2464,  -719,  1027,  2772,  4517,  6262,  8008,  9753, 11498, 13243, 14989, 16734, 18480, 20225, 21971, 23716, 25461, 27207, 28952, 30698,-30388, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.074,
static constexpr const int16_t inclination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ { -12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12580,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581, },
/* LAT: -80 */ { -13668,-13535,-13374,-13194,-12999,-12797,-12593,-12392,-12200,-12023,-11866,-11731,-11621,-11534,-11471,-11430,-11410,-11413,-11441,-11495,-11578,-11692,-11836,-12009,-12206,-12423,-12652,-12885,-13113,-13326,-13513,-13664,-13769,-13821,-13819,-13766,-13668, },
/* LAT: -70 */ { -14118,-13800,-13481,-13157,-12825,-12480,-12124,-11765,-11420,-11110,-10855,-10670,-10556,-10503,-10490,-10495,-10505,-10517,-10542,-10598,-10705,-10878,-11122,-11434,-11804,-12220,-12667,-13131,-13597,-14050,-14469,-14817,-15011,-14961,-14731,-14434,-14118, },
/* LAT: -60 */ { -13526,-13174,-12837,-12504,-12161,-11788,-11372,-10916,-10447,-10014, -9679, -9498, -9491, -9625, -9830,-10027,-10160,-10212,-10205,-10193,-10238,-10392,-10675,-11078,-11572,-12125,-12710,-13306,-13894,-14455,-14952,-15243,-15075,-14694,-14289,-13898,-13526, },
/* LAT: -50 */ { -12499,-12159,-11829,-11508,-11185,-10838,-10438, -9966, -9434, -8909, -8512, -8376, -8567, -9023, -9588,-10107,-10478,-10655,-10639,-10495,-10353,-10351,-10560,-10966,-11501,-12091,-12678,-13219,-13668,-13968,-14077,-14005,-13803,-13520,-13193,-12847,-12499, },
/* LAT: -40 */ { -11240,-10895,-10551,-10207, -9867, -9528, -9166, -8738, -8215, -7646, -7210, -7152, -7595, -8410, -9333,-10170,-10840,-11291,-11452,-11303,-10969,-10689,-10666,-10933,-11387,-11891,-12341,-12670,-12833,-12840,-12749,-12610,-12429,-12197,-11911,-11584,-11240, },
/* LAT: -30 */ {  -9601, -9228, -8854, -8466, -8073, -7695, -7336, -6941, -6426, -5812, -5348, -5406, -6149, -7338, -8591, -9696,-10622,-11347,-11769,-11785,-11431,-10924,-10577,-10562,-10805,-11126,-11388,-11509,-11451,-11275,-11098,-10958,-10808,-10599,-10318, -9974, -9601, },
/* LAT: -20 */ {  -7369, -6939, -6529, -6105, -5660, -5227, -4832, -4412, -3842, -3153, -2689, -2916, -3992, -5588, -7221, -8606, -9690,-10484,-10945,-11003,-10659,-10054, -9491, -9234, -9275, -9435, -9581, -9605, -9437, -9164, -8964, -8869, -8756, -8545, -8228, -7819, -7369, },
/* LAT: -10 */ {  -4411, -3890, -3447, -3015, -2559, -2106, -1687, -1222,  -587,   125,   506,   115, -1176, -3074, -5056, -6690, -7813, -8470, -8755, -8710, -8319, -7648, -6983, -6628, -6582, -6674, -6795, -6824, -6639, -6341, -6178, -6174, -6120, -5897, -5514, -4992, -4411, },
/* LAT:   0 */ {   -901,  -295,   157,   554,   971,  1389,  1785,  2241,  2838,  3427,  3649,  3184,  1922,    34, -2015, -3693, -4735, -5189, -5264, -5106, -4682, -3981, -3276, -2896, -2832, -2905, -3033, -3109, -2981, -2742, -2678, -2803, -2848, -2653, -2230, -1607,  -901, },
/* LAT:  10 */ {   2567,  3176,  3599,  3935,  4288,  4656,  5014,  5413,  5878,  6260,  6312,  5846,  4789,  3241,  1549,   151,  -682,  -953,  -876,  -650,  -251,   376,  1008,  1351,  1413,  1363,  1259,  1167,  1211,  1319,  1253,  1004,   830,   911,  1262,  1857,  2567, },
/* LAT:  20 */ {   5419,  5936,  6308,  6599,  6912,  7256,  7604,  7961,  8305,  8516,  8440,  7993,  7173,  6086,  4958,  4036,  3488,  3351,  3489,  3726,  4049,  4507,  4966,  5223,  5277,  5253,  5202,  5145,  5137,  5124,  4959,  4640,  4355,  4271,  4442,  4859,  5419, },
/* LAT:  30 */ {   7570,  7937,  8251,  8532,  8840,  9189,  9550,  9898, 10183, 10304, 10168,  9756,  9134,  8425,  7761,  7242,  6939,  6886,  7020,  7226,  7468,  7763,  8050,  8224,  8278,  8286,  8285,  8276,  8257,  8180,  7965,  7620,  7273,  7056,  7039,  7231,  7570, },
/* LAT:  40 */ {   9265,  9485,  9740, 10025, 10352, 10715, 11086, 11430, 11688, 11776, 11632, 11276, 10805, 10330,  9930,  9642,  9486,  9475,  9580,  9737,  9909, 10090, 10260, 10385, 10462, 10518, 10570, 10603, 10590, 10485, 10248,  9903,  9539,  9256,  9113,  9124,  9265, },
/* LAT:  50 */ {  10801, 10923, 11125, 11396, 11721, 12077, 12434, 12754, 12980, 13043, 12906, 12609, 12243, 11896, 11618, 11427, 11330, 11322, 11384, 11483, 11594, 11708, 11823, 11938, 12055, 12175, 12286, 12359, 12354, 12234, 11992, 11667, 11328, 11044, 10854, 10774, 10801, },
/* LAT:  60 */ {  12318, 12393, 12546, 12766, 13039, 13342, 13647, 13915, 14093, 14121, 13985, 13734, 13443, 13170, 12947, 12788, 12695, 12660, 12673, 12718, 12784, 12867, 12972, 13102, 13259, 13434, 13598, 13709, 13719, 13604, 13381, 13103, 12824, 12586, 12416, 12325, 12318, },
/* LAT:  70 */ {  13759, 13804, 13903, 14048, 14230, 14436, 14647, 14829, 14933, 14910, 14769, 14565, 14345, 14139, 13965, 13828, 13733, 13677, 13656, 13667, 13708, 13778, 13880, 14015, 14180, 14366, 14550, 14693, 14743, 14674, 14514, 14316, 14121, 13956, 13836, 13770, 13759, },
/* LAT:  80 */ {  15003, 15018, 15058, 15120, 15199, 15287, 15368, 15412, 15389, 15304, 15187, 15060, 14936, 14821, 14720, 14638, 14575, 14534, 14515, 14518, 14543, 14592, 14663, 14754, 14865, 14991, 15126, 15257, 15364, 15410, 15376, 15293, 15199, 15117, 15054, 15015, 15003, },
/* LAT:  90 */ {  15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.074,
static constexpr const int16_t strength_table[19][37] {
//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
/* LAT: -90 */ {  5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, },
/* LAT: -80 */ {  6066, 6004, 5926, 5834, 5732, 5621, 5503, 5382, 5259, 5139, 5025, 4919, 4825, 4745, 4682, 4636, 4612, 4609, 4629, 4675, 4744, 4838, 4951, 5082, 5226, 5375, 5525, 5668, 5799, 5913, 6006, 6075, 6120, 6140, 6137, 6111, 6066, },
/* LAT: -70 */ {  6311, 6179, 6031, 5867, 5690, 5498, 5293, 5078, 4859, 4643, 4440, 4257, 4099, 3967, 3862, 3785, 3737, 3724, 3751, 3826, 3952, 4131, 4358, 4624, 4918, 5225, 5528, 5812, 6062, 6267, 6419, 6515, 6558, 6552, 6503, 6421, 6311, },
/* LAT: -60 */ {  6195, 6005, 5806, 5598, 5381, 5147, 4891, 4612, 4320, 4030, 3761, 3533, 3352, 3216, 3117, 3043, 2993, 2972, 2997, 3086, 3252, 3500, 3824, 4208, 4629, 5062, 5484, 5868, 6194, 6443, 6608, 6688, 6692, 6630, 6518, 6369, 6195, },
/* LAT: -50 */ {  5851, 5623, 5392, 5163, 4932, 4688, 4418, 4115, 3786, 3454, 3151, 2909, 2745, 2653, 2604, 2571, 2539, 2513, 2518, 2588, 2757, 3042, 3434, 3902, 4407, 4913, 5389, 5809, 6149, 6392, 6532, 6575, 6534, 6425, 6265, 6069, 5851, },
/* LAT: -40 */ {  5398, 5154, 4911, 4673, 4439, 4203, 3949, 3665, 3352, 3025, 2725, 2500, 2381, 2353, 2373, 2396, 2403, 2393, 2382, 2409, 2534, 2801, 3212, 3721, 4267, 4793, 5262, 5653, 5947, 6135, 6225, 6229, 6161, 6032, 5852, 5635, 5398, },
/* LAT: -30 */ {  4881, 4642, 4405, 4172, 3947, 3729, 3510, 3279, 3024, 2749, 2491, 2306, 2232, 2255, 2322, 2394, 2462, 2515, 2540, 2553, 2616, 2806, 3158, 3641, 4170, 4670, 5092, 5413, 5618, 5719, 5746, 5720, 5642, 5510, 5332, 5117, 4881, },
/* LAT: -20 */ {  4323, 4112, 3905, 3702, 3506, 3324, 3156, 2993, 2816, 2619, 2428, 2292, 2247, 2287, 2375, 2485, 2614, 2745, 2839, 2878, 2901, 2990, 3221, 3597, 4045, 4473, 4826, 5066, 5174, 5183, 5153, 5106, 5023, 4896, 4730, 4534, 4323, },
/* LAT: -10 */ {  3791, 3632, 3481, 3335, 3200, 3080, 2977, 2887, 2791, 2679, 2557, 2456, 2406, 2425, 2508, 2636, 2792, 2953, 3081, 3147, 3163, 3186, 3302, 3547, 3870, 4192, 4459, 4627, 4665, 4614, 4546, 4482, 4393, 4268, 4120, 3957, 3791, },
/* LAT:   0 */ {  3412, 3321, 3239, 3166, 3112, 3074, 3049, 3032, 3011, 2964, 2886, 2791, 2707, 2671, 2707, 2807, 2940, 3076, 3194, 3272, 3304, 3325, 3396, 3548, 3754, 3967, 4148, 4257, 4266, 4199, 4112, 4019, 3906, 3775, 3642, 3519, 3412, },
/* LAT:  10 */ {  3283, 3253, 3234, 3232, 3257, 3305, 3363, 3419, 3456, 3448, 3380, 3265, 3136, 3037, 3005, 3042, 3122, 3220, 3321, 3407, 3471, 3532, 3618, 3734, 3867, 4003, 4123, 4195, 4199, 4139, 4031, 3888, 3727, 3568, 3433, 3338, 3283, },
/* LAT:  20 */ {  3400, 3405, 3433, 3488, 3582, 3704, 3835, 3954, 4038, 4051, 3978, 3836, 3667, 3523, 3442, 3426, 3459, 3530, 3625, 3722, 3812, 3909, 4019, 4129, 4236, 4346, 4447, 4514, 4526, 4470, 4335, 4134, 3908, 3699, 3537, 3437, 3400, },
/* LAT:  30 */ {  3723, 3733, 3790, 3892, 4037, 4210, 4387, 4545, 4654, 4682, 4609, 4453, 4261, 4092, 3982, 3933, 3934, 3982, 4067, 4163, 4260, 4364, 4479, 4597, 4716, 4840, 4959, 5046, 5075, 5020, 4866, 4628, 4355, 4101, 3902, 3776, 3723, },
/* LAT:  40 */ {  4223, 4224, 4293, 4419, 4589, 4778, 4962, 5120, 5225, 5251, 5182, 5032, 4842, 4664, 4532, 4454, 4425, 4444, 4502, 4580, 4664, 4760, 4875, 5008, 5158, 5319, 5469, 5580, 5622, 5570, 5417, 5180, 4907, 4647, 4437, 4293, 4223, },
/* LAT:  50 */ {  4831, 4829, 4889, 5002, 5151, 5311, 5461, 5582, 5655, 5663, 5598, 5470, 5304, 5138, 4998, 4898, 4841, 4827, 4849, 4898, 4966, 5055, 5173, 5323, 5498, 5682, 5848, 5968, 6015, 5974, 5845, 5649, 5423, 5206, 5026, 4899, 4831, },
/* LAT:  60 */ {  5392, 5384, 5416, 5482, 5570, 5665, 5752, 5816, 5848, 5837, 5781, 5685, 5563, 5433, 5312, 5214, 5146, 5110, 5107, 5134, 5189, 5274, 5391, 5537, 5704, 5873, 6021, 6128, 6174, 6153, 6071, 5944, 5797, 5653, 5530, 5441, 5392, },
/* LAT:  70 */ {  5726, 5709, 5709, 5724, 5747, 5774, 5797, 5810, 5808, 5787, 5746, 5687, 5615, 5538, 5463, 5398, 5349, 5320, 5314, 5333, 5377, 5446, 5537, 5646, 5763, 5878, 5978, 6052, 6093, 6097, 6068, 6014, 5947, 5876, 5812, 5760, 5726, },
/* LAT:  80 */ {  5789, 5772, 5759, 5748, 5738, 5729, 5719, 5707, 5691, 5672, 5649, 5623, 5595, 5567, 5541, 5520, 5506, 5500, 5504, 5519, 5545, 5579, 5622, 5670, 5720, 5768, 5811, 5846, 5871, 5884, 5887, 5880, 5866, 5848, 5828, 5807, 5789, },
/* LAT:  90 */ {  5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, },
};
