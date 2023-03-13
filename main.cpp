#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "dependente\glew\glew.h"

#include "dependente\glfw\glfw3.h"

#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

#include "shader.hpp"


GLFWwindow* window;
const int width = 728, height = 728;
float x = 0;

glm::vec3 shipPos(0.0f, -0.7f, 0.0f);
glm::vec3 bulletPos(1.0f);
glm::vec3 asteroid1Pos(0.0f, 0.7f, 0.0f);
glm::vec3 asteroid2Pos(-0.5f, 0.7f, 0.0f);
glm::vec3 asteroid3Pos(0.5f, 0.7f, 0.0f);



void window_callback(GLFWwindow* window, int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);
}

int main(void)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	window = glfwCreateWindow(width, height, "Space ship", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, width, height);

	glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//ship
	GLuint programID = LoadShaders("SimpleVertexShaderShip.vertexshader", "SimpleFragmentShaderShip.fragmentshader");

	GLfloat vertices[] = {
		-0.05f, -0.0f, 0.0f,
		0.05f, -0.0f, 0.0f,
		0.0f, 0.1f, 0.0f
	};
	GLuint indices[] = {
		0,1,2
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO_ID;
	GLuint EBO_ID;
	glGenBuffers(1, &VBO_ID);
	glGenBuffers(1, &EBO_ID);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GL_FLOAT),0);
	glEnableVertexAttribArray(0);


	//bullet
	GLuint programIDBullet = LoadShaders("SimpleVertexShaderBullet.vertexshader", "SimpleFragmentShaderBullet.fragmentshader");

	GLfloat verticesBullet[] = {
		-0.02f, 0.2f, 0.0f,
		0.02f, 0.2f, 0.0f,
		0.0f, 0.25f, 0.0f

	};
	GLuint indicesBullet[] = {
		0,1,2

	};

	GLuint VAOBullet;
	glGenVertexArrays(1, &VAOBullet);
	glBindVertexArray(VAOBullet);

	GLuint VBO_IDBullet;
	GLuint EBO_IDBullet;
	glGenBuffers(1, &VBO_IDBullet);
	glGenBuffers(1, &EBO_IDBullet);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_IDBullet);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBullet), verticesBullet, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_IDBullet);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesBullet), indicesBullet, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GL_FLOAT),0);
	glEnableVertexAttribArray(0);


	//asteroid
	GLuint programIDAsteroid1 = LoadShaders("SimpleVertexShaderAst1.vertexshader", "SimpleFragmentShaderAst1.fragmentshader");

	GLfloat verticesAsteroid1[] = {
		-0.1f,0.6f,0.0f,
		0.1f,0.6f,0.0f,
		-0.1f,0.8f,0.0f,
		0.1f,0.8f,0.0f

	};
	GLuint indicesAsteroid1[] = {
		0,1,2,
		1,3,2
	};

	GLuint VAOAsteroid1;
	glGenVertexArrays(1, &VAOAsteroid1);
	glBindVertexArray(VAOAsteroid1);

	GLuint VBO_IDAsteroid1;
	GLuint EBO_IDAsteroid1;
	glGenBuffers(1, &VBO_IDAsteroid1);
	glGenBuffers(1, &EBO_IDAsteroid1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_IDAsteroid1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAsteroid1), verticesAsteroid1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_IDAsteroid1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesAsteroid1), indicesAsteroid1, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GL_FLOAT),0);
	glEnableVertexAttribArray(0);


	GLuint programIDAsteroid2 = LoadShaders("SimpleVertexShaderAst2.vertexshader", "SimpleFragmentShaderAst2.fragmentshader");

	GLfloat verticesAsteroid2[] = {

		-0.6f,0.6f,0.0f,
		-0.4f,0.6f,0.0f,
		-0.6f,0.8f,0.0f,
		-0.4f,0.8f,0.0f

	};
	GLuint indicesAsteroid2[] = {
		0,1,2,
		1,3,2

	};

	GLuint VAOAsteroid2;
	glGenVertexArrays(1, &VAOAsteroid2);
	glBindVertexArray(VAOAsteroid2);

	GLuint VBO_IDAsteroid2;
	GLuint EBO_IDAsteroid2;
	glGenBuffers(1, &VBO_IDAsteroid2);
	glGenBuffers(1, &EBO_IDAsteroid2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_IDAsteroid2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAsteroid2), verticesAsteroid2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_IDAsteroid2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesAsteroid2), indicesAsteroid2, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GL_FLOAT),0);
	glEnableVertexAttribArray(0);


	GLuint programIDAsteroid3 = LoadShaders("SimpleVertexShaderAst3.vertexshader", "SimpleFragmentShaderAst3.fragmentshader");

	GLfloat verticesAsteroid3[] = {

		0.4f,0.6f,0.0f,
		0.6f,0.6f,0.0f,
		0.4f,0.8f,0.0f,
		0.6f,0.8f,0.0f

	};
	GLuint indicesAsteroid3[] = {
		0,1,2,
		1,3,2

	};

	GLuint VAOAsteroid3;
	glGenVertexArrays(1, &VAOAsteroid3);
	glBindVertexArray(VAOAsteroid3);

	GLuint VBO_IDAsteroid3;
	GLuint EBO_IDAsteroid3;
	glGenBuffers(1, &VBO_IDAsteroid3);
	glGenBuffers(1, &EBO_IDAsteroid3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_IDAsteroid3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAsteroid3), verticesAsteroid3, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_IDAsteroid3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesAsteroid3), indicesAsteroid3, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GL_FLOAT),0);
	glEnableVertexAttribArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	glm::mat4 trans(1.0f);

	glfwSetFramebufferSizeCallback(window, window_callback);

	//show ship
	glUseProgram(programID);
	glBindVertexArray(VAO);
	trans = glm::translate(trans, glm::vec3(shipPos.x, shipPos.y, 0.0));
	unsigned int transformLoc = glGetUniformLocation(programID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);
		glBindVertexArray(VAO);


		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && shipPos.x > -0.95) {

			glm::mat4 trans(1.0f);

			shipPos.x = shipPos.x - 0.0005f;
			//std::cout << shipPos.x<<std::endl;

			trans = glm::translate(trans, glm::vec3(shipPos.x, shipPos.y, 0.0));
			unsigned int transformLoc = glGetUniformLocation(programID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && shipPos.x < 0.95) {

			glm::mat4 trans(1.0f);
			shipPos.x = shipPos.x + 0.0005f;
			//std::cout << shipPos.x << std::endl;

			trans = glm::translate(trans, glm::vec3(shipPos.x, shipPos.y, 0.0));
			unsigned int transformLoc = glGetUniformLocation(programID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && shipPos.y < 0.9) {

			glm::mat4 trans(1.0f);
			shipPos.y = shipPos.y + 0.0005f;
			//std::cout << shipPos.y << std::endl;

			trans = glm::translate(trans, glm::vec3(shipPos.x, shipPos.y, 0.0));
			unsigned int transformLoc = glGetUniformLocation(programID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && shipPos.y > -1) {

			glm::mat4 trans(1.0f);
			shipPos.y = shipPos.y - 0.0005f;
			//std::cout << shipPos.y << std::endl;

			trans = glm::translate(trans, glm::vec3(shipPos.x, shipPos.y, 0.0));
			unsigned int transformLoc = glGetUniformLocation(programID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		}

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


		//asteroid1
		glUseProgram(programIDAsteroid1);
		glBindVertexArray(VAOAsteroid1);

		glm::mat4 transAs1(1.0f);

		if (asteroid1Pos.y > -2.0) {
			asteroid1Pos.y = asteroid1Pos.y - 0.00003f;
			//std::cout << asteroidPosSS.y << std::endl;

			transAs1 = glm::translate(transAs1, glm::vec3(0.0, asteroid1Pos.y, 0.0));
			transAs1 = glm::rotate(transAs1, (float)glfwGetTime() * 100, glm::vec3(0.0, asteroid1Pos.y, 0.0));

			unsigned int transformLoc = glGetUniformLocation(programIDAsteroid1, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transAs1));

		}

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		if (bulletPos.x > asteroid1Pos.x - 0.1 && bulletPos.x < asteroid1Pos.x + 0.1
			&& bulletPos.y > asteroid1Pos.y - 0.0006 && bulletPos.y < asteroid1Pos.y + 0.0006
			/* && asteroid1Pos.y < 0.7*/) {
			
			bulletPos.y = 1.2;
			asteroid1Pos.x = 0.0f;
			asteroid1Pos.y = 0.7f;

			trans = glm::translate(trans, glm::vec3(asteroid1Pos.x, asteroid1Pos.y, 0.0));
			unsigned int transformLoc = glGetUniformLocation(programIDAsteroid1, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
				
		}

		if (asteroid1Pos.y < -2.0) {
			asteroid1Pos.x = 0.0f;
			asteroid1Pos.y = 0.7f;
		}

		if (shipPos.x > asteroid1Pos.x - 0.1 && shipPos.x < asteroid1Pos.x + 0.1
			&& shipPos.y > asteroid1Pos.y - 0.0006 && shipPos.y < asteroid1Pos.y + 0.0006
			&& asteroid1Pos.y < 0.7) 
		{
			//std::cout << "Game over" << std::endl;
			break;
		}


		//asteroid2
		glm::mat4 transAs2(1.0f);
		glUseProgram(programIDAsteroid2);
		glBindVertexArray(VAOAsteroid2);


		if (asteroid2Pos.y > -2.0) {
			asteroid2Pos.y = asteroid2Pos.y - 0.0002f;
			float angle = 360;
			angle =angle-0.00002;
			//std::cout << "1" << std::endl;
			//(float)glfwGetTime() * 100

			transAs2 = glm::rotate(transAs2, angle, glm::vec3(0.0, 0.0, 1.0));
			transAs2 = glm::translate(transAs2, glm::vec3(0.0, asteroid2Pos.y, 0.0));
		
		
			unsigned int transformLoc = glGetUniformLocation(programIDAsteroid2, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transAs2));

		}

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		if (bulletPos.x > asteroid2Pos.x - 0.1 && bulletPos.x < asteroid2Pos.x + 0.1
			&& bulletPos.y > asteroid2Pos.y - 0.0006 && bulletPos.y < asteroid2Pos.y + 0.0006
			/* && asteroid2Pos.y < 0.7*/) {
		
			bulletPos.y = 1.2;

			asteroid2Pos.x = -0.05f;
			asteroid2Pos.y = 0.7f;

			trans = glm::translate(trans, glm::vec3(asteroid2Pos.x, asteroid2Pos.y, 0.0));
			unsigned int transformLoc = glGetUniformLocation(programIDAsteroid2, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			
		}

		if (asteroid2Pos.y < -2.0) {
			asteroid2Pos.x = -0.05f;
			asteroid2Pos.y = 0.7f;
		}

		if (shipPos.x > asteroid2Pos.x - 0.1 && shipPos.x < asteroid2Pos.x + 0.1
			&& shipPos.y > asteroid2Pos.y - 0.0006 && shipPos.y < asteroid2Pos.y + 0.0006
			&& asteroid2Pos.y < 0.7)
		{
			//std::cout << "Game over" << std::endl;
			break;
		}


		//asteroid3
		glm::mat4 transAs3(1.0f);
		glUseProgram(programIDAsteroid3);
		glBindVertexArray(VAOAsteroid3);


		if (asteroid3Pos.y > -2.0) {
			asteroid3Pos.y = asteroid3Pos.y - 0.00005f;
			//std::cout << asteroidPosSS.y << std::endl;

			transAs3 = glm::translate(transAs3, glm::vec3(0.0, asteroid3Pos.y, 0.0));
			//transAs3 = glm::rotate(transAs3, (float)glfwGetTime() * 100, glm::vec3(0.0, asteroid3Pos.y, 0.0));
			unsigned int transformLoc = glGetUniformLocation(programIDAsteroid3, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transAs3));

		}

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		if (bulletPos.x > asteroid3Pos.x - 0.1 && bulletPos.x < asteroid3Pos.x + 0.1
			&& bulletPos.y > asteroid3Pos.y - 0.0006 && bulletPos.y < asteroid3Pos.y + 0.0006
			/* && asteroid3Pos.y < 0.7*/){

			bulletPos.y = 1.2;
			asteroid3Pos.x = 0.5f;
			asteroid3Pos.y = 0.7f;

			trans = glm::translate(trans, glm::vec3(asteroid3Pos.x, asteroid3Pos.y, 0.0));
			unsigned int transformLoc = glGetUniformLocation(programIDAsteroid3, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			
		}

		if (asteroid3Pos.y < -2.0) {
			asteroid3Pos.x = 0.5f;
			asteroid3Pos.y = 0.7f;
		}

		if (shipPos.x > asteroid3Pos.x - 0.1 && shipPos.x < asteroid3Pos.x + 0.1
			&& shipPos.y > asteroid3Pos.y - 0.0006 && shipPos.y < asteroid3Pos.y + 0.0006
			&& asteroid3Pos.y < 0.7)
		{
			//std::cout << "Game over" << std::endl;
			break;
		}


		//bullet
		glm::mat4 transb(1.0f);

		glBindVertexArray(VAOBullet);
		glUseProgram(programIDBullet);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

			glm::mat4 transb(1.0f);
			bulletPos = shipPos;
			bulletPos.y = bulletPos.y - 0.15;

		}

		bulletPos.y = bulletPos.y + 0.005f;
		//std::cout << bulletPos.y << std::endl;
		transb = glm::translate(transb, glm::vec3(bulletPos.x, bulletPos.y, 0.0));

		unsigned int transformLocb = glGetUniformLocation(programIDBullet, "transform");
		glUniformMatrix4fv(transformLocb, 1, GL_FALSE, glm::value_ptr(transb));

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	}

	std::cout << "Game over" << std::endl;

	glDeleteBuffers(1, &VBO_ID);
	glDeleteBuffers(1, &EBO_ID);
	glDeleteBuffers(1, &VAO);
	glDeleteProgram(programID);

	glDeleteBuffers(1, &VBO_IDAsteroid1);
	glDeleteBuffers(1, &EBO_IDAsteroid1);
	glDeleteBuffers(1, &VAOAsteroid1);
	glDeleteProgram(programIDAsteroid1);

	glDeleteBuffers(1, &VBO_IDAsteroid2);
	glDeleteBuffers(1, &EBO_IDAsteroid2);
	glDeleteBuffers(1, &VAOAsteroid2);
	glDeleteProgram(programIDAsteroid2);

	glDeleteBuffers(1, &VBO_IDAsteroid3);
	glDeleteBuffers(1, &EBO_IDAsteroid3);
	glDeleteBuffers(1, &VAOAsteroid3);
	glDeleteProgram(programIDAsteroid3);

	glDeleteBuffers(1, &VBO_IDBullet);
	glDeleteBuffers(1, &EBO_IDBullet);
	glDeleteBuffers(1, &VAOBullet);
	glDeleteProgram(programIDBullet);

	glfwTerminate();

	return 0;
}


