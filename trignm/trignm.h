/*Degrees and radians convertion*/
float sml_to_deg(float rad);
float sml_to_deg(float rad);

/*Reduction of angles (-2PI, 2PI)*/
float sml_normalize_angle_signed(float deg);
float sml_normalize_rad_signed(float rad);

/*Simple check is angles adjacent*/
int sml_is_angles_adjacent(float first_angle, float second_angle);

/*Check in what quarter of circle is angle*/
/*int is too large?*/
int sml_find_quadrant_deg(float deg);
int sml_find_quadrant_rad(float rad);
