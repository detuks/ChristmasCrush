#include "Actor.h"

Actor::Actor()
{
    pitch =0;
}

void Actor::loadModel(const char* fileName)
{
    setTexture(loadTexture(fileName,width,height));

    modelID=glGenLists(1);	//I generate a unique identifier for the list
    glNewList(modelID,GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D,getTexture());
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
		glVertex2f(-width/2,-height/2);
		glTexCoord2f(1,0);
		glVertex2f(width/2,-height/2);
		glTexCoord2f(1,1);
		glVertex2f(width/2,height/2);
		glTexCoord2f(0,1);
		glVertex2f(-width/2,height/2);
    glEnd();

    glEndList();
}

void Actor::update(float xc,float yc)
{
    pos.x=xc;
    pos.y=yc;
}

void Actor::setTexture(int tex)
{
    texture = tex;
}

int Actor::getTexture()
{
    return texture;
}


void Actor::setModelID(int id)
{
    modelID = id;
}
int Actor::getModelID()
{
    return modelID;
}

unsigned int Actor::loadTexture(const char* filename,int &w,int &h)
{
    printf("loading image %s\n",filename);
    SDL_Surface* img=IMG_Load(filename);

    SDL_PixelFormat form= {NULL,32,4,0,0,0,0,8,8,8,8,0xff000000,0x00ff0000,0x0000ff00,0x000000ff,0,255};

    SDL_Surface* img2=SDL_ConvertSurface(img,&form,SDL_SWSURFACE);

    unsigned int texture;

    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    w=img2->w;
    h=img2->h;
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2->w,img2->h,0,GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,img2->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    SDL_FreeSurface(img);
    SDL_FreeSurface(img2);
    if(texture == 0)
        printf("Failed loading texture! \n");

    printf("loaded image %s\n",filename);
    return texture;
}
