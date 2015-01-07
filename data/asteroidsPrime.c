#include <stdio.h>
#include <math.h>
#include "gfx3.h"
#include <time.h>
#include <stdlib.h>

static int XSIZE = 800;
static int YSIZE = 800;
static int LARGE = 80;
static int MEDIUM = 40;
static int SMALL = 20;
static int L_SPEED = 5;

typedef struct Asteroids
{
  float xpos;
  float ypos;
  int r;
  float speed;
  float angle; 
  struct Asteroids *next;
}Asteroid;

void update_asteroids(Asteroid *);

int main()
{
  char c;
  srand(time(NULL));
  Asteroid *head = NULL, *p = NULL, *tail;
  int numAsteroids = 1, i;
  for(i=0;i<numAsteroids;i++)
  {
    p = (Asteroid *) malloc(sizeof(Asteroid));
    if(!head) head = tail = p;
    p->xpos = rand()%(XSIZE+1);
    p->ypos = rand()%(YSIZE+1);
    p->speed = L_SPEED;
    p->angle = ((float)rand()/(float)(RAND_MAX)*2*M_PI);
    p->r = LARGE;
    tail->next = p;
    tail = p;
    tail->next = NULL;
  }
/*  while(p)
  {
    printf("xpos: %d    ypos: %d    radius: %d    speed:  %f    angle:  %f\n",p->xpos,p->ypos,p->r,p->speed,p->angle);
    p=p->next;
  }
*/
  gfx_open(XSIZE,YSIZE,"Asteroids");
while(c!='q')
{
  p = head;
  gfx_clear();
  while(p)
  {
    gfx_circle(p->xpos,p->ypos,p->r);
    p=p->next;
  }
  gfx_flush();
  usleep(10000);
  c = 'z';
  if(gfx_event_waiting())
  {
    c = gfx_wait();
  }
  update_asteroids(head);
}
}

void update_asteroids(Asteroid *p)
{
  while(p)
  {
    p->xpos = p->xpos + p->speed * sin(p->angle);
    p->ypos = p->ypos - p->speed * cos(p->angle);
    if(p->xpos>XSIZE+p->r) p->xpos=0-p->r;
    if(p->xpos<0-p->r) p->xpos=XSIZE+p->r;
    if(p->ypos>YSIZE+p->r) p->ypos=0-p->r;
    if(p->ypos<0-p->r) p->ypos=YSIZE+p->r;
    p=p->next;
  }
}
