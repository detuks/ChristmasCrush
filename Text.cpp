#include "Text.h"

Text::Text()
{
    //ctor
}

string Text::convertInt(float number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

void Text::writeGlut(string text, int x, int y){
    glRasterPos2i(x,y);

    for(int i = 0; i < text.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text.data()[i]);
    }
}
