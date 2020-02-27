#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>
#include "spotlight.h"

static float modelAmb[4] = {0.2, 0.2, 0.2, 1.0}
      ,      matAmb[4] = {0.2, 0.2, 0.2, 1.0}
      ,      matDiff[4] = {0.8, 0.8, 0.8, 1.0}
      ,      matSpec[4] = {0.4, 0.4, 0.4, 1.0}
      ,      matEmission[4] = {0.0, 0.0, 0.0, 1.0};

static Light spots[] =
{
  // Declare the Spotlight Values
  {
    {0.2, 0.2, 0.2, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 2.0},  /* diffuse */
    {0.4, 0.4, 0.4, 1.0},  /* specular */
    {0.0, 0.0, 0.0, 1.0},  /* position */
    {0.0, -1.0, 0.0},   /* direction */
    20.0,
    40.0,             /* exponent, cutoff */
    {0.0, 1.0, 0.0},    /* attenuation */
    {0.0, 0.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 80.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 10.0, 0.0, TWO_PI / 40.0}  /* arc increment */
  }
};

// Draws a plane with Resolution w, h
static void drawPlane(int w, int h)
{
  int i, j;
  float dw = 1.0 / w;
  float dh = 1.0 / h;

  glPushMatrix();
    glRotatef(-90.0, 1, 0, 0);
    glScalef(2., 3., 1.);
    glTranslatef(-.5, -.25, -.5);

    glNormal3f(0.0, 0.0, 1.0);
    for (j = 0; j < h; ++j) {
      glBegin(GL_TRIANGLE_STRIP);
      for (i = 0; i <= w; ++i) {
        glVertex2f(dw * i, dh * (j + 1));
        glVertex2f(dw * i, dh * j);
      }
      glEnd();
    }
  glPopMatrix();
}

// Rotation Variable to Animate the Spotlight
float spin = 0;

// Point the light in the Direction you want, and set it to a Position
void aimLight(Light * light)
{
    light->rot[0] = 0;
    light->rot[1] = 20;
    light->rot[2] = spin;

    light->trans[0] = 0.;
    light->trans[1] = .75;
    light->trans[2] = 0.;
}

// Render the Scene
void display(void)
{
  Light *light = &spots[0];
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
    aimLight(light);
    LIGHT_set(light, GL_LIGHT0);
    drawPlane(64, 64);
  glPopMatrix();

  glutSwapBuffers();
}

double i = 0;

// Animate the Moving Spotlight
void animate(void)
{
  i += M_PI / 128;
  spin = 45 * cos(i);
  sleep(.25);
  glutPostRedisplay();
  
}

void visibilityFunc(int state)
{
  if (state == GLUT_VISIBLE)
    glutIdleFunc(animate);
  else
    glutIdleFunc(NULL);
}

int main(int argc, char **argv)
{
  Light *light = &spots[0];
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(1280, 720);
  glutInitWindowPosition(10,10);
  glutCreateWindow("Spotlight Demo Computergrafik");
  
  glutDisplayFunc(display);
  glutVisibilityFunc(visibilityFunc);

  glMatrixMode(GL_PROJECTION);
  glFrustum(-1, 1, -1, 1, 2, 6);

  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0.0, 0.0, -3.0);
  glRotatef(45.0, 1, 0, 0);

  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);


  LIGHT_init(light, GL_LIGHT0);

  glutMainLoop();

  return 0;
}