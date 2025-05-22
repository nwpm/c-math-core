#ifndef TRIGNM_H
#define TRIGNM_H

/*Degrees and radians convertion*/
float sml_to_deg(float rad);
float sml_to_rad(float deg);

/*Reduction of angles (-2PI, 2PI)*/
float sml_normalize_angle(float rad);

/*Simple check is angles adjacent*/
/*FLOAT COMPARISON*/
int sml_is_angles_adjacent(float first_angle, float second_angle);

/*Check in what quarter of circle is angle*/
/*int is too large?*/
int sml_find_quadrant(float rad);

#endif
