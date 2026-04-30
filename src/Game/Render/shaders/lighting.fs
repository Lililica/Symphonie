#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add your custom variables here

#define     MAX_LIGHTS              4
#define     LIGHT_DIRECTIONAL       0
#define     LIGHT_POINT             1

struct Light {
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
};

// Input lighting values
uniform Light lights[MAX_LIGHTS];
uniform vec4 ambient;
uniform vec3 viewPos;

vec3 HemisphereLight(vec3 normal)
{
    vec3 skyColor = vec3(0.38, 0.48, 0.65);
    vec3 groundColor = vec3(0.18, 0.14, 0.10);
    float horizon = normal.y * 0.5 + 0.5;
    return mix(groundColor, skyColor, clamp(horizon, 0.0, 1.0));
}

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord);
    vec3 directLight = vec3(0.0);
    vec3 indirectLight = vec3(0.0);
    vec3 normal = normalize(fragNormal);
    vec3 viewD = normalize(viewPos - fragPosition);
    vec3 specular = vec3(0.0);

    vec4 tint = colDiffuse*fragColor;
    vec3 baseColor = texelColor.rgb * tint.rgb;
    float ao = clamp(0.35 + 0.65 * (normal.y * 0.5 + 0.5), 0.35, 1.0);

    // NOTE: Implement here your fragment shader code

    indirectLight += HemisphereLight(normal) * ambient.rgb;

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (lights[i].enabled == 1)
        {
            vec3 light = vec3(0.0);

            if (lights[i].type == LIGHT_DIRECTIONAL)
            {
                light = -normalize(lights[i].target - lights[i].position);
            }

            if (lights[i].type == LIGHT_POINT)
            {
                light = normalize(lights[i].position - fragPosition);
            }

            float NdotL = max(dot(normal, light), 0.0);
            float wrapDiffuse = clamp((NdotL + 0.35) / 1.35, 0.0, 1.0);
            directLight += lights[i].color.rgb * wrapDiffuse;
            indirectLight += lights[i].color.rgb * NdotL * 0.18;

            float specCo = 0.0;
            if (NdotL > 0.0)
            {
                specCo = pow(max(0.0, dot(viewD, reflect(-(light), normal))), 16.0); // 16 refers to shine
            }
            specular += lights[i].color.rgb * specCo * 0.35;
        }
    }

    vec3 lighting = ambient.rgb * 0.2 + directLight + indirectLight;
    vec3 color = baseColor * lighting * ao + specular * texelColor.rgb;

    finalColor = vec4(color, texelColor.a * tint.a);
    finalColor += vec4(texelColor.rgb * tint.rgb * ambient.rgb * 0.08, 0.0);

    finalColor = clamp(finalColor, 0.0, 1.0);

    // Gamma correction
    finalColor = pow(finalColor, vec4(1.0/2.2));
}
