#include "ObjectLoader.h"

ObjectLoader::ObjectLoader()
{
    //ctor
}


void ObjectLoader::loadObject(const char* filename, std::vector<Obstacle*> *obstacles, std::vector<Mob*> *mobs, float *sx,float *sy)
{

     printf("Sakam ielasit limena informaciju\n");
    std::ifstream in(filename);
    if(!in.is_open())
    {
        printf("Neizdevas ieladet limeni\n");
        return;
    }
    char buf[256];/// temp saglabasana

    while(!in.eof())
    {
        in.getline(buf,256);	//while we are not in the end of the file, read everything as a string to the coord vector
        coord.push_back(new std::string(buf));
        printf("%s\n",buf);
    }
    printf("faila liniju skaits: %d\n", coord.size());
    for(int i=0; i<coord.size(); i++)/// izejam cauru visam rindam no objekta faila
    {


        if((*coord[i])[0]=='#')
            continue;///komentarus izlaizam
        if((*coord[i])[0]=='c')
        {
            float x,y;
            scanf((*coord[i]).c_str(),"c %f %f",sx,sy);
            sx=0;
            sy=0;
        }
        if(((*coord[i])[0]=='l'))///bilde
        {

            if(((*coord[i])[1]=='m') && ((*coord[i])[2]=='i') )
            {
                char  bildesNosk[200];
                sscanf(coord[i]->c_str(),"lmi %s",bildesNosk);
                gameMap.loadModel(bildesNosk);
                gameMap.updateColVec();
                obstacles->push_back(&gameMap);
                printf("--Ieladeja mapi!\n");
            }
            if(((*coord[i])[1]=='m') && ((*coord[i])[2]=='1') )
            {
                char  bildesNosk[200];
                sscanf(coord[i]->c_str(),"lm1 %s",bildesNosk);
                printf("bilde: %s",bildesNosk);
                evilPing.loadModel(bildesNosk);
            }
            if(((*coord[i])[1]=='m') && ((*coord[i])[2]=='2') )
            {
                char  bildesNosk[200];
                sscanf(coord[i]->c_str(),"lm2 %s",bildesNosk);
                evilPingM.loadModel(bildesNosk);
            }
            if(((*coord[i])[1]=='b') && ((*coord[i])[2]=='1') )
            {
                char  bildesNosk[200];
                sscanf(coord[i]->c_str(),"lb1 %s",bildesNosk);
                block1.loadModel(bildesNosk);
                //obstacles->push_back(&block1);
            }
            if(((*coord[i])[1]=='b') && ((*coord[i])[2]=='2') )
            {
                char  bildesNosk[200];
                sscanf(coord[i]->c_str(),"lb2 %s",bildesNosk);
                block2.loadModel(bildesNosk);
            }

            //temp(bildesNosk);
        }
        if(((*coord[i])[0]=='b'))///bloki
        {
            if(((*coord[i])[1]=='1'))
            {
                float x,y,pitch;
                Obstacle block;
                sscanf(coord[i]->c_str(),"b1 %f %f %f",&x,&y,&pitch);
                bl[obCount].width = block1.width;
                bl[obCount].height = block1.height;
                bl[obCount].setModelID(block1.getModelID());
                bl[obCount].update(x,y);
                bl[obCount].pitch = pitch;
                bl[obCount].updateColVec();
                //printf("block x %d y %d mod %d\n",x,y,bl1.getModelID());
               // printf("whaat: %s\n",coord[i]->c_str());

                obstacles->push_back(&bl[obCount]);
                obCount++;
            }
            if(((*coord[i])[1]=='2'))
            {
                float x,y,pitch;
                sscanf(coord[i]->c_str(),"b2 %f %f %f",&x,&y,&pitch);
                bl[obCount].width = block2.width;
                bl[obCount].height = block2.height;
                bl[obCount].setModelID(block2.getModelID());
                bl[obCount].update(x,y);
                bl[obCount].pitch = pitch;
                bl[obCount].updateColVec();
                obstacles->push_back(&bl[obCount]);
                obCount++;
            }
        }

    }
}

unsigned int ObjectLoader::loadTexture(const char* filename)
{
    SDL_Surface* img=IMG_Load(filename);
    SDL_PixelFormat form= {NULL,32,4,0,0,0,0,8,8,8,8,0xff000000,0x00ff0000,0x0000ff00,0x000000ff,0,255};
    SDL_Surface* img2=SDL_ConvertSurface(img,&form,SDL_SWSURFACE);
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2->w,img2->h,0,GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,img2->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    SDL_FreeSurface(img);
    SDL_FreeSurface(img2);
    return texture;
}
