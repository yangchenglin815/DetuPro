const int IMG_NUM = 5;
const float M_PI = 3.1415926;

varying vec4 uv_position;
varying vec4 uv_position1;

uniform int has_logo;
uniform int show_mid_line_or_not;
uniform int rotate_or_not;

uniform sampler2D sampler_weight[IMG_NUM - 1];
uniform sampler2D sampler_fisheye[IMG_NUM];

uniform vec2 fisheye_size[IMG_NUM];
uniform float fisheye_size_ratio[IMG_NUM];

uniform float fisheye_a[IMG_NUM];
uniform float fisheye_b[IMG_NUM];
uniform float fisheye_c[IMG_NUM];
//uniform float fisheye_d[IMG_NUM];
//uniform float fisheye_e[IMG_NUM];
uniform float fisheye_radius[IMG_NUM];
uniform vec2 fisheye_center[IMG_NUM];
uniform float fisheye_yaw[IMG_NUM];
uniform float fisheye_pitch[IMG_NUM];
uniform float fisheye_roll[IMG_NUM];
uniform float fisheye_hd[IMG_NUM];
uniform float fisheye_ve[IMG_NUM];
//uniform float fisheye_sg[IMG_NUM];
//uniform float fisheye_st[IMG_NUM];
uniform float fisheye_fov[IMG_NUM];

uniform vec2 transform;

vec3 EquiRect2Sphere(vec2 pos)
{
	float theta = pos.x * M_PI;
	float phi = pos.y * M_PI / 2.0;
	float sin_theta = sin(theta);
	float cos_theta = cos(theta);
	float sin_phi = sin(phi);
	float cos_phi = cos(phi);
	float x = sin_theta * cos_phi;
	float y = cos_theta * cos_phi;
	float z = sin_phi;
	return vec3(x, y, z);
}

vec2 Sphere2EquiRect(vec3 pos)
{
	float phi = asin(pos.z); //(-M_PI_2, M_PI_2)
	float theta = atan(pos.x, pos.y);//(-M_PI, M_PI)
	return vec2(theta / M_PI, phi / M_PI * 2);
}

vec3 SphereRotate(vec3 pos, float radian, vec3 axis)
{
	vec4 pos_4d = vec4(pos.xyz, 0);

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	float sin_theta = sin(radian);
	float cos_theta = cos(radian);
	float m = 1.0 - cos_theta;

	mat4 rotate_matrix;
	rotate_matrix[0][0] = m * x * x + cos_theta;
	rotate_matrix[0][1] = m * x * y + z * sin_theta;
	rotate_matrix[0][2] = m * z * x - y * sin_theta;
	rotate_matrix[0][3] = 0.0;
	rotate_matrix[1][0] = m * x * y - z * sin_theta;
	rotate_matrix[1][1] = m * y * y + cos_theta;
	rotate_matrix[1][2] = m * y * z + x * sin_theta;
	rotate_matrix[1][3] = 0.0;
	rotate_matrix[2][0] = m * z * x + y * sin_theta;
	rotate_matrix[2][1] = m * y * z - x * sin_theta;
	rotate_matrix[2][2] = m * z * z + cos_theta;
	rotate_matrix[2][3] = 0.0;
	rotate_matrix[3][0] = 0.0;
	rotate_matrix[3][1] = 0.0;
	rotate_matrix[3][2] = 0.0;
	rotate_matrix[3][3] = 1.0;

	vec4 pos_after = rotate_matrix * pos_4d;
	return pos_after.xyz;
}

vec3 Sphere2Fisheye(vec3 pos, int index)
{
	vec3 after_pos = pos;

	if (fisheye_yaw[index] != 0.0){
		after_pos = SphereRotate(pos, radians(fisheye_yaw[index]), vec3(0, 0, -1));
	}

	if (fisheye_pitch[index] != 0.0){
		after_pos = SphereRotate(after_pos, radians(fisheye_pitch[index]), vec3(-1, 0, 0));
	}

	
	if (fisheye_roll[index] != 0.0){
		after_pos = SphereRotate(after_pos, radians(fisheye_roll[index]), vec3(0, -1, 0));
	}

	float x = after_pos.x;
	float y = after_pos.y;
	float z = after_pos.z;

	float phi = atan(sqrt(x * x + z * z), y);
	float theta = atan(z, x);
	phi = phi / M_PI * 180.0;

	float radius_ratio = phi / (fisheye_fov[index] / 2.0);

	float distortion_param = fisheye_a[index] * pow(radius_ratio, 4.0) +
		fisheye_b[index] * pow(radius_ratio, 3.0) +
		fisheye_c[index] * pow(radius_ratio, 2.0) +
		(1.0 - fisheye_a[index] - fisheye_b[index] - fisheye_c[index]) * radius_ratio;

	float cur_radius = fisheye_radius[index] * fisheye_size_ratio[index];
	vec2 cur_center = fisheye_center[index] * fisheye_size_ratio[index];
	vec2 cur_size = fisheye_size[index] * fisheye_size_ratio[index];

	float img_dx = (1.0 + distortion_param * cos(theta)) * cur_radius + cur_center.x - cur_radius;
	float img_dy = (1.0 + distortion_param * sin(theta)) * cur_radius + cur_center.y - cur_radius;

	img_dx += fisheye_hd[index] * fisheye_size_ratio[index];
	img_dy += fisheye_ve[index] * fisheye_size_ratio[index];

	return vec3(img_dx, img_dy, phi * 2.0);
}

void main(void)
{
	vec3 color[IMG_NUM];
	float weight[IMG_NUM];
	vec3 pano_color=vec3(0,0,0);
	float weight_total = 0.0;
	bool is_uv_within_logo = false;
	bool is_vertex_on_outer_mid_line = false;
	bool is_vertex_on_inner_mid_line = false;

	if (rotate_or_not==1)
	{
		uv_position1.y = -uv_position.y;
		uv_position1.x = -uv_position.x;
	}
	else
	{
		uv_position1.y = uv_position.y;
		uv_position1.x = uv_position.x;
	}



	if ((uv_position1.x >= -2.0 / 1600.0 && uv_position1.x < 0.0)
		|| (uv_position1.y > -2.0 / 800.0 && uv_position1.y <= -1.0 / 800.0))
	{
		is_vertex_on_outer_mid_line = true;
	}

	if ((uv_position1.x >= 0.0 && uv_position1.x < 2.0 / 1600)
		|| (uv_position1.y > -1.0 / 800.0 && uv_position1.y <= 0.0))
	{
		is_vertex_on_inner_mid_line = true;
	}

	vec2 color_uv = vec2(-uv_position1.x, uv_position1.y); //fisheye mirror
	vec2 weight_uv = uv_position1.xy;

	vec3 original_color_sphere_pos, color_sphere_pos;
	original_color_sphere_pos = color_sphere_pos = EquiRect2Sphere(color_uv);

	vec3 weight_sphere_pos = EquiRect2Sphere(weight_uv);

	//////////////////rotate////////////////////
	if (transform.x != 0.0){
		color_sphere_pos = SphereRotate(color_sphere_pos, radians(-transform.x), vec3(0, 0, -1));
		weight_sphere_pos = SphereRotate(weight_sphere_pos, radians(transform.x), vec3(0, 0, -1));
	}
	if (transform.y != 0.0){
		color_sphere_pos = SphereRotate(color_sphere_pos, radians(-transform.y), vec3(-1, 0, 0));
		weight_sphere_pos = SphereRotate(weight_sphere_pos, radians(-transform.y), vec3(-1, 0, 0));
	}

	weight_uv = Sphere2EquiRect(weight_sphere_pos);

	/////////////normalize weight uv//////////////////
	weight_uv.x = (weight_uv.x + 1.0) / 2.0;
	weight_uv.y = (1.0 - weight_uv.y) / 2.0;

	for (int i = 0; i <IMG_NUM; i++)
	{
		vec3 color_fisheye_pos = Sphere2Fisheye(color_sphere_pos, i);

		if (i == IMG_NUM - 1)
		{
			if (has_logo == 1){
				color_fisheye_pos = Sphere2Fisheye(original_color_sphere_pos, i);
			}
			else{
				continue;
			}
		}

		//////calculate positon fisheye radius///////////////////
		vec2 cur_fisheye_size = fisheye_size[i] * fisheye_size_ratio[i];
		vec2 cur_fisheye_center = fisheye_center[i] * fisheye_size_ratio[i];
		float x_shift = color_fisheye_pos.x - cur_fisheye_center.x;
		float y_shift = color_fisheye_pos.y - cur_fisheye_center.y;
		float cur_radius = sqrt(x_shift * x_shift + y_shift * y_shift);

		///////normalize fisheye position////////////////////////////
		color_fisheye_pos.x = color_fisheye_pos.x / cur_fisheye_size.x;
		color_fisheye_pos.y = color_fisheye_pos.y / cur_fisheye_size.y;

		if (color_fisheye_pos.x < 0.0 || color_fisheye_pos.x > 1.0 ||
			color_fisheye_pos.y < 0.0 || color_fisheye_pos.y > 1.0 ||
			color_fisheye_pos.z > fisheye_fov[i] ||
			cur_radius > fisheye_radius[i] * fisheye_size_ratio[i])
		{
			color[i] = vec3(0, 0, 0);
		}
		else{
			color[i] = texture2D(sampler_fisheye[i], color_fisheye_pos.xy).xyz;
			if (i == IMG_NUM - 1)
			{
				is_uv_within_logo = true;
				if (abs(cur_radius - fisheye_radius[i] * fisheye_size_ratio[i]) <= 2)
				{
					color[i] = vec3(255, 255, 255);
				}
			}			
		}

		if (i == IMG_NUM - 1){
			weight[i] = 0;
		}
		else{
			weight[i] = texture2D(sampler_weight[i], weight_uv).r;
		}		

		pano_color += color[i] * weight[i];
		weight_total += weight[i];
	}

	if (is_uv_within_logo){
		pano_color = color[IMG_NUM - 1];
	}
	else{
		pano_color /= weight_total;
	}
	
	if (is_vertex_on_outer_mid_line && show_mid_line_or_not == 1){
		gl_FragColor = vec4(255, 255, 255, 176.0 / 255.0);
	}
	else if (is_vertex_on_inner_mid_line && show_mid_line_or_not == 1){
		gl_FragColor = vec4(255, 255, 255, 68.0 / 255.0);
	}
	else{
		gl_FragColor = vec4(pano_color, 1);
	}	
}





