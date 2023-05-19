#version 330 core

#define MAX_DIR_LIGHTS_SIZE 10
#define MAX_POINT_LIGHTS_SIZE 10
#define MAX_SPOT_LIGHTS_SIZE 10

struct DirLight {
    // global direction of light source (from light source to fragment).
    vec3 direction;
    vec3 color;
};

struct PointLight {
    vec3 position;
    vec3 color;

    vec3 attenuation; // kq, kl, kc
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;

    vec3 attenuation;
    // The cutoff angles represented in cosines 
    // why cosine? bec arccosine is costy to compute.
    float innerCutoff;
    float outerCutoff;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    // sampler2D ambient;
    sampler2D roughness;
    sampler2D emissive;
};

struct LitFrag {
    vec3 diffuse;
    vec3 specular;
    // float ambient;
    float shininess;
};

in Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 normal;
    vec3 worldPos;
    vec3 viewDir;
} frag;

out vec4 frag_color;

uniform int dirLightSize;
uniform int pointLightSize;
uniform int spotLightSize;

uniform DirLight dirLights[MAX_DIR_LIGHTS_SIZE];
uniform PointLight pointLights[MAX_POINT_LIGHTS_SIZE];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS_SIZE];

uniform vec3 ambientLight;
uniform Material material;

// lightDir is from fragment to light source
// lightDir, viewDir and normal are assumed to be normalized
vec3 processLight(vec3 lightColor, vec3 lightDir, LitFrag litFrag) {

    vec3 reflectedDir = reflect(-lightDir, frag.normal);

    float diff = max(dot(frag.normal, lightDir), 0.0);
    float spec = pow(max(dot(frag.viewDir, reflectedDir), 0.0), litFrag.shininess);

    vec3 diffuse = diff * lightColor * litFrag.diffuse;
    vec3 specular = spec * lightColor * litFrag.specular;

    return (diffuse + specular);
}

vec3 calcDirLight(DirLight light, LitFrag litFrag) {

    vec3 lightDir = normalize(-light.direction);
    return processLight(light.color, lightDir, litFrag);
}

vec3 calcPointLight(PointLight light, LitFrag litFrag) {
    
    vec3 lightDir = normalize(light.position - frag.worldPos);
    
    float d = length(light.position - frag.worldPos);
    float attenuation = 1.0 / dot(light.attenuation, vec3(d*d, d, 1.0));

    return attenuation * processLight(light.color, lightDir, litFrag);
    // return processLight(light.color, lightDir, litFrag);
}

vec3 calcSpotLight(SpotLight light, LitFrag litFrag) {

    vec3 lightDir = normalize(light.position - frag.worldPos);
    
    float d = length(light.position - frag.worldPos);
    float attenuation = 1.0 / dot(light.attenuation, vec3(d*d, d, 1.0));

    float theta = dot(normalize(-light.direction), lightDir);
    float epsilon = light.innerCutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

    return intensity * attenuation * processLight(light.color, lightDir, litFrag);
}



void main(){
    
    LitFrag litFrag;

    litFrag.diffuse = vec3(texture(material.diffuse, frag.tex_coord));
    litFrag.specular = vec3(texture(material.specular, frag.tex_coord));
    // float litFrag.ambient = texture(material.ambient, frag.tex_coord).r
    vec3 emissive = vec3(texture(material.emissive, frag.tex_coord));
    float roughness = texture(material.roughness, frag.tex_coord).r;

    litFrag.shininess = 2.0 / pow(clamp(roughness, 0.001, 0.999), 4.0) - 2.0;
    // vec3 ambient = ambientLight * litFrag.diffuse * litFrag.ambient;
    vec3 ambient = ambientLight * litFrag.diffuse;

    vec3 color = emissive + ambient; 

    // Direct lights
    for(int lightIndex = 0; lightIndex < dirLightSize; lightIndex++)
        color += calcDirLight(dirLights[lightIndex], litFrag);
    // Point lights
    for(int lightIndex = 0; lightIndex < pointLightSize; lightIndex++)
        color += calcPointLight(pointLights[lightIndex], litFrag);
    // Spot lights
    for(int lightIndex = 0; lightIndex < spotLightSize; lightIndex++)
        color += calcSpotLight(spotLights[lightIndex], litFrag);

    frag_color = vec4(color, 1.0);
}