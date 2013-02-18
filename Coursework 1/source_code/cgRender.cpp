#include "cgRender.h"
#include "surfaceModelParser.cpp"

void init() 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  cout << "init" << endl;

  
  glShadeModel (GL_SMOOTH);
  
  // Enable lighting
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);

	float pos[] = {-2.0f, 2.0f, -3.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	float dif[] = {1.0f,1.0f,1.0f,1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	float amb[] = {0.2f,0.2f, 0.2f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);

	/*	
  glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT,  LightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  LightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
  

  // Set material parameters
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  MaterialSpecular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MaterialShininess);
	*/
  
  // Enable Z-buffering
  glEnable(GL_DEPTH_TEST);
  
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
  cout << "display" << endl;
  parse();
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

  /*
  for (all polygons)
    glBegin(GL_POLYGON);
    for (all vertices of polygon)
      // Define texture coordinates of vertex
      glTexCoord2f(...);
      // Define normal of vertex
      glNormal3f(...);
      // Define coordinates of vertex
      glVertex3f(...);
    }
    glEnd();
  }
  glFlush ();
  //  or, if double buffering is used,
  //  glutSwapBuffers();
  */

void reshape (int w, int h)
{
  cout << "reshape" << endl;

  glViewport (0, 0, (GLsizei) w , (GLsizei) h); 
/*
	glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective((GLdouble) 10,(GLdouble)  10,(GLdouble)  10,(GLdouble)  10);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 0, 0, 0, 0, 0, 0, 0);*/
  /*
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fovy, aspect, near, far);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
  */
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 27: // ESC
    exit(0);
    break;
  }
}

int main(int argc, char** argv)
{
  // Initialize graphics window
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
  //  Or, can use double buffering
  //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 

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
