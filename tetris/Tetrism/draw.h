#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DRAW_KEY_LEFT   GLFW_KEY_LEFT
#define DRAW_KEY_UP     GLFW_KEY_UP
#define DRAW_KEY_RIGHT  GLFW_KEY_RIGHT
#define DRAW_KEY_DOWN   GLFW_KEY_DOWN
#define DRAW_KEY_ENTER  GLFW_KEY_ENTER
#define DRAW_KEY_SPACE  GLFW_KEY_SPACE
#define DRAW_KEY_ESCAPE GLFW_KEY_ESCAPE


int DRAW_COORD_HEIGHT;
int DRAW_COORD_WIDTH;


GLuint uniColor;
GLuint offset;
GLuint coords;
GLuint stretch;
GLuint shaderProgram;
GLuint vertexShader;
GLuint fragmentShader;
GLuint vbo;
GLuint vao;
GLFWwindow* window;
float verts[] = 
{
	 0.8,  0.8,
	 0.8, -0.8,
	-0.8,  0.8,

	
	 0.8, -0.8,
	-0.8,  0.8,
	-0.8, -0.8,

	 0.8,  0.8,
	 0.8, -0.8,
	-0.8,  0.8,

	
	 0.8, -0.8,
	-0.8,  0.8,
	-0.8, -0.8
};

GLchar* read_shader(const GLchar* source);



void draw_set_coord_size(int a, int b)
{
	DRAW_COORD_WIDTH  = a;
	DRAW_COORD_HEIGHT = b;
}

void draw_swap_buffers()
{
	glfwSwapBuffers(window);
}

void draw_fill_square(int j, int i)
{
	glUniform2f(coords, i, j);
	glUniform2f(stretch, 1.0, 1.0);
	glDrawArrays(GL_TRIANGLES, 6, 12);
}

void draw_wait(int ms)
{
	long startd = 1000*clock()/1000;

	while (!glfwWindowShouldClose(window) && 1000*clock()/1000 - startd < ms)
		glfwPollEvents();
}

void draw_bar(float x1, float y1, float x2, float y2, float scale)
{
	glUniform2f(scale, (x2 - x1)*scale, 1.0);
	glUniform2f(coords,  x1, y1);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_square(int j, int i)
{
	glUniform2f(coords, i, j);
	glUniform2f(stretch, 1.0, 1.0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_square_area(int x1, int y1, int x2, int y2)
{
	/* 
	int i, j;
	for (i = y1; i < y2; i++)
	for (j = x1; j < x2; j++)
	{
		draw_square(i, j);
	}
	/* */
	glUniform2f(stretch, x2 - x1, y2 - y1);
	glUniform2f(coords, x1, y1);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_clear()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void draw_change_color(float r, float g, float b)
{
	glUniform3f(uniColor, r, g, b);
}


int draw_is_pressed(int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

void draw_init(int _width, int _height)
{
	/* */
	verts[0]  = -1.0;
	verts[1]  = 1.0;

	verts[2]  = 1.0/(DRAW_COORD_WIDTH/2.0) - 1.0;
	verts[3]  = 1.0;
	
	verts[4] = 1.0/(DRAW_COORD_WIDTH/2.0) - 1.0;
	verts[5] = 1.0 - 1.0/(DRAW_COORD_HEIGHT/2.0);
	


	verts[6] = 1.0/(DRAW_COORD_WIDTH/2.0) - 1.0;
	verts[7] = 1.0 - 1.0/(DRAW_COORD_HEIGHT/2.0);
	
	verts[8] = -1.0;
	verts[9] = 1.0 - 1.0/(DRAW_COORD_HEIGHT/2.0);

	verts[10] = -1.0;
	verts[11] = 1.0;

	

	verts[12]  = verts[0] + 0.4/DRAW_COORD_WIDTH;
	verts[13]  = verts[1] - 0.4/DRAW_COORD_HEIGHT;

	verts[14]  = verts[2] - 0.4/DRAW_COORD_WIDTH;
	verts[15]  = verts[3] - 0.4/DRAW_COORD_HEIGHT;
	
	verts[16] = verts[4] - 0.4/DRAW_COORD_WIDTH;
	verts[17] = verts[5] + 0.4/DRAW_COORD_HEIGHT;
	


	verts[18] = verts[6] - 0.4/DRAW_COORD_WIDTH;
	verts[19] = verts[7] + 0.4/DRAW_COORD_HEIGHT;
	
	verts[20] = verts[8] + 0.4/DRAW_COORD_WIDTH;
	verts[21] = verts[9] + 0.4/DRAW_COORD_HEIGHT;

	verts[22] = verts[10] + 0.4/DRAW_COORD_WIDTH;
	verts[23] = verts[11] - 0.4/DRAW_COORD_HEIGHT;
	/* */

	if(glfwInit() == -1)
	{
		printf("Error during glfw_Init()\n");
		exit(1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	window = glfwCreateWindow(_width, _height, "Tetrism", NULL, NULL);
	
	if (!window)
	{
		printf("Error during glfwCreateWindow(...)\n");
		exit(2);
	}


	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);


	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	
	GLint status;
	const GLchar* fragmentSource_ = "#version 400\n"
									"uniform vec3 triColor;\n"
									"out vec4 outColor;\n"
									"\n"
									"void main()\n"
									"{\n"
									"	outColor = vec4(triColor, 1.0);\n"
									"}\n"
									"\n";
	//printf(fragmentSource_);
	const GLchar* vertexSource_   = "#version 400\n"
									"in vec2 position;\n"
									"uniform vec2 offset;\n"
									"uniform vec2 coords;\n"
									"uniform vec2 stretch;\n"
									"\n"
									"void main()\n"
									"{\n"
									"	gl_Position = vec4(-1 + (1 + position.x)*stretch.x + coords.x*offset.x, 1 + (-1 + position.y)*stretch.y - coords.y*offset.y, 0.0, 1.0);\n"
									//"	gl_Position = vec4(position.x + coords.x*offset.x, position.y - coords.y*offset.y, 0.0, 1.0);\n"
									"}\n"
									"\n";
	//printf(vertexSource_);
	const GLchar** vertexSource   = &vertexSource_;
	const GLchar** fragmentSource = &fragmentSource_;
	

	GLuint fragmentShader         = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		printf("Error compiling the fragment shader.\n%s\n", buffer);
		exit(4);
	}

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertexSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		printf("Error compiling the vertex shader.\n%s\n", buffer);
		exit(5);
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

	offset   = glGetUniformLocation(shaderProgram, "offset");
	coords   = glGetUniformLocation(shaderProgram, "coords");
	stretch  = glGetUniformLocation(shaderProgram, "stretch");
	uniColor = glGetUniformLocation(shaderProgram, "triColor");

	glUniform2f(offset, 2.0/DRAW_COORD_WIDTH, 2.0/DRAW_COORD_HEIGHT);
}

int draw_should_close()
{
	return glfwWindowShouldClose(window);
}

void draw_poll_events()
{
	glfwPollEvents();
}

void draw_end()
{
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	glfwDestroyWindow(window);
	glfwTerminate();
}
