#include <stdio.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>


void init(void){
glClearColor(0.0,0.0,0.0,0.0);
glShadeModel(GL_FLAT);
glEnable (GL_DEPTH_TEST);
glEnable (GL_LIGHTING);
glEnable (GL_LIGHT0);
}

void display(void){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glColor3f(1.0,1.0,1.0);
glLoadIdentity();
gluLookAt(0.0,10.0,3.0,0.0,0.0,0.0,0.0,1.0,0.0);
glutSwapBuffers();
glutSolidSphere(2.0,80,50);
glutSolidCone(2.0,5.0,50,1);
glFlush();
}

void reshape(int w, int h){
glViewport(0, 0 , (GLsizei) w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);
glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(500,500);
glutInitWindowPosition(100,100);
glutCreateWindow("Kelompok 9");
init();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMainLoop();
return 0;
}
