// julia.c - Interactive Julia Set in OpenGL 4.0

#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

// Window dimensions (1080p)
const GLuint WIDTH = 1920, HEIGHT = 1080;

// 100 default iterations is good for smooth zooming performance
// 5000 is the limit for beating double precision floating point

// Julia set parameters
double zoom = 1.0;
double offsetX = 0.0;
double offsetY = 0.0;

// Complex constant for the Julia set
double juliaRe = -0.7;
double juliaIm = 0.27015;

// Mouse interaction
int isDragging = 0;
double lastMouseX = 0.0;
double lastMouseY = 0.0;

// Inversion toggle
int invertColors = 0;

// Color mode
int colorMode = 0;

// Max iterations
int maxIterations = 100;

// Vertex shader source code
const GLchar* vertexShaderSource = "#version 400 core\n"
"in vec2 position;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position, 0.0, 1.0);\n"
"}\0";

// Fragment shader source code for Julia set
const GLchar* fragmentShaderSource = "#version 400 core\n"
"out vec4 color;\n"
"uniform vec2 resolution;\n"
"uniform double zoom;\n"
"uniform dvec2 offset;\n"
"uniform dvec2 juliaC;\n"
"uniform int invert;\n"
"uniform int max_iterations;\n"
"uniform int colorMode;\n"
"\n"
"vec3 getColor(float t) {\n"
"    vec3 palette[5] = vec3[](vec3(0.0, 0.0, 0.0),   // Black\n"
"                              vec3(0.1, 0.1, 0.5),  // Blue\n"
"                              vec3(0.3, 0.7, 0.9),  // Cyan\n"
"                              vec3(0.8, 0.9, 0.3),  // Yellow-Green\n"
"                              vec3(1.0, 1.0, 1.0)); // White\n"
"    float scaledT = t * 4.0;\n"
"    int idx1 = int(scaledT);\n"
"    int idx2 = idx1 + 1;\n"
"    float fraction = fract(scaledT);\n"
"    return mix(palette[idx1], palette[min(idx2, 4)], fraction);\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"    dvec2 z = (gl_FragCoord.xy - 0.5 * resolution) / (resolution.y * zoom) + offset;\n"
"    int i;\n"
"    for (i = 0; i < max_iterations; i++) {\n"
"        if (dot(z, z) > 4.0) break;\n"
"        z = dvec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + juliaC;\n"
"    }\n"
"    float t = float(i) / float(max_iterations);\n"
"    if (invert == 1) t = 1.0 - t;\n"
"    vec3 col;\n"
"    if (colorMode == 0) {\n" // Grayscale mode
"        col = vec3(t);\n"
"    } else {\n"              // Escape-time palette mode
"        col = getColor(t);\n"
"    }\n"
"    color = vec4(col, 1.0);\n"
"}\0";

// Callback for scroll input (zooming)
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    double mx = (xpos - WIDTH / 2.0) / (HEIGHT * zoom) + offsetX;
    double my = (HEIGHT / 2.0 - ypos) / (HEIGHT * zoom) + offsetY;

    if (yoffset > 0) zoom *= 1.1;
    else zoom /= 1.1;

    offsetX = mx - (xpos - WIDTH / 2.0) / (HEIGHT * zoom);
    offsetY = my - (HEIGHT / 2.0 - ypos) / (HEIGHT * zoom);
}

// Callback for mouse button input (panning)
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            isDragging = 1;
            glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
        }
        else if (action == GLFW_RELEASE)
        {
            isDragging = 0;
        }
    }
}

// Callback for cursor movement (panning)
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (isDragging)
    {
        double dx = xpos - lastMouseX;
        double dy = ypos - lastMouseY;

        offsetX -= dx / (HEIGHT * zoom);
        offsetY += dy / (HEIGHT * zoom);

        lastMouseX = xpos;
        lastMouseY = ypos;
    }
}

// Callback for key input (invert colors, color modes, adjust iterations and complex number, and quit)
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_C)
        {
            colorMode = !colorMode; // Change color mode
            printf("Color mode: %s\n", colorMode == 0 ? "Grayscale" : "Escape-Time Palette");
        }
        else if (key == GLFW_KEY_I)
        {
            invertColors = !invertColors; // Invert colors
            printf("Inversion mode: %s\n", invertColors ? "Enabled" : "Disabled");
        }
        else if (key == GLFW_KEY_Q)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE); // Quit
        }
        else if (key == GLFW_KEY_COMMA && mods & GLFW_MOD_SHIFT) // Key <
        {
            maxIterations = (maxIterations > 100) ? maxIterations - 100 : 100;
            printf("Max iterations: %d\n", maxIterations);
        }
        else if (key == GLFW_KEY_PERIOD && mods & GLFW_MOD_SHIFT) // Key >
        {
            maxIterations += 100;
            printf("Max iterations: %d\n", maxIterations);
        }
        else if (key == GLFW_KEY_R) // Modify Julia parameter
        {
            juliaRe += 0.01;
            printf("Julia constant (real part) increased to %.5f\n", juliaRe);
        }
        else if (key == GLFW_KEY_F)
        {
            juliaRe -= 0.01;
            printf("Julia constant (real part) decreased to %.5f\n", juliaRe);
        }
        else if (key == GLFW_KEY_T)
        {
            juliaIm += 0.01;
            printf("Julia constant (imaginary part) increased to %.5f\n", juliaIm);
        }
        else if (key == GLFW_KEY_G)
        {
            juliaIm -= 0.01;
            printf("Julia constant (imaginary part) decreased to %.5f\n", juliaIm);
        }
    }
}

int main()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 16); // MSAA 16x is best visually at 1080p

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Interactive Julia Set", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glEnable(GL_MULTISAMPLE);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLfloat vertices[] = {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f
    };
    GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    GLint resLoc = glGetUniformLocation(shaderProgram, "resolution");
    GLint zoomLoc = glGetUniformLocation(shaderProgram, "zoom");
    GLint offsetLoc = glGetUniformLocation(shaderProgram, "offset");
    GLint juliaCLoc = glGetUniformLocation(shaderProgram, "juliaC");
    GLint invertLoc = glGetUniformLocation(shaderProgram, "invert");
    GLint colorModeLoc = glGetUniformLocation(shaderProgram, "colorMode");
    GLint maxIterLoc = glGetUniformLocation(shaderProgram, "max_iterations");

    glfwSwapInterval(0); // Disable VSync with 0 / enable VSync with 1

    double lastTime = glfwGetTime();
    int frameCount = 0;

    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        frameCount++;

        if (deltaTime >= 1.0)
        {
            printf("FPS: %d\n", frameCount);
            frameCount = 0;
            lastTime = currentTime;
        }

        // Render loop
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glUniform2f(resLoc, (float)WIDTH, (float)HEIGHT);
        glUniform1d(zoomLoc, zoom);
        glUniform2d(offsetLoc, offsetX, offsetY);
        glUniform2d(juliaCLoc, juliaRe, juliaIm); // Set Julia constant
        glUniform1i(invertLoc, invertColors);
        glUniform1i(maxIterLoc, maxIterations);
        glUniform1i(colorModeLoc, colorMode);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}
