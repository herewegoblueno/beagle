#version 400 core

in vec3 color;
in vec3 pos; //(object space)
in float timevar;

out vec4 fragColor;

//Not in use at the moment
vec3 rangeLimit(vec3 v){
    v.x = 1.f / (1 + exp(- 0.6 * v.x));
    v.y = 1.f / (1 + exp(- 0.6 * v.y));
    v.z = 1.f / (1 + exp(- 0.6 * v.z));
    return v;
}

//For CrossProductNode
vec3 my_cross(vec3 a, vec3 b){
    vec3 product = cross(a, b);
    product = normalize(product);
    product *= (length(a) + length(b)) / 2.f;
    return product;
}

float rand(vec2 c){
        return fract(sin(dot(c.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

//Credit for the next 3 functions (for perlin noise):
//https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83

float rand(vec2 c){
        return fract(sin(dot(c.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float noise(vec2 p, float freq ){
        float unit = 2/freq;
        vec2 ij = floor(p/unit);
        vec2 xy = mod(p,unit)/unit;
        xy = 0.5 * (1.0 -cos(3.1415 * xy));
        float a = rand((ij+vec2(0.,0.)));
        float b = rand((ij+vec2(1.,0.)));
        float c = rand((ij+vec2(0.,1.)));
        float d = rand((ij+vec2(1.,1.)));
        float x1 = mix(a, b, xy.x);
        float x2 = mix(c, d, xy.x);
        return mix(x1, x2, xy.y);
}

float pNoise(vec2 p, int res){
        float persistance = .5;
        float n = 0.;
        float normK = 0.;
        float f = 4.;
        float amp = 1.;
        int iCount = 0;
        for (int i = 0; i< 50; i++){
                n+=amp*noise(p, f);
                f*=2.;
                normK+=amp;
                amp*=persistance;
                if (iCount == res) break;
                iCount++;
        }
        float nf = n/normK;
        return nf * nf * nf * nf;
}

vec3 perlinNoiseVec3(vec3 v, vec3 f){
    int res = int(length(f) * 5);
    return vec3(pNoise(v.xy, res), pNoise(v.yz, res), pNoise(v.zx, res));
}

void main(){
    //Default value of fragColor
    fragColor = vec4(pos.r - timevar, pos.g + timevar, -timevar + pos.b, 1) / 0.5f;
    fragColor += vec4(color, 1) / 0.5f;
}
