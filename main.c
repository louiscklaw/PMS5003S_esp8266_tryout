
/* gcc test.c  -o test.out */

#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

// 42 4D 00 1C 00 0A 00 0E   00 0E 00 0A 00 0E 00 0E
// 07 B6 02 57 00 50 00 05   00 00 00 00 00 00 02 62

// Frame length high 8 bits
// Frame length low 8 bits
// Frame length=2x13+2(data+check bytes)

// Data 1 high 8 bits ……
// Data 1 low 8 bits ……
// Data1 refers to PM1.0 concentration unit μ g/m3（CF=1，standard particle）*

// Data2 high 8 bits ……
// Data2 low 8 bits ……
// Data2 refers to PM2.5 concentration unit μ g/m3（CF=1，standard particle）

// Data3 high 8 bits ……
// Data3 low 8 bits ……
// Data3 refers to PM10 concentration unit μ g/m3（CF=1，standard particle）

// Data4 high 8 bits ……
// Data4 low 8 bits ……
// Data4 refers to PM1.0 concentration unit * μ g/m3（under atmospheric environment）

// Data5 high 8 bits ……
// Data5 low 8 bits ……
// Data 5 refers to PM2.5 concentration unit μ g/m3（under atmospheric environment）

// Data6 high 8 bits …….
// Data6 low 8 bits ……
// Data 6 refers to concentration unit (under atmospheric environment) μ g/m3

// Data7 high 8 bits ……
// Data7 low 8 bits ……
// Data7 indicates the number of particles with diameter beyond 0.3 um in 0.1 L of air.

// Data8 high 8 bits ……
// Data8 low 8 bits ……
// Data 8 indicates the number of particles with diameter beyond 0.5 um in 0.1 L of air.

// Data9 high 8 bits ……
// Data9 low 8 bits
// Data 9 indicates the number of particles with diameter beyond 1.0 um in 0.1 L of air.

// Data10 high 8 bits ……
// Data10 low 8 bits ……
// Data10 indicates the number of particles with diameter beyond 2.5 um in 0.1 L of air.

// Data11 high 8 bits ……
// Data11 low 8 bits ……
// Data11 indicates the number of particles with diameter beyond 5.0 um in 0.1 L of air.

// Data12 high 8 bits ……
// Data12 low 8 bits ……
// Data12 indicates the number of particles with diameter beyond 10 um in 0.1 L of air.

// Data13 high 8 bits ……
// Data13 low 8 bits ……
// Data13 Reserved

// Data and check high 8 bits ……
// Low 8 bits
// Data and check low 8 bits ……
// Check code=Start character1+ Start character2+……..+data13

#define MSG_START_0 0
#define MSG_START_1 1
#define MSG_FRAME_LEN_0 2
#define MSG_FRAME_LEN_1 3

#define PM1_0_CF1_HIGH 4
#define PM1_0_CF1_LOW 5
#define PM2_5_CF1_HIGH 6
#define PM2_5_CF1_LOW 7
#define PM10_CF1_HIGH 8
#define PM10_CF1_LOW 9

#define PM1_0_ATOMSPHERIC_HIGH 10
#define PM1_0_ATOMSPHERIC_LOW 11
#define PM2_5_ATOMSPHERIC_HIGH 12
#define PM2_5_ATOMSPHERIC_LOW 13
#define PM10_ATOMSPHERIC_HIGH 14
#define PM10_ATOMSPHERIC_LOW 15

#define PM0_3_DIA_HIGH 16
#define PM0_3_DIA_LOW 17
#define PM0_5_DIA_HIGH 18
#define PM0_5_DIA_LOW 19
#define PM1_0_DIA_HIGH 20
#define PM1_0_DIA_LOW 21

#define PM2_5_DIA_HIGH 22
#define PM2_5_DIA_LOW 23
#define PM5_0_DIA_HIGH 24
#define PM5_0_DIA_LOW 25
#define PM10_DIA_HIGH 26
#define PM10_DIA_LOW 27

#define RESERVED_0 28
#define RESERVED_1 29

#define MSG_CHECK_0 30
#define MSG_CHECK_1 31


char sample_pms5003_msg[] = {0x42, 0x4D, 0x00, 0x1C, 0x00, 0x0A, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0A, 0x00, 0x0E, 0x00, 0x0E, 0x07, 0xB6, 0x02, 0x57, 0x00, 0x50, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x62};

char sample_pms5003_msg_1[]=  {0x0E, 0x07, 0xB6, 0x02, 0x57, 0x00, 0x50, 0x00, 0x42, 0x4D, 0x00, 0x1C, 0x00, 0x0A, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0A, 0x00, 0x0E, 0x00, 0x0E, 0x07, 0xB6, 0x02, 0x57, 0x00, 0x50, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x62};

char STARTCHAR1=0x42;
char STARTCHAR2=0x4D;

const char *HELLOWORLD = "helloconstant";

int bcdToDecString(char bcd_char)
{
    char dec_string[10];
    int i_output=0;
    sprintf(dec_string, "%d", bcd_char);
    i_output = atoi(dec_string);
}

int getDatafromArray(char msg_input[], int pos)
{
    int i_test = bcdToDecString(msg_input[pos]);
}

int getPM1_0CFFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM1_0_CF1_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM1_0_CF1_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM1.0 concentration （CF=1，standard particle）: %d\n", readings);

    return readings;
}

int getPM2_5CFFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM10_CF1_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM10_CF1_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM2.5 concentration （CF=1，standard particle）: %d\n", readings);

    return readings;
}

int getPM10CFFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM10_CF1_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM10_CF1_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM10 concentration （CF=1，standard particle）: %d\n", readings);

    return readings;
}

int getPM1_0AtomFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM1_0_ATOMSPHERIC_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM1_0_ATOMSPHERIC_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM1.0 concentration （under atmospheric environment）: %d\n", readings);

    return readings;
}

int getPM2_5AtomFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM2_5_ATOMSPHERIC_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM2_5_ATOMSPHERIC_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM2.5 concentration （under atmospheric environment）: %d\n", readings);

    return readings;
}

int getPM10AtomFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM10_ATOMSPHERIC_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM10_ATOMSPHERIC_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM10 concentration （under atmospheric environment）: %d\n", readings);

    return readings;
}

int getPM0_3DiaFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM0_3_DIA_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM0_3_DIA_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM0.3 concentration  diameter (beyond 0.3 um in 0.1 L of air): %d\n", readings);

    return readings;
}

int getPM0_5DiaFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM0_5_DIA_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM0_5_DIA_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM0.5 concentration  diameter (beyond 0.3 um in 0.1 L of air): %d\n", readings);

    return readings;
}

int getPM1_0DiaFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM1_0_DIA_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM1_0_DIA_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM1.0 concentration  diameter (beyond 1.0 um in 0.1 L of air): %d\n", readings);

    return readings;
}

int getPM2_5DiaFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM2_5_DIA_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM2_5_DIA_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM2.5 concentration  diameter (beyond 1.0 um in 0.1 L of air): %d\n", readings);

    return readings;
}

int getPM5_0DiaFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM5_0_DIA_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM5_0_DIA_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM5.0 concentration  diameter (beyond 1.0 um in 0.1 L of air): %d\n", readings);

    return readings;
}

int getPM10DiaFromMsg(char msg_input[])
{
    int upper_8bits = getDatafromArray(msg_input,PM10_DIA_HIGH);
    int lower_8bits = getDatafromArray(msg_input,PM10_DIA_LOW);

    int readings = upper_8bits* 255 + lower_8bits;
    printf("trying to get PM10 concentration  diameter (beyond 1.0 um in 0.1 L of air): %d\n", readings);

    return readings;
}


int getStartCharacterPos(char msg_input[], int msg_len)
{
    int startpos = -1;
    printf("array len %d\n", msg_len);

    for(int i=0;i<msg_len; i++)
    {
        printf("check the pos %d\n", i);
        if (msg_input[i] ==STARTCHAR1)
        {
            if (msg_input[1] == STARTCHAR2)
            {
                printf("msg start at pos %d\n", i);
                startpos = i;
                break;
            }
        }
    }
    return startpos;
}

void parsePMS5003SMessage(char pms5003s_message[], int msg_len)
{
    int start_pos = -1;
    start_pos = getStartCharacterPos(pms5003s_message, msg_len);
    getPM1_0CFFromMsg(pms5003s_message);
    getPM2_5CFFromMsg(pms5003s_message);
    getPM10CFFromMsg(pms5003s_message);

    getPM1_0AtomFromMsg(pms5003s_message);
    getPM2_5AtomFromMsg(pms5003s_message);
    getPM10AtomFromMsg(pms5003s_message);

    getPM0_3DiaFromMsg(pms5003s_message);
    getPM0_5DiaFromMsg(pms5003s_message);
    getPM1_0DiaFromMsg(pms5003s_message);
    getPM2_5DiaFromMsg(pms5003s_message);
    getPM5_0DiaFromMsg(pms5003s_message);
    getPM10DiaFromMsg(pms5003s_message);

}

int main()
{
    // printf() displays the string inside quotation

    printf("%s\n", HELLOWORLD);
    int msg_len = sizeof(sample_pms5003_msg);
    parsePMS5003SMessage(sample_pms5003_msg, msg_len);



    return 0;
}
