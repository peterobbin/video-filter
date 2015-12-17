
uniform sampler2DRect tex0;
uniform float u_bwshift;
uniform vec2 u_resolution;
uniform vec2 u_tex0Resolution;
varying vec2 texCoordVarying;

vec4 average(vec4 c){

	float average = (c.r + c.g + c.b) / 3.0;
	vec4 averageColor = vec4(vec3(average), 1.0);
	return averageColor;
}

void main(){
    
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
   // st *= 2.;
    vec4 color;
    
    //texCoordVarying.x += 0.5;
    color = texture2DRect(tex0, texCoordVarying);
    color = average(color);
    color = smoothstep(0.0 + u_bwshift, 1.0 + u_bwshift, color);
    color.a = 1.0;
    

    
    gl_FragColor = color;
}