#ifndef TEXT_H
#define TEXT_H

#include <gl\gl.h>                        // Header File For The OpenGL32 Library
#include <gl\glu.h>                       // Header File For The GLu32 Library
#include <glut.h>
#include <string>
#include <sstream>


using namespace std;

class Text
{
    public:
        Text();
        string convertInt(float number);
        void writeGlut(string text, int x, int y);
    protected:
    private:
};

#endif // TEXT_H
