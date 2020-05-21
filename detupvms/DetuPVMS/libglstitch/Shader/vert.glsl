attribute vec4 in_position;

varying vec4 uv_position;
varying vec4 uv_position1;


void main(void)
{
	uv_position1 = uv_position = gl_Position = in_position;
}



