#include <stdio.h>
#include <math.h>
#include "gfx3.h"
#include "asteroidsTfn.h"
#include <time.h>
#include <stdlib.h>

static int XSIZE = 800;
static int YSIZE = 800;
static int LARGE = 80;
static int MEDIUM = 40;
static int SMALL = 20;
static int L_SPEED = 5;


int main()
{
  // initializations
  srand(time(NULL));					// seed random number generator with time
  Ship ship, *pship = &ship;				// A ship objects named ship and a pointer to that ship
  Bullet *bhead = NULL, *b = NULL, *btail;
  int lives=3;
  int score = 0;					// score counter. Starts at 0
  int isdrawn = 1;
  char c;						// char variable for choice of user
  Asteroid *head, *p;					// Pointers to Asteroid struct. head (head pointer) p (for iteration)
  int numAsteroids = 2;					// numAsteroids = determined by level
  //creation of linked list of asteroids
  head = init_asteroids(numAsteroids);			// initialize linked list of Asteroids
  init_ship(pship,lives);						// initialize a ship
  update_ship(pship,M_PI/10,1);				//hack fix for bug. don't worry about it
  update_ship(pship,-M_PI/10,1);

  gfx_open(XSIZE,YSIZE,"Asteroids");
  c = menu();						// displays the menu, returns either q, p, or i
  while(c!='q')
  {
    gfx_clear();
    p = head;						// resets the pointer to the beginning of the linked list

    //draw functions
    if(isdrawn==1){
      draw_ship(pship);
    }
    if(pship->inv%5==1 && pship->inv!=0)
    {
      if(isdrawn) isdrawn = 0;
      else isdrawn = 1;
    }
    if(pship->inv==0) isdrawn=1;
    draw_bullet(bhead);
    draw_asteroids(head);
    draw_score(score);
    draw_lives(pship);
    gfx_flush();

    //update functions
    update_ship(pship,0,.993); 			 //update_ship() when outside of if(event_waiting) is only responsible for decelerating the ship
    update_bullets(&bhead);
    update_asteroids(head);				// updates the position of each asteroid

    usleep(20000);

    //collision detection
    head = detect_collision(head,pship->xnose,pship->ynose,&score,&lives,pship);
    head = detect_collision(head,pship->xwing1,pship->ywing1,&score,&lives,pship);
    head = detect_collision(head,pship->xwing2,pship->ywing2,&score,&lives,pship);
    if(!head)
    {
      printf("Waiting");
      gfx_wait();
    }
    if(pship->lives==0)
    {
//            return 0;
      c = end_screen(score); //ends game

    }


    if(gfx_event_waiting())
    {
      c = gfx_wait(); //wait for event

      switch(c){
	case 'R':  				//up arrow
	  pship->speed=4;  				//the ship instantaneously has a v of 3
	  update_ship(pship,0,1.1);  		//ship is updated immediately
	  break;
	case 'Q':
	  update_ship(pship,M_PI/10,1);		//left arrow
	  break;				//the ship stops accelerating forward and rotates a set angle
	case 'S':
	  update_ship(pship,-M_PI/10,1);		//right arrow
	  break;				//the ship stops accelerating forward and rotates a set angle
	case ' ':
	  bhead = init_bullet(bhead, pship);	//when the player shoots, a new node is created
	  break;
      }
    }
  }
}
