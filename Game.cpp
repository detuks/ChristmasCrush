#include "Game.h"

Game::Game()
{
    isRunning = true;
    arrowKeys = 0;
    focusPlayer = false;
}

void Game::init()
{
    printf("Spele sakas\n");

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_WM_SetCaption("ChristmasCrusher",NULL);

    SDL_SetVideoMode(width,height,32,SDL_OPENGL);

    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,width,height,1.0,-1.0,1.0);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setupGame();
}

void Game::setupGame()
{
    objLoad.loadObject("levels/Level1.chcr",&obstacles,&mobs,&startX,&startY);

    player.update(0,0);
    ///load Objects
   //gameMap.loadModel("img/MapSurface.png");
    player.loadModel("img/CuckBlocker.png");
    //evilPing.loadModel("img/evilPingM.png");
    ammoUsing.loadModel("img/ammo_iceBall.png");
    //obst.loadModel("img/IceCubes.png");
    explode.loadModel("img/ammo_iceBallBum.png");
    ammoUsing.setExplodeModel(explode.getModelID());

    player.setAmmoType(&ammoUsing);
    //evilPing.update(50,50);
    //obst.update(100,100);
    //obst.updateColVec();
    //gameMap.updateColVec();
    //gameMap.obstacles.push_back(&obst);
    //camera.setFocusAt(&evilPing);
}

void Game::start()
{
    init();

    while(isRunning)
    {
        startTime = SDL_GetTicks();
        ///reading input
        while( SDL_PollEvent(&event) )
        {
            readKeyPress(&event);
        }
        update();

        ///rendering
        render();

        SDL_GL_SwapBuffers();
        //fix fps
        if(1000/60>(SDL_GetTicks()-startTime))
            SDL_Delay(1000/60-(SDL_GetTicks()-startTime));
    }
    SDL_Quit();
}

void Game::update()
{
    ///Camera
    camera.update();
    if((arrowKeys & 1) == 1)
        camera.update(0,5);
    if((arrowKeys & 2) == 2)
        camera.update(PI,5);
    if((arrowKeys & 4) == 4)
        camera.update(PI/2,5);
    if((arrowKeys & 8) == 8)
        camera.update(-PI/2,5);
    ///padod koordianta uz kuram jaskatas speletaja aktierim
    player.setPitch(camera.mX-camera.pos.x,camera.mY-camera.pos.y);

    ///Actors

   // disc = obst.lineToCircle(obst.c1,obst.c2,player.pos,20);
    //disc = obst.dist_Point_to_Line(player.pos,obst.c1,obst.c2);
    player.updatePos();

    /// collision
    for (std::vector<Obstacle*>::iterator it = obstacles.begin() ; it != obstacles.end(); ++it)
    {
        Obstacle* ob = *it;
        ob->collision(&player,20);
        for (std::vector<Ammo>::iterator it2 = player.ammo.begin() ; it2 != player.ammo.end();)
        {
            Ammo ac = *it2;
            if(ob->collision(&ac,5))
            {
                it2->explode();
            }
            ++it2;
        }

    }

    if(focusPlayer)
        camera.setFocusAt(&player);

}



void Game::render()
{

    glClear(GL_COLOR_BUFFER_BIT);
    ///zime objektus
    for (std::vector<Obstacle*>::iterator it = obstacles.begin() ; it != obstacles.end(); ++it)
    {
        Obstacle* ob = *it;
        ob->render();
    }
    ///zime monstrikus
    for (std::vector<Mob*>::iterator it = mobs.begin() ; it != mobs.end(); ++it)
    {
        Mob* mob = *it;
        mob->render();
    }



    ///zimet mapi UNDER CONSTRUCTION
    //gameMap.render();
    ///Obstacles render
    //obst.render();


    ///zimet speletaju
   // evilPing.render();
    player.render();


    debug();
}

void Game::readKeyPress(SDL_Event *event)
{
    //ja uzklikskina "x"
    if( event->type == SDL_QUIT)
    {
        isRunning = false;
    }
    //escape
    if( event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_ESCAPE )
    {
        isRunning = false;
    }

    if( event->type == SDL_KEYDOWN  )
    {
        ///iesledz debug
        if(event->key.keysym.sym == SDLK_F2)
        {
            debugMode =(debugMode==true ? false : true);
            //isRunning = false;
        }
        if(event->key.keysym.sym == SDLK_LEFT) //1
        {
            arrowKeys+=1;
        }
        if(event->key.keysym.sym == SDLK_RIGHT) //2
        {
            arrowKeys+=2;
        }
        if(event->key.keysym.sym == SDLK_UP) // 4
        {
            arrowKeys+=4;
        }
        if(event->key.keysym.sym == SDLK_DOWN) // 8
        {
            arrowKeys+=8;
        }
        if(event->key.keysym.sym == SDLK_SPACE) // 8
        {
            focusPlayer = true;
        }

    }
    else if( event->type == SDL_KEYUP  )
    {
        if(event->key.keysym.sym == SDLK_LEFT) //1
        {
            arrowKeys-=1;
        }
        if(event->key.keysym.sym == SDLK_RIGHT) //2
        {
            arrowKeys-=2;
        }
        if(event->key.keysym.sym == SDLK_UP) // 4
        {
            arrowKeys-=4;
        }
        if(event->key.keysym.sym == SDLK_DOWN) // 8
        {
            arrowKeys-=8;
        }
        if(event->key.keysym.sym == SDLK_SPACE) // 8
        {
            focusPlayer = false;
        }
    }
    if(event->type == SDL_MOUSEBUTTONDOWN)
    {
        player.shootAmmo();
    }
}

void Game::debug()
{
    if(!debugMode)
        return;
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glOrtho(0,width,height,0,-1,1);//set matrix
    text.writeGlut("DEBUG: col: "+text.convertInt(float(obstacles.size()))+" : " +  text.convertInt(float(startX))+ " : " + text.convertInt(float(startY) ),100,20);
    text.writeGlut("DEBUG:mouse screen " + text.convertInt(float(camera.mX - camera.pos.x))+ " : " + text.convertInt(float(camera.mY - camera.pos.y) ),100,50);
    text.writeGlut("DEBUG:camera " + text.convertInt(float(camera.pos.x))+ " : " + text.convertInt(float(camera.pos.y) ),100,80);
    text.writeGlut("DEBUG:player screeen " + text.convertInt(float(player.pos.x))+ " : " + text.convertInt(float(player.pos.y) ),100,110);
    text.writeGlut("DEBUG:player pitch " + text.convertInt(float(player.pitch)) ,100,150);
    glPopMatrix();
}


void Game::stop()
{
    isRunning =false;
}

