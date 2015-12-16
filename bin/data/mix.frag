
uniform sampler2DRect u_tex0;
uniform sampler2DRect u_tex1;
uniform vec2 u_resolution;
uniform vec2 u_tex0Resolution;
uniform int u_mode;
uniform int u_swap;
uniform float u_opacity;
varying vec2 texCoordVarying;

vec4 average(vec4 c){

	float average = (c.r + c.g + c.b) / 3.0;
	vec4 averageColor = vec4(vec3(average), 1.0);
	return averageColor;
}

//https://github.com/jamieowen/glsl-blend
float blendScreen(float base, float blend) {
    return 1.0-((1.0-base)*(1.0-blend));
}

vec3 blendScreen(vec3 base, vec3 blend) {
    return vec3(blendScreen(base.r,blend.r),blendScreen(base.g,blend.g),blendScreen(base.b,blend.b));
}

vec3 blendScreen(vec3 base, vec3 blend, float opacity) {
    return (blendScreen(base, blend) * opacity + blend * (1.0 - opacity));
}

vec3 blendMultiply(vec3 base, vec3 blend) {
    return base*blend;
}

vec3 blendMultiply(vec3 base, vec3 blend, float opacity) {
    return (blendMultiply(base, blend) * opacity + blend * (1.0 - opacity));
}

float blendAdd(float base, float blend) {
    return min(base+blend,1.0);
}

vec3 blendAdd(vec3 base, vec3 blend) {
    return min(base+blend,vec3(1.0));
}

vec3 blendAdd(vec3 base, vec3 blend, float opacity) {
    return (blendAdd(base, blend) * opacity + blend * (1.0 - opacity));
}


void main(){
    
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
   // st *= 2.;
    vec4 color = vec4(1.0);
    
    //texCoordVarying.x += 0.5;

    vec4 color1 = vec4(1.0);
    vec4 color2 = vec4(1.0);

    if  (u_swap == 0){
        color1 = texture2DRect(u_tex1, texCoordVarying);
        color2 = texture2DRect(u_tex0, texCoordVarying);
    }

    if  (u_swap == 1){
        color1 = texture2DRect(u_tex0, texCoordVarying);
        color2 = texture2DRect(u_tex1, texCoordVarying);
    }

    vec3 mixcolor = vec3(1.0);
    if (u_mode == 0){
        mixcolor = blendScreen(color1.rgb, color2.rgb, u_opacity);
    }

    if (u_mode == 1){
        mixcolor = blendMultiply(color1.rgb, color2.rgb, u_opacity);
    }

    if (u_mode == 2){
        mixcolor = blendAdd(color1.rgb, color2.rgb, u_opacity);
    }


    color = vec4(mixcolor.r, mixcolor.g, mixcolor.b, 1.0);
    //color = texture2DRect(u_tex1, texCoordVarying);
   // color = average(color);
    color.a = 1.0;
    

    gl_FragColor = color;
}