#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <iomanip>

using json = nlohmann::json;

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

int orientation(const Point& p, const Point& q, const Point& r) {
    float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or counterclockwise
}

bool isCounterclockwise(const std::vector<Point>& poly) {
    int n = poly.size();
    if (n < 3) return true; // Not enough points

    int o = orientation(poly[0], poly[1], poly[2]);

    for (int i = 1; i < n - 1; i++) {
        int currentOrientation = orientation(poly[i], poly[i + 1], poly[0]);

        if (currentOrientation != o) return false;
    }

    return true;
}

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

    if (!buttonN && get_size_with_1(points) + 1 > 2) {
        glBegin(GL_POLYGON);
        glColor4f(1.0, 1.0, 1.0, 0.5);
        if (!isCounterclockwise(points)) {
            for (auto it = points.rbegin(); it != points.rend(); ++it) {
                glVertex2f(it->x, it->y);
            }
        } else {
            for (const Point& p : points) {
                glVertex2f(p.x, p.y);
            }
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

void savePointsToJson(const std::vector<Point>& points, const std::string& filename) {
    json jsonPoints;

    for (const Point& p : points) {
        jsonPoints.push_back({ {"x", p.x}, {"y", p.y} });
    }

    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cout << "Error opening the file!" << std::endl;
    }
    else {
        outputFile << std::setw(4) << jsonPoints;
    }
}

void loadPointsFromJson(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cout << "Error opening the file!" << std::endl;
    }
    else {
        json jsonPoints;
        inputFile >> jsonPoints;

        points.clear();
        for (const auto& point : jsonPoints) {
            points.push_back({ point["x"], point["y"] });
        }

        glutPostRedisplay();
    }
}

void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
    case 'n':
        buttonN = true;
        std::cout << "New";
        glutPostRedisplay();
        break;

    case 'd':
        points.clear();
        glutPostRedisplay();
        break;

    case 'z':
        if (!points.empty()) {
            Point last_symbol = points[get_size_with_1(points)];
            points.pop_back();
            cancel_points.push_back(last_symbol);
            glutPostRedisplay();
        }
        break;

    case 'y':
        if (!cancel_points.empty()) {
            points.push_back(cancel_points.back());
            cancel_points.pop_back();
        }
        glutPostRedisplay();
        break;

    case 's':
        savePointsToJson(points, "C:/Users/Misha/Documents/GitHub/misis2023f-22-01-Trufmanov-M-A/prj.cw/res/test_output.json");
        break;
    case 'o':
        loadPointsFromJson("C:/Users/Misha/Documents/GitHub/misis2023f-22-01-Trufmanov-M-A/prj.cw/res/test_output.json");
        break;
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

            if (!isCounterclockwise(points)) {
                std::reverse(points.begin(), points.end());
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

    loadTexture("C:/Users/Misha/Documents/GitHub/misis2023f-22-01-Trufmanov-M-A/prj.cw/res/example_im.jpg");

    glutMainLoop();
    return 0;
}
