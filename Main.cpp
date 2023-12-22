#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSrc = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSrc = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"FragColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
"}\0";

int main() {
	glfwInit();

	// Telling glfw which version of openGL to use. (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// The 3 lines are the positions of the vertices of the object we're rendering out.
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

	GLFWwindow* window = glfwCreateWindow(400, 400, "Game", NULL, NULL);

	// Error handling for no window being created.
	if (window == NULL) {
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Creates window.

	gladLoadGL(); // Loads openGL configs

	glViewport(0, 0, 400, 400); // setting window viewport or size

	// creating and referencing shaders 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	// initializing the shader program for attachment.
	GLuint shaderProgram = glCreateProgram();

	// attaching VS & FS together then linking afterwards.
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Deleting shaders since no longer needed.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Binding to buffer to send as one giant package
	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO); // Generate VAO before VBO. Order matters
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// (Position of vertex attrib, # of floats, value types, (only if coords are int), amount of data between each vertice, pointer where array begins)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// order matters here as well for unbinding VAO & VBO.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	
	

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		glfwPollEvents(); // Processes events of window, prevents error (draging, moving, rescaling etc.)
	}

	glfwTerminate();
	return 0;
}