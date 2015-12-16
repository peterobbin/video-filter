uniform sampler2DRect tex0;
uniform vec2 u_resolution;
uniform float u_time;
uniform float u_amount;
uniform vec2 u_mouse;
uniform vec2 u_tex0Resolution;
varying vec2 texCoordVarying;
#define PI 3.1415926;

vec4 average(vec4 c){

	float average = (c.r + c.g + c.b) / 3.0;
	vec4 averageColor = vec4(vec3(average), 1.0);
	return averageColor;
}

float random (vec2 st) { 
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))* 
        43758.5453123);
}


float noise (vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) + 
            (c - a)* u.y * (1.0 - u.x) + 
            (d - b) * u.x * u.y;
}

void main(){
    
    vec2 st = texCoordVarying; 
    vec2 storigin = texCoordVarying/ u_tex0Resolution;
    vec2 mouse = u_mouse/ u_tex0Resolution;
    
    vec4 color;

    float pct = 0.0;
    pct = 1. - distance(storigin,mouse + 0.0) * u_amount;
  
     float offset = 0.5 ;
     float angle = noise( storigin  + u_time)*PI ;
     float radius = offset;

     vec2 distort= radius * vec2(cos(angle),sin(angle));

    storigin *= pct ;  
    storigin *=  u_tex0Resolution;
    //st += distort;

    //st += vec2(cos(angle),sin(angle);
    color = texture2DRect(tex0, storigin );
   // color = average(color);
    //color = smoothstep(0.0, 1.0 , color);
    //color.a = 1.0;
    

    gl_FragColor = color;
}




