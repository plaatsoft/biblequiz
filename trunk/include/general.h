/**
 * @file
 * @brief This file contain all defines
 *
 *  Created by wplaat (www.plaatsoft.nl)
 *
 *  Copyright (C) 2008-2010
 *  =======================
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

#include "GRRLIB.h"

// -----------------------------------------------------------
// DEFINES
// -----------------------------------------------------------

#define LAN(x) x

#define PROGRAM_NAME	    		"BibleQuiz"
#define PROGRAM_VERSION     	"0.95"
#define RELEASE_DATE        	"31-03-2009" 

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

#define COLOR_LIGHTBLUE     	0xEBCE87
#define COLOR_WHITESMOKE   	0xFFFFFF
#define IMAGE_COLOR         	0xFFFFFFFF

#define WSP_POINTER_X       	200
#define WSP_POINTER_Y       	250

#define MAX_LANGUAGES			6
#define MAX_BUTTONS         	10
#define MAX_TOPICS				20
#define MAX_HIGHSCORE			(MAX_LANGUAGES * MAX_TOPICS)
#define MAX_QUESTIONS			100
#define MAX_ANSWERS         	4
#define MAX_RUMBLE				4
#define MAX_HORZ_PIXELS			640
#define MAX_VERT_PIXELS			480
#define MAX_SOUND_VOLUME		10
#define MAX_BUFFER_SIZE	    	8196
#define MAX_LEN			 		200
#define MAX_MUSIC_TRACK     	10
#define MAX_ANGLE					360
#define MAX_ALFA					128
#define MAX_POINTERS         	4

#define IR_X_OFFSET         	40
#define IR_Y_OFFSET         	40

#define MUSIC_MULTIPLER			5
#define EFFECT_MULTIPLER		20

#define ICON_X						440
#define ICON_Y						-25
#define ICON_ZOOM					0.3

#define BUTTON_A            	(WPAD_BUTTON_A     | WPAD_CLASSIC_BUTTON_A)
#define BUTTON_HOME         	(WPAD_BUTTON_HOME  | WPAD_CLASSIC_BUTTON_HOME)
#define BUTTON_1            	(WPAD_BUTTON_1     | WPAD_CLASSIC_BUTTON_X)
#define BUTTON_2            	(WPAD_BUTTON_2     | WPAD_CLASSIC_BUTTON_Y)
#define BUTTON_MINUS        	(WPAD_BUTTON_MINUS | WPAD_CLASSIC_BUTTON_MINUS)
#define BUTTON_PLUS         	(WPAD_BUTTON_PLUS  | WPAD_CLASSIC_BUTTON_PLUS)

// -----------------------------------------------------------
// ENUMS
// -----------------------------------------------------------

enum
{
   stateIntro1=0,   
   stateIntro2=1, 
   stateIntro3=2,    
   stateMenu=3,
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
   bool done;
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
  GRRLIB_texImg italiano_flag;
  
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
  GRRLIB_texImg image;
  int     x;
  int     xOffset;
  int     y;
  int     yOffset;
  int     angle;
  int     rumble;
}
pointer;

pointer pointers[MAX_POINTERS];

/** 
 * @mainpage Wii BibleQuiz Documentation
 * @image html BibleQuiz.png
 *   Welcome to the BibleQuiz documentation.
 *
 * @section Introduction
 *   BibleQuiz is a classic bible quiz game for the Nintendo Wii.
 *
 * @section Links
 *   Website: http://www.plaatsoft.nl\n
 *   Code: http://code.google.com/p/biblequiz\n
 *
 * @section Credits
 *   Documentation: wplaat\n
 *
 * @section ReleaseNotes
 *  <b>16-05-2010 Version 0.96</b>
 *  - GUI:
 *   - Added italiano translation (Thanks Ezio Soma).
 *  - Core: 
 *   - Added random question mode (Thanks Ezio Soma).
 *  - Content:
 *   - Added 194 (5 topics) italiano questions (Thanks Ezio Soma)
 *  - Core:
 *   - Build game with devkitPPC r21 compiler
 *
 *  <b>31-03-2010 Version 0.95</b>
 *  - GUI:
 *    - Update main menu screen information.
 *    - Improve game icon.
 *  - Core:
 *    - WiiMote timeout increase from 60 to 300 seconds.
 *    - Improve stability.
 *    - Improve network thread.
 *    - Use libfat 1.0.7 as disk access engine.
 *    - Use libogc 1.8.3 as Wii interface engine.
 *  - General:
 *   - Make source code compliant with r21 compiler.
 *   - Added source code to Google Code Repository.
 *   - Added source code documentation (Javadoc style).
 *   - Added Doxygen (automatic documentation generation tool) config file.
 *   - Build game with devkitPPC r21 compiler.
 *
 *  <b>19-11-2009 Version 0.94</b>
 *  - GUI:
 *   - Update main menu screen.
 *  - Core:
 *   - Improve stablility.
 *   - Added functionality to trace game events to trace file.
 *   - Improve network thread.
 *   - Use libfat 1.0.6 as disk access engine.
 *   - Use libmxml 2.6 library as xml engine.
 *   - Use libogc 1.8.0 library as Wii interface engine.
 *  - Content:
 *   - Added 10 spanish questions (1 topic)
 *  - General:
 *   - Maintenance release.
 *   - Build game with devkitPPC r19 compiler.
 *
 *  <b>10-09-2009 Version 0.93</b>
 *  - GUI:
 *   - Improve intro screens.
 *  - Core:
 *   - Use the asndlib (part of libogc) now as standard sound engine.
 *   - Use libfat 1.0.4 as disk access engine.
 *   - use libogc 1.7.1a as Wii interface engine.
 *  - General:
 *   - Build game with devkitPPC r17 compiler.
 *
 *  <b>13-03-2009 Version 0.92</b>
 *  - GUI:
 *   - Improve intro screens.
 *   - Added fps information on all screens.
 *  - Core:
 *   - Added screenshot functionality with plus button.
 *   - use GRRLIB v4.0 library as graphical render engine.
 *   - Pictures are store on the SdCard in the following directory sd:/apps/bibleQuiz
 *  - General:
 *   - Build game with devkitPPC r16 compiler.
 *
 *  <b>06-02-2009 Version 0.91</b>
 *  - GUI:
 *   - Add multi player mode for two, three and four players.
 *   - Improve third intro screen.
 *  - Core:
 *   - Increase http receive buffer size to 8196 bytes.
 *   - Use only one unique cookie number during the game.
 *   - Bugfix: Highscore is now always loaded correctly.
 *  - General:
 *   - Build game with devkitPPC r16 compiler.
 *
 *  <b>15-01-2009 Version 0.90</b>
 *  - GUI:
 *   - Update url on intro screens to www.plaatsoft.nl (My new domain).
 *   - Network thread status is now showed on welcome screen.
 *  - Core:
 *   - Bugfix: Remove some small reported graphical bugs.
 *   - Bugfix: Remove several bugs in network thread.
 *  - General:
 *   - Build game with devkitPPC r16 compiler.
 *
 *  <b>23-12-2008 Version 0.80</b>
 *  - GUI:
 *   - Bugfix: IR pointer doesn't disappear anymore.
 *  - Core:
 *   - Added SDHC card support
 *   - Added power button support
 *  - General:
 *   - Build game with devkitPPC r16 compiler.
 *
 *  <b>09-12-2008 Version 0.70</b>
 *  - GUI:
 *   - Added release notes screen.
 *   - Added functionality to fetch release notes from internet.
 *   - Improve highscore information (Show maximun score pre topic). 
 *   - Improve IR pointer.
 *  - Improve result screen information. 
 *  - Core:
 *   - Added google analytic http request (including highscore information).
 *  - General:
 *   - Build game with devkitPPC r16 compiler.
 * 
 *  <b>26-11-2008 Version 0.60</b>
 *  - GUI:
 *   - All texts are now created with the freetype library (Thanks DrTwox) 
 *   - Added check if new version is available.
 *   - Added animated screen icons
 *  - Core:
 *   - Solved some minor reported bugs
 *   - use ligogc 1.7.1 as Wii Interface library.
 *  - Content:
 *   - Added 100 english questions (4 topics).
 *   - Added 10 dutch questions (1 topic).
 *   - Added 10 german questions (1 topic).
 *   - Added france translation.
 *   - Corrected some wrong answers.
 *  - General:
 *   - Build game with devkitPPC r16 compiler.
 *
 *  <b>19-11-2008 Version 0.40</b>
 *  - GUI:
 *   - Added highscore screen.
 *   - Highscore is stored (in xml format) on the SD card
 *   - Added credits screen.
 *   - Added help (minus button) screen.
 *   - Added 10 music tracks.
 *  - Core:
 *   - Use freetype library as font render engine for screen (sub)titles.
 *   - Hotfix to prevent core dump with 60Hz (480i) Tv mode
 *  - Content:
 *  	- Added 170 english questions (8 topics).
 *  	- Added 100 dutch questions (4 topics).
 *  	- Added spanisch translation.
 *  - General:
 *   - Donated the bibleQuiz source code to the community. Comments are welcome ;-} 
 *   - Build game with devkitPPC r15 compiler.
 * 
 *  <b>15-11-2008 Version 0.30</b>
 *  - GUI:
 *   - Added language / topic select screen
 *   - Added goodbye screen
 *   - Added sound volume control screen
 *  - Content:
 *   - Added German language
 *   - Added 20 English question (1 topic)
 *   - Added 10 Dutch question (1 topic)
 *  - General:
 *   - First release for the Wii HomeBrew community
 *   - Complete rebuild from game engine
 *   - Build game with devkitPPC r15 compiler.
 * 
 *  <b>08-11-2008 Version 0.20</b>
 *  - GUI:
 *   - Added question result image with animation
 *   - Added multi language support
 *   - Added three hint buttons
 *   - Added score result screen
 *   - Added exit button
 *  - Core:
 *   - Added support for xml question files
 *   - Added support for 60Hz (480i) TV mode
 *   - Added sndlib module with some sound effects
 *   - Added question word wrap function 
 *  - General:
 *   - Build game with devkitPPC r15 compiler.
 * 
 *  <b>03-11-2008 Version 0.10</b>
 *  - GUI:
 *   - Added WiiRemote IR control.
 *   - Added three welcome screens.
 *   - Added button rumble effect.
 *  - Core:
 *   - Use GRRlib are graphical engine.
 *   - Use libogc 1.6.0 as Wii Interface engine.
 *  - General:
 *   - Started programming.
 *   - Gameboard design.
 *   - Build game with devkitPPC r15 compiler.
 *
 * @section Licence
 *   <b>Copyright (c) 2008-2010 Plaatsoft</b>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, version 2.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
// -----------------------------------------------------------
// The End
// -----------------------------------------------------------