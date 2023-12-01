#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <vector>
#include <fstream>
bool buttonPressed = false;
bool button1 = false;
bool buttonN = false;

struct Point {
    float x, y;
};

int get_size_with_1(std::vector<Point> points) {
    return (points.size() - 1);
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

std::fstream& operator<<(std::fstream& fs, const Point& point) {
    fs << "(" << point.x << ", " << point.y << ")";
    return fs;
}

/*void drawPoint(int x, int y, float red, float green, float blue) {
    glPointSize(5.0);
    glColor3f(red, green, blue);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
*/

GLuint textureID;
std::vector<Point> points;
std::vector<Point> new_points;
std::vector<Point> cancel_points;

void display() {
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0, -1.0);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0, -1.0);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0, 1.0);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0, 1.0);
    glEnd();

    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);

    for (const Point& p : points) {
        glVertex2f(p.x, p.y);
    }
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);

    if (points.size() >= 2) {
        for (size_t i = 0; i < points.size() - 1; ++i) {
            glVertex2f(points[i].x, points[i].y);
            glVertex2f(points[i + 1].x, points[i + 1].y);
        }
    }
    if ((buttonPressed || button1) && points.size() != 0) {
        button1 = true;
        glVertex2f(points[points.size() - 1].x, points[points.size() - 1].y);
        glVertex2f(points[0].x, points[0].y);
    }
    glEnd();

    if (buttonN) {
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        for (const Point& p : new_points) {
            glVertex2f(p.x, p.y);
        }
        glEnd();

        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);

        if (new_points.size() >= 2) {
            for (size_t i = 0; i < new_points.size() - 1; ++i) {
                glVertex2f(new_points[i].x, new_points[i].y);
                glVertex2f(new_points[i + 1].x, new_points[i + 1].y);
            }
        }
        if ((buttonPressed || button1) && new_points.size() != 0) {
            button1 = true;
            glVertex2f(new_points[new_points.size() - 1].x, new_points[new_points.size() - 1].y);
            glVertex2f(new_points[0].x, new_points[0].y);
        }
        glEnd();

    }



    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT);
}

void loadTexture(const char* filename) {
    textureID = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureID == 0) {
        printf("Error loading texture: %s\n", SOIL_last_result());
    }
}

void keyboardFunc(unsigned char key, int x, int y) {
    if (key == 'b') {
        buttonPressed = true;
        std::cout << "Last " << points[points.size() - 1] << " First " << points[0] << std::endl;
        glutPostRedisplay();
    }

    if (key == 'n') {
        buttonN = true;
        std::cout << "New";
        glutPostRedisplay();
    }

    if (key == 'd') {
        points.clear();
        glutPostRedisplay();
    }

    if (key == 'z') {
        Point last_symbol = points[get_size_with_1(points)];
        points.pop_back();
        cancel_points.push_back(last_symbol);
        glutPostRedisplay();
    }

    if (key == 'y') {
        points.push_back(cancel_points[0]);
        cancel_points.pop_back();
        glutPostRedisplay();
    }



    if (key == 's') {
        std::ofstream outputFile("C:/Users/Misha/Documents/GitHub/misis2023f-22-01-Trufmanov-M-A/prj.cw/test_output.txt");
        outputFile.clear();
        if (!outputFile.is_open()) {
            std::cout << "Error opening the file!" << std::endl;
        }
        else {
            outputFile.clear();
            for (int i = 0; i < get_size_with_1(points); i++) {
                outputFile << points[i] << " ";
            }
        }


    }
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        float glX = (float)(x * 2) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
        float glY = 1.0 - (float)(y * 2) / glutGet(GLUT_WINDOW_HEIGHT);
        if (buttonN == true) {
            new_points.push_back({ glX, glY });
            std::cout << new_points[new_points.size() - 1] << ", ";
        }
        else {
            points.push_back({ glX, glY });
            std::cout << points[points.size() - 1] << ", ";
        }
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    std::string str;
    std::string colors;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Image Display");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboardFunc);
    glEnable(GL_TEXTURE_2D);

    loadTexture("C:/Users/Misha/Documents/GitHub/misis2023f-22-01-Trufmanov-M-A/prj.cw/example_im.jpg");

    glutMainLoop();
    return 0;
}
