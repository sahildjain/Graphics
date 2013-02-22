#include "cgRender.h"
#include "surfaceModelParser.h"

GLfloat eyex;
GLfloat eyey;
GLfloat eyez;
GLfloat centerx;
GLfloat centery;
GLfloat centerz;
GLfloat upx = 0;
GLfloat upy = 1;
GLfloat upz = 0;
GLfloat lightz = 10.0f;
GLfloat lightx = 50.0f;
GLfloat LightPosition[] = {lightx, 0, lightz};

void init() 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  cout << "init" << endl;

	GLfloat LightAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat LightSpecular[] = {0.2f, 0.2f, 0.2f, 0.2f};
	GLfloat MaterialSpecular[] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat MaterialShininess[] = {10.0};
  
  glShadeModel (GL_SMOOTH);
  
  // Enable lighting
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MaterialSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MaterialShininess);
  
  // Enable Z-buffering
  glEnable(GL_DEPTH_TEST);

	GLuint texture;
	glEnable(GL_TEXTURE_2D);
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texdata);

}

void setAttr(Vertex * vertex, int id) {
	TextureMapping mapping = textures[id];
	glTexCoord2f(mapping.x, mapping.y);
	glNormal3f(vertex->normal.x, vertex->normal.y, vertex->normal.z);
	glVertex3f(vertex->x, vertex->y, vertex->z);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3i(100, 100, 100);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
  
  glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

  cout << "display" << endl;

	for(VECPOLYGON::iterator it = polygons.begin(); it != polygons.end(); ++it) {
		glBegin(GL_POLYGON);
		Polygon polygon = *it;
		setAttr(polygon.first, polygon.first->index);
		setAttr(polygon.second, polygon.second->index);
		setAttr(polygon.third, polygon.third->index);
		glEnd();
	}
	glFlush();
}

void reshape (int w, int h)
{
  cout << "reshape" << endl;
  glViewport (0, 0, (GLsizei) w , (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, w/h, 0.001, 10);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
		case 27: // ESC
		  exit(0);
		  break;
		case 119: // w
			eyex -= 0.01;
			break;
		case 115: // s
			eyex += 0.01;
			break;
		case 97: // a
			eyez +=0.01;
			break;
		case 100: // d
			eyez -= 0.01;
			break;
		case 105: // i
			lightz += 0.01;
			break;
		case 107: // k
			lightz -= 0.01;
			break;
		case 106: // j
			lightx += 0.01;
			break;
		case 108: // l
			lightx -= 0.01;
			break;
		case 114: // r
			eyey += 0.01;
			break;
		case 102: // f
			eyey -= 0.01;
			break;
		default:
			display();	
	}
	display();
}

int main(int argc, char** argv)
{
	parse();
  // Initialize graphics window
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 

  glutInitWindowSize (256, 256); 
  glutInitWindowPosition (0, 0);
  glutCreateWindow (argv[0]);

  // Initialize OpenGL
  init();

  // Initialize callback functions
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

  // Start rendering 
  glutMainLoop();
}
