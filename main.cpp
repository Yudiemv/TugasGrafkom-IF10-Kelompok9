#include <stdio.h>
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>


int w=1024, h=720, z=0;
int x1=0, y1=0, sudut=0, z1=0, skalaX=0, skalaY=0;

GLuint texture; //array untuk texture

GLuint LoadTexture( const char * filename, int width, int height )
{
GLuint texture;
unsigned char * data;
FILE * file;

file = fopen( filename, "rb" );
if ( file == NULL ) return 0;
data = (unsigned char *)malloc( width * height * 3 );
fread( data, width * height * 3, 1, file );
fclose( file );

glGenTextures( 1, &texture );
glBindTexture( GL_TEXTURE_2D, texture );
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
free( data ); //free the texture
return texture; //return whether it was successfull
}

void FreeTexture( GLuint texture )
{
glDeleteTextures( 1, &texture );
}



GLfloat redDiffuseMaterial[] = {1.0, 0.5, 0.3};
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0};
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0};
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0};
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0};
GLfloat blankMaterial[] = {0.0, 0.0, 0.0};
GLfloat mShininess[] = {128};

bool diffuse = false;
bool emissive = false;
bool specular = false;


void init(void){
glClearColor(0.0,0.0,0.0,0.0);
glShadeModel(GL_FLAT);
glEnable (GL_DEPTH_TEST);
glEnable (GL_LIGHTING);
glEnable (GL_LIGHT0);
}

void light (void) {
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
}

void display(void){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();

gluLookAt(0.0,10.0,3.0,0.0,0.0,0.0,0.0,1.0,0.0);

glEnable( GL_TEXTURE_2D ); //enable 2D texturing
glEnable(GL_TEXTURE_GEN_S);
glEnable(GL_TEXTURE_GEN_T);
light();

glTranslatef(0,z,0);
glRotatef(sudut,x1,y1,z1);

//Balon
texture = LoadTexture( "lines.raw", 256, 256 );
glBindTexture( GL_TEXTURE_2D, texture );
glutSolidSphere(2.0,20,50);

glPushMatrix();
glTranslatef(0,0,2.9);
glScalef(1,1,0.5);
glutSolidTorus(0.19,0.20,20,50);
glPopMatrix();

glPushMatrix();
glTranslatef(0,0,1);
glutSolidCone(1.734,2,20,50);
glPopMatrix();

FreeTexture( texture );

//Kotak dibawah balon
glPushMatrix();
glTranslatef(0,0,3.2);
glScalef(1,1,0.25);
glutSolidTorus(0.19,0.20,20,50);
glPopMatrix();


glPushMatrix();
glTranslatef(0,0,3.43);
glScalef(1,1,0.6);
texture = LoadTexture( "Box.raw", 256, 256 );
glBindTexture( GL_TEXTURE_2D, texture );
glutSolidCube(0.6);
FreeTexture( texture );
glPopMatrix();



glutSwapBuffers();
glFlush();
}

void reshape(int w, int h){
glViewport(0, 0 , (GLsizei) w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);
glMatrixMode(GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y) {
    if (key=='s')
    {
        if (specular==false)
        {
            specular = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
        }
        else if (specular==true)
        {
            specular = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blankMaterial);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, blankMaterial);
        }
    }
    
    if (key=='d')
    {
        if (diffuse==false)
        {
            diffuse = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
        }
        else if (diffuse==true)
        {
            diffuse = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
        }
    }
    
    if (key=='e')
    {
        if (emissive==false)
        {
            emissive = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenEmissiveMaterial);
        }
        else if (emissive==true)
        {
            emissive = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blankMaterial);
        }
    }
    if (key == 'x')
    {
        x1=1;
        y1=0;
        z1=0;
        sudut+=10;
    }
    if (key == 'y')
    {
        y1=1;
        x1=0;
        z1=0;
        sudut+=10;
    }
    if (key == 'z')
    {
        y1=0;
        x1=0;
        z1=1;
        sudut+=10;
    }
}

void mySpecialKeyboard(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        z+=1;
        break;
    case GLUT_KEY_DOWN:
        z-=1;
        break;
    }
}

int main(int argc, char** argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);\
glutInitWindowSize(500,500);
glutInitWindowPosition(100,100);
glutCreateWindow("Kelompok 9");
init();
glutDisplayFunc(display);
glutIdleFunc(display);
glutReshapeFunc(reshape);
glutKeyboardFunc (keyboard);
glutSpecialFunc(mySpecialKeyboard);
glutMainLoop();
return 0;
}
