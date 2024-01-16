# OpenGL Experiments

This project will serve as a deeper look into how OpenGl functions and how to display 3D objects.

This project serves as an exercise of setting up a structure for a C++ project and OpenGL at the same time. (faire d'une pierre deux coups)

## Currently Working On

-- There is no ouput in the app window, Why might it be
Tried fixes:

- Iamge was not being read correctly, now does but did not fix the error

Possible Fixes:

- From [learnopengl](https://learnopengl.com/Getting-started/Textures) copy the code for the textures since the freecodecamp tutorial video does mostly the same.
- Might the problem be cause by the warning when make is ran in the command line :
  `/Users/ilkerakbiyik/Desktop/dev-stuff/opengl-experiments/shaderClass.cpp:63:12: warning: result of comparison against a string literal is unspecified (use an explicit string comparison function instead) [-Wstring-compare]
if (type != "PROGRAM")
       ^  ~~~~~~~~~
  `
- Consider removing scale variable to simplify the app and focus on textures

_Gonna remove all the code for the textures and render a simple triangle with the texture, making sure the code works_

- Don't use any of the modules I created following the tutorial on youtube for this one, turns out I don't really understand their purpose

## TODO Next

Try to finish the exercises on the website before moving on

- An extra challange would be setting different colors for each vertex