#ifndef GPS_H
#define GPS_H

typedef struct
{
    double latitude;
    double longtude;
} geographic_point;

void gps_init(void);

geographic_point get_geographic_point(void);

void get_RMC_string(void);

#endif
