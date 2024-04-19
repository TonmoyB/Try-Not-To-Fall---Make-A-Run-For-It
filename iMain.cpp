/*------------------------------------------------------\
|PROJECT NAME - TRY NOT TO FALL (MAKE A RUN FOR IT)		|
|														|
|	TEAM MEMBERS:	ANIMESH DAS CHOWDHURY	(058)		|
|					TONMOY BANIK			(059)		|
|					MD. TANVEER SHAMS		(060)		|
|					SANJIDA AKTER			(076)		|
\------------------------------------------------------*/
#include "Header\iGraphics.h"
#include "time.h"	//FOR TIME CAPTURE
#include "bass.h"	//FOR SOUND

//SOUND Variables
HSTREAM menusound;
HSTREAM clicksound;
HSTREAM hoversound;
HSTREAM ingamesound;
HSTREAM creditsound;

//iSetTimer Variables
int PM1, AC, BM, CM;

//highscore & time properties
int timeStart;
int timeEnd;
bool timeStartcapture= false;
bool timeEndcapture = false;
int SCORE;

//iInitialize Properties
#define screenWidth 1280	//[actual screenwidth is 1216]
#define screenHeight 720
#define projectName "TRY NOT TO FALL - MAKE A RUN FOR IT"

//background Properties
#define NumberOfSlices 20
int level1[NumberOfSlices];	//Background Day
int level2[NumberOfSlices];	//Background Night
int level3[NumberOfSlices];	//Background GreenHill Day

#define DefiningBackground BackgroundRendering1();
#define BackgroundChoice level1[i]

//Character Properties
int ch[12];
int Character = 0;

//:::::::::::::::::MenuPNG Properties:::::::::::::::::::::::
int menu[7][2];	//Storing PNGs
int diff[7];

//================
int gamestate = 0;//Scenerio Change--------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!########################################!!!!!!!!!!!!!!!!!!!!!!!!!-------------------------------------------------
//================

bool click = false;
bool cursorhover = false;
bool flagB[10];
int healthbar = 5;
int health[5];


bool checked = false;

int highscore[10] = {0};
char PlayerName[10][1000];
int len;
char nameTemp[1000];
char name[1000] = {};
char tmpName[1000];
int temp;

struct background{
	int x;
	int y;
};
background BGcoordinate[NumberOfSlices];

struct menubutton
{
	int x;
	int y;
	int height;
	int width;
	bool selectingArea;

	menubutton(int menux, int menuy)
	{
		x				= menux;
		y				= menuy;
		height			= 50;
		width			= 200;
		selectingArea	= false;	//if false then pic1, if true then pic2	
	}
};

struct pillar {
    int p_x;
	int p_y;
    int p_width;
	int p_height;
	int p_difference;


    pillar() {}
    pillar(int x, int y, int width, int height, int difference) {
        p_x = x;
        p_y = y;
		p_width = width;
		p_height = height;
		p_difference = difference;
    }
} pill[13];

struct stick
{
    int x;
    int y;
    int w;
    int h;
	int length;
	double angle;
	bool fall;

	stick(){}
    stick(int _x, int _y, int _w, int _h)
    {
        x = _x;	//pillar er x + width
        y = _y;	//height of piller
        w = _w;
        h = _h;
		length = 2;
		angle = 0;
		fall = false;
    }


}stick10[10];

//:::::::::::::::::::::::MENU BUTTON::::::::::::::::::::::::::::::::
menubutton playbutton (60, 380);
menubutton instructionsbutton(60, 300);
menubutton highscorebutton(60, 220);
menubutton creditsbutton(60, 140);
menubutton exitbutton(60 , 60);
//::::::::::::::::::::DIFFICULTIES BUTTON:::::::::::::::::::::::::::
menubutton easybutton (508, 335);
menubutton mediumbutton(508, 255);
menubutton hardbutton(508, 175);

//FOR BUTTON POSITION ANALYSIS
bool areaSelected(int mx, int my, menubutton obj)
{
	if( (mx > obj.x && mx < obj.x + obj.width) && (my > obj.y && my < obj.y + obj.height))
		return true;

	return false;
}

//Testing if the cursor is or isnt inside the button area
bool menuSelectingArea(int mx, int my){		
	bool truth = false;
	
	if(gamestate == 0)	//for MENU SCREEN BUTTONS
	{

		if( areaSelected(mx, my, playbutton) )
		{
			playbutton.selectingArea = true;
			truth = true;
			BASS_ChannelPlay(hoversound, false);
		}

		else
			playbutton.selectingArea = false;
		
		if( areaSelected(mx, my, instructionsbutton) )
		{
			instructionsbutton.selectingArea = true;
			truth =true;
			BASS_ChannelPlay(hoversound, false);
		}
		else
			instructionsbutton.selectingArea = false;
		
		if( areaSelected(mx, my, highscorebutton) )
		{
			highscorebutton.selectingArea = true;
			truth =true;
			BASS_ChannelPlay(hoversound, false);
		}
		else
			highscorebutton.selectingArea = false;

		if( areaSelected(mx, my, creditsbutton) )
		{
			creditsbutton.selectingArea = true;
			truth =true;
			BASS_ChannelPlay(hoversound, false);
		}
		else
			creditsbutton.selectingArea = false;
		
		if( areaSelected(mx, my, exitbutton) )
		{
			exitbutton.selectingArea = true;
			truth =true;
			BASS_ChannelPlay(hoversound, false);
		}
		else
			exitbutton.selectingArea = false;
		
		
	}

	if(gamestate == 13)		//for DIFFICULTIES SCREEN BUTTONS
	{
		if( areaSelected(mx, my, easybutton) )
		{
			easybutton.selectingArea = true;
			truth =true;
			BASS_ChannelPlay(hoversound, false);
		}
		else
			easybutton.selectingArea = false;
		
		if( areaSelected(mx, my, mediumbutton) )
		{
			mediumbutton.selectingArea = true;
			truth =true;
			BASS_ChannelPlay(hoversound, false);
		}
		else
			mediumbutton.selectingArea = false;
		
		if( areaSelected(mx, my, hardbutton) )
		{
			hardbutton.selectingArea = true;
			truth =true;
			BASS_ChannelPlay(hoversound, false);
		}
		else
			hardbutton.selectingArea = false;
	}
	return truth;
}

//TIME CAPTURE TO SET HIGHSCORE
void clockcapture()
{
	if(timeStartcapture == true){
		timeStart = clock();
		printf("timeStart: %d\n", timeStart);
		timeStartcapture = false;
	}
	if(timeEndcapture == true){
		timeEnd = clock();
		printf("timeEnd: %d\n", timeEnd);
		timeEndcapture = false;

		printf("total time: %d", (timeEnd - timeStart)/1000);


	}

}

//BACKGROUND SLICES SET POSITION
void setBackground(){
	int XcoordinateShifted=0;
	for (int i=0; i<20 ; i++){
		BGcoordinate[i].x = XcoordinateShifted;
		BGcoordinate[i].y = 0;
		
		XcoordinateShifted += 64;
	}
}

//BACKGROUND ANIMATION
void BackgroundMotion(){
		int testNum=4;

		for(int i=0 ; i<NumberOfSlices ; i++)
		{
			BGcoordinate[i].x -=testNum;

			if(BGcoordinate[i].x <= -63)
			{
				BGcoordinate[i].x=screenWidth-64;
			}	
		}
}

//CHARACTER ANIMATION
void CharacterMotion(){
	Character++;

	if(Character>=10 ){
		Character = 0;
	}
}

//HIGHSCORE SORTING AND UPDATING
void sortleaderboard()
{
	for (int i = 0; i < 9; i++){
		for (int j = i + 1; j < 10; j++){
			int temp;
			if (highscore[i] > highscore[j] && highscore[j] != 0){
				temp = highscore[i];
				highscore[i] = highscore[j];
				highscore[j] = temp;
				strcpy(tmpName, PlayerName[i]);
				strcpy(PlayerName[i], PlayerName[j]);
				strcpy(PlayerName[j], tmpName);
			}
			if(highscore[i] == 0 && highscore[j] != 0) {
				temp = highscore[i];
				highscore[i] = highscore[j];
				highscore[j] = temp;
				strcpy(tmpName, PlayerName[i]);
				strcpy(PlayerName[i], PlayerName[j]);
				strcpy(PlayerName[j], tmpName);
			}
		}
	}
}
void updateleaderboard()
{
	sortleaderboard();
	FILE *fp, *Fp;
	fp = fopen("score.txt", "w");
	Fp = fopen("name.txt", "w");
	/*for (int i = 0; i < 10; i++){

		fprintf(fp, "%d\n",highscore[i]);
		fprintf(Fp, "%s\n", PlayerName[i]);
	}*/
	fclose(fp);
	fclose(Fp);
}
void leaderboard()
{
	FILE *fp, *Fp;
	fp = fopen("score.txt", "r");
	Fp = fopen("name.txt", "r");
	for (int i = 0; i < 10; i++){
		fscanf(fp, "%d", &highscore[i]);
		fscanf(Fp, "%s", PlayerName[i]);
	}
}

bool PlayerFlag = false;

//=================PILLAR PROPERTIES============================
void PillMov() {
	int test = 4;
	for(int i = 0; i < 10; i++) 
	{
		pill[i].p_x -= test;
		stick10[i].x -= test;	//stick is syncing with piller's x coordinate
			
		if( i != 0 && pill[i].p_x <= 0 && flagB[i]==false)
		{
			if(pill[i].p_x < 0 )
			{
				pill[i].p_x = 0;
			}
			
			stick10[i].x = pill[i].p_x + pill[i].p_width - 3;
			stick10[i].h = 0;
			
			if(i == 9 && gamestate==1)
			{
				gamestate = 8;
			}
			if(i==9 && gamestate==14)
			{
				gamestate = 9;
			}
			if(i==9 && gamestate ==15)
			{
				timeEndcapture = true;
				clockcapture();
				gamestate = 20;
				SCORE = (abs(timeEnd - timeStart))/1000;
				if(SCORE < highscore[9] || highscore[9] == 0)
				{
					highscore[9] = SCORE;
					PlayerFlag = true;
				}  
			}
			iPauseTimer(CM);
			iPauseTimer(BM);
			iPauseTimer(PM1);
			flagB[i] = true;	
		}
	}
}

//LVL 1 :: pill_W(70-90) :: pill_D(200-450)
void pillGen() {	
	for(int i = 0; i < 10; i++) 
	{
		if(i==0)
		{
			pill[0].p_x = 0;	//constant
			pill[0].p_y = 0;
			pill[0].p_width = 90/*rand() % 20 + 70*/;
			pill[0].p_height = 200;

			stick10[0].x = pill[0].p_x + pill[0].p_width - 3;
			stick10[0].y = pill[0].p_height;
			stick10[0].w = 3 ;
			stick10[0].h = 0 ;			//constant
		}
		else{
		pill[i].p_x = pill[i - 1].p_x + rand() % 250 + 200;	//:::::::::::::::::::::::::::::::::::::::::
		pill[i].p_y = 0;
		pill[i].p_width = rand() % 20 + 70;
		pill[i].p_height = 200;

		stick10[i].x = pill[i].p_x + pill[i].p_width - 3;
		stick10[i].y = pill[i].p_height;
		stick10[i].w = 3 ;
		stick10[i].h = 0 ;			//constant
		}
	}
	for(int i = 0 ; i<9 ; i++)
	{
		pill[i].p_difference = pill[i+1].p_x - (stick10[i].x + 3);
	}
}
//LVL 2 :: pill_W(50-70) :: pill_D(200-450)
void pillGen2() 
{
		for(int i = 0; i < 10; i++) 
		{
			if(i==0)
			{
				pill[0].p_x = 0;	//constant
				pill[0].p_y = 0;
				pill[0].p_width = 70/*rand() % 20 + 50*/;
				pill[0].p_height = 200;

				stick10[0].x = pill[0].p_x + pill[0].p_width - 3;
				stick10[0].y = pill[0].p_height;
				stick10[0].w = 3 ;
				stick10[0].h = 0 ;			//constant
			}
			else{
			pill[i].p_x = pill[i - 1].p_x + rand() % 250 + 200;	//:::::::::::::::::::::::::::::::::::::::::
			pill[i].p_y = 0;
			pill[i].p_width = rand() % 20 + 50;
			pill[i].p_height = 200;

			stick10[i].x = pill[i].p_x + pill[i].p_width - 3;
			stick10[i].y = pill[i].p_height;
			stick10[i].w = 3 ;
			stick10[i].h = 0 ;			//constant
			}
		}
	
		for(int i = 0 ; i<9 ; i++)
		{
			pill[i].p_difference = pill[i+1].p_x - (stick10[i].x + 3);
		}
//	}
}
//LVL 3 :: pill_W(35-50) :: pill_D(200-450)
void pillGen3() 
{
	for(int i = 0; i < 10; i++) {
		if(i==0)
		{
			pill[0].p_x = 0;	//constant
			pill[0].p_y = 0;
			pill[0].p_width = 50/*rand() % 15 + 35*/;
			pill[0].p_height = 200;

			stick10[0].x = pill[0].p_x + pill[0].p_width - 3;
			stick10[0].y = pill[0].p_height;
			stick10[0].w = 3 ;
			stick10[0].h = 0 ;			//constant
		}
		else{
		pill[i].p_x = pill[i - 1].p_x + rand() % 250 + 200;	//:::::::::::::::::::::::::::::::::::::::::
		pill[i].p_y = 0;
		pill[i].p_width = rand() % 15 + 35;
		pill[i].p_height = 200;


		stick10[i].x = pill[i].p_x + pill[i].p_width - 3;
		stick10[i].y = pill[i].p_height;
		stick10[i].w = 3 ;
		stick10[i].h = 0 ;			//constant
		}
	}
	
	for(int i = 0 ; i<9 ; i++)
	{
		pill[i].p_difference = pill[i+1].p_x - (stick10[i].x + 3);
	}

}

//STICK ROTATION
void angle_change()
{
	for(int i=0 ; i<10 ; i++)
	{
		if((((pill[i].p_difference > stick10[i].h) || (pill[i].p_difference + pill[i+1].p_width)<= stick10[i].h )) && pill[i].p_x==0 )	//player wont cross the stick
		{
			if((pill[i].p_difference > stick10[i].h))
			{
				if((stick10[i].angle <= 0 && stick10[i].angle > -180) && stick10[i].fall == true && pill[i].p_x==0)
					stick10[i].angle -= 3;

				if(stick10[i].angle == -180)
				{

					temp = gamestate;
					printf("temp = %d\n", temp);
					gamestate =16;		//didnt cross
					stick10[i].angle = 0;
					stick10[i].fall = false;
					stick10[i].h = 0;
			
				}
			}
			if((pill[i].p_difference + pill[i+1].p_width)<= stick10[i].h )
			{
				if((stick10[i].angle <= 0 && stick10[i].angle > -180) && stick10[i].fall == true && pill[i].p_x==0)
					stick10[i].angle -= 3;

				if(stick10[i].angle == -180){

					temp = gamestate;
					printf("temp = %d\n", temp);
					gamestate =17;		//crossed
					stick10[i].angle = 0;
					stick10[i].fall = false;
					stick10[i].h = 0;			
				}
			}				
		}
		else										//player will cross the stick
			{
			if((stick10[i].angle <= 0 && stick10[i].angle > -90) && stick10[i].fall == true && pill[i].p_x==0){
				stick10[i].angle -= 3;
				if(stick10[i].angle == -90)
				{	
					iResumeTimer(PM1);
					iResumeTimer(BM);
					iResumeTimer(CM);
				}
			}
		}		
	}
}
//:::::::::::::::::::::::::::::::::::::::::::PILLAR:::::::::::::::::::::::::::::::::::::::::::
//pillar p1(0,25),p2(300,40), p3(950,105);
//LVL 1 --> Width(70-90)
//LVL 2 --> Width(50-70)
//LVL 3 --> Width(25-40)

//______________________________________________________________________________________________
//:-:-:-:-:-:-:-:-:-:-:-:-iDraw Functions-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:

//MENU
void GameState00()
{
	BASS_ChannelStop(creditsound);
	BASS_ChannelStop(ingamesound);
	BASS_ChannelPlay(menusound, false);
	BASS_ChannelPlay(clicksound, true);
		
	iShowImage(0, 0, screenWidth, screenHeight, menu[0][0]);

	//:::::::::::::PLAY_BUTTON:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if(playbutton.selectingArea == false)
		iShowImage(playbutton.x, playbutton.y, playbutton.width, playbutton.height, menu[1][0]);
	else if(playbutton.selectingArea == true && click == true)
	{
		BASS_ChannelPlay(ingamesound, true);

		click = false;
		gamestate = 11;
	}
	else
		iShowImage(playbutton.x, playbutton.y, playbutton.width, playbutton.height, menu[1][1]);

	//:::::::::::::INSTRUCTIONS_BUTTON:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if(instructionsbutton.selectingArea == false)
		iShowImage(instructionsbutton.x, instructionsbutton.y, instructionsbutton.width, instructionsbutton.height, menu[3][0]);
	else if(instructionsbutton.selectingArea == true && click == true)
	{
		click = false;
		gamestate = 2;
	}
	else
		iShowImage(instructionsbutton.x, instructionsbutton.y, instructionsbutton.width, instructionsbutton.height, menu[3][1]);

	//::::::::::::::HIGHSCORE_BUTTON:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if(highscorebutton.selectingArea == false)
		iShowImage(highscorebutton.x, highscorebutton.y, highscorebutton.width, highscorebutton.height, menu[4][0]);
	else if(highscorebutton.selectingArea == true && click == true)
	{
		click = false;
		gamestate = 3;	
	}
	else
		iShowImage(highscorebutton.x, highscorebutton.y, highscorebutton.width, highscorebutton.height, menu[4][1]);

	//::::::::::::::::::::CREDITS_BUTTON::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if(creditsbutton.selectingArea == false)
		iShowImage(creditsbutton.x, creditsbutton.y, creditsbutton.width, creditsbutton.height, menu[5][0]);
	else if(creditsbutton.selectingArea == true && click == true)
	{
		BASS_ChannelPlay(creditsound, true);
				
		click = false;
		gamestate = 4;

	}
	else
		iShowImage(creditsbutton.x, creditsbutton.y, creditsbutton.width, creditsbutton.height, menu[5][1]);
		
	//:::::::::::::::::::::::EXIT BUTTON:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if(exitbutton.selectingArea == false)
		iShowImage(exitbutton.x, exitbutton.y, exitbutton.width, exitbutton.height, menu[6][0]);
	else if(exitbutton.selectingArea == true && click == true)
	{
		click = false;
		gamestate = 5;
	}
	else
		iShowImage(exitbutton.x, exitbutton.y, exitbutton.width, exitbutton.height, menu[6][1]);

}

//STORYLINE1
void GameState00_1()
{
	BASS_ChannelStop(menusound);
	iShowImage(0, 0, screenWidth, screenHeight, iLoadImage("Menu\\StoryLine1.png"));
}

//STORYLINE2
void GameState00_2()
{
	iShowImage(0, 0, screenWidth, screenHeight, iLoadImage("Menu\\StoryLine2.png"));
}

//DIFFICULTIES
void GameState00_3()
{
	BASS_ChannelPlay(clicksound, true);
	iShowImage(0, 0, screenWidth, screenHeight, diff[6]);

	//:::::::::::::EASY_BUTTON:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if(easybutton.selectingArea == false)
		iShowImage(easybutton.x, easybutton.y, easybutton.width, easybutton.height, diff[0]);

	else if(easybutton.selectingArea == true && click == true)
	{
		healthbar = 5;	
		click = false;
		timeStartcapture = true;
		clockcapture();

		gamestate = 1;
	}

	else
		iShowImage(easybutton.x, easybutton.y, easybutton.width, easybutton.height, diff[3]);


	//:::::::::::::MEDIUM_BUTTON:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if(mediumbutton.selectingArea == false)
		iShowImage(mediumbutton.x, mediumbutton.y, mediumbutton.width, mediumbutton.height, diff[1]);

	else if(mediumbutton.selectingArea == true && click == true)
	{
		healthbar = 3;	
		click = false;
		timeStartcapture = true;
		clockcapture();

		gamestate = 1;
	}

	else
		iShowImage(mediumbutton.x, mediumbutton.y, mediumbutton.width, mediumbutton.height, diff[4]);


	//::::::::::::::HARD_BUTTON:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	if(hardbutton.selectingArea == false)
		iShowImage(hardbutton.x, hardbutton.y, hardbutton.width, hardbutton.height, diff[2]);

	else if(hardbutton.selectingArea == true && click == true)
	{
		healthbar = 1;		
		click = false;
		timeStartcapture = true;
		clockcapture();

		gamestate = 1;
	}
	else
		iShowImage(hardbutton.x, hardbutton.y, hardbutton.width, hardbutton.height, diff[5]);
}

//PLAYSCREEN1
void GameState01()
{
	BASS_ChannelPlay(ingamesound, false);

	//Background
	for(int i=0 ; i<20 ; i++)
	{
		iShowImage(BGcoordinate[i].x, BGcoordinate[i].y, (screenWidth/NumberOfSlices) , 720, level1[i]);
	}

	//Pillar
	for(int i = 0; i < 10; i++) 
	{
		iSetColor(255, 128, 0);
		iFilledRectangle(pill[i].p_x, pill[i].p_y, pill[i].p_width, pill[i].p_height);
	}
			
	//Stick
	for(int i = 0 ; i<10 ; i++)
	{
		if(stick10[i].fall == true)
		{
			iRotate(stick10[i].x, stick10[i].y, stick10[i].angle);
			iSetColor(255, 128, 0);
			iFilledRectangle(stick10[i].x, stick10[i].y, stick10[i].w, stick10[i].h);
			iUnRotate();
		}				
		else
		{
			iSetColor(96,96,96);
			iFilledRectangle(stick10[i].x, stick10[i].y, stick10[i].w, stick10[i].h);
		}
		//Character *animation on if(fall==true), else*animation off
		iShowImage(-5 , 193 , 50, 80 , ch[Character] );		
	}

	//HEALTH
	if(healthbar == 5)
		iShowImage(950, 660, 250, 40, health[4]);
	else if(healthbar == 4)
		iShowImage(950, 660, 250, 40, health[3]);
	else if(healthbar == 3)
		iShowImage(950, 660, 250, 40, health[2]);
	else if(healthbar == 2)
		iShowImage(950, 660, 250, 40, health[1]);
	else if(healthbar == 1)
		iShowImage(950, 660, 250, 40, health[0]);			

}

//PLAYSCREEN2
void GameState01_4()
{
	//Background
	for(int i=0 ; i<20 ; i++)
	{
		iShowImage(BGcoordinate[i].x, BGcoordinate[i].y, (screenWidth/NumberOfSlices) , 720, level2[i]);
	}

	//Pillar
	for(int i = 0; i < 10; i++) 
	{
		iSetColor(0,204,204);
		iFilledRectangle(pill[i].p_x, pill[i].p_y, pill[i].p_width, pill[i].p_height);
	}
			
	//Stick
	for(int i = 0 ; i<10 ; i++)
	{
		if(stick10[i].fall == true)
		{
			iRotate(stick10[i].x, stick10[i].y, stick10[i].angle);
			iSetColor(0,204,204);
			iFilledRectangle(stick10[i].x, stick10[i].y, stick10[i].w, stick10[i].h);
			iUnRotate();
		}				
		else
		{
			iSetColor(255,255,255);
			iFilledRectangle(stick10[i].x, stick10[i].y, stick10[i].w, stick10[i].h);
		}
		//Character *animation on if(fall==true), else*animation off
		iShowImage(-5 , 193 , 50, 80 , ch[Character] );		
	}

	//HEALTH
	if(healthbar == 5)
		iShowImage(950, 660, 250, 40, health[4]);
	else if(healthbar == 4)
		iShowImage(950, 660, 250, 40, health[3]);
	else if(healthbar == 3)
		iShowImage(950, 660, 250, 40, health[2]);
	else if(healthbar == 2)
		iShowImage(950, 660, 250, 40, health[1]);
	else if(healthbar == 1)
		iShowImage(950, 660, 250, 40, health[0]);

}

//PLAYSCREEN3
void GameState01_5()
{
	//Background
	for(int i=0 ; i<20 ; i++)
	{
		iShowImage(BGcoordinate[i].x, BGcoordinate[i].y, (screenWidth/NumberOfSlices) , 720, level3[i]);
	}

	//Pillar
	for(int i = 0; i < 10; i++) 
	{
		iSetColor(178,255,102);
		iFilledRectangle(pill[i].p_x, pill[i].p_y, pill[i].p_width, pill[i].p_height);
	}
			
	//Stick
	for(int i = 0 ; i<10 ; i++)
	{
		if(stick10[i].fall == true)
		{
			iRotate(stick10[i].x, stick10[i].y, stick10[i].angle);
			iSetColor(178,255,102);
			iFilledRectangle(stick10[i].x, stick10[i].y, stick10[i].w, stick10[i].h);
			iUnRotate();
		}				
		else
		{
			iSetColor(178,102,255);
			iFilledRectangle(stick10[i].x, stick10[i].y, stick10[i].w, stick10[i].h);
		}
		//Character *animation on if(fall==true), else*animation off
		iShowImage(-5 , 193 , 50, 80 , ch[Character] );		
	}			
	//HEALTH
	if(healthbar == 5)
		iShowImage(950, 660, 250, 40, health[4]);
	else if(healthbar == 4)
		iShowImage(950, 660, 250, 40, health[3]);
	else if(healthbar == 3)
		iShowImage(950, 660, 250, 40, health[2]);
	else if(healthbar == 2)
		iShowImage(950, 660, 250, 40, health[1]);
	else if(healthbar == 1)
		iShowImage(950, 660, 250, 40, health[0]);
}

//INSTRUCTIONS
void GameState02()
{
	iShowImage(0, 0, screenWidth-64, screenHeight, iLoadImage("Menu\\instructions.png")); 
}

//HIGH SCORE
void GameState03()
{
	iShowImage(0, 0, screenWidth-64, screenHeight, iLoadImage("Menu\\highscore.png"));
	iSetColor(0, 204, 204);
	iText(120, 540, "R  A  N  K ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(540, 540, "N  A  M  E ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(920, 540, "PLAY TIME(sec.)", GLUT_BITMAP_TIMES_ROMAN_24);
	iLine(110,530,1118,530);
	for(int i = 0, j = 500; i < 10; i++, j-=50){
		char score[1000];
		char sl[3];
		//printf("%d\t",highscore[i]);
		_itoa(highscore[i], score, 10);
		_itoa(i + 1, sl, 10);
		if(i <= 2) iSetColor(255, 255, 0);
		else iSetColor(255, 255, 255);
		iText(150, j, sl, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(545, j, PlayerName[i], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1020, j, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

//CREDITS
void GameState04()
{
	iShowImage(0, 0, screenWidth-64, screenHeight, iLoadImage("Menu\\CreditsFinal.png")); 
	BASS_ChannelStop(menusound);
	
}

//EXIT
void GameState05()
{
	exit(0);
}

//GAMEOVER
void GameState06()
{
	iShowImage(0, 0, screenWidth-64, screenHeight, iLoadImage("gameIMG\\gameover.png"));
	//::::::::::::Resets Everything::::::::::::::::::
					iPauseTimer(PM1);
					iPauseTimer(BM);
					iPauseTimer(CM);
            pillGen(), setBackground(), Character = 0;
            for(int i = 0; i < 10; i++) {
                stick10[i].fall = false;
                flagB[i] = false;
                stick10[i].angle = 0;
            }
}

//GAMEFINISHED
void GameState07()
{
	iShowImage(0, 0, screenWidth-64, screenHeight, iLoadImage("gameIMG\\gamefinished.png")); 
	char score[1000];
	_itoa(SCORE, score, 10);
	iText(310, 200, "You Finished the game within :", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(630, 200, score, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(670, 200, "seconds", GLUT_BITMAP_TIMES_ROMAN_24);
	//::::::::::::Resets PlayScreen 1::::::::::::::::::
			iPauseTimer(PM1);
			iPauseTimer(BM);
			iPauseTimer(CM);
        pillGen(),setBackground(), Character = 0;
        for(int i = 0; i < 10; i++) 
		{
           stick10[i].fall = false;
           flagB[i] = false;
		   stick10[i].angle = 0;
		}
}

//STAGE1FINISHED
void GameState08()
{
	iShowImage(0, 0, screenWidth-64, screenHeight, iLoadImage("gameIMG\\stage1com.png")); 

	//::::::::::::Resets PlayScreen 2::::::::::::::::::
			iPauseTimer(BM);
			iPauseTimer(CM);
			iPauseTimer(PM1);
        pillGen2(),setBackground(), Character = 0;
        for(int i = 0; i < 10; i++) 
		{
            stick10[i].fall = false;
            flagB[i] = false;
            stick10[i].angle = 0;
        }
}

//STAGE2FINISHED
void GameState09()
{
	iShowImage(0, 0, screenWidth-64, screenHeight, iLoadImage("gameIMG\\stage2com.png")); 
	//::::::::::::Resets PlayScreen 3::::::::::::::::::
			iPauseTimer(BM);
			iPauseTimer(CM);
			iPauseTimer(PM1);
        pillGen3(),setBackground(), Character = 0;
        for(int i = 0; i < 10; i++) 
		{
            stick10[i].fall = false;
            flagB[i] = false;
            stick10[i].angle = 0;
        }
}

//didnt reach
void GameState16()
{
	iShowImage(0,0, 1280-64,720, iLoadImage("gameIMG\\notreached.png"));
	checked= true;
}

//crossed 2nd pillar
void GameState17()
{
	iShowImage(0,0, 1280-64,720, iLoadImage("gameIMG\\crossed.png"));
	checked = true;
}

//NAME input page
void GameState20() 
{
	iShowImage(0, 0, screenWidth-64, screenHeight, iLoadImage("Menu\\NmeInput.png"));
	iSetColor(255,255,255);
	iText(460, 420, "ENTER YOUR NAME  :", GLUT_BITMAP_TIMES_ROMAN_24);
	//iRectangle(465, 320, 230, 60);
	iLine(465, 320, 695, 320);
	//iText(850, 200, score, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(490, 340, nameTemp, GLUT_BITMAP_TIMES_ROMAN_24);
}
//-----------------iDraw Properties ENDs---------------------------------------



void iDraw()
{
    iClear();
			
	if(gamestate == 0)				//MENU
		GameState00();

	else if(gamestate == 11)		//STORYLINE PAGE1
		GameState00_1();

	else if(gamestate == 12)		//STORYLINE PAGE2
		GameState00_2();

	else if(gamestate == 13)		//DIFFICULTIES
		GameState00_3();

	else if(gamestate == 1)			//PLAYSCENE1
		GameState01();		

	else if(gamestate == 14)		//PLAYSCENE2
		GameState01_4();
			
	else if(gamestate == 15)		//PLAYSCENE3
		GameState01_5();	

	else if(gamestate == 2)			//INSTRUCTIONS
		GameState02();

	else if(gamestate == 3)		//HIGHSCORE
		GameState03();

	else if(gamestate == 4)		//CREDITS
		GameState04();

	else if(gamestate == 5)		//EXIT
		GameState05();

	else if(gamestate == 6)		//GAMEOVER
		GameState06();

	else if(gamestate == 7)		//GAMEFINISHED
		GameState07();

	else if(gamestate == 8)		//STAGE1FINISHED
		GameState08();
			
	else if(gamestate == 9)		//STAGE2FINISHED
		GameState09();

	else if(gamestate ==16)		//didnt reach
		GameState16();

	else if(gamestate ==17)		//2nd pillar crossed
		GameState17();
	
	else if(gamestate == 20)	//Name Input
		GameState20();
}

void iMouseMove(int mx, int my)
{
	
}
void iPassiveMouseMove(int mx, int my)
{
	menuSelectingArea(mx, my);
			
	if(menuSelectingArea(mx, my ) == true)
		cursorhover = true;
	else
		cursorhover = false;
	//printf("iPassiveMouseMove %d %d\n", mx, my);
}
void iMouse(int button, int state, int mx, int my)//==========
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(menuSelectingArea(mx, my) == true)
			click = true;		
		else
			click = false;
								
		printf("Clicked\n");				
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}

void iKeyboard(unsigned char key)
{
	if( (gamestate==16 || gamestate==17) && checked == true )		//HEALTH DECREASING HERE
	{
		if(key)
		{
			if(healthbar==5)
			{
				checked = false;
				healthbar = 4;
				gamestate = temp;
				printf("temp = %d\n", temp);
			}
			else if(healthbar==4)
			{
				checked = false;
				healthbar = 3;
				gamestate = temp;
				printf("temp = %d\n", temp);
			}
			else if(healthbar==3)
			{
				checked = false;
				healthbar = 2;
				gamestate = temp;		//return from where the game will resume
				printf("temp = %d\n", temp);
			}
			else if(healthbar==2)
			{
				checked = false;
				healthbar = 1;
				gamestate = temp;		//return from where the game will resume
				printf("temp = %d\n", temp);
			}
			else if(healthbar==1)
			{
				checked = false;
				healthbar = 0;
				gamestate = 6;		//gameover screen will be shown

				printf("temp = 6\n", temp);
			}
		}
	}
	
	if(gamestate == 12)
	{
		if(key == '\r')
		{
			gamestate = 13;
			BASS_ChannelPlay(clicksound, true);
		}
	}
	if(gamestate == 6 || gamestate == 7)
	{
		if(key == '\b')
			gamestate = 0;
	}

	if(gamestate == 8 && key)
		gamestate=14;

	if(gamestate == 9 && key)
		gamestate=15;

	if( (gamestate==2 || gamestate==3 || gamestate==4 ) && key == '\b' )
	{
			printf("BACKSPACE pressed\n");
					gamestate=0;
					click= false;
	}

/*	if( (gamestate==1 ) && key == '\b' )
	{
		gamestate = 6;
		click = false;
	}*/
	if((gamestate == 1) || (gamestate == 14) || (gamestate ==15))
	{
		for(int i=0 ; i<10 ; i++)
		{
			checked = false;
			if ( pill[i].p_x == 0 && key == ' ' && stick10[i].fall == false )
			{
				stick10[i].h += 4 ;
				//stick10[i].length +=4;
			}
			if( pill[i].p_x == 0 && (key == 'q' || key == 'Q') && stick10[i].fall == false )
			{
				stick10[i].fall = true;
			}
		}
	}
	if(key == 'p')		//PAUSE KEY
	{
		if(gamestate ==1)
		{
			iPauseTimer(PM1);
			iPauseTimer(BM);
			iPauseTimer(CM);
		}
		if(gamestate ==14)
		{
			iPauseTimer(PM1);
			iPauseTimer(BM);
			iPauseTimer(CM);
		}
		if(gamestate ==15)
		{
			iPauseTimer(PM1);
			iPauseTimer(BM);
			iPauseTimer(CM);
		}
	}
	if(key == '`' )			//DEBUGING KEY
	{
		if(gamestate ==1)
		{
			iResumeTimer(PM1);
			iResumeTimer(BM);
			iResumeTimer(CM);
		}
		if(gamestate ==14)
		{
			iResumeTimer(PM1);
			iResumeTimer(BM);
			iResumeTimer(CM);
		}
		if(gamestate ==15)
		{
			iResumeTimer(PM1);
			iResumeTimer(BM);
			iResumeTimer(CM);
		}
	}
	if(gamestate == 20) {
		if(key == '\b') 
		{
			len--;
			if(len < 0) len = 0;
				nameTemp[len] = '\0';
		}
		else if(key == '\r') {
			gamestate = 7;
			if(PlayerFlag = true) 
			{
				strcpy(PlayerName[9], nameTemp);
				updateleaderboard();
				strcpy(nameTemp,name);
			}
		}
		else 
		{
			nameTemp[len] = key;
			len++;
		}
	}
}
void iSpecialKeyboard(unsigned char key)
{
	if(gamestate == 11)
	{
		if(key == GLUT_KEY_RIGHT){
			gamestate = 12;
			BASS_ChannelPlay(clicksound, true);
		}
	}
	if(gamestate == 11)
	{
		if(key == GLUT_KEY_LEFT){
			gamestate = 0;
			BASS_ChannelPlay(clicksound, true);
		}
			
	}
	if(gamestate == 12)
	{
		if(key == GLUT_KEY_LEFT){
			gamestate = 11;
			BASS_ChannelPlay(clicksound, true);
		}
	}
	if(gamestate == 13)
	{
		if(key == GLUT_KEY_LEFT){
			gamestate = 12;
			BASS_ChannelPlay(clicksound, true);
		}
	}

}

//BACKGROUND SLICES ARE SAVED AS INTEGER HERE
void BackgroundRendering1(){
	//LEVEL 1 Background Image Paths [DAY]
	level1[0] = iLoadImage("BGlvl1\\1.png");
	level1[1] = iLoadImage("BGlvl1\\2.png");
	level1[2] = iLoadImage("BGlvl1\\3.png");
	level1[3] = iLoadImage("BGlvl1\\4.png");
	level1[4] = iLoadImage("BGlvl1\\5.png");
	level1[5] = iLoadImage("BGlvl1\\6.png");
	level1[6] = iLoadImage("BGlvl1\\7.png");
	level1[7] = iLoadImage("BGlvl1\\8.png");
	level1[8] = iLoadImage("BGlvl1\\9.png");
	level1[9] = iLoadImage("BGlvl1\\10.png");
	level1[10] = iLoadImage("BGlvl1\\11.png");
	level1[11] = iLoadImage("BGlvl1\\12.png");
	level1[12] = iLoadImage("BGlvl1\\13.png");
	level1[13] = iLoadImage("BGlvl1\\14.png");
	level1[14] = iLoadImage("BGlvl1\\15.png");
	level1[15] = iLoadImage("BGlvl1\\16.png");
	level1[16] = iLoadImage("BGlvl1\\17.png");
	level1[17] = iLoadImage("BGlvl1\\18.png");
	level1[18] = iLoadImage("BGlvl1\\19.png");
	level1[19] = iLoadImage("BGlvl1\\20.png");

}
void BackgroundRendering2(){
		//LEVEL 2 Background Image Paths [NIGHT]
	level2[0] = iLoadImage("BGlvl2\\1.png");
	level2[1] = iLoadImage("BGlvl2\\2.png");
	level2[2] = iLoadImage("BGlvl2\\3.png");
	level2[3] = iLoadImage("BGlvl2\\4.png");
	level2[4] = iLoadImage("BGlvl2\\5.png");
	level2[5] = iLoadImage("BGlvl2\\6.png");
	level2[6] = iLoadImage("BGlvl2\\7.png");
	level2[7] = iLoadImage("BGlvl2\\8.png");
	level2[8] = iLoadImage("BGlvl2\\9.png");
	level2[9] = iLoadImage("BGlvl2\\10.png");
	level2[10] = iLoadImage("BGlvl2\\11.png");
	level2[11] = iLoadImage("BGlvl2\\12.png");
	level2[12] = iLoadImage("BGlvl2\\13.png");
	level2[13] = iLoadImage("BGlvl2\\14.png");
	level2[14] = iLoadImage("BGlvl2\\15.png");
	level2[15] = iLoadImage("BGlvl2\\16.png");
	level2[16] = iLoadImage("BGlvl2\\17.png");
	level2[17] = iLoadImage("BGlvl2\\18.png");
	level2[18] = iLoadImage("BGlvl2\\19.png");
	level2[19] = iLoadImage("BGlvl2\\20.png");

}
void BackgroundRendering3(){
		//LEVEL 3 Background Image Paths [GREEN HILLS]
	level3[0] = iLoadImage("BGlvl3\\1.png");
	level3[1] = iLoadImage("BGlvl3\\2.png");
	level3[2] = iLoadImage("BGlvl3\\3.png");
	level3[3] = iLoadImage("BGlvl3\\4.png");
	level3[4] = iLoadImage("BGlvl3\\5.png");
	level3[5] = iLoadImage("BGlvl3\\6.png");
	level3[6] = iLoadImage("BGlvl3\\7.png");
	level3[7] = iLoadImage("BGlvl3\\8.png");
	level3[8] = iLoadImage("BGlvl3\\9.png");
	level3[9] = iLoadImage("BGlvl3\\10.png");
	level3[10] = iLoadImage("BGlvl3\\11.png");
	level3[11] = iLoadImage("BGlvl3\\12.png");
	level3[12] = iLoadImage("BGlvl3\\13.png");
	level3[13] = iLoadImage("BGlvl3\\14.png");
	level3[14] = iLoadImage("BGlvl3\\15.png");
	level3[15] = iLoadImage("BGlvl3\\16.png");
	level3[16] = iLoadImage("BGlvl3\\17.png");
	level3[17] = iLoadImage("BGlvl3\\18.png");
	level3[18] = iLoadImage("BGlvl3\\19.png");
	level3[19] = iLoadImage("BGlvl3\\20.png");	

}

//CHARACTER SLICES ARE SAVED AS INTEGER HERE
void CharacterRendering(){
	ch[0] = iLoadImage("char\\1.png");
	ch[1] = iLoadImage("char\\2.png");
	ch[2] = iLoadImage("char\\3.png");
	ch[3] = iLoadImage("char\\4.png");
	ch[4] = iLoadImage("char\\5.png");
	ch[5] = iLoadImage("char\\6.png");
	ch[6] = iLoadImage("char\\7.png");
	ch[7] = iLoadImage("char\\8.png");
	ch[8] = iLoadImage("char\\9.png");
	ch[9] = iLoadImage("char\\10.png");
	
}

//MENUBUTTON, DIFFICULTIES BUTTON, HEALTHBAR PNGs ARE SAVED HERE
void MenuPNG(){
	menu[0][0] = iLoadImage("Button\\MenuFinal.png");
	menu[1][0] = iLoadImage("Button\\PlayS.png");
	menu[2][0] = iLoadImage("Button\\StoryLineS.png");
	menu[3][0] = iLoadImage("Button\\InstructionsS.png");
	menu[4][0] = iLoadImage("Button\\HighScoreS.png");
	menu[5][0] = iLoadImage("Button\\CreditsS.png");
	menu[6][0] = iLoadImage("Button\\ExitS.png");
	menu[1][1] = iLoadImage("Button\\PlayN.png");
	menu[2][1] = iLoadImage("Button\\StoryLineN.png");
	menu[3][1] = iLoadImage("Button\\InstructionsN.png");
	menu[4][1] = iLoadImage("Button\\HighScoreN.png");
	menu[5][1] = iLoadImage("Button\\CreditsN.png");
	menu[6][1] = iLoadImage("Button\\ExitN.png");
	
}
void diffPNG()
{
	diff[0] = iLoadImage("Button\\easyO.png");
	diff[1] = iLoadImage("Button\\mediumO.png");
	diff[2] = iLoadImage("Button\\hardO.png");
	diff[3] = iLoadImage("Button\\easyW.png");
	diff[4] = iLoadImage("Button\\mediumW.png");
	diff[5] = iLoadImage("Button\\hardW.png");
	diff[6] = iLoadImage("Menu\\Difficulties.png");

}
void healthPNG()
{
	health[0] = iLoadImage("health\\1.png");
	health[1] = iLoadImage("health\\2.png");
	health[2] = iLoadImage("health\\3.png");
	health[3] = iLoadImage("health\\4.png");
	health[4] = iLoadImage("health\\5.png");

}

//SOUND FILES ARE STORED AND DECLARED HERE
void loadsound()
{
		menusound = BASS_StreamCreateFile(false, "Sound\\Menu0.wav", 0,0, BASS_SAMPLE_LOOP);	//BASS_SAMPLE_MONO [for once]LOOP
		clicksound = BASS_StreamCreateFile(false, "Sound\\Click.wav", 0,0, BASS_SAMPLE_MONO);
		hoversound = BASS_StreamCreateFile(false, "Sound\\Hover.wav", 0,0, BASS_SAMPLE_MONO);
		ingamesound = BASS_StreamCreateFile(false, "Sound\\ingameSound.wav", 0,0, BASS_SAMPLE_LOOP);
		creditsound = BASS_StreamCreateFile(false, "Sound\\credits.wav", 0,0, BASS_SAMPLE_LOOP);			
}


//Xx-------------::MAIN FUNCTION::----------------xX
int main()
{	
	leaderboard();
	updateleaderboard();
	iInitialize(screenWidth-64 , screenHeight, projectName);

	if (!BASS_Init(-1, 44100, 0, NULL, NULL))
		printf("Failed in BASS_Init" ) ;

	loadsound();

	MenuPNG();
	diffPNG();
	healthPNG();

	setBackground();
	BackgroundRendering1();
	pillGen();
	BackgroundRendering2();
	BackgroundRendering3();
	CharacterRendering();

	AC	= iSetTimer(1,angle_change);
	BM	= iSetTimer(30, BackgroundMotion);
	CM	= iSetTimer(90, CharacterMotion);
	PM1	= iSetTimer(1,PillMov);		

    iStart();
    return 0;
}