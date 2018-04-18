#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DRAW1_KEY_LEFT   GLFW_KEY_LEFT
#define DRAW1_KEY_UP     GLFW_KEY_UP
#define DRAW1_KEY_RIGHT  GLFW_KEY_RIGHT
#define DRAW1_KEY_DOWN   GLFW_KEY_DOWN
#define DRAW1_KEY_ENTER  GLFW_KEY_ENTER
#define DRAW1_KEY_SPACE  GLFW_KEY_SPACE
#define DRAW1_KEY_ESCAPE GLFW_KEY_ESCAPE


int DRAW1_COORD_HEIGHT;
int DRAW1_COORD_WIDTH;


GLuint uniColor;
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
	-0.8, -0.8
};

GLchar* read_shader(const GLchar* source);



void draw_set_coord_size(int a, int b)
{
	DRAW1_COORD_WIDTH  = a;
	DRAW1_COORD_HEIGHT = b;
}

void draw_swap_buffers()
{
	glfwSwapBuffers(window);
}

void draw_fill_square(int j, int i)
{
	verts[0]  = i/(DRAW1_COORD_WIDTH/2.0) - 1 + 0.3/DRAW1_COORD_WIDTH;
	verts[1]  = 1 - j/(DRAW1_COORD_HEIGHT/2.0) - 0.3/DRAW1_COORD_HEIGHT;

	verts[2]  = (i + 1)/(DRAW1_COORD_WIDTH/2.0) - 1 - 0.3/DRAW1_COORD_WIDTH;
	verts[3]  = 1 - j/(DRAW1_COORD_HEIGHT/2.0) - 0.3/DRAW1_COORD_HEIGHT;
	
	verts[4] = (i + 1)/(DRAW1_COORD_WIDTH/2.0) - 1 - 0.3/DRAW1_COORD_WIDTH;
	verts[5] = 1 - (j + 1)/(DRAW1_COORD_HEIGHT/2.0) + 0.3/DRAW1_COORD_HEIGHT;
	


	verts[6] = (i + 1)/(DRAW1_COORD_WIDTH/2.0) - 1 - 0.3/DRAW1_COORD_WIDTH;
	verts[7] = 1 - (j + 1)/(DRAW1_COORD_HEIGHT/2.0) + 0.3/DRAW1_COORD_HEIGHT;
	
	verts[8] = i/(DRAW1_COORD_WIDTH/2.0) - 1 + 0.3/DRAW1_COORD_WIDTH;
	verts[9] = 1 - (j + 1)/(DRAW1_COORD_HEIGHT/2.0) + 0.3/DRAW1_COORD_HEIGHT;

	verts[10] = i/(DRAW1_COORD_WIDTH/2.0) - 1 + 0.3/DRAW1_COORD_WIDTH;
	verts[11] = 1 - j/(DRAW1_COORD_HEIGHT/2.0) - 0.3/DRAW1_COORD_HEIGHT;
	
	
	
	//verts[0]  = (verts[0]*2 + verts[5])/3;
	//verts[1]  = (verts[1]*2 + verts[11])/3;

	//verts[5]  = (verts[5]*2 + verts[0])/3;
	//verts[6]  = (verts[6]*2 + verts[11])/3;

	//
	//verts[10] = (verts[10]*2 + verts[0])/3;
	//verts[11] = (verts[11]*2 + verts[1])/3;
	


	//verts[15] = (verts[15]*2 + verts[0])/3;
	//verts[16] = (verts[16]*2 + verts[1])/3;
	
	//verts[20] = (verts[20]*2 + verts[5])/3;
	//verts[21] = (verts[21]*2 + verts[1])/3;

	//verts[25] = (verts[25]*2 + verts[10])/3;
	//verts[26] = (verts[26]*2 + verts[11])/3;


	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 6);

}


void draw_wait(int ms)
{
	long startd = 1000*clock()/1000;

	while (1000*clock()/1000 - startd < ms)
		glfwPollEvents();
}

void draw_square(int j, int i)
{
	verts[0]  = i/(DRAW1_COORD_WIDTH/2.0) - 1;
	verts[1]  = 1 - j/(DRAW1_COORD_HEIGHT/2.0);

	verts[2]  = (i + 1)/(DRAW1_COORD_WIDTH/2.0) - 1;
	verts[3]  = 1 - j/(DRAW1_COORD_HEIGHT/2.0);
	
	verts[4] = (i + 1)/(DRAW1_COORD_WIDTH/2.0) - 1;
	verts[5] = 1 - (j + 1)/(DRAW1_COORD_HEIGHT/2.0);
	


	verts[6] = (i + 1)/(DRAW1_COORD_WIDTH/2.0) - 1;
	verts[7] = 1 - (j + 1)/(DRAW1_COORD_HEIGHT/2.0);
	
	verts[8] = i/(DRAW1_COORD_WIDTH/2.0) - 1;
	verts[9] = 1 - (j + 1)/(DRAW1_COORD_HEIGHT/2.0);

	verts[10] = i/(DRAW1_COORD_WIDTH/2.0) - 1;
	verts[11] = 1 - j/(DRAW1_COORD_HEIGHT/2.0);


	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void draw_square_area(int x1, int y1, int x2, int y2)
{
	int i, j;
	for (i = y1; i < y2; i++)
	for (j = x1; j < x2; j++)
	{
		draw_square(i, j);
	}
}

void draw_clear()
{

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void draw_change_color(float r, float g, float b)
{
	glUniform3f(uniColor, r, g, b);
	//verts[2] = r;
	//verts[3] = g;
	//verts[4] = b;

	//verts[7] = r;
	//verts[8] = g;
	//verts[9] = b;
	
	//verts[12] = r;
	//verts[13] = g;
	//verts[14] = b;
	
	//verts[17] = r;
	//verts[18] = g;
	//verts[19] = b;
	
	//verts[22] = r;
	//verts[23] = g;
	//verts[24] = b;

	//verts[27] = r;
	//verts[28] = g;
	//verts[29] = b;
}


int draw_is_pressed(int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

void draw_init(int _width, int _height)
{
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


	window = glfwCreateWindow(_width, _height, "l33tris", NULL, NULL);
	
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
	const GLchar* fragmentSource_ = "#version 150\nuniform vec3 triColor;\nout vec4 outColor;\nvoid main(){outColor = vec4(triColor, 1.0);}\n";
	//printf(fragmentSource_);
	const GLchar* vertexSource_   = "#version 150\nin vec2 position;\nvoid main(){gl_Position = vec4(position, 0.0, 1.0);}\n";
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


	uniColor = glGetUniformLocation(shaderProgram, "triColor");
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
