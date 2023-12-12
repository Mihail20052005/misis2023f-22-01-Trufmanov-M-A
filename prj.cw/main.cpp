#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>


bool buttonPressed = false;
bool button1 = false;
bool buttonN = false;
bool isRightMouseButtonPressed = false;
int draggedPointIndex = -1;
double point_size;

struct Point {
    float x, y;
};

int get_size_with_1(const std::vector<Point>& points) {
    return static_cast<int>(points.size()) - 1;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

std::fstream& operator<<(std::fstream& fs, const Point& point) {
    fs << "(" << point.x << ", " << point.y << ")";
    return fs;
}

GLuint textureID;
std::vector<Point> points;
std::vector<Point> new_points;
std::vector<Point> cancel_points;

void display() {
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0, -1.0);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0, -1.0);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0, 1.0);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0, 1.0);
    glEnd();

    glPointSize(point_size);


    glColor3f(1.0, 1.0, 0.0);

    
    glBegin(GL_POINTS);
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

    if (!buttonN) {
        glBegin(GL_POLYGON);
        glColor4f(1.0, 1.0, 1.0, 0.5);
        for (const Point& p : points) {
            glVertex2f(p.x, p.y);
        }
        glEnd();
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    if (buttonN || !buttonN) {
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
            glVertex2f(new_points.back().x, new_points.back().y);
            glVertex2f(new_points.front().x, new_points.front().y);
        }
        glEnd();

        glBegin(GL_POLYGON);
        glColor4f(1.0, 1.0, 1.0, 0.5); 
        for (const Point& p : new_points) {
            glVertex2f(p.x, p.y);
        }
        glEnd();
    }

    glDisable(GL_BLEND);
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
        if (!points.empty()) {
            Point last_symbol = points[get_size_with_1(points)];
            points.pop_back();
            cancel_points.push_back(last_symbol);
        }
        glutPostRedisplay();
    }

    if (key == 'y') {
        if (!cancel_points.empty()) {
            points.push_back(cancel_points.back());
            cancel_points.pop_back();
        }
        glutPostRedisplay();
    }

    if (key == 's') {
        std::ofstream outputFile("C:/Users/Misha/Documents/GitHub/misis2023f-22-01-Trufmanov-M-A/prj.cw/test_output.txt");
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

        bool pointDeleted = false;

        if (buttonN) {
            for (size_t i = 0; i < new_points.size(); ++i) {
                float distance = sqrt(pow(glX - new_points[i].x, 2) + pow(glY - new_points[i].y, 2));
                if (distance < 0.05) {
                    new_points.erase(new_points.begin() + i);
                    pointDeleted = true;
                    break;
                }
            }
        }
        else {
            for (size_t i = 0; i < points.size(); ++i) {
                float distance = sqrt(pow(glX - points[i].x, 2) + pow(glY - points[i].y, 2));
                if (distance < 0.05) {
                    points.erase(points.begin() + i);
                    pointDeleted = true;
                    break;
                }
            }
        }

        if (!pointDeleted) {
            if (buttonN) {
                new_points.push_back({ glX, glY });
                std::cout << "New: " << new_points[new_points.size() - 1] << ", ";
            }
            else {
                points.push_back({ glX, glY });
                std::cout << "Points: " << points[points.size() - 1] << ", ";
            }
        }

        glutPostRedisplay();
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        float glX = (float)(x * 2) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
        float glY = 1.0 - (float)(y * 2) / glutGet(GLUT_WINDOW_HEIGHT);

        for (size_t i = 0; i < points.size(); ++i) {
            float distance = sqrt(pow(glX - points[i].x, 2) + pow(glY - points[i].y, 2));
            if (distance < 0.05) {
                isRightMouseButtonPressed = true;
                draggedPointIndex = i;
                break;
            }
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        isRightMouseButtonPressed = false;
        draggedPointIndex = -1;
    }
}

void mouseMotion(int x, int y) {
    if (isRightMouseButtonPressed && draggedPointIndex != -1) {
        float glX = (float)(x * 2) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
        float glY = 1.0 - (float)(y * 2) / glutGet(GLUT_WINDOW_HEIGHT);

        points[draggedPointIndex].x = glX;
        points[draggedPointIndex].y = glY;

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    std::string colors;
    std::cin >> point_size;
    std::cin >> colors;
    GLfloat color_r = 1.0f, color_g = 1.0f, color_b = 0.0f;

    color_r = float(colors[0]);
    color_g = float(colors[1]);
    color_b = float(colors[2]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Image Display");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboardFunc);
    glEnable(GL_TEXTURE_2D);

    loadTexture("C:/Users/Misha/Documents/GitHub/misis2023f-22-01-Trufmanov-M-A/prj.cw/example_im.jpg");

    glutMainLoop();
    return 0;
}