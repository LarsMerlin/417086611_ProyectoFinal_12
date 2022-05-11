// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
//Other libs
#include "stb_image.h"
// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Other Libs
#include "SOIL2/SOIL2.h"


// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

float rot1 = -1.5708;
float rot2 = -3.14159;
// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLuint uniformColor2 = 0;
glm::vec2 offset = glm::vec2(0.0f, 0.0f);

float offsetu = 0.0f;
float offsetv = 0.0f;

int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto final FLLA", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shaders/modelloading.vs", "Shaders/modelloading.frag");
    Shader shader1("Shaders/Modelloading.vs", "Shaders/Mloading.frag");
    Shader Anim3("Shaders/anim3.vs", "Shaders/anim3.frag");

    // Carga de modelos

    Model desk((char*)"Models/MLars/escritoriolars.obj");
    Model espada1((char*)"Models/MLarsEspada/espada1lars.obj");
    Model espada2((char*)"Models/MLarsEspada/espada2lars.obj");
    Model escudo1((char*)"Models/MLarsEscudo/Escudo1.obj");
    Model sofa((char*)"Models/MLarsSofa/sofa.obj");
    Model reloj((char*)"Models/MLarsReloj/reloj.obj");
    Model piso((char*)"Models/MLarsPiso/piso.obj");
    Model pisoint((char*)"Models/MLarsPiso/pisoint.obj");
    Model camino((char*)"Models/MLarsPiso/camino.obj");
    Model chimenea((char*)"Models/MLarsChimenea/chimenea.obj");
    Model cuenco((char*)"Models/MLarsChimenea/cuenco.obj");
    Model flama((char*)"Models/MLarsChimenea/flama.obj");
    Model letras((char*)"Models/MLarsLetras/letras.obj");
    Model Room1((char*)"Models/MLarsCuartoint/Kitroom1.obj");
    Model Room2((char*)"Models/MLarsCuartoint/Kitroom2.obj");
    Model ARoom((char*)"Models/MLarsCuarto/ARoom.obj");
    Model ARoom2((char*)"Models/MLarsCuarto/ARoom2.obj");
    Model ParteB1((char*)"Models/LarsFachada/ParteB1.obj");
    Model ParteB2((char*)"Models/LarsFachada/ParteB2.obj");
    Model ParteA1((char*)"Models/LarsFachada/ParteA1.obj");
    Model ParteA2((char*)"Models/LarsFachada/ParteA2.obj");
    Model ParteP1((char*)"Models/LarsFachada/ParteP1.obj");
    Model ParteP2((char*)"Models/LarsFachada/ParteP2.obj");
    Model ParteP3((char*)"Models/LarsFachada/ParteP3.obj");
    Model ParteS((char*)"Models/LarsFachada/ParteS.obj");
    Model PartePA1((char*)"Models/LarsFachada/PartePA1.obj");
    Model PartePA2((char*)"Models/LarsFachada/PartePA2.obj");
    Model PartePB2((char*)"Models/LarsFachada/PartePB2.obj");
    Model Puerta((char*)"Models/LarsAccesorios/puerta.obj");
    Model Ventana((char*)"Models/LarsAccesorios/ventana.obj");
    Model Cuadro((char*)"Models/LarsAccesorios/cuadro.obj");

    /* Model Piso((char*)"Models/Sea/Sea.obj");*/
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);



    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        offset = glm::vec2(0.0f, 0.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glUniform2fv(glGetUniformLocation(shader.Program, "offset"), 1, glm::value_ptr(offset));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded models
        glm::mat4 model(1);
        model = glm::scale(model, glm::vec3(2.75f, 0.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform2fv(uniformColor2, 1, glm::value_ptr(offset));
        piso.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
        model = glm::scale(model, glm::vec3(0.70f, 1.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-27.25f, 0.1f, 7.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        camino.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(1.535f, 1.0f, 1.6825f));
        model = glm::translate(model, glm::vec3(2.0f, 0.1f, 1.25f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pisoint.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(2.5f, 2.0f, 2.5f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.1f, 2.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        desk.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.5f, 5.75f, -12.0f));
        model = glm::rotate(model, glm::radians(-220.0f), glm::vec3(0.0f, 0.0, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        espada1.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(6.25f, 5.0f, -12.0f));
        model = glm::rotate(model, glm::radians(220.0f), glm::vec3(0.0f, 0.0, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        espada2.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.25f, 5.75f, -11.75f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        escudo1.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(1.25f, 1.5f, 1.0f));
        model = glm::translate(model, glm::vec3(8.0f, 0.0f, -1.0f));
        model = glm::rotate(model, glm::radians(-3.14159f), glm::vec3(0.0f, 1.0, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        sofa.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.1f, -3.25f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        reloj.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.5f, 0.5f, -11.0f));
        model = glm::scale(model, glm::vec3(2.5f, 1.5f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        chimenea.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.5f, 0.5f, -9.6f));
        model = glm::scale(model, glm::vec3(2.4f, 3.0f, 2.4f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuenco.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(6.0f, 8.0f, -12.0f));
        model = scale(model, glm::vec3(0.75f, 0.6f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        letras.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.8f, 0.1f, -0.7f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Room1.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.68f, -0.15f, -0.6f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Room2.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(19.75f, -0.1f, -1.75f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom.Draw(shader);
        glBindVertexArray(0);


        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(9.25f, -0.1f, -1.75f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0, 0.0f));
        model = glm::translate(model, glm::vec3(-0.75f, -0.1f, -7.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0, 0.0f));
        model = glm::translate(model, glm::vec3(13.25f, -0.1f, -7.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
        model = glm::translate(model, glm::vec3(0.55f, -0.1f, 7.65f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
        model = glm::translate(model, glm::vec3(14.55f, -0.1f, 7.65f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.45f, -0.1f, 16.65f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom2.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.45f, -0.1f, 2.65f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom2.Draw(shader);
        glBindVertexArray(0);


        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(24.15f, -0.1f, 16.65f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom2.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(24.15f, -0.1f, 2.65f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom2.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(9.25f, -0.1f, -1.65f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom2.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(19.85f, -0.1f, -1.65f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ARoom2.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-9.5f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ParteB1.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-9.0f, -0.3f, 5.25f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ParteB2.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-8.5f, -1.0f, 8.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ParteA1.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-8.35f, 5.5f, -6.15f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ParteA2.Draw(shader);
        glBindVertexArray(0);


        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.35f, 0.0f, -1.4f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ParteP1.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.35f, 0.0f, -1.4f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ParteP2.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.35f, 0.0f, -1.25f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ParteP3.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.0f, 0.0f, -1.25f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ParteS.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.25f, 0.0f, -1.4f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PartePA1.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.15f, 0.0f, -1.4f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PartePA2.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.15f, 0.0f, -1.25f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PartePB2.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.35f, 0.085f, -1.35f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Puerta.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.25f, 0.2f, -1.65f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Ventana.Draw(shader);
        glBindVertexArray(0);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 1.0f));
        model = glm::translate(model, glm::vec3(0.4f, 1.5f, -13.75f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cuadro.Draw(shader);
        glBindVertexArray(0);



        ////Usando otro Shader 
        //shader1.Use();
        //view = camera.GetViewMatrix();
        //offset = glm::vec2(0.0f, 0.0f);
        //glUniform2fv(glGetUniformLocation(shader.Program, "offset"), 1, glm::value_ptr(offset));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        offsetu += 0.001f;
        offsetv = 0.0f;
        offset = glm::vec2(offsetu, offsetv);
        glUniform2fv(glGetUniformLocation(shader.Program, "offset"), 1, glm::value_ptr(offset));
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.5f, 0.5f, -10.0f));
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        flama.Draw(shader);
        glBindVertexArray(0);





        /*offsetu += 0.0001f;
        offsetv = 0.0f;
        offset = glm::vec2(offsetu, offsetv);
        glUniform2fv(glGetUniformLocation(shader.Program, "offset"), 1, glm::value_ptr(offset));
        model=glm::mat4(1)
        model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Piso.Draw(shader);
        glBindVertexArray(0);*/



        glfwSwapBuffers(window);




    }



    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS) //Presionado
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE) //Soltado
        {
            keys[key] = false;
        }
    }

}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

