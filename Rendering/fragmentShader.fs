#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 normal;
in vec3 fragPos;
in vec3 lightPosView;

out vec4 fragColor;

uniform vec3 lightColor;
uniform Material material;

void main() {
    // Ambient lighting
    vec3 ambient = material.ambient * lightColor;
    // Diffuse lighting
    vec3 lightDir = normalize(lightPosView - fragPos);
    float diffuseIntensity = max(dot(normal, lightDir), 0.0);
    vec3 diffuse =  material.diffuse * diffuseIntensity * lightColor;
    // Specular lighting
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(-fragPos);
    float specularIntensity = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * specularIntensity * lightColor;
    // Phong lighting
    fragColor = vec4((ambient + diffuse + specular), 1.0f);
}