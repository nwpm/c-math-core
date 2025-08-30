#ifndef CM_CIRCLE_H
#define CM_CIRCLE_H

#define PI 3.14159265

int cm_on_circle(double x, double y, double r, double px1, double px2);

inline double cm_circumference(double r) { return 2 * PI * r; }
inline double cm_circle_area(double r) { return PI * r * r; }

#endif
