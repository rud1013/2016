#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int i;
	if (i1 - i0 == 0) {
		i = j0;
		while (i < j1)
		{
			drawPixel(i1, i, red, green, blue);
			i++;
		}
	}
	i = i0;
	if ((j1 - j0) != 0)
		while (i < i1)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawPixel(i, j, red, green, blue);
			drawPixel(i, j - 1, red, green, blue); drawPixel(i, j + 1, red, green, blue);
			i++;
		}
	i = i0;
	while (i<i1)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;
		drawPixel(i, j, red, green, blue);
		i++;
	}
}

void drawthickLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
		drawPixel(i, j - 1, red, green, blue);
		drawPixel(i, j + 1, red, green, blue);
	}
}

void square(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	drawLine(i0, j0, i1, j0, red, green, blue);
	drawLine(i0, j0, i0, j1, red, green, blue);
	drawLine(i1, j0, i1, j1, red, green, blue);
	drawLine(i0, j1, i1, j1, red, green, blue);
}

void fillsquare(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int i = j0;
	while (i<j1) {
		drawLine(i0, i, i1, i, red, green, blue);
		i++;
	}
}

void triangle(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int x = (i0 + i1) / 2;

	drawLine(i0, j0, x, j1, red, green, blue);
	drawLine(x, j1, i1, j0, red, green, blue);
	drawLine(i0, j0, i1, j0, red, green, blue);
}

void pentagon(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int x = (i0 + i1) / 2;
	int y = ((j0 + j1) / 7) * 4;
	int z = (i1 - i0) / 4;

	drawLine(i0, y, x, j1, red, green, blue);
	drawLine(x, j1, i1, y, red, green, blue);
	drawLine(i0 + z, j0, i1 - z, j0, red, green, blue);
	drawLine(i0, y, i0 + z, j0, red, green, blue);
	drawLine(i1 - z, j0, i1, y, red, green, blue);

}

void circle(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int x = (i0 + i1) / 2;
	int y = (j0 + j1) / 2;
	int r = (j1 - j0) / 2;
	double num;
	int x0, y0;

	for (int i = 0; i < 360; i++)
	{
		num = i*(3.14 / 180);
		x0 = x + r*sin(num);
		y0 = y + r*cos(num);
		drawPixel(x0, y0, red, green, blue);

	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	const int i0 = 100, i1 = 200;
	const int j0 = 50, j1 = 80;
	drawLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);

	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		std::fill_n(pixels, width*height * 3, 1.0f);

		//drawOnPixelBuffer();

		//TODO: RGB struct

		//draw
		drawthickLine(40, 280, 160, 420, 0.0f, 0.0f, 1.0f);
		square(240, 280, 380, 420, 1.0f, 0.0f, 1.0f);
		fillsquare(440, 280, 580, 420, 0.0f, 1.0f, 0.0f);
		triangle(40, 40, 200, 200, 1.0f, 1.0f, 0.0f);
		pentagon(240, 40, 400, 200, 0.3f, 0.0f, 0.3f);
		circle(420, 40, 600, 200, 0.5f, 0.0f, 0.1f);

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}

