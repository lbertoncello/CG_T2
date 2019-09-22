#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "draw.h"
#include "tinyxml.h"

using namespace std;

const string config_base_filename = "/config.xml";
string arenaFilename;
float speedMult;

string window_title;
int window_size_x = 1000;
int window_size_y = 1000;
int window_initial_x_position = 100;
int window_initial_y_position = 100;

Color circleDefaultColor;
Color circleModelDefaultColor;
Color circleModelOverlapColor;
Color backgroundColor;

bool isLeftMouseButtonPressed = false;
bool isRightMouseButtonPressed = false;

Draw draw;

void circleInit(TiXmlElement *application)
{
    TiXmlElement *circle = application->FirstChildElement("circulo");
    TiXmlAttribute *circleAttribute = circle->FirstAttribute();

    while (circleAttribute)
    {
        if (strcmp(circleAttribute->Name(), "raio") == 0)
        {
            draw.setRadius(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corR") == 0)
        {
            circleDefaultColor.setR(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corG") == 0)
        {
            circleDefaultColor.setG(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corB") == 0)
        {
            circleDefaultColor.setB(stof(circleAttribute->Value()));
        }

        circleAttribute = circleAttribute->Next();
    }
}

void circleModelInit(TiXmlElement *application)
{
    TiXmlElement *circle = application->FirstChildElement("circuloModelo");
    TiXmlAttribute *circleAttribute = circle->FirstAttribute();

    while (circleAttribute)
    {
        if (strcmp(circleAttribute->Name(), "raio") == 0)
        {
            draw.setRadius(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corR") == 0)
        {
            circleModelDefaultColor.setR(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corG") == 0)
        {
            circleModelDefaultColor.setG(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corB") == 0)
        {
            circleModelDefaultColor.setB(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corSobreposicaoR") == 0)
        {
            circleModelOverlapColor.setR(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corSobreposicaoG") == 0)
        {
            circleModelOverlapColor.setG(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corSobreposicaoB") == 0)
        {
            circleModelOverlapColor.setB(stof(circleAttribute->Value()));
        }

        circleAttribute = circleAttribute->Next();
    }
}

void dimensionInit(TiXmlElement *window)
{
    TiXmlElement *dimension = window->FirstChildElement("dimensao");
    TiXmlAttribute *dimensionAttribute = dimension->FirstAttribute();

    while (dimensionAttribute)
    {
        if (strcmp(dimensionAttribute->Name(), "largura") == 0)
        {
            window_size_x = stof(dimensionAttribute->Value());
        }
        else if (strcmp(dimensionAttribute->Name(), "altura") == 0)
        {
            window_size_y = stof(dimensionAttribute->Value());
        }

        dimensionAttribute = dimensionAttribute->Next();
    }
}

void backgroundInit(TiXmlElement *window)
{
    TiXmlElement *background = window->FirstChildElement("fundo");
    TiXmlAttribute *backgroundAttribute = background->FirstAttribute();

    while (backgroundAttribute)
    {
        if (strcmp(backgroundAttribute->Name(), "corR") == 0)
        {
            backgroundColor.setR(stof(backgroundAttribute->Value()));
        }
        else if (strcmp(backgroundAttribute->Name(), "corG") == 0)
        {
            backgroundColor.setG(stof(backgroundAttribute->Value()));
        }
        else if (strcmp(backgroundAttribute->Name(), "corB") == 0)
        {
            backgroundColor.setB(stof(backgroundAttribute->Value()));
        }

        backgroundAttribute = backgroundAttribute->Next();
    }
}

void titleInit(TiXmlElement *window)
{
    TiXmlElement *title = window->FirstChildElement("titulo");

    window_title = title->GetText();
}

void windowInit(TiXmlElement *application)
{
    TiXmlElement *window = application->FirstChildElement("janela");

    dimensionInit(window);
    backgroundInit(window);
    titleInit(window);
}

void arenaInit(TiXmlElement *application)
{
    TiXmlElement *arquivoArena = application->FirstChildElement("arquivoDaArena");
    string filename = arquivoArena->FirstChildElement("nome")->GetText();
    string format = arquivoArena->FirstChildElement("tipo")->GetText();
    string path = arquivoArena->FirstChildElement("caminho")->GetText();

    arenaFilename = path + "/" + filename + "." + format;
}

void jogadorInit(TiXmlElement *application)
{
    TiXmlElement *jogador = application->FirstChildElement("jogador");
    TiXmlAttribute *jogadorAttribute = jogador->FirstAttribute();

    while (jogadorAttribute)
    {
        if (strcmp(jogadorAttribute->Name(), "vel") == 0)
        {
            speedMult = stof(jogadorAttribute->Value());
        }

        jogadorAttribute = jogadorAttribute->Next();
    }
}

bool parametersInit(const char *filename)
{
    TiXmlDocument doc(filename);
    bool loadOkay = doc.LoadFile();

    if (loadOkay)
    {
        TiXmlElement *application = doc.RootElement();

        arenaInit(application);
        jogadorInit(application);

        return true;
    }
    else
    {
        cout << "Failed to load file" << endl;

        return false;
    }
}

void display(void)
{
    /* Limpar todos os pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    draw.drawAllCircles();

    /* Não esperar */
    glFlush();
}

void idle(void)
{
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            isLeftMouseButtonPressed = false;
            draw.updateCurrentCenter(x, y, window_size_x, window_size_y);

            Circle circle(draw.getCurrentCenter().getX(), draw.getCurrentCenter().getY(), draw.getRadius());

            if (draw.checkIntersection(circle) == false)
            {
                draw.addCircle(circle);
            }
        }
        else
        {
            isLeftMouseButtonPressed = true;
        }
    }

    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            isRightMouseButtonPressed = false;
            draw.setCurrentCircleMoving(NULL);
        }
        else
        {
            draw.chooseCircleToMove();

            isRightMouseButtonPressed = true;
        }
    }
}

void motion(int x, int y)
{
    if (isLeftMouseButtonPressed)
    {
        draw.updateCurrentCenter(x, y, window_size_x, window_size_y);
    }

    if (isRightMouseButtonPressed)
    {
        draw.updateCurrentCenter(x, y, window_size_x, window_size_y);
    }
}

void passiveMotion(int x, int y)
{
    draw.updateCurrentCenter(x, y, window_size_x, window_size_y);
}

void init(void)
{
    glClearColor(backgroundColor.getR(), backgroundColor.getG(), backgroundColor.getB(), 0.0);

    /* Inicializa sistema de viz */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

//    glOrtho(0, window_size_x, 0, window_size_y, -1, 1);
    glOrtho(200, 800, 200, 800, -1, 1);
}

void readCircle(TiXmlElement *circle)
{
    TiXmlAttribute *circleAttribute = circle->FirstAttribute();
    Circle _circle;

    while (circleAttribute)
    {
        if (strcmp(circleAttribute->Name(), "cx") == 0)
        {
            _circle.setCenter_x(stof(circleAttribute->Value()));
        } else if (strcmp(circleAttribute->Name(), "cy") == 0)
        {
            _circle.setCenter_y(stof(circleAttribute->Value()));
        } else if (strcmp(circleAttribute->Name(), "r") == 0)
        {
            _circle.setRadius(stof(circleAttribute->Value()));
        } else if (strcmp(circleAttribute->Name(), "fill") == 0)
        {
            _circle.setColor(Color(circleAttribute->Value()));

            cout << circleAttribute->Value()  << endl;

            if(circleAttribute->Value() == string("blue")) {
                _circle.setMainCircle(true);
            } else if(circleAttribute->Value() == string("orange")) {
                _circle.setTerrestrial(true);
            }
        } else if (strcmp(circleAttribute->Name(), "id") == 0)
        {
            _circle.setId(stoi(circleAttribute->Value()));
        }

        circleAttribute = circleAttribute->Next();
    }

    if(_circle.isMainCircle()) {
        window_size_x = 2 * _circle.getRadius();
        window_size_y = 2 * _circle.getRadius();
    }

    draw.addCircle(_circle);
}

void readLine(TiXmlElement *line)
{
    TiXmlAttribute *lineAttribute = line->FirstAttribute();

    while (lineAttribute)
    {
        if (strcmp(lineAttribute->Name(), "x1") == 0)
        {
            cout << "x1: " << stof(lineAttribute->Value()) << endl;
        }

        lineAttribute = lineAttribute->Next();
    }
}

bool readArenaFile()
{
    TiXmlDocument doc(arenaFilename.c_str());
    bool loadOkay = doc.LoadFile();

    if (loadOkay)
    {
        //TiXmlElement *arenaDescription = doc.RootElement();
        TiXmlNode *arenaDescription = doc.FirstChildElement("svg");

        TiXmlElement *element = arenaDescription->FirstChildElement();

        for (element; element; element = element->NextSiblingElement())
        {
            if (element->ValueTStr() == "circle")
            {
                cout << "circle" << endl;
                readCircle(element);
            }
            else if (element->ValueTStr() == "line")
            {
                cout << "line" << endl;
                readLine(element);
            }
        }

        return true;
    }
    else
    {
        cout << "Failed to load file" << endl;

        return false;
    }
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        string filename = argv[1] + config_base_filename;

        if (parametersInit(filename.c_str()))
        {
            if (readArenaFile())
            {
                cout << "Filename: " << arenaFilename << endl;
                cout << "Mult: " << speedMult << endl;

                glutInit(&argc, argv);
                glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
                glutInitWindowSize(window_size_x, window_size_y);
                glutInitWindowPosition(window_initial_x_position, window_initial_y_position);
                glutCreateWindow(window_title.c_str());
                init();
                glutDisplayFunc(display);

                //glutMouseFunc(mouse);
                //glutMotionFunc(motion);
                //glutPassiveMotionFunc(passiveMotion);

                glutIdleFunc(idle);
                glutMainLoop();

                return 0;
            }
            else
            {
                cout << "Erro ao carregar os dados da arena." << endl;

                return 1;
            }
        }
    }
    else
    {
        cout << "Voce deve passar como parametro o diretorio de arquivo config.xml" << endl;

        return 1;
    }
}