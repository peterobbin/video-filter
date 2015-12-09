//
//#define PI 3.14159265359
//
//uniform sampler2DRect tex0;
//uniform float u_bwshift;
//uniform vec2 u_resolution;
//
//vec4 average(vec4 c){
//
//	float average = (c.r + c.g + c.b) / 3.0;
//	vec4 averageColor = vec4(vec3(average), 1.0);
//	return averageColor;
//}
//
//
//void main () {
//    vec2 st = gl_FragCoord.xy/u_resolution.xy;
//
//    
//    st *= 2.;
//    vec4 color = vec4(st.x,st.y,0.0,1.0);
//    
//
//    color = texture2DRect(tex0,st);
//    color = average(color);
//    color = smoothstep(0.2, 1.0, color);
//
//    gl_FragColor = color;
//}


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
    
    
//    color += 1.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -4.0, 0.0));
//    color += 2.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -3.0, 0.0));
//    color += 3.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -2.0, 0.0));
//    color += 4.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -1.0, 0.0));
//    
//    color += 5.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt, 0));
//    
//    color += 4.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 1.0, 0.0));
//    color += 3.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 2.0, 0.0));
//    color += 2.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 3.0, 0.0));
//    color += 1.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 4.0, 0.0));
    
//    color /= 25.0;
    
    gl_FragColor = color;
}