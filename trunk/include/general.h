/* 
**  bibleQuiz for Wii - Created by wplaat (www.plaatsoft.nl) 
**
**  Copyright (C) 2008-2009
**  =======================
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, version 2.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "GRRLIB.h"

// -----------------------------------------------------------
// DEFINES
// -----------------------------------------------------------

#define LAN(x) x

#define PROGRAM_NAME	    		"BibleQuiz"
#define PROGRAM_VERSION     	"0.94"
#define RELEASE_DATE        	"19-11-2009" 

#define FILENAME_LANGUAGES  	"languages.xml"
#define DATA_DIRECTORY      	"sd:/apps/bibleQuiz/data"
#define HIGHSCORE_FILENAME  	"sd:/apps/bibleQuiz/highscore.xml"
#define TRACE_FILENAME      	"sd:/apps/bibleQuiz/biblequiz.trc"
#define GAME_DIRECTORY      	"sd:/apps/bibleQuiz/"
#define URL_TOKEN           	" Version "

// Check latest available version 
#define URL1                	"http://www.plaatsoft.nl/service/releasenotes2.html"
#define ID1			        		"UA-6887062-1"

// Fetch Release notes
#define URL2                	"http://www.plaatsoft.nl/service/releasenotes2.html"
#define ID2				    		"UA-6887062-1"

// Set Get Today HighScore
#define URL3                	"http://www.plaatsoft.nl/service/score_set_today.php"
#define ID3				    		"UA-6887062-1"

// Set Get Global HighScore
#define URL4                	"http://www.plaatsoft.nl/service/score_set_global.php"
#define ID4				    		"UA-6887062-1"

#define COLOR_LIGHTBLUE     0xEBCE87
#define COLOR_WHITESMOKE    0xFFFFFF
#define IMAGE_COLOR         0xFFFFFFFF

#define WSP_POINTER_X       200
#define WSP_POINTER_Y       250

#define MAX_LANGUAGES		5
#define MAX_BUTTONS         10
#define MAX_TOPICS			20
#define MAX_HIGHSCORE		(MAX_LANGUAGES * MAX_TOPICS)
#define MAX_QUESTIONS		100
#define MAX_ANSWERS         4
#define MAX_RUMBLE			4
#define MAX_HORZ_PIXELS		640
#define MAX_VERT_PIXELS		480
#define MAX_SOUND_VOLUME	10
#define MAX_BUFFER_SIZE	    8196
#define MAX_LEN			 	200
#define MAX_MUSIC_TRACK     10
#define MAX_ANGLE			360
#define MAX_ALFA			128
#define MAX_POINTER         4

#define IR_X_OFFSET         40
#define IR_Y_OFFSET         40

#define MUSIC_MULTIPLER		5
#define EFFECT_MULTIPLER	20

#define ICON_X				440
#define ICON_Y				-25
#define ICON_ZOOM			0.3

#define BUTTON_A            (WPAD_BUTTON_A     | WPAD_CLASSIC_BUTTON_A)
#define BUTTON_HOME         (WPAD_BUTTON_HOME  | WPAD_CLASSIC_BUTTON_HOME)
#define BUTTON_1            (WPAD_BUTTON_1     | WPAD_CLASSIC_BUTTON_X)
#define BUTTON_2            (WPAD_BUTTON_2     | WPAD_CLASSIC_BUTTON_Y)
#define BUTTON_MINUS        (WPAD_BUTTON_MINUS | WPAD_CLASSIC_BUTTON_MINUS)
#define BUTTON_PLUS         (WPAD_BUTTON_PLUS  | WPAD_CLASSIC_BUTTON_PLUS)

// -----------------------------------------------------------
// TYPEDEFS and ENUMS
// -----------------------------------------------------------
 
typedef struct
{
    int  id;
	char name[MAX_LEN];
	char translation[MAX_LEN];
	char topics[MAX_LEN];
}
language;

language languages[MAX_LANGUAGES+1];

typedef struct
{
    int  id;
    char name[MAX_LEN];
	char filename[MAX_LEN];
}
topic;

typedef struct 
{
	char author[MAX_LEN];
	char topic[MAX_LEN];
	char timestamp[MAX_LEN];
	char note[MAX_LEN];
}
info;

info information;

topic topics[MAX_TOPICS];

typedef struct
{
   char question[MAX_LEN]; 
   char answerA[MAX_LEN]; 
   char answerB[MAX_LEN]; 
   char answerC[MAX_LEN]; 
   char answerD[MAX_LEN]; 
   int  answer;
   char explanation[MAX_LEN]; 
   bool played;
   bool enabled[4];
} 
question;

question questions[MAX_QUESTIONS+1];


typedef struct 
{
    char labelWelcome[MAX_LEN];
	char labelTopic[MAX_LEN];
	char labelScore[MAX_LEN];
	char labelCreated[MAX_LEN];
	char labelQuestion[MAX_LEN];
	char labelAnswers[MAX_LEN];
	char labelResult[MAX_LEN];
	char labelCategory1[MAX_LEN];
	char labelCategory2[MAX_LEN];
	char labelCategory3[MAX_LEN];
	char labelRight[MAX_LEN];
	char labelWrong[MAX_LEN];
	char labelAuthor[MAX_LEN];
	char labelGoodbye[MAX_LEN];
	char labelMusic[MAX_LEN];
	char labelEffects[MAX_LEN];
	char labelHighScore[MAX_LEN];
	char labelDate[MAX_LEN];
    char labelHints[MAX_LEN];
	char labelPlayTime[MAX_LEN];
	char labelResults[MAX_LEN];
	char labelHelp[MAX_LEN];
	char labelTrack[MAX_LEN];
	char labelNewVersion[MAX_LEN];
		
	char buttonAnswerA[MAX_LEN];
	char buttonAnswerB[MAX_LEN];
	char buttonAnswerC[MAX_LEN];
	char buttonAnswerD[MAX_LEN];
	char buttonHint[MAX_LEN];
	char buttonRetry[MAX_LEN];
	char buttonPlay[MAX_LEN];
	char buttonNext[MAX_LEN];
	char buttonStop[MAX_LEN];
	char buttonExit1[MAX_LEN];
	char buttonExit2[MAX_LEN];
	char buttonContinue[MAX_LEN];
	char buttonSound[MAX_LEN];
	char buttonBack[MAX_LEN];
	char buttonCredits[MAX_LEN];
	char buttonPrevious[MAX_LEN];
	char buttonReleaseNotes[MAX_LEN];
}
trans;

trans translation;


typedef struct
{
   GRRLIB_texImg image;
   GRRLIB_texImg imageSelect;
   char name[MAX_LEN]; 
   bool enabled;
   int x;
   int y;
   int xtext;
   int ytext;
} 
button;

button buttons[MAX_BUTTONS+1];


typedef struct 
{
  // png + jpg Image index  
  GRRLIB_texImg button1;
  GRRLIB_texImg button1select;
  GRRLIB_texImg button2;
  GRRLIB_texImg button2select;
  GRRLIB_texImg button3;
  GRRLIB_texImg button3select;
  
  GRRLIB_texImg banner;
  GRRLIB_texImg panel1;
  GRRLIB_texImg panel2;
  GRRLIB_texImg bar1;
  GRRLIB_texImg bar_cursor1;
  
  GRRLIB_texImg english_flag;
  GRRLIB_texImg nederlands_flag;
  GRRLIB_texImg deutsch_flag;
  GRRLIB_texImg spanish_flag;
  GRRLIB_texImg france_flag;
  
  GRRLIB_texImg help;
  GRRLIB_texImg right;
  GRRLIB_texImg wrong;
  GRRLIB_texImg sound;
  GRRLIB_texImg exit;
  GRRLIB_texImg info;
  GRRLIB_texImg question;
  
  GRRLIB_texImg background1;
  GRRLIB_texImg background2;
  GRRLIB_texImg background3;
  GRRLIB_texImg background4;
  
  GRRLIB_texImg pointer1;
  GRRLIB_texImg pointer2;
  GRRLIB_texImg pointer3;
  GRRLIB_texImg pointer4;
  
  GRRLIB_texImg logo;
  GRRLIB_texImg logo1;
  GRRLIB_texImg logo2;
  GRRLIB_texImg logo3;
  GRRLIB_texImg logo4;
  GRRLIB_texImg logo5;
  GRRLIB_texImg logo6;
} 
image;

image images;


typedef struct
{
  time_t startTime;
  time_t playTime;
  int    score;
  int    questions;
  int    hint;
  int    topicId;
  char   topic[MAX_LEN];
  int    languageId;
}
highscore;

highscore highscores[MAX_TOPICS+1];

typedef struct 
{
  ir_t    ir;
  int     x;
  int     xOffset;
  int     y;
  int     yOffset;
  int     angle;
  int     rumble;
}
pointer;

pointer pointers[MAX_POINTER];

// -----------------------------------------------------------
// ENUMS
// -----------------------------------------------------------

enum
{
   stateIntro1=0,   
   stateIntro2=1, 
   stateIntro3=2,    
   stateWelcome=3,
   stateQuestion=4,
   stateAnswer=5,
   stateResult=6,
   stateGoodbye=7,
   stateSound=8,
   stateCredits=9,
   stateHighScore=10,
   stateHelp=11,
   stateReleaseNotes=12,
   stateNone=13 
};

enum
{
   fontTitle=0,
   fontSubTitle=1,
   fontParagraph=2,
   fontNormal=3,
   fontSpecial=4,
   fontButton=5,
   fontNew=6,
   fontHead=7
};

// -----------------------------------------------------------
// The End
// -----------------------------------------------------------