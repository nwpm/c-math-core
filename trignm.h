/*Degrees and radians convertion*/
float to_deg(float rad);
float to_deg(float rad);

/*Reduction of angles (-2PI, 2PI)*/
float normalize_angle_signed(float deg);
float normalize_rad_signed(float rad);

/*Simple check is angles adjacent*/
int is_angles_adjacent(float first_angle, float second_angle);

/*Check in what quarter of circle is angle*/
/*int is too large?*/
int find_quadrant_deg(float deg);
int find_quadrant_rad(float rad);

/*Find absolute value of number*/
/*Function must be in other file*/
float absolute_value(float val);
