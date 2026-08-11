#ifndef DS1307_H
#define DS1307_H

void RTC_Init(void);

void RTC_SetTime(
    unsigned char hour,
    unsigned char minute,
    unsigned char second
);

void RTC_SetDate(
    unsigned char date,
    unsigned char month,
    unsigned char year
);

void RTC_GetTime(
    unsigned char *hour,
    unsigned char *minute,
    unsigned char *second
);

void RTC_GetDate(
    unsigned char *date,
    unsigned char *month,
    unsigned char *year
);

#endif