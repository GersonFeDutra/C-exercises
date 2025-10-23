#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Ângulo de rotação do sol
float angle = 0.0f;
int windowWidth = 800;
int windowHeight = 600;

void init(void) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.1, 0.3, 1.0); // Azul mais escuro para o fundo
    
    // Habilitar blending para o efeito de bloom
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Suavização de pontos e linhas para melhorar o gradiente
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void drawSky(void) {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Céu com gradiente suave
    glBegin(GL_QUADS);
    // Parte superior - azul escuro
    glColor3f(0.1, 0.2, 0.4);
    glVertex2f(0, windowHeight);
    glVertex2f(windowWidth, windowHeight);
    
    // Parte inferior - azul claro
    glColor3f(0.3, 0.5, 0.8);
    glVertex2f(windowWidth, 0);
    glVertex2f(0, 0);
    glEnd();
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);
}

void drawGround(void) {
    glDisable(GL_LIGHTING);
    
    // Piso com gradiente
    glBegin(GL_QUADS);
    // Parte próxima - verde claro
    glColor3f(0.2, 0.5, 0.2);
    glVertex3f(-20.0, -3.0, 20.0);
    glVertex3f(20.0, -3.0, 20.0);
    
    // Parte distante - verde escuro
    glColor3f(0.1, 0.3, 0.1);
    glVertex3f(20.0, -3.0, -20.0);
    glVertex3f(-20.0, -3.0, -20.0);
    glEnd();
    
    glEnable(GL_LIGHTING);
}

void drawSunCore(void) {
    // Núcleo do sol - esfera sólida
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    
    glDisable(GL_LIGHTING);
    
    // Gradiente radial manual para o núcleo
    int slices = 32;
    int stacks = 32;
    float radius = 0.8f;
    
    for (int i = 0; i < stacks; i++) {
        float phi1 = (float)i / stacks * M_PI;
        float phi2 = (float)(i + 1) / stacks * M_PI;
        
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float theta = (float)j / slices * 2.0f * M_PI;
            
            // Cor baseada na posição radial
            float intensity = 1.0f - (float)i / stacks * 0.3f;
            float edgeIntensity = 1.0f - (float)(i + 1) / stacks * 0.3f;
            
            // Cor do centro (amarelo brilhante) para as bordas (laranja)
            float r1 = 1.0f * intensity;
            float g1 = 0.9f * intensity;
            float b1 = 0.1f * intensity;
            
            float r2 = 1.0f * edgeIntensity;
            float g2 = 0.9f * edgeIntensity;
            float b2 = 0.1f * edgeIntensity;
            
            float x1 = radius * sin(phi1) * cos(theta);
            float y1 = radius * cos(phi1);
            float z1 = radius * sin(phi1) * sin(theta);
            
            float x2 = radius * sin(phi2) * cos(theta);
            float y2 = radius * cos(phi2);
            float z2 = radius * sin(phi2) * sin(theta);
            
            glColor3f(r1, g1, b1);
            glVertex3f(x1, y1, z1);
            
            glColor3f(r2, g2, b2);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
    
    gluDeleteQuadric(quadric);
}

void drawSunGlow(void) {
    // Efeito de bloom - múltiplas camadas com transparência
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    int glowLayers = 6;
    float baseRadius = 0.8f;
    
    for (int i = 0; i < glowLayers; i++) {
        float radius = baseRadius + (i + 1) * 0.3f;
        float alpha = 0.15f - (i * 0.02f);
        
        glColor4f(1.0f, 0.7f, 0.1f, alpha);
        
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, 0, 0);
        
        int segments = 32;
        for (int j = 0; j <= segments; j++) {
            float angle = 2.0f * M_PI * j / segments;
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            glVertex3f(x, y, 0);
        }
        glEnd();
    }
    
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void drawSun(void) {
    glPushMatrix();
    glTranslatef(0.0, 2.0, 0.0);  // Posição do sol
    glRotatef(angle, 0.0, 1.0, 0.0);  // Rotação
    
    // Desenhar o glow primeiro (por trás)
    //drawSunGlow();
    
    // Depois o núcleo
    drawSunCore();
    
    // // Raios de luz adicionais
    // glDisable(GL_DEPTH_TEST);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    // 
    // int rays = 12;
    // float rayLength = 2.5f;
    // 
    // for (int i = 0; i < rays; i++) {
    //     float rayAngle = (360.0f / rays) * i;
    //     glPushMatrix();
    //     glRotatef(rayAngle, 0, 0, 1);
    //     
    //     glColor4f(1.0f, 0.8f, 0.2f, 0.3f);
    //     glBegin(GL_TRIANGLES);
    //     glVertex3f(0, 0, 0);
    //     glVertex3f(-0.1f, rayLength, 0);
    //     glVertex3f(0.1f, rayLength, 0);
    //     glEnd();
    //     
    //     glPopMatrix();
    // }
    
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Primeiro desenhar o céu (fundo)
    drawSky();
    
    glLoadIdentity();
    
    // Configuração da câmera
    gluLookAt(0.0, 1.0, 8.0,    // Posição da câmera
              0.0, 0.0, 0.0,    // Para onde está olhando
              0.0, 1.0, 0.0);   // Vetor "up"
    
    drawGround();
    drawSun();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void) {
    angle += 0.8f;  // Incrementa o ângulo de rotação
    if(angle > 360.0f) angle -= 360.0f;
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            // Aumenta a intensidade do bloom
            break;
        case GLUT_KEY_DOWN:
            // Diminui a intensidade do bloom
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sol Radiante com Efeito Bloom - OpenGL/FreeGLUT");
    
    // Tentar habilitar multisampling para suavização extra
    GLint buffers, samples;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &buffers);
    glGetIntegerv(GL_SAMPLES, &samples);
    if (buffers > 0 && samples > 1) {
        glEnable(GL_MULTISAMPLE);
    }
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutSpecialFunc(specialKeys);
    
    printf("Controles:\n");
    printf("- Setas: Ajustar efeito de bloom\n");
    printf("- A cena roda automaticamente\n");
    
    glutMainLoop();
    return 0;
}
