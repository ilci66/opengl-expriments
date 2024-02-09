# OpenGL Experiments

This project will serve as a deeper look into how OpenGl functions and how to display 3D objects.

This project also serves as an exercise of setting up the structure for a C++ project and OpenGL at the same time. (faire d'une pierre deux coups)

## Notes on colors

We only see the reflected colors in real life by the object. Reflected color is perceived by the eye not the colors absorbed by the object.

The sun light is actually white; in RGB terms (1, 1, 1). When calculating the objects perceived color under a certain light source I just neeed to multiply it with the light source:

```
glm::vec3 lightColor(0.33f, 0.42f, 0.18f);
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
glm::vec3 result = lightColor * toyColor; // = (0.33f, 0.21f, 0.06f);
```
