#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform float mixValue;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;

uniform vec3 viewPos; 

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;

    //˥������
    float constant;
    float linear;
    float quadratic;
};


uniform Material material;
uniform Light light;

void main()
{
    vec3 lightDir = light.position - FragPos;
    //���Դ���ž����˥��
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// ��������
    vec3 ambient = texture(material.diffuse, TexCoord).rgb * light.ambient;
  	
    // ������ 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * texture(material.diffuse, TexCoord).rgb * light.diffuse * attenuation;
    
    // ���淴��
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  //��������
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular,TexCoord).rgb * spec * light.specular * attenuation;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
