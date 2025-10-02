#include <GL/glut.h>
#include <math.h>

// Ângulo de rotação do sol
float angle = 0.0f;

void init(void) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Configuração de iluminação para o sol
    GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 0.8, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    // Material para o sol
    GLfloat mat_ambient[] = {0.7, 0.7, 0.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void drawSky(void) {
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    // Céu - gradiente do azul claro para azul escuro
    glColor3f(0.5, 0.7, 1.0);  // Azul claro (base)
    glVertex3f(-10.0, -2.0, -10.0);
    glVertex3f(10.0, -2.0, -10.0);
    
    glColor3f(0.2, 0.3, 0.8);  // Azul escuro (topo)
    glVertex3f(10.0, 10.0, -10.0);
    glVertex3f(-10.0, 10.0, -10.0);
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawGround(void) {
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.6, 0.3);  // Verde
    glVertex3f(-10.0, -2.0, 10.0);
    glVertex3f(10.0, -2.0, 10.0);
    glVertex3f(10.0, -2.0, -10.0);
    glVertex3f(-10.0, -2.0, -10.0);
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawSun(void) {
    glPushMatrix();
    glTranslatef(0.0, 2.0, 0.0);  // Posição do sol
    glRotatef(angle, 0.0, 1.0, 0.0);  // Rotação
    
    // Esfera com gradiente radial
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    
    // Desenha múltiplas esferas concêntricas com cores diferentes para criar gradiente
    glDisable(GL_LIGHTING);
    for(float i = 1.0; i > 0.0; i -= 0.1) {
        float intensity = i;
        glColor3f(1.0 * intensity, 0.8 * intensity, 0.0 * intensity);
        gluSphere(quadric, 0.5 * i, 32, 32);
    }
    glEnable(GL_LIGHTING);
    
    gluDeleteQuadric(quadric);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Configuração da câmera
    gluLookAt(0.0, 0.0, 8.0,    // Posição da câmera
              0.0, 0.0, 0.0,    // Para onde está olhando
              0.0, 1.0, 0.0);   // Vetor "up"
    
    drawSky();
    drawGround();
    drawSun();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void) {
    angle += 0.5f;  // Incrementa o ângulo de rotação
    if(angle > 360.0f) angle -= 360.0f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sol Radiante com Ceu e Piso - OpenGL/FreeGLUT");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}
