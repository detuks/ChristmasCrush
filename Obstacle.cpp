#include "Obstacle.h"

Obstacle::Obstacle()
{
    updateColVec();
}


void Obstacle::updateColVec()
{
    ///ok look
    c1.x=pos.x+(width/2)*cos(pitch-PI)-(height/2)*sin(pitch-PI);
    c1.y=pos.y+(width/2)*sin(pitch-PI)+(height/2)*cos(pitch-PI);

    c2.x=pos.x+(width/2)*cos(pitch-PI)+(height/2)*sin(pitch-PI);
    c2.y=pos.y+(width/2)*sin(pitch-PI)-(height/2)*cos(pitch-PI);

    c3.x=pos.x-(width/2)*cos(pitch-PI)+(height/2)*sin(pitch-PI);
    c3.y=pos.y-(width/2)*sin(pitch-PI)-(height/2)*cos(pitch-PI);

    c4.x=pos.x-(width/2)*cos(pitch-PI)-(height/2)*sin(pitch-PI);
    c4.y=pos.y-(width/2)*sin(pitch-PI)+(height/2)*cos(pitch-PI);
}


void Obstacle::render()
{
     glPushMatrix();
    glTranslatef(pos.x,pos.y,0);

    glRotatef((pitch*radToDeg),0,0,1);

    glCallList(getModelID());

    glPopMatrix();

    ///Collision debug
   /* glPointSize(5.0);
    glBegin(GL_POINT);
        glVertex2f(c1.x,c1.y);
    glEnd();*/

}

bool Obstacle::collision(Actor *act, float radius)
{
    if(lineToCircle(c1,c2,act->pos,radius) || lineToCircle(c2,c3,act->pos,radius)
        || lineToCircle(c3,c4,act->pos,radius) || lineToCircle(c4,c1,act->pos,radius))
    {
        act->pos = act->oldPos;

        return true;
    }
    return false;
}

float Obstacle::lineToCircle(Vec2 p1, Vec2 p2,
                              Vec2 cp, float r)
{
    float m;
    if(p2.x!=p1.x)
        m = (p2.y-p1.y)/(p2.x-p1.x);
    else
        m=p2.x;
    float b = p1.y-m*p1.x;
    float r2 = r*r;
    float b2 = b*b;
    float m2= m*m;
    float u2 = cp.x*cp.x;
    float v2 = cp.y*cp.y;
    float u = cp.x;
    float v = cp.y;


    float d = -b2+r2+m2*r2-2*b*m*u -m2*u2+2*b*v+2*m*u*v-v2;

    if(d >= 0)
    {
         Vec2 vekt = p2-p1;
        float halfLen = (vekt.x*vekt.x+vekt.y*vekt.y)/4+r*r;

        Vec2 mid((p1.x+p2.x)/2,(p1.y+p2.y)/2);
        float dist = (cp.x-mid.x)*(cp.x-mid.x)+(mid.y-cp.y)*(mid.y-cp.y);
        if(dist < halfLen)
        {
            float pen = ((p1.y-p2.y)*cp.x + (p2.y-p1.x)*cp.y+(p1.x*p2.y -p2.x*p1.y))/(vekt.x*vekt.x+vekt.y*vekt.y);
            return pen;
        }

    }
    return 0;
}

float Obstacle::dist_Point_to_Line( Vec2 p, Vec2 l1, Vec2 l2)
{
     Vec2 v = l1 - l2;
     Vec2 w = p - l1;

     double c1 = w.dotProduct(v); ///dot(w,v);
     double c2 = v.dotProduct(v); ///dot(v,v);
     double b = c1 / c2;

     Vec2 pb = l1 + v*b;
     return sqrtf((p.x-pb.x)*(p.x-pb.x)+(pb.y-p.y)*(pb.y-p.y));
}
