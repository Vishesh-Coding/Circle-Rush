#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>

#define ScWidth 1000
#define ScHeight 700

using namespace std;
 
int main(){
	// for unique random number generation
	srand((unsigned) time(0));
	
	int gd = DETECT, gm, err, tmp;
	initgraph( & gd, & gm, "C:\\tc\\bgi");
  
	// px-Player X, py-Player Y, pr-Player Radius, pStep-Player Step
	int px=350, py=515, pr=12, pStep=6;
	
	// bx-Bar X, by-Bar Y, bw-Bar Width, bh-Bar Height
	int bx=200, by=500, bw=300, bh=30;
	
	//enemy (x,y,type[enemy,fruit])
	int enemy[5][3]= { {ScWidth/2, 0, 0} };
	// ei-enemy index, eStep- enemy Step, eGap-enemy Gap, er-enemy radius
	int ei=1, eStep=4, eGap=0, er=12;
	
	char option, txtChances[5], txtScore[5];
	int chances = 0, score = 0;	
 	
	while(1){
		setcolor(WHITE);
		
		//Draw Board
		rectangle(0,0,ScWidth-300,ScHeight);
		rectangle(ScWidth-300,0,ScWidth,ScHeight);
		
		// printing chances
		settextstyle(4,0,3);
		outtextxy(ScWidth-220, 100, "Chances");
		settextstyle(4,0,7);
		outtextxy(ScWidth-180, 150, itoa(chances,txtChances,10)); 
		
		// printing score
		settextstyle(4,0,4);
		outtextxy(ScWidth-220, 300, "Score");
		settextstyle(4,0,7);
		
		// itoa function converts number to character array
		if( score<10 ) // if score is one digit 
			outtextxy(ScWidth-180, 370, itoa(score,txtScore,10));
		else if( score>=10 )// if score is more than one digit
			outtextxy(ScWidth-220, 370, itoa(score,txtScore,10));
		 
		
		//draw bar
		rectangle(bx,by,bx+bw,by+bh);
		
		if(kbhit()){ // if any key is pressed while playing
			option = getch(); // catch that character in options variable
			if(option == 32){ // if spacebar (code: 32) is pressed
				pStep = -pStep; // reverse ball direction
			}
		}
		
		// Draw Enemies
		for(int i=0; i<ei; i++){
			if( enemy[i][2] == 0 ){ // if type is enemey (code: 0) 
				setcolor(WHITE);
				setfillstyle(3,WHITE);
			}else if( enemy[i][2] == 1 ){  // if type is fruit (code: 1)
				setcolor(GREEN);
				setfillstyle(3,GREEN);
			}
			fillellipse(enemy[i][0], enemy[i][1], er, er);
			enemy[i][1] += eStep; // update enemy y position for enemy movement
			if(enemy[i][1]-er > by+bh){ // if enemy goes below bar
				enemy[i][0]=bx+rand()%bw; // generate enemy at random pos on x axis
				enemy[i][1]=0; // set inital enemy y pos to 0
				if(i==0)
					enemy[i][2]=1; // make every first enemy a fruit
			}
		}
		
		// Generate Enemies
		if( ei < 5 ){ // generate enemy only if they are less than 5
			enemy[ei][0] = bx+rand()%bw; // random enemy position at x axis
			enemy[ei][1] = 0; // 0 at y axis 
			enemy[ei][2] = 0; // type = enemy
			
			eGap = 100+rand()%200; // for random vertical gap between enemies
			if( enemy[ei-1][1] >= eGap )
				ei++; // create new enemy if last enemy moves to specific gap position
		}
		
		//Player Hit
		for(int i=0; i<ei; i++){
			if( enemy[i][1]+er >= py-pr ){ 
				if( px >= enemy[i][0]-er && px <= enemy[i][0]+er ){
					if( enemy[i][2] == 0 ){ // if type = enemy
						chances--; // decrease chances
						enemy[i][1] = 0; // reset enemy position
						if(chances <= 0){ // if chances are 0 or less
							cleardevice(); 
							
							settextstyle(4,0,4);
							outtextxy(300,200, "Game Over"); 
							
							//On Game over reset chances, score and Enemey Index
							chances = 3;
							score = 0;
							ei = 1;
							
							getch();
							break;
						}
					}
					else{ // If player hit fruit 
						score += 5; // update score
						enemy[i][1] = 0; // reset enemey y position to 0
					}
				}
			}
		}
		
		// Draw Player 
		setcolor(YELLOW); // for border color
		setfillstyle(1,YELLOW); // for fill color and other styles
		fillellipse(px, py, pr, pr);
		px += pStep; // increment playerX for ball movement
		
		// restrict ball to move inside bar
		if( px-pr<=bx || px+pr>=bx+bw ){
			pStep = -pStep;
		}
		
		delay(30);
		cleardevice();
	}
	
	
	getch();
	closegraph();
}
