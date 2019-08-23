#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

static int year = 0, day = 0, moon=0;

void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);

  float mat_shininess = 50;
  float light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
  float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  float light_position[] = { 1.0, 1.0, 1.0, 0.0 };

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &mat_shininess);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
}

void years_mover(int d) // Ciclo de rotacion infinito
{
  year = (year + 5) % 360;
  moon = (moon + 10) % 360;
  glutPostRedisplay();
}


void display (void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0);
  glColor3f(1.0, 0.0, 0.0);
  // Dibujando el sistema planetario
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(1.0, 200, 64); /* Dibuja el sol */ 
    glRotatef((GLfloat) year, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 0.0, 0.0);
    glPushMatrix();
      glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
      glColor3f(0.0, 0.0, 1.0);
      glutSolidSphere(0.2, 50, 32); /* dibuja el planeta */ 
    glPopMatrix();
    glRotatef ((GLfloat) moon, 0.0, 1.0, 0.0);
    glTranslatef (0.5, 0.0, 0.0);
    glColor3f (0.7, 0.7, 0.7);
    glutSolidSphere(0.07, 200, 32); /* Dibuja la luna */
  glPopMatrix();
  glutTimerFunc(10, years_mover, 0); // Ejecuta el ciclo de rotacion automatico
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) // Manipular la rotacion
{
  switch (key)
  {
    case 'd': // rotacion de la tierra sobre si misma
      day = (day + 10) % 360;  
      glutPostRedisplay();
      break;
    case 'D': // rotacion inversa de la tierra sobre si misma
      day = (day - 10) % 360;
      glutPostRedisplay();
      break;
    case 'y': // rotacion de la tierra sobre el sol
      year = (year + 5) % 360;
      glutPostRedisplay();
      break;
    case 'Y': // rotacion inversa de la tierra sobre el sol
      year = (year - 5) % 360;
      glutPostRedisplay();
      break;
    case 'm': // rotacion de la luna sobre si misma
      moon = (moon + 10) % 360;
      glutPostRedisplay();
      break;
    case 'M': // rotacion inversa de la luna sobre si misma
      moon = (moon - 10) % 360;
      glutPostRedisplay();
      break;
    default:
      break;
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Planets");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}



