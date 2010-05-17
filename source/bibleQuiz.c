/** 
 *  @file
 *  @brief Wii BibleQuiz game core
 *  @author wplaat
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <ogcsys.h>
#include <gccore.h>
#include <gcmodplay.h> 
#include <wiiuse/wpad.h>
#include <fat.h>
#include <mxml.h>
#include <asndlib.h>   
#include <fcntl.h>
#include <unistd.h>
#include <time.h> 
#include <ft2build.h> 
#include FT_FREETYPE_H 
#include <ogc/lwp_watchdog.h>	

#include "general.h" 
#include "http.h"
#include "trace.h"
#include "track1_mod.h"
#include "track2_mod.h"
#include "track3_mod.h"
#include "track4_mod.h"
#include "track5_mod.h"
#include "track6_mod.h"
#include "track7_mod.h"
#include "track8_mod.h"
#include "track9_mod.h"
#include "effect1_wav.h"
#include "effect2_wav.h"
#include "effect3_wav.h"

// -----------------------------------------------------------
// VARIABLES
// -----------------------------------------------------------

//u32     *frameBuffer[1] = {NULL};
GXRModeObj *rmode = NULL;
Mtx     GXmodelView2D;

static  MODPlay snd1;

int     yOffset           = 0;
int     yjpegOffset       = 0;
int     angle             = 0;
int     alfa              = 0;
bool    alfa_direction    = true;
float   size              = 0;
float   wave1             = 0;
float   wave2             = 0;

int     score             = 0;
int     hintCounter       = 0;
time_t  startTime;
time_t  playTime;
bool    correctAnswer     = false;

int     maxQuestions      = 0;
int     maxLanguages      = 0;
int     maxTopics         = 0;
int     maxButtons        = 0;
int     maxHighScores     = 0;

int     selectedLanguage  = 0;
int     selectedTopic     = 0;
int     selectedQuestion  = 0;
int     rndSelectedQuestion  = 0;
int     selectedMusic     = 0;

int     musicVolume       = 5;
int     effectVolume      = 5;
int     notesStartLine    = 0;
int     noteDelay         = 0;

int     stateMachine;
int     stateMachinePrev;
int     stateMachineStorage;
int     stateMachineStorage2;

// Poweroff flag
bool bPowerOff = false;	

FT_Library library=NULL;  
FT_Face face=NULL;              
FT_GlyphSlot slot;        
FT_Bitmap *FT_image;

// Banner Image
extern const unsigned char 	   pic1data[];
extern int      pic1length;

// Button1 Image
extern const unsigned char     pic2data[];
extern int      pic2length;

// Button1select Image
extern const unsigned char     pic3data[];
extern int      pic3length;

// Button2 Image
extern const unsigned char     pic4data[];
extern int      pic4length;

// Button2select Image
extern const unsigned char     pic5data[];
extern int      pic5length;

// Panel1 Image
extern const unsigned char     pic7data[];
extern int      pic7length;

// pionter Image
extern const unsigned char     pic8data[];
extern int      pic8length;

// Welcome1 Image
extern const unsigned char     pic9data[];
extern int      pic9length;

// Welcome2 Image
extern const unsigned char     pic10data[];
extern int      pic10length;

// Welcome3 Image
extern const unsigned char     pic11data[];
extern int      pic11length;

// welcome4 Image
extern const unsigned char     pic12data[];
extern int      pic12length;

// english flag Image
extern const unsigned char     pic13data[];
extern int      pic13length;

// nederlands flag Image
extern const unsigned char     pic14data[];
extern int      pic14length;

// deutsch flag Image
extern const unsigned char     pic15data[];
extern int      pic15length;

// Italiano flag Image
extern const unsigned char     pic45data[];
extern int      pic45length;

// bar1 Image
extern const unsigned char     pic16data[];
extern int      pic16length;

// bar_cursor1 Image
extern const unsigned char     pic17data[];
extern int      pic17length;

// button3 Image
extern const unsigned char     pic18data[];
extern int      pic18length;

// button3select Image
extern const unsigned char     pic19data[];
extern int      pic19length;

// Panel2 Image
extern const unsigned char     pic21data[];
extern int      pic21length;

// Spanish flag Image
extern const unsigned char     pic22data[];
extern int      pic22length;

// Help image
extern const unsigned char     pic23data[];
extern int      pic23length;

// france flag image
extern const unsigned char     pic24data[];
extern int      pic24length;

// right icon
extern const unsigned char     pic25data[];
extern int      pic25length;

// wrong icon
extern const unsigned char     pic26data[];
extern int      pic26length;

// sound icon 
extern const unsigned char     pic28data[];
extern int      pic28length;

// exit icon 
extern const unsigned char     pic29data[];
extern int      pic29length;

// Info icon 
extern const unsigned char     pic30data[];
extern int      pic30length;

// Question icon 
extern const unsigned char     pic31data[];
extern int      pic31length;

// Background1 icon
extern const unsigned char     pic33data[];
extern int      pic33length;

// Background2 icon
extern const unsigned char     pic34data[];
extern int      pic34length;

// Background3 icon
extern const unsigned char     pic35data[];
extern int      pic35length;

// pointer2 image
extern const unsigned char     pic36data[];
extern int      pic36length;

// pointer3 image
extern const unsigned char     pic37data[];
extern int      pic37length;

// pointer4 image
extern const unsigned char     pic38data[];
extern int      pic38length;

// logo2 image
extern const unsigned char     pic39data[];
extern int      pic39length;

// logo3 icon
extern const unsigned char     pic40data[];
extern int      pic40length;

// logo4 image
extern const unsigned char     pic41data[];
extern int      pic41length;

// logo5 image
extern const unsigned char     pic42data[];
extern int      pic42ength;

// logo6 image
extern const unsigned char     pic43data[];
extern int      pic43length;

// background4 image
extern const unsigned char     pic44data[];
extern int      pic44length;


// Language xml file.
extern char     xml1data[];
extern int      xml1length;

// English translation xml file.
extern char     xml2data[];
extern int      xml2length;

// -----------------------------------------------------------
// GAME LOGIC
// -----------------------------------------------------------

static u8 CalculateFrameRate() {

    static u8 frameCount = 0;
    static u32 lastTime;
    static u8 FPS = 0;
    u32 currentTime = ticks_to_millisecs(gettime());

    frameCount++;
    if(currentTime - lastTime > 1000) {
        lastTime = currentTime;
        FPS = frameCount;
        frameCount = 0;
    }
    return FPS;
}

void saveHighScore(char* filename) {

   char *s_fn="saveHighScore";
   traceEvent(s_fn,0,"enter");
   
   int i;
   mxml_node_t *xml;
   mxml_node_t *group;
   mxml_node_t *data=NULL;   
   char tmp[100];
      
   xml = mxmlNewXML("1.0");   
   group = mxmlNewElement(xml, "bibleQuiz");
   for(i=0; i<maxHighScores; i++) {
	
      data = mxmlNewElement(group, "topic");
  
      //Create Some config value
	  sprintf(tmp, "%d", (int) highscores[i].startTime);
      mxmlElementSetAttr(data, "startTime", tmp);
	  
	  sprintf(tmp, "%d", (int) highscores[i].playTime);
	  mxmlElementSetAttr(data, "playTime", tmp);
	  
	  sprintf(tmp, "%d", highscores[i].score);
      mxmlElementSetAttr(data, "score", tmp);
	  
	  sprintf(tmp, "%d", highscores[i].questions);
      mxmlElementSetAttr(data, "questions", tmp);
	  
	  sprintf(tmp, "%d", highscores[i].hint);
      mxmlElementSetAttr(data, "hint", tmp);
	  
	  sprintf(tmp, "%d", highscores[i].topicId);
      mxmlElementSetAttr(data, "topicId", tmp);
	  
      sprintf(tmp, "%s", highscores[i].topic);
      mxmlElementSetAttr(data, "topic", tmp);
	  
	  sprintf(tmp, "%d", highscores[i].languageId);
      mxmlElementSetAttr(data, "languageId", tmp);
   }
  
   /* now lets save the xml file to a file! */
   FILE *fp;
   fp = fopen(filename, "w");

   mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);
   
   /*Time to clean up!*/
   fclose(fp);
   mxmlDelete(data);
   mxmlDelete(group);
   mxmlDelete(xml);
   
   traceEvent(s_fn,0,"leave [void]");
}
  
void initHighScore(char* filename) {

   char *s_fn="initHighScore" ;
   traceEvent(s_fn,0,"enter");
   
   maxHighScores=0;

   FILE *fp;
   mxml_node_t *tree=NULL;
   mxml_node_t *data=NULL;
   const char *tmp;
   
   /*Load our xml file! */
   fp = fopen(filename, "r");
   if (fp!=NULL)
   {
     tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
     fclose(fp);

     for (data = mxmlFindElement(tree, tree, "topic", NULL, NULL, MXML_DESCEND);
       data != NULL;
       data = mxmlFindElement(data, tree, "topic", NULL, NULL, MXML_DESCEND)) {		   
		 
        tmp=mxmlElementGetAttr(data,"startTime");   
        if (tmp!=NULL) highscores[maxHighScores].startTime=atoi(tmp); else highscores[maxHighScores].startTime=0;
		
		tmp=mxmlElementGetAttr(data,"playTime"); 
		if (tmp!=NULL) highscores[maxHighScores].playTime=atoi(tmp); else highscores[maxHighScores].playTime=0;
		
		tmp=mxmlElementGetAttr(data,"score"); 
		if (tmp!=NULL) highscores[maxHighScores].score=atoi(tmp); else highscores[maxHighScores].score=0;
		
		tmp=mxmlElementGetAttr(data,"questions"); 
		if (tmp!=NULL) highscores[maxHighScores].questions=atoi(tmp); else highscores[maxHighScores].questions=0;
				
		tmp=mxmlElementGetAttr(data,"hint"); 
		if (tmp!=NULL) highscores[maxHighScores].hint=atoi(tmp); else highscores[maxHighScores].hint=0;

		tmp=mxmlElementGetAttr(data,"topicId"); 
		if (tmp!=NULL) highscores[maxHighScores].topicId=atoi(tmp); else highscores[maxHighScores].topicId=0;

        tmp=mxmlElementGetAttr(data,"topic"); 
		if (tmp!=NULL) strcpy(highscores[maxHighScores].topic,tmp); else strcpy(highscores[maxHighScores].topic,"");
		
		tmp=mxmlElementGetAttr(data,"languageId"); 
		if (tmp!=NULL) highscores[maxHighScores].languageId=atoi(tmp); else highscores[maxHighScores].languageId=0;
		
		maxHighScores++;
	 } 
   }   
   mxmlDelete(data);
   mxmlDelete(tree);
   traceEvent(s_fn,0,"leave [void]");
}

void processHighScore(void) {

   char *s_fn="processHighScore";
   traceEvent(s_fn,0,"enter");

   bool found=false;
   int i;
   
   // Check if highscore is reached
   for (i=0; i<maxHighScores; i++) {
	
      if ( topics[selectedTopic].id==highscores[i].topicId ) {
		
			// Update exiting entry, if needed
         if ( score>highscores[i].score) {
			
				highscores[i].startTime=startTime;
				highscores[i].playTime=playTime;
				highscores[i].score=score;
				highscores[i].questions=maxQuestions;
				highscores[i].hint=hintCounter;
				highscores[i].topicId=topics[selectedTopic].id;
				strcpy(highscores[i].topic,topics[selectedTopic].name);
				highscores[i].languageId=languages[selectedLanguage].id;
			   
				// Store updated high score in file
				saveHighScore(HIGHSCORE_FILENAME);
			}
			found=true;
		}
   }
   
   // new entry in highscore 
   if (!found) {
	
		highscores[maxHighScores].startTime=startTime;
		highscores[maxHighScores].playTime=playTime;
		highscores[maxHighScores].score=score;
		highscores[maxHighScores].questions=maxQuestions;
		highscores[maxHighScores].hint=hintCounter;
		highscores[maxHighScores].topicId=topics[selectedTopic].id;
		strcpy(highscores[maxHighScores].topic,topics[selectedTopic].name);
		highscores[maxHighScores].languageId=languages[selectedLanguage].id;
		maxHighScores++;
	  
		// Store new high score in file
		saveHighScore(HIGHSCORE_FILENAME);
   }
   traceEvent(s_fn,0,"leave [void]");
}

void initThreads(void) { 

   char *s_fn="initThreads";
   traceEvent(s_fn,0,"enter");
   
   char userData1[MAX_LEN];
   char userData2[MAX_LEN];

   // Set userData1   		 
   memset(userData1,0x00,sizeof(userData1));
   sprintf(userData1,"%s=%s",PROGRAM_NAME,PROGRAM_VERSION);
		
   // Get userData2 
   memset(userData2,0x00,sizeof(userData2));
   sprintf(userData2,"appl=%s",PROGRAM_NAME);
	   
   LAN(tcp_start_thread(PROGRAM_NAME, PROGRAM_VERSION, 
						ID1, URL1, 
						ID2, URL2, 
						ID3, URL3, 
						ID4, URL4, 
						URL_TOKEN, userData1, userData2);)
						
   traceEvent(s_fn,0,"leave [void]");
}

void initGame() {

   char *s_fn="initGame";
   traceEvent(s_fn,0,"enter");
	
   // Clear memory  
   memset(languages,0x00,sizeof(languages));
   memset(topics,0x00,sizeof(topics));
   memset(questions,0x00,sizeof(questions));
   memset(buttons,0x00,sizeof(buttons));
   memset(highscores,0x00,sizeof(highscores));   
   memset(&images,0x00,sizeof(images));
   memset(&information,0x00,sizeof(information));
   memset(&translation,0x00,sizeof(translation));
   
   // Set variables
   stateMachine=stateIntro1;    
   stateMachinePrev=stateNone; 
   
   selectedLanguage=0;
   selectedTopic=0;
   selectedQuestion=0;

   selectedMusic=1;
   musicVolume=5;
   effectVolume=8;
   
   notesStartLine=4;
   noteDelay=0;

   angle=0;
   alfa=0;
   alfa_direction=true;

   score=0;
   hintCounter=0;
   startTime=time(NULL);
   correctAnswer=false;
   
   traceEvent(s_fn,0,"leave [void]");
}

void initLanguages(char* filename)
{
   char *s_fn="initLanguages";
   traceEvent(s_fn,0,"enter");
   
   maxLanguages=0;

   FILE *fp;
   mxml_node_t *tree;
   mxml_node_t *group;   
   const char  *pointer;

   char tmp[MAX_LEN];
   sprintf(tmp,"%s/%s", DATA_DIRECTORY, filename);

   /*Load our xml file! */
   fp = fopen(tmp, "r");
   if (fp!=NULL) {   
      tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
      fclose(fp);
   } else {
      // If file is not found, us internal xml file.
      tree = mxmlLoadString(NULL, xml1data, MXML_TEXT_CALLBACK);
   }
    
   // Read Questions
   for (group = mxmlFindElement(tree, tree, "language", NULL, NULL, MXML_DESCEND);
        group != NULL;
        group = mxmlFindElement(group, tree, "language", NULL, NULL, MXML_DESCEND)) {
		  
      pointer=mxmlElementGetAttr(group,"name");
		if (pointer!=NULL)  {
			strcpy(languages[maxLanguages].name,pointer); 
		} else {
			strcpy(languages[maxLanguages].name,"");
		}
	  	  
      pointer=mxmlElementGetAttr(group,"translation");
      if (pointer!=NULL) {
			strcpy(languages[maxLanguages].translation,pointer); 
		} else { 
			strcpy(languages[maxLanguages].translation,"");
		}
	  
      pointer=mxmlElementGetAttr(group,"topics");
      if (pointer!=NULL) { 
			strcpy(languages[maxLanguages].topics,pointer); 
		} else {
			strcpy(languages[maxLanguages].topics,"");
		}
	
      pointer=mxmlElementGetAttr(group,"id");
      if (pointer!=NULL) {
			languages[maxLanguages].id=atoi(pointer); 
		} else {
			languages[maxLanguages].id=0;
		}
	 	  
		maxLanguages++;	  
   }
   
   mxmlDelete(group);
   mxmlDelete(tree);
   traceEvent(s_fn,0,"leave [void]");
}

void initMusicTrack(void)
{
   char *s_fn="initMusicTrack";
   traceEvent(s_fn,0,"enter");
   
   
   switch (selectedMusic)
   {
      case 1 : MODPlay_SetMOD(&snd1, track1_mod);
			   MODPlay_Start(&snd1);	
			   break;	
			   
      case 2 : MODPlay_SetMOD(&snd1, track2_mod);
			   MODPlay_Start(&snd1);	
			   break;
			   
      case 3 : MODPlay_SetMOD(&snd1, track3_mod);
			   MODPlay_Start(&snd1);	
			   break;
			   
      case 4 : MODPlay_SetMOD(&snd1, track4_mod);
			   MODPlay_Start(&snd1);	
			   break;
			   
      case 5 : MODPlay_SetMOD(&snd1, track5_mod);
			   MODPlay_Start(&snd1);	
			   break;	
		   
	  case 6 : MODPlay_SetMOD(&snd1, track6_mod);
			   MODPlay_Start(&snd1);	
			   break;	
			   
	  case 7 : MODPlay_SetMOD(&snd1, track7_mod);
			   MODPlay_Start(&snd1);	
			   break;	
			   
	  case 8 : MODPlay_SetMOD(&snd1, track8_mod);
			   MODPlay_Start(&snd1);	
			   break;	
			   
	  case 9 : MODPlay_SetMOD(&snd1, track9_mod);
			   MODPlay_Start(&snd1);	
			   break;
   } 
   
	MODPlay_SetVolume( &snd1, 
		musicVolume*MUSIC_MULTIPLER,
		musicVolume*MUSIC_MULTIPLER); 
   
	traceEvent(s_fn,0,"leave [void]");
}


void storeXmlValue(mxml_node_t *tree, char *key, char *value) {

   char *s_fn="storeXmlValue";
   traceEvent(s_fn,0,"enter");
    
	mxml_node_t *group;
	const char  *pointer;
  
	group = mxmlFindElement(tree, tree, key, NULL, NULL, MXML_DESCEND);  
	pointer=mxmlElementGetAttr(group,"value");
  
	if (pointer!=NULL) {
     strcpy(value,pointer); 
	} else  {  
     strcpy(value,"");
	}
	mxmlDelete(group);   
	
	traceEvent(s_fn,0,"leave [void]");
}


void initTranslation(char* filename) {
	  
   char *s_fn="initTranslation";
   traceEvent(s_fn,0,"enter");
   
   FILE *fp;
   mxml_node_t *tree;
      
   char tmp[MAX_LEN];
   sprintf(tmp,"%s/%s", DATA_DIRECTORY, filename);
   
   /*Load our xml file! */
   fp = fopen(tmp, "r");
   if (fp!=NULL) {   
      tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
      fclose(fp);
   } else {
      // If file is not found, us internal xml files.	  
      tree = mxmlLoadString(NULL,xml2data, MXML_TEXT_CALLBACK);  
   }

   storeXmlValue(tree, "labelWelcome", translation.labelWelcome);
   storeXmlValue(tree, "labelTopic", translation.labelTopic);
   storeXmlValue(tree, "labelScore", translation.labelScore);
   storeXmlValue(tree, "labelCreated", translation.labelCreated);
   storeXmlValue(tree, "labelQuestion", translation.labelQuestion);
   storeXmlValue(tree, "labelAnswers", translation.labelAnswers);
   storeXmlValue(tree, "labelResult", translation.labelResult);
   storeXmlValue(tree, "labelCategory1", translation.labelCategory1);  
   storeXmlValue(tree, "labelCategory2", translation.labelCategory2);  
   storeXmlValue(tree, "labelCategory3", translation.labelCategory3);   
   storeXmlValue(tree, "labelRight", translation.labelRight); 
   storeXmlValue(tree, "labelWrong", translation.labelWrong);
   storeXmlValue(tree, "labelAuthor", translation.labelAuthor);
   storeXmlValue(tree, "labelGoodbye", translation.labelGoodbye);
   storeXmlValue(tree, "labelMusic", translation.labelMusic);
   storeXmlValue(tree, "labelEffects", translation.labelEffects);
   storeXmlValue(tree, "labelHighScore", translation.labelHighScore);
   storeXmlValue(tree, "labelDate", translation.labelDate);
   storeXmlValue(tree, "labelHints", translation.labelHints);
   storeXmlValue(tree, "labelPlayTime", translation.labelPlayTime);
   storeXmlValue(tree, "labelResults", translation.labelResults);   
   storeXmlValue(tree, "labelHelp", translation.labelHelp);
   storeXmlValue(tree, "labelTrack", translation.labelTrack);
   storeXmlValue(tree, "labelNewVersion", translation.labelNewVersion);
      
   storeXmlValue(tree, "buttonAnswerA", translation.buttonAnswerA);
   storeXmlValue(tree, "buttonAnswerB", translation.buttonAnswerB);
   storeXmlValue(tree, "buttonAnswerC", translation.buttonAnswerC);
   storeXmlValue(tree, "buttonAnswerD", translation.buttonAnswerD);
   storeXmlValue(tree, "buttonHint", translation.buttonHint);	  
   storeXmlValue(tree, "buttonRetry", translation.buttonRetry);	  
   storeXmlValue(tree, "buttonPlay", translation.buttonPlay);
   storeXmlValue(tree, "buttonNext", translation.buttonNext);
   storeXmlValue(tree, "buttonStop", translation.buttonStop);
   storeXmlValue(tree, "buttonExit1", translation.buttonExit1);
   storeXmlValue(tree, "buttonExit2", translation.buttonExit2);   
   storeXmlValue(tree, "buttonContinue", translation.buttonContinue);    
   storeXmlValue(tree, "buttonSound", translation.buttonSound); 
   storeXmlValue(tree, "buttonBack", translation.buttonBack);
   storeXmlValue(tree, "buttonCredits", translation.buttonCredits);
   storeXmlValue(tree, "buttonPrevious", translation.buttonPrevious);
   storeXmlValue(tree, "buttonReleaseNotes", translation.buttonReleaseNotes);
	
   mxmlDelete(tree);
   
   traceEvent(s_fn,0,"leave [void]");
}

void initPointer() {
   int i;
	
	for (i=0; i<MAX_POINTERS; i++) {
	
		switch(i)
		{
		   case 0: 
				pointers[i].image = images.pointer1;
				break;

		   case 1: 
				pointers[i].image = images.pointer2;
				break;

		   case 2: 
				pointers[i].image = images.pointer3;
				break;

		   case 3: 
				pointers[i].image = images.pointer4;
				break;
		}
	}		
}

void initTopics(char* filename) {

   char *s_fn="initTopics";
   traceEvent(s_fn,0,"enter");
   
   
   maxTopics=0;

   FILE *fp;
   mxml_node_t *tree;
   mxml_node_t *group;   
   const char  *pointer;
   char tmp[MAX_LEN];
   
   sprintf(tmp,"%s/%s", DATA_DIRECTORY, filename);
   
   /*Load our xml file! */
   fp = fopen(tmp, "r");
   if (fp!=NULL) {   
      tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
      fclose(fp);
   } else {
      // If file is not found, return direct
      maxTopics=-1;
      return;
   }
    
   // Read Questions
   for (group = mxmlFindElement(tree, tree, "topic", NULL, NULL, MXML_DESCEND);
        group != NULL;
       group = mxmlFindElement(group, tree, "topic", NULL, NULL, MXML_DESCEND))
   {		  
			pointer=mxmlElementGetAttr(group,"name");
			if (pointer!=NULL) {
				strcpy(topics[maxTopics].name,pointer); 
			} else {
				strcpy(topics[maxTopics].name,"");
			}
	  
			pointer=mxmlElementGetAttr(group,"filename");
			if (pointer!=NULL) {
				strcpy(topics[maxTopics].filename,pointer); 
			} else {
				strcpy(topics[maxTopics].filename,"");
			}
   	  
			pointer=mxmlElementGetAttr(group,"id");
			if (pointer!=NULL) {
				topics[maxTopics].id=atoi(pointer); 
			} else {
				topics[maxTopics].id=0;
			}
   
        maxTopics++;    
   }     
   mxmlDelete(group);
   mxmlDelete(tree);   
   
   traceEvent(s_fn,0,"leave [void]");
}

void initQuestions(char* filename)
{
   char *s_fn="initQuestions";
   traceEvent(s_fn,0,"enter");
   
   maxQuestions=0;
   
   FILE *fp;
   mxml_node_t *tree;
   mxml_node_t *group;   
   const char  *pointer;
   char tmp[MAX_LEN];
   
   sprintf(tmp,"%s/%s", DATA_DIRECTORY, filename);
   
   /*Load our xml file! */
   fp = fopen(tmp, "r");
   if (fp!=NULL)
   {   
      tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
      fclose(fp);
   }
   else
   {
      // If file is not found, return direct
	  maxQuestions=-1;
      return;
   }
   
   // Read General stuff of question xm file
   group = mxmlFindElement(tree, tree, "header", NULL, NULL, MXML_DESCEND);  
	 
   pointer=mxmlElementGetAttr(group,"topic");
   if (pointer!=NULL) strcpy(information.topic,pointer); else strcpy(information.topic,"");
	  
   pointer=mxmlElementGetAttr(group,"author");
   if (pointer!=NULL) strcpy(information.author,pointer); else strcpy(information.author,"");
   
   pointer=mxmlElementGetAttr(group,"created");
   if (pointer!=NULL) strcpy(information.timestamp,pointer); else strcpy(information.timestamp,"");

   pointer=mxmlElementGetAttr(group,"note");
   if (pointer!=NULL) strcpy(information.note,pointer); else strcpy(information.note,"");

   // Read Questions
   for (group = mxmlFindElement(tree, tree, "item", NULL, NULL, MXML_DESCEND);
        group != NULL;
        group = mxmlFindElement(group, tree, "item", NULL, NULL, MXML_DESCEND))
   {		  
      pointer=mxmlElementGetAttr(group,"question");
	  if ((pointer!=NULL) && (strlen(pointer)>0))
	  {
	      strcpy(questions[maxQuestions].question,pointer); 
	  }  
	  else 
	  {  
	     strcpy(questions[maxQuestions].question,"");
	  }
	  
      pointer=mxmlElementGetAttr(group,"answerA");
      if ((pointer!=NULL) && (strlen(pointer)>0))
	  {
	     strcpy(questions[maxQuestions].answerA,pointer);
		 questions[maxQuestions].enabled[0]=true; 
      }
      else 
	  {
	     strcpy(questions[maxQuestions].answerA,"");
		 questions[maxQuestions].enabled[0]=false;
	  }
  
      pointer=mxmlElementGetAttr(group,"answerB");
      if ((pointer!=NULL) && (strlen(pointer)>0))
      {  
	      questions[maxQuestions].enabled[1]=true;
          strcpy(questions[maxQuestions].answerB,pointer); 
	  }
	  else 
	  {
	      strcpy(questions[maxQuestions].answerB,"");
		  questions[maxQuestions].enabled[1]=false;
      }
  
      pointer=mxmlElementGetAttr(group,"answerC");
      if ((pointer!=NULL) && (strlen(pointer)>0))
	  {
	      questions[maxQuestions].enabled[2]=true;
	      strcpy(questions[maxQuestions].answerC,pointer); 
	  }
	  else 
	  {
	      strcpy(questions[maxQuestions].answerC,"");
		  questions[maxQuestions].enabled[2]=false;
	  }
  
      pointer=mxmlElementGetAttr(group,"answerD");
      if ((pointer!=NULL) && (strlen(pointer)>0))
      { 
	      questions[maxQuestions].enabled[3]=true;
	      strcpy(questions[maxQuestions].answerD,pointer);  
      }
      else 
	  { 
	      strcpy(questions[maxQuestions].answerD,"");
		  questions[maxQuestions].enabled[3]=false;
	  }
	  
	  //reset the "done" flag
	  
	  questions[maxQuestions].done=false;

    
      pointer=mxmlElementGetAttr(group,"answer");
      if (pointer!=NULL) 
	  {
	     // Convert (A,B,C,D) to (1,2,3,4)
         questions[maxQuestions].answer=pointer[0]-64;  
	  }
	  else
	  {
	     questions[maxQuestions].answer=0;
	  }
		 
	  pointer=mxmlElementGetAttr(group,"explanation");	 
	  if (pointer!=NULL) strcpy(questions[maxQuestions].explanation,pointer); else strcpy(questions[maxQuestions].explanation,"");
		 		 
	  questions[maxQuestions].played=false;
	  
	  maxQuestions++;
   }
     
   mxmlDelete(group);
   mxmlDelete(tree);
   
   traceEvent(s_fn,0,"leave [void]");
}

void initImages(void)
{
   char *s_fn="initImages";
   traceEvent(s_fn,0,"enter");
   
   // Buttons & Panels
   images.button1=GRRLIB_LoadTexture( pic2data);
   images.button1select=GRRLIB_LoadTexture( pic3data);
   images.button2=GRRLIB_LoadTexture( pic4data);
   images.button2select=GRRLIB_LoadTexture( pic5data);
   images.banner=GRRLIB_LoadTexture( pic1data);
   images.panel1=GRRLIB_LoadTexture( pic7data);  
   images.bar1=GRRLIB_LoadTexture( pic16data);
   images.bar_cursor1=GRRLIB_LoadTexture( pic17data);
   images.button3=GRRLIB_LoadTexture( pic18data);
   images.button3select=GRRLIB_LoadTexture( pic19data);
   images.panel2=GRRLIB_LoadTexture( pic21data);
   
   images.pointer1=GRRLIB_LoadTexture( pic8data);
   images.pointer2=GRRLIB_LoadTexture( pic36data);
   images.pointer3=GRRLIB_LoadTexture( pic37data);
   images.pointer4=GRRLIB_LoadTexture( pic38data);
   
   // Land flags
   images.spanish_flag=GRRLIB_LoadTexture( pic22data);
   GRRLIB_InitTileSet(&images.spanish_flag, images.spanish_flag.w, 1, 0);
   images.france_flag=GRRLIB_LoadTexture( pic24data);
   GRRLIB_InitTileSet(&images.france_flag, images.france_flag.w, 1, 0);
   images.english_flag=GRRLIB_LoadTexture( pic13data);
   GRRLIB_InitTileSet(&images.english_flag, images.english_flag.w, 1, 0);
   images.nederlands_flag=GRRLIB_LoadTexture( pic14data);
   GRRLIB_InitTileSet(&images.nederlands_flag, images.nederlands_flag.w, 1, 0);
   images.deutsch_flag=GRRLIB_LoadTexture( pic15data);
   GRRLIB_InitTileSet(&images.deutsch_flag, images.deutsch_flag.w, 1, 0);
   images.italiano_flag=GRRLIB_LoadTexture( pic45data);
   GRRLIB_InitTileSet(&images.italiano_flag, images.italiano_flag.w, 1, 0);

   // icons
   images.help=GRRLIB_LoadTexture( pic23data);   
   images.right=GRRLIB_LoadTexture( pic25data);
   images.wrong=GRRLIB_LoadTexture( pic26data);
   images.sound=GRRLIB_LoadTexture( pic28data);
   images.exit=GRRLIB_LoadTexture( pic29data);
   images.info=GRRLIB_LoadTexture( pic30data);
   images.question=GRRLIB_LoadTexture( pic31data);
   
   // backgrounds
   images.background1=GRRLIB_LoadTexture( pic33data);
   images.background2=GRRLIB_LoadTexture( pic34data);
   images.background3=GRRLIB_LoadTexture( pic35data);   
   images.background4=GRRLIB_LoadTexture( pic44data); 
   
   // Logo
   images.logo1=GRRLIB_LoadTexture( pic9data ); 
   images.logo2=GRRLIB_LoadTexture( pic39data );
   images.logo3=GRRLIB_LoadTexture( pic40data );
   images.logo4=GRRLIB_LoadTexture( pic41data );
   images.logo5=GRRLIB_LoadTexture( pic42data );
   images.logo6=GRRLIB_LoadTexture( pic43data );
   
   images.logo=GRRLIB_LoadTexture( pic39data );
   GRRLIB_InitTileSet(&images.logo, images.logo.w, 1, 0);   
   
    traceEvent(s_fn,0,"leave [void]");
}

void initButtons(void)
{  
   switch (stateMachine)
   {
      case stateMenu:
		{

			maxButtons=6;
			angle=0;
			alfa=0;
			alfa_direction=true;
   
			// Language button
			buttons[0].image=images.button1;
			buttons[0].imageSelect=images.button1select;
			strcpy(buttons[0].name,languages[selectedLanguage].name);
			buttons[0].x=10;
			buttons[0].y=332+yOffset;
			buttons[0].enabled=true;
			buttons[0].xtext=buttons[0].x+
				(buttons[0].image.w/2)-
				((strlen(buttons[0].name)*13)/2);
			buttons[0].ytext=buttons[0].y+25;
  
			// Topic button
			buttons[1].image=images.button1;
			buttons[1].imageSelect=images.button1select;
			strcpy(buttons[1].name,topics[selectedTopic].name);
			buttons[1].x=10;
			buttons[1].y=391+yOffset;
			if (maxQuestions!=-1) {
				buttons[1].enabled=true; 
			} else {
				buttons[1].enabled=false;
			}
			buttons[1].xtext=buttons[1].x+
				(buttons[1].image.w/2)-
				((strlen(buttons[1].name)*13)/2);
			buttons[1].ytext=buttons[1].y+25;
   
			// Sound button
			buttons[2].image=images.button1;
			buttons[2].imageSelect=images.button1select;
			strcpy(buttons[2].name,translation.buttonSound);
			buttons[2].x=194;
			buttons[2].y=332+yOffset;
			buttons[2].enabled=true;
			buttons[2].xtext=buttons[2].x+
				(buttons[2].image.w/2)-
				((strlen(buttons[2].name)*13)/2);
			buttons[2].ytext=buttons[2].y+25;
  
			// Play button
			buttons[3].image=images.button1;
			buttons[3].imageSelect=images.button1select;
			strcpy(buttons[3].name,translation.buttonPlay);
			buttons[3].x=(MAX_HORZ_PIXELS-200);
			buttons[3].y=332+yOffset;
			if (maxQuestions!=-1) {
				buttons[3].enabled=true; 
			} else {
				buttons[3].enabled=false;
			}
			buttons[3].xtext=buttons[3].x+
				(buttons[3].image.w/2)-
				((strlen(buttons[3].name)*13)/2);
			buttons[3].ytext=buttons[3].y+25;
   
			// Stop button
			buttons[4].image=images.button1;
			buttons[4].imageSelect=images.button1select;
			strcpy(buttons[4].name,translation.buttonStop);
			buttons[4].x=(MAX_HORZ_PIXELS-200);
			buttons[4].y=391+yOffset;
			buttons[4].enabled=true;
			buttons[4].xtext=buttons[4].x+
				(buttons[4].image.w/2)-
				((strlen(buttons[4].name)*13)/2);
			buttons[4].ytext=buttons[4].y+25;
   
			// High Score button
			buttons[5].image=images.button1;
			buttons[5].imageSelect=images.button1select;
			strcpy(buttons[5].name,translation.labelHighScore);
			buttons[5].x=194;
			buttons[5].y=391+yOffset;
			if (maxQuestions!=-1) {
				buttons[5].enabled=true; 
			} else {
				buttons[5].enabled=false;
			}
			buttons[5].xtext=buttons[5].x+
				(buttons[5].image.w/2)-
				((strlen(buttons[5].name)*13)/2);
			buttons[5].ytext=buttons[5].y+25;  
		}
		break;
	  
		case stateQuestion: 
		{
			maxButtons=7;
			angle=0;

			// Hint1 button 
			buttons[0].image=images.button2;
			buttons[0].imageSelect=images.button2select;
			strcpy(buttons[0].name,translation.buttonHint);
			buttons[0].x=375;
			buttons[0].y=350+yOffset;
			buttons[0].enabled=true;
			buttons[0].xtext=buttons[0].x+20;
			buttons[0].ytext=buttons[0].y+35;
   
			// Hint2 button 
			buttons[1].image=images.button2;
			buttons[1].imageSelect=images.button2select;
			strcpy(buttons[1].name,translation.buttonHint);   
			buttons[1].x=455;
			buttons[1].y=350+yOffset;
			buttons[1].enabled=true;
			buttons[1].xtext=buttons[1].x+20;
			buttons[1].ytext=buttons[1].y+35;
   
			// Hint3 button 
			buttons[2].image=images.button2;
			buttons[2].imageSelect=images.button2select;
			strcpy(buttons[2].name,translation.buttonHint);
			buttons[2].x=535;
			buttons[2].y=350+yOffset;
			buttons[2].enabled=true;
			buttons[2].xtext=buttons[2].x+20;
			buttons[2].ytext=buttons[2].y+35;
   
			// AnswerA button
			buttons[3].image=images.button1;
			buttons[3].imageSelect=images.button1select;
			strcpy(buttons[3].name,translation.buttonAnswerA);
			buttons[3].x=10;
			buttons[3].y=332+yOffset;
			if (questions[rndSelectedQuestion].enabled[0]) {	
				buttons[3].enabled=true; 
			} else {
				buttons[3].enabled=false;
			}
			buttons[3].xtext=buttons[3].x+
				(buttons[3].image.w/2)-
				((strlen(buttons[3].name)*13)/2);
			buttons[3].ytext=buttons[3].y+25;
      
			// AnswerB button
			buttons[4].image=images.button1;
			buttons[4].imageSelect=images.button1select;
			strcpy(buttons[4].name,translation.buttonAnswerB);
			buttons[4].x=192;
			buttons[4].y=332+yOffset;
			if (questions[rndSelectedQuestion].enabled[1]) {
				buttons[4].enabled=true; 
			} else {
				buttons[4].enabled=false;
			}
			buttons[4].xtext=buttons[4].x+
				(buttons[4].image.w/2)-
				((strlen(buttons[4].name)*13)/2);
			buttons[4].ytext=buttons[4].y+25;
      
			// AnswerC button
			buttons[5].image=images.button1;
			buttons[5].imageSelect=images.button1select;
			strcpy(buttons[5].name,translation.buttonAnswerC);
			buttons[5].x=10;
			buttons[5].y=391+yOffset;
			if (questions[rndSelectedQuestion].enabled[2]) {
				buttons[5].enabled=true; 
			} else { 
				buttons[5].enabled=false; 
			}
			buttons[5].xtext=buttons[5].x+
				(buttons[5].image.w/2)-
				((strlen(buttons[5].name)*13)/2);
			buttons[5].ytext=buttons[5].y+25;
   
			// AnswerD button
			buttons[6].image=images.button1;
			buttons[6].imageSelect=images.button1select;
			strcpy(buttons[6].name,translation.buttonAnswerD);
			buttons[6].x=192;
			buttons[6].y=391+yOffset;
			if (questions[rndSelectedQuestion].enabled[3]) {
				buttons[6].enabled=true; 
			} else {
				buttons[6].enabled=false;
			}
			buttons[6].xtext=buttons[6].x+
				(buttons[6].image.w/2)-
				((strlen(buttons[6].name)*13)/2);
			buttons[6].ytext=buttons[6].y+25;
   
	  }
	  break;
	  
      case stateAnswer:
	  {

   maxButtons=1;
   angle=0;
   alfa=0;
   alfa_direction=true;
   
   // Next button
   buttons[0].image=images.button1;
   buttons[0].imageSelect=images.button1select;
   strcpy(buttons[0].name,translation.buttonNext);
   buttons[0].x=10;
   buttons[0].y=332+yOffset;
   buttons[0].enabled=true;
   buttons[0].xtext=buttons[0].x+
		(buttons[0].image.w/2)-
		((strlen(buttons[0].name)*13)/2);
   buttons[0].ytext=buttons[0].y+25;
   
	  }
	  break;
	  
	  
	  case stateResult:
	  {
	  
   maxButtons=1;
   angle=0;
   alfa=0;
   alfa_direction=true;

   // Next button
   buttons[0].image=images.button1;
   buttons[0].imageSelect=images.button1select;
   strcpy(buttons[0].name,translation.buttonNext);
   buttons[0].x=10;
   buttons[0].y=391+yOffset;
   buttons[0].enabled=true;
   buttons[0].xtext=buttons[0].x+
		(buttons[0].image.w/2)-
		((strlen(buttons[0].name)*13)/2);
   buttons[0].ytext=buttons[0].y+25;
   
	  }
	  break;
	  
	  case stateGoodbye:
	  {
	  
   maxButtons=6;
   angle=0;
   alfa=0;
   alfa_direction=true;
   
   // Continue button
   buttons[0].image=images.button1;
   buttons[0].imageSelect=images.button1select;
   strcpy(buttons[0].name,translation.buttonContinue);
   buttons[0].x=10;
   buttons[0].y=332+yOffset;
   buttons[0].enabled=true;
   buttons[0].xtext=buttons[0].x+(buttons[0].image.w/2)-((strlen(buttons[0].name)*13)/2);
   buttons[0].ytext=buttons[0].y+25;
  
   // Credits button
   buttons[1].image=images.button1;
   buttons[1].imageSelect=images.button1select;
   strcpy(buttons[1].name,translation.buttonCredits);
   buttons[1].x=10;
   buttons[1].y=391+yOffset;
   buttons[1].enabled=true;
   buttons[1].xtext=buttons[1].x+(buttons[1].image.w/2)-((strlen(buttons[1].name)*13)/2);
   buttons[1].ytext=buttons[1].y+25;
   
   // Exit1 (To HBC) button
   buttons[2].image=images.button1;
   buttons[2].imageSelect=images.button1select;
   strcpy(buttons[2].name,translation.buttonExit1);
   buttons[2].x=(MAX_HORZ_PIXELS-200);
   buttons[2].y=332+yOffset;
   buttons[2].enabled=true;
   buttons[2].xtext=buttons[2].x+(buttons[2].image.w/2)-((strlen(buttons[2].name)*13)/2);
   buttons[2].ytext=buttons[2].y+25;
   
   // Exit2 (Reset Wii) button
   buttons[3].image=images.button1;
   buttons[3].imageSelect=images.button1select;
   strcpy(buttons[3].name,translation.buttonExit2);
   buttons[3].x=(MAX_HORZ_PIXELS-200);
   buttons[3].y=391+yOffset;
   buttons[3].enabled=true;
   buttons[3].xtext=buttons[3].x+(buttons[3].image.w/2)-((strlen(buttons[3].name)*13)/2);
   buttons[3].ytext=buttons[3].y+25;  
         
   // Help button
   buttons[4].image=images.button1;
   buttons[4].imageSelect=images.button1select;
   strcpy(buttons[4].name,translation.labelHelp);
   buttons[4].x=194;
   buttons[4].y=332+yOffset;
   buttons[4].enabled=true;
   buttons[4].xtext=buttons[4].x+(buttons[4].image.w/2)-((strlen(buttons[4].name)*13)/2);
   buttons[4].ytext=buttons[4].y+25;
   
    // Credits button
   buttons[5].image=images.button1;
   buttons[5].imageSelect=images.button1select;
   strcpy(buttons[5].name,translation.buttonReleaseNotes);
   buttons[5].x=194;
   buttons[5].y=391+yOffset;
   buttons[5].enabled=true;
   buttons[5].xtext=buttons[5].x+10+(buttons[5].image.w/2)-((strlen(buttons[5].name)*13)/2);
   buttons[5].ytext=buttons[5].y+25;
   
	  }
	  break;
	  
	  case stateSound:
	  {

   maxButtons=7;
   angle=0;
   alfa=0;
   alfa_direction=true;
 
   // Back button
   buttons[0].image=images.button1;
   buttons[0].imageSelect=images.button1select;
   strcpy(buttons[0].name,translation.buttonBack);
   buttons[0].x=10;
   buttons[0].y=391+yOffset;
   buttons[0].enabled=true;
   buttons[0].xtext=buttons[0].x+(buttons[0].image.w/2)-((strlen(buttons[0].name)*13)/2);
   buttons[0].ytext=buttons[0].y+25;
   
   // - music volume button
   buttons[1].image=images.button3;
   buttons[1].imageSelect=images.button3select;
   strcpy(buttons[1].name,"-");
   buttons[1].x=40;
   buttons[1].y=110+yOffset;
   buttons[1].enabled=true;
   buttons[1].xtext=buttons[1].x+(buttons[1].image.w/2)-((strlen(buttons[1].name)*13)/2);
   buttons[1].ytext=buttons[1].y+25;
   
   // + music volume button
   buttons[2].image=images.button3;
   buttons[2].imageSelect=images.button3select;
   strcpy(buttons[2].name,"+");
   buttons[2].x=MAX_HORZ_PIXELS-100;
   buttons[2].y=110+yOffset;
   buttons[2].enabled=true;
   buttons[2].xtext=buttons[2].x+(buttons[2].image.w/2)-((strlen(buttons[2].name)*13)/2);
   buttons[2].ytext=buttons[2].y+25;
   
   // - effect volume button
   buttons[3].image=images.button3;
   buttons[3].imageSelect=images.button3select;
   strcpy(buttons[3].name,"-");
   buttons[3].x=40;
   buttons[3].y=210+yOffset;
   buttons[3].enabled=true;
   buttons[3].xtext=buttons[3].x+(buttons[3].image.w/2)-((strlen(buttons[3].name)*13)/2);
   buttons[3].ytext=buttons[3].y+25;
   
   // + effect volume button
   buttons[4].image=images.button3;
   buttons[4].imageSelect=images.button3select;
   strcpy(buttons[4].name,"+");
   buttons[4].x=MAX_HORZ_PIXELS-100;
   buttons[4].y=210+yOffset;
   buttons[4].enabled=true;
   buttons[4].xtext=buttons[4].x+(buttons[4].image.w/2)-((strlen(buttons[4].name)*13)/2);
   buttons[4].ytext=buttons[4].y+25;
   
   // - music track button
   buttons[5].image=images.button3;
   buttons[5].imageSelect=images.button3select;
   strcpy(buttons[5].name,"-");
   buttons[5].x=100;
   buttons[5].y=300+yOffset;
   buttons[5].enabled=true;
   buttons[5].xtext=buttons[5].x+(buttons[5].image.w/2)-((strlen(buttons[5].name)*13)/2);
   buttons[5].ytext=buttons[5].y+25;
   
   // + music track button
   buttons[6].image=images.button3;
   buttons[6].imageSelect=images.button3select;
   strcpy(buttons[6].name,"+");
   buttons[6].x=MAX_HORZ_PIXELS-150;
   buttons[6].y=300+yOffset;
   buttons[6].enabled=true;
   buttons[6].xtext=buttons[6].x+(buttons[6].image.w/2)-((strlen(buttons[6].name)*13)/2);
   buttons[6].ytext=buttons[6].y+25;
	  
	  }
	  break;
	  
	  case stateCredits:
	  {

   maxButtons=1;
   angle=0;
   alfa=0;
   alfa_direction=true;
   
   // Back button
   buttons[0].image=images.button1;
   buttons[0].imageSelect=images.button1select;
   strcpy(buttons[0].name,translation.buttonBack);
   buttons[0].x=10;
   buttons[0].y=391+yOffset;
   buttons[0].enabled=true;
   buttons[0].xtext=buttons[0].x+(buttons[0].image.w/2)-((strlen(buttons[0].name)*13)/2);
   buttons[0].ytext=buttons[0].y+25;
	  
	  }
	  break;
	  	  
	  case stateHighScore:
	  {
	  
   maxButtons=1;
   angle=0;
   alfa=0;
   alfa_direction=true;
      
   // Back button
   buttons[0].image=images.button1;
   buttons[0].imageSelect=images.button1select;
   strcpy(buttons[0].name,translation.buttonBack);
   buttons[0].x=10;
   buttons[0].y=391+yOffset;
   buttons[0].enabled=true;
   buttons[0].xtext=buttons[0].x+(buttons[0].image.w/2)-((strlen(buttons[0].name)*13)/2);
   buttons[0].ytext=buttons[0].y+25;
   
   
	  }
	  break;
	  
	  case stateHelp:
	  {

   maxButtons=1;
   angle=0;
   alfa=0;
   alfa_direction=true;
   
   // Back button
   buttons[0].image=images.button1;
   buttons[0].imageSelect=images.button1select;
   strcpy(buttons[0].name,translation.buttonBack);
   buttons[0].x=10;
   buttons[0].y=391+yOffset;
   buttons[0].enabled=true;
   buttons[0].xtext=buttons[0].x+(buttons[0].image.w/2)-((strlen(buttons[0].name)*13)/2);
   buttons[0].ytext=buttons[0].y+25;
	  
	  }
	  break;
	  
	  case stateReleaseNotes:
	  {

   maxButtons=1;
   angle=0;
   alfa=0;
   alfa_direction=true;
   
   // Back button
   buttons[0].image=images.button1;
   buttons[0].imageSelect=images.button1select;
   strcpy(buttons[0].name,translation.buttonBack);
   buttons[0].x=10;
   buttons[0].y=391+yOffset;
   buttons[0].enabled=true;
   buttons[0].xtext=buttons[0].x+(buttons[0].image.w/2)-((strlen(buttons[0].name)*13)/2);
   buttons[0].ytext=buttons[0].y+25;
	  
	  }
	  break;
	  
   }  
}

void initStateMachine( void )
{	
   switch( stateMachine )
	{
	   case stateMenu:	
			initButtons();   	      
		    break;
			  
	   case stateQuestion:
			if (stateMachinePrev!=stateMachine) initButtons();  
		   break;
		 
	   case stateAnswer:
			if (stateMachinePrev!=stateMachine) initButtons(); 
		   break;
			  
		case stateResult:
			if (stateMachinePrev!=stateMachine) initButtons();  
		   break;
				
		case stateSound:
		   if (stateMachinePrev!=stateMachine) initButtons();
			break;
				
		 case stateGoodbye:
			if (stateMachinePrev!=stateMachine) initButtons();  
		   break;		

		 case stateCredits:
			if (stateMachinePrev!=stateMachine) initButtons();  
		   break;			
				
		 case stateHighScore:
			if (stateMachinePrev!=stateMachine) initButtons();  
		   break;	
				
		 case stateHelp:
			if (stateMachinePrev!=stateMachine) initButtons();  
		   break;	
				
		 case stateReleaseNotes:
			if (stateMachinePrev!=stateMachine) initButtons();  
		   break;	
    }	
    stateMachinePrev=stateMachine;
}

void nextquestion(void) {

	//select a random question
	//srand(10000);
	while (maxQuestions<=(
		rndSelectedQuestion=(int)(((double)rand() / 
		   ((double)(RAND_MAX)+(double)(1)) ) * maxQuestions+1)));

	//if question already done increment of 1 and go to the next question
	while(questions[rndSelectedQuestion].done) {
		rndSelectedQuestion = ((rndSelectedQuestion+1) % maxQuestions)+1;
	}
	questions[rndSelectedQuestion].done=true;
}


// -----------------------------------------------------------
// BUTTON LOGIC
// -----------------------------------------------------------

int buttonSelected(int x, int y) {
   int i;
   
   for (i=0; i<maxButtons; i++) {
	
       if ( buttons[i].enabled &&
	        (x>=buttons[i].x) && (x<=buttons[i].x+buttons[i].image.w) && 
	        (y>=buttons[i].y) && (y<=buttons[i].y+buttons[i].image.h) ) {
			  
          SND_SetVoice(SND_GetFirstUnusedVoice(), 
				VOICE_MONO_16BIT, 
				8000, 
				0, 
				(char *) 
				effect3_wav, 
				effect3_wav_size, 
				effectVolume*EFFECT_MULTIPLER, 
				effectVolume*EFFECT_MULTIPLER, 
				NULL);
				
	      return i;
	   }	   
   }
   return -1;
}

void buttonHint(int number) {

   bool flag=true;
   int i=0;
   int count=0;
      
   // If more than one answer is possible continue
   for (i=0; i<MAX_ANSWERS; i++) {   
      if (questions[rndSelectedQuestion].enabled[i]) count++;
   }
         
   if (count>1) {
	
		while (flag) {
			// Random disable answer
			int number=rand() % 4;
			if (((number+1)!=questions[rndSelectedQuestion].answer) 
				&& questions[rndSelectedQuestion].enabled[number]==true) {
			
				// Disable question answer
				questions[rndSelectedQuestion].enabled[number]=false;
		 
				// Disable answer button
				buttons[number+3].enabled=false;
				hintCounter++;
		 
				flag=false;
			}
		}
		buttons[number].enabled=false;
   }
}

void buttonLanguage(void)
{
   if (++selectedLanguage>=maxLanguages) {
		selectedLanguage=0;
	}
	
	selectedTopic=0;
	selectedQuestion=0;
	score=0;
	hintCounter=0;
	   
	initTranslation(languages[selectedLanguage].translation);
	initTopics(languages[selectedLanguage].topics);
	initQuestions( topics[selectedTopic].filename );
}

void buttonTopic(void)
{
   if (++selectedTopic>=maxTopics) {
		selectedTopic=0;
	}

   score=0;
	selectedQuestion=0;
	//rndSelectedQuestion=0;
	hintCounter=0;
	
	initQuestions(topics[selectedTopic].filename);
}

void buttonPlay(void) {

	selectedQuestion=0;
	nextquestion();
	//rndSelectedQuestion=0;
	score=0;
	hintCounter=0;
	startTime=time(NULL);
	
	correctAnswer=false;
   initQuestions( topics[selectedTopic].filename );
   
	stateMachine=stateQuestion;
}

void buttonAnswer(int number) {

	stateMachine=stateAnswer;
  
	if (questions[rndSelectedQuestion].answer==number) {
		score++;
		correctAnswer=true;	
		//SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 8000, 0, (char *) effect1_wav, effect1_wav_size, effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);             
	} else {
	    correctAnswer=false;
		//SND_SetVoice(SND_GetFirstUnusedVoice(), VOICE_MONO_16BIT, 8000, 0, (char *) effect2_wav, effect2_wav_size, effectVolume*EFFECT_MULTIPLER, effectVolume*EFFECT_MULTIPLER, NULL);		
	}
}
			
void buttonExit(int index) {    

   // Stop network thread
   LAN(tcp_stop_thread();)

   // Stop music track
   MODPlay_Stop(&snd1);
	
   if (index==0)
   {   
	   exit(0);
   }
   else
   {
	   SYS_ResetSystem(SYS_RESTART,0,0);	
   }
}


void buttonNext(void) {
   if (++selectedQuestion>=maxQuestions) {	
      playTime = time(NULL)-startTime; 
      processHighScore();
      stateMachine=stateResult;
   } else {
	  nextquestion();
      stateMachine=stateQuestion;
   }
}
	  	 

void buttonMinus(void) {

   if ((stateMachine!=stateGoodbye) && 
		(stateMachine!=stateHelp) && 
		(stateMachine!=stateCredits)) {
	  stateMachineStorage2=stateMachine;
	  stateMachine=stateHelp;
   }
}
 
void buttonMinusVolume(int index) {

   if (index==0) {
       // Music volume
	   if (musicVolume>0) { 
			musicVolume--;   
		}
	   MODPlay_SetVolume( &snd1, 
			musicVolume*MUSIC_MULTIPLER,
			musicVolume*MUSIC_MULTIPLER);
			
   } else if (index==1) {
      
		// Effect volume
      if (effectVolume>0) {
			effectVolume--; 
		}
		
   } else if (index==2) {
	
      MODPlay_Stop(&snd1);
      if (selectedMusic>1) {
			selectedMusic--; 
		} else { 
			selectedMusic=(MAX_MUSIC_TRACK-1);
		}
		initMusicTrack();
   }
}

void buttonPlusVolume(int index) {

   if (index==0)
   {
       // Music volume
	   if (musicVolume<MAX_SOUND_VOLUME) {
			musicVolume++;   
		}
	   MODPlay_SetVolume( &snd1, 
			musicVolume*MUSIC_MULTIPLER,
			musicVolume*MUSIC_MULTIPLER); 
   }
   else if (index==1) {
	
      // Effect volume
      if (effectVolume<MAX_SOUND_VOLUME) {
			effectVolume++; 
		}
		
   } else if (index==2) {
	
      MODPlay_Stop(&snd1);
      if (selectedMusic<MAX_MUSIC_TRACK) {
			selectedMusic++; 
		} else {
			selectedMusic=1;
		}
		initMusicTrack();
   }
}

void buttonHome(void)
{
   if (stateMachine!=stateGoodbye) {
	  stateMachineStorage=stateMachine;
	  stateMachine=stateGoodbye;
   } else {      
      buttonExit(0);
   }
}

void button1x(void)
{
   bool flag = true;
 
   MODPlay_Stop(&snd1);  
   if (selectedMusic<MAX_MUSIC_TRACK) {
		selectedMusic++; 
	} else {
		selectedMusic=1;   
	}
   initMusicTrack();
      
   // Handle buttons events  
   while ( flag && !bPowerOff)
   {
      WPAD_ScanPads(); 	
      if (WPAD_ButtonsUp(0) & BUTTON_1) {
			flag=false;
		}
   }
}

void button2y(void)
{
   bool flag = true;
 
   MODPlay_Stop(&snd1);
   if (selectedMusic>1) {
		selectedMusic--; 
	} else {
		selectedMusic=(MAX_MUSIC_TRACK-1);   
	}
   initMusicTrack();
      
   // Handle buttons events  
   while ( flag && !bPowerOff) {
      WPAD_ScanPads(); 	
      if (WPAD_ButtonsUp(0) & BUTTON_2) {
			flag=false;
		}
   }
}

void buttonA(int x,int y) {

	int i;
	for (i=0; i<MAX_POINTERS; i++) 
	{
		pointers[i].rumble=MAX_RUMBLE;
	}

	switch (stateMachine)  
	{
		case stateIntro1:
		{
			size=0;
			stateMachine=stateIntro2;
		}
		break;

		case stateIntro2:
		{
			stateMachine=stateIntro3;
		}
		break;
	 
		case stateIntro3:
		{
			stateMachine=stateMenu;
		}
		break;
		
		case stateMenu:
		{
			switch (buttonSelected(x,y))
			{
				case 0: // language button	
				  buttonLanguage();
			      break;
	  
	      case 1: // topic button
				  buttonTopic();
			      break;
				  
		  case 2: // sound button
				  stateMachine=stateSound;
			      break;
	  
	      case 3: // play button		 
				  buttonPlay();
			      break;
		  
		  case 4: // Stop button event	
				  stateMachineStorage=stateMachine;
			      stateMachine=stateGoodbye;
			      break;	
				  
		  case 5: // high Score button
				  stateMachine=stateHighScore;
			      break;
 
	    }
     }
	 break;
	 
     case stateQuestion:
	 {
	    switch (buttonSelected(x,y))
	    {
          case 0: // hint 1	button event	
		          buttonHint(0); 			 
			      break;
	  
	      case 1: // hint 2 button event
			      buttonHint(1);
			      break;
	  
	      case 2: // hint 3 button event
			      buttonHint(2);
			      break;
	  
	      case 3: // Answer A button event
			      buttonAnswer(1);
			      break;
	  
	      case 4: // Answer B button event
		      	  buttonAnswer(2);
			      break;
	  
		  case 5: // Answer C button event
			      buttonAnswer(3);
			      break;
	  
	      case 6: // Answer D button event
		    	  buttonAnswer(4);
			      break;
	    }
     }
     break;
	 
     case stateAnswer:
	 {
	    switch (buttonSelected(x,y))
	    { 
		  case 0: // Next button event	
		          buttonNext(); 			 
			      break;
	    }
				  
	 }	 
	 break;
	 
	 case stateResult:
	 {     
  	      switch (buttonSelected(x,y))
	      {
	         case 0: // Next button event	        
			         stateMachine=stateHighScore;
			         break;	   	 
		  }
	 }
	 break;
	 
	 case stateHighScore:
	 {     
  	      switch (buttonSelected(x,y))
	      {				 
		     case 0: // Back button event
			         stateMachine=stateMenu;
			         break;
		  }
	 }
	 break;	
	 	 
	 case stateHelp:
	 {     
  	      switch (buttonSelected(x,y))
	      {				 
		     case 0: // Back button event
			         stateMachine=stateMachineStorage2;
			         break;
		  }
	 }
	 break;	
	 
	 case stateSound:
	 {     
  	      switch (buttonSelected(x,y))
	      {
	         case 0: // Back button event          
			         stateMachine=stateMenu;
			         break;	   
					 
			 case 1: // - music volume button event	           
			         buttonMinusVolume(0);
			         break;	   
			 
			 case 2: // + music volume button event	           
			         buttonPlusVolume(0);
			         break;	 
					 
			 case 3: // - effect volume button event	           
			         buttonMinusVolume(1);
			         break;	   
			 
			 case 4: // + effect volume button event	           
			         buttonPlusVolume(1);
			         break;	 
					 
			 case 5: // - music track button event	           
			         buttonMinusVolume(2);
			         break;	   
			 
			 case 6: // + music track  button event	           
			         buttonPlusVolume(2);
			         break;
					 
		  }
	 }
	 break;
	 	 
	 case stateCredits:
	 {     
  	      switch (buttonSelected(x,y))
	      {
	         case 0: // back button event           
			         stateMachine=stateGoodbye;
			         break;	     
		  }
	 }	 
	 break;
	 
	 case stateGoodbye:
	 {     
  	      switch (buttonSelected(x,y))
	      {
	         case 0: // Continue button event	           
			         stateMachine=stateMachineStorage;
			         break;	   
			   
			 case 1: // Show Credit Screen	           
			         stateMachine=stateCredits;
			         break;	 
					 
	         case 2: // Exit (to HBC) button event	           
			         buttonExit(0);
			         break;	 
					 
		     case 3: // Exit (reset Wii) button event	           
			         buttonExit(1);
			         break;	
					 
			 case 4: // Help button event	           
			         stateMachineStorage2=stateMachine;
					 stateMachine=stateHelp;
			         break;	
					 
			 case 5: // ReleaseNotes button event	           
			         stateMachineStorage2=stateMachine;
					 stateMachine=stateReleaseNotes;
			         break;	
		  }
	 }
	 break;	 
	 
	 case stateReleaseNotes:
	 {     
  	      switch (buttonSelected(x,y))
	      {				 
		     case 0: // Back button event
			         stateMachine=stateMachineStorage2;
			         break;
		  }
	 }
	 break;	
   }         
}

//	PowerOff callback function.
void doPowerOff( void ) {
	bPowerOff = true;
	return;
}

//	PowerOff callback function for the Wii Remote power button.
void doPadPowerOff( s32 chan ) {
	if ( chan == WPAD_CHAN_0 ) {
		bPowerOff = true;
	}
	return;
}
 
// -----------------------------------------------------------
// SCREEN LOGIC
// -----------------------------------------------------------

void drawText(int x, int y, int type, char *text) {

   char tmp[MAX_LEN];
   memset(tmp,0x00,sizeof(tmp));
   
   if (text==NULL) return;    		
   strcpy(tmp, text);
	 
   switch (type)
   {
      case fontTitle: 
	   {
	      if (x==0) x=320-((strlen(tmp)*33)/2);  
		  GRRLIB_Printf2(x, y-70, tmp, 72, COLOR_WHITESMOKE); 
	   }
	   break;
	   	   
	   case fontSubTitle:
	   {
	      if (x==0) x=320-((strlen(tmp)*10)/2);
		  GRRLIB_Printf2(x, y, tmp, 24, COLOR_WHITESMOKE);          
	   }
	   break;
	   
	   case fontParagraph:
	   {
	       if (x==0) x=320-((strlen(tmp)*8)/2);	   
		   GRRLIB_Printf2(x, y, tmp, 14, COLOR_LIGHTBLUE);            
	   }
	   break;
	   	   
	   case fontNormal:
	   {
	       if (x==0) x=320-((strlen(tmp)*7)/2);
		   GRRLIB_Printf2(x, y, tmp, 16, COLOR_WHITESMOKE);            
	   }
	   break;
	   
	   case fontButton:
	   {
		   GRRLIB_Printf2(x, y-13, tmp, 24, COLOR_WHITESMOKE);            
	   }
	   break;
	   
	   case fontHead:
	   {
		   GRRLIB_Printf2(x, y-13, tmp, 24, COLOR_LIGHTBLUE);            
	   }
	   break;
	   
	   case fontNew:
	   {
	       if (x==0) x=320-((strlen(tmp)*6)/2);	   
		   GRRLIB_Printf2(x, y, tmp, 14, COLOR_LIGHTBLUE);            
	   }
	   break;
	   
	   case fontSpecial:
	   {
	       if (x==0) x=320-((strlen(tmp)*10)/2);
		   GRRLIB_Printf2(x, y, tmp, 10, COLOR_WHITESMOKE);            
	   }
	   break;
   }
}

void drawWordwrap(char *input, int x, int y, int maxLineWidth, int stepSize) 
{
   char tmp[MAX_LEN];
   int startIndex=0;
   int lastSpace=0;
   int endIndex=strlen(input);
   int ypos=y+yOffset;
   int i,z=0;

    // Make local copy   
   strcpy(tmp,input);
		
   for (i=0; i<endIndex; i++)
   {
      if (tmp[i]==' ') lastSpace=i;	 
	  if (z++>maxLineWidth)
	  {
	     tmp[lastSpace]=0x00;
	     drawText(x, ypos, fontNormal, tmp+startIndex);
	
		 startIndex=lastSpace+1;
		 ypos=ypos+stepSize;
		 z=0;
	  }
   }
   if (z<=maxLineWidth)
   {
	  drawText(x, ypos, fontNormal, tmp+startIndex);
   }
}

void drawButtons()
{
   int i;
   int j;
   
   bool selected=false;
   
   for (i=0; i<maxButtons; i++) {	  
      if ( buttons[i].enabled ) {
			selected=false;
	  
			for (j=0 ;j<MAX_POINTERS; j++) {
				if ((pointers[j].xOffset>=buttons[i].x) && 
					(pointers[j].xOffset<=buttons[i].x+buttons[i].image.w) && 
					(pointers[j].yOffset>=buttons[i].y) && 
					(pointers[j].yOffset<=buttons[i].y+buttons[i].image.h) ) {
					
					selected=true;
					if (--pointers[j].rumble>0) {
						WPAD_Rumble(j,1); 
					} else {
						WPAD_Rumble(j,0);
					}
				}
			}
  
         if (selected) {  
    	     // Draw selected button
             GRRLIB_DrawImg(buttons[i].x, 
					buttons[i].y, 
					buttons[i].imageSelect, 0, 1, 1, IMAGE_COLOR );		  
			} else {
				// Draw not selected button
				GRRLIB_DrawImg(buttons[i].x, 
					buttons[i].y, 
					buttons[i].image, 0, 1, 1, IMAGE_COLOR );
   	   }
			drawText(buttons[i].xtext,
				buttons[i].ytext, 
				fontButton, buttons[i].name);
      }
  	}
   	
	// If no button selected, stop rumble on all pointers
	if (!selected) {
  	  for (j=0; j<MAX_POINTERS; j++) {
	     WPAD_Rumble(j,0);
	     pointers[j].rumble=MAX_RUMBLE;
	  }	  
	}
}

void drawWelcomeScreen()
{
   int ypos=130+yOffset;
	char *version=NULL;
	char *status=NULL;
   char tmp[MAX_LEN];
	int j=0;
 
	// Draw panel
	GRRLIB_DrawImg(10,60, images.panel1, 0, 1, 1, IMAGE_COLOR );
	
	// Draw title
	drawText(0, ypos, fontTitle, translation.labelWelcome);
		
	// Check is new bibleQuiz version is available
	LAN(version=tcp_get_version();)
	if ( 	(version!=NULL) && 
			(strlen(version)>0) && 
			(strcmp(version,PROGRAM_VERSION)!=0)) {    
			
			char tmp[MAX_LEN];
			sprintf(tmp,"%s [v%s]",translation.labelNewVersion,version);
			drawText(0, ypos+5, fontNew, tmp);
   }
    
	// Draw content
	LAN( status = tcp_get_state(); )
	if (status!=NULL) {
	   sprintf(tmp,"Network Thread: %s",status);
	} else {
	   sprintf(tmp,"Network Thread: disabled" );
	}
	drawText(40, 80, fontSpecial, tmp);

	ypos+=20;
	sprintf(tmp,"%s:", translation.labelTopic);
	drawText(40, ypos, fontParagraph, tmp);
	ypos+=12;
	if (maxQuestions!=-1) {
		drawText(40, ypos, fontNormal, information.topic);
	}
	
	ypos+=30;
	sprintf(tmp,"%s:", translation.labelCreated);
	drawText(40, ypos, fontParagraph, tmp);
	ypos+=12;
	if (maxQuestions!=-1) {
		drawText(40, ypos, fontNormal, information.timestamp);
	}
	
	ypos+=30;
	sprintf(tmp,"%s:", translation.labelAuthor);
	drawText(40, ypos, fontParagraph, tmp);
	ypos+=12;
	if (maxQuestions!=-1) {
		drawText(40, ypos, fontNormal, information.author);
	}
	
	ypos+=20;
	if (maxQuestions!=-1) {
		drawWordwrap( information.note, 0, ypos-10, 70, 15);
	}

	// Draw flag logo		 
	for(j=0;j<images.english_flag.h;j++) {
   		  
		switch (selectedLanguage) {  
		
			case 0: GRRLIB_DrawTile(420+sin(wave1)*50,180+yOffset+(j/2),images.english_flag, 0, 1, 1, IMAGE_COLOR,j );
					break;
					 
			case 1: GRRLIB_DrawTile(420+sin(wave1)*50,180+yOffset+(j/2),images.nederlands_flag, 0, 1, 1, IMAGE_COLOR,j );
					break;
					 
			case 2: GRRLIB_DrawTile(420+sin(wave1)*50,180+yOffset+(j/2),images.deutsch_flag, 0, 1, 1, IMAGE_COLOR,j );
					break;
		
			case 3: GRRLIB_DrawTile(420+sin(wave1)*50,180+yOffset+(j/2),images.spanish_flag, 0, 1, 1, IMAGE_COLOR,j );
					break;
				
			case 4: GRRLIB_DrawTile(420+sin(wave1)*50,180+yOffset+(j/2),images.france_flag, 0, 1, 1, IMAGE_COLOR,j );
					break;
					
			case 5: GRRLIB_DrawTile(420+sin(wave1)*50,180+yOffset+(j/2),images.italiano_flag, 0, 1, 1, IMAGE_COLOR,j );
					break;
		}
		wave1+=0.02;
   }
	wave2+=0.02;
   wave1=wave2;
	
	sprintf(tmp,"%d fps", CalculateFrameRate());
	drawText(20, 330, fontSpecial, tmp);
}

void drawQuestionScreen(void) { 
   int ypos=yOffset+70;
   char tmp[MAX_LEN];
	
   // Draw panel
   GRRLIB_DrawImg(10,60, images.panel1, 0, 1, 1, IMAGE_COLOR );

    // Draw background1 icon
	GRRLIB_DrawImg(200,140+yOffset, images.background1, 0, 2.8, 2.8, IMAGE_COLOR );
	
	// Draw question icon
	GRRLIB_DrawImg(ICON_X,ICON_Y+yOffset, images.question, 0, ICON_ZOOM, ICON_ZOOM, IMAGE_COLOR );
			
	// Draw title
	sprintf(tmp,"%s:", translation.labelTopic);
	drawText(40, ypos, fontParagraph, tmp );
	
	// Draw Content
	ypos+=15;
	sprintf(tmp,"%s:", information.topic);
	drawText(40, ypos, fontNormal, tmp );
	     
	ypos+=30;
	sprintf(tmp,"%s:", translation.labelQuestion);
   drawText(40, ypos, fontParagraph, tmp);
	drawWordwrap( questions[rndSelectedQuestion].question, 40, ypos-10, 70, 15);
    	
	ypos+=90;
   sprintf(tmp,"%s:", translation.labelAnswers);
   drawText(40, ypos, fontParagraph, tmp);
	
	ypos+=15;
	if (questions[rndSelectedQuestion].enabled[0]) {	 
	  sprintf(tmp,"A) %s", questions[rndSelectedQuestion].answerA);
	  drawText(40, ypos, fontNormal, tmp);
   }	

	ypos+=15;      
	if (questions[rndSelectedQuestion].enabled[1]) {
	  sprintf(tmp,"B) %s", questions[rndSelectedQuestion].answerB);
	  drawText(40, ypos, fontNormal, tmp);
	}

    ypos+=15;    
	if (questions[rndSelectedQuestion].enabled[2]) {
	  sprintf(tmp,"C) %s", questions[rndSelectedQuestion].answerC);
	  drawText(40, ypos, fontNormal, tmp);
	}
	 
    ypos+=15; 
	if (questions[rndSelectedQuestion].enabled[3]) {
	  sprintf(tmp,"D) %s", questions[rndSelectedQuestion].answerD);
	  drawText(40, ypos, fontNormal, tmp);
	}
	
	sprintf(tmp,"%d fps", CalculateFrameRate());
	drawText(20, 330, fontSpecial, tmp);
}

void drawResultScreen(void) {  
	int  ypos=yOffset+140;
	float cat1=maxQuestions*0.6;
	float cat2=maxQuestions*0.8;
	char tmp[MAX_LEN];
	
	// Draw panel
   GRRLIB_DrawImg(10,60,images.panel2, 0, 1, 1, IMAGE_COLOR );
 	
   // Draw background2 icon
	GRRLIB_DrawImg(180,90+yOffset,images.background2, 0, 1.4, 1.2, 0x88888888 );
	
	// Draw Info icon
	GRRLIB_DrawImg(ICON_X,ICON_Y+yOffset, images.info, 0, ICON_ZOOM, ICON_ZOOM, IMAGE_COLOR );

   // Show title
   drawText(0, ypos, fontTitle, translation.labelResults);
 
   // Show Content
	ypos+=40;
	drawText(0, ypos, fontSubTitle, translation.labelResult);
	
   ypos+=60;
	sprintf(tmp,"%2.2f-%d.00 %s", cat2+1, maxQuestions, translation.labelCategory1);
	drawText(0, ypos, fontSubTitle, tmp );	
	
   ypos+=30;
	sprintf(tmp,"%2.2f-%2.2f %s ", cat1+1, cat2, translation.labelCategory2);
	drawText(0, ypos, fontSubTitle, tmp );	

   ypos+=30;
	sprintf(tmp,"0.00-%2.2f %s", cat1, translation.labelCategory3);
	drawText(0, ypos, fontSubTitle, tmp);
	
	sprintf(tmp,"%d fps", CalculateFrameRate());
	drawText(20, 395, fontSpecial, tmp);
}

void drawAnswerScreen(void) {		 
   int ypos=200+yOffset;
	char tmp[MAX_LEN];
	
   // Draw panel
   GRRLIB_DrawImg(10,60, images.panel1, 0, 1, 1, IMAGE_COLOR );

    // Draw background1 icon
	GRRLIB_DrawImg(200,140+yOffset, images.background1, 0, 2.8, 2.8, IMAGE_COLOR);
		
	// Draw title
   if ( correctAnswer ) {
	    // Draw Right icon
	    GRRLIB_DrawImg(ICON_X,ICON_Y+yOffset, images.right, 0, ICON_ZOOM, ICON_ZOOM, IMAGE_COLOR );
		
		// Draw Righ label		
		drawText(0, ypos, fontTitle, translation.labelRight);
	} else {
	    // Draw Wrong Icon
	    GRRLIB_DrawImg(ICON_X,ICON_Y+yOffset, images.wrong, 0, ICON_ZOOM, ICON_ZOOM, IMAGE_COLOR );
		
		// Draw Wrong Label		
		drawText(0, ypos, fontTitle, translation.labelWrong);
	}
	ypos+=15;
	if (strlen(questions[rndSelectedQuestion].explanation))	{	 
	  drawText(0, ypos+30, fontNormal, questions[rndSelectedQuestion].explanation);
   }
	sprintf(tmp,"%d fps", CalculateFrameRate());
	drawText(20, 330, fontSpecial, tmp);
}

void drawSoundScreen(void) {  

    int ypos=100+yOffset;
	char tmp[MAX_LEN];
	
	// Draw panel
    GRRLIB_DrawImg(10,60, images.panel2, 0, 1, 1, IMAGE_COLOR );
	
	// Draw Sound icon
	GRRLIB_DrawImg((640/2)-128, ((480/2)-140)+yOffset, images.sound, angle, 1, 1, IMAGE_COLOR );
	
    // Draw content	
    drawText(0, ypos, fontSubTitle, translation.labelMusic);	
	ypos+=20;
    GRRLIB_DrawImg(104,ypos, images.bar1, 0, 1, 1, IMAGE_COLOR );
	ypos+=10;
	GRRLIB_DrawImg(115+(musicVolume*40),ypos, images.bar_cursor1, 0, 1, 1, IMAGE_COLOR );
  
    ypos+=80;
    drawText(0, ypos, fontSubTitle, translation.labelEffects);
	ypos+=20;	
	GRRLIB_DrawImg(104,ypos, images.bar1, 0, 1, 1, IMAGE_COLOR );
	ypos+=10;
	GRRLIB_DrawImg(115+(effectVolume*40),ypos, images.bar_cursor1, 0, 1, 1, IMAGE_COLOR );
	
	ypos+=70;
	sprintf(tmp,"%s [%d]", translation.labelTrack, selectedMusic);
	drawText(0, ypos, fontSubTitle, tmp);		
	
	sprintf(tmp,"%d fps", CalculateFrameRate());
	drawText(20, 395, fontSpecial, tmp);
}

void drawGoodbyeScreen(void) {

   int ypos=205+yOffset;
	char tmp[MAX_LEN];
	
	// Draw panel
   GRRLIB_DrawImg(10,60, images.panel1, 0, 1, 1, IMAGE_COLOR );

   // Draw Exit icon
	GRRLIB_DrawImg(ICON_X,ICON_Y+yOffset,images.exit, 0, ICON_ZOOM, ICON_ZOOM, IMAGE_COLOR );
 	
   // Draw title
	drawText(0, ypos, fontTitle, translation.labelGoodbye);		
	
	sprintf(tmp,"%d fps", CalculateFrameRate());
	drawText(20, 330, fontSpecial, tmp);
}

void drawCreditsScreen(void) {

   int  ypos=yOffset+65;
	char tmp[MAX_LEN];
	
   // Draw panel
   GRRLIB_DrawImg(10,60, images.panel2, 0, 1, 1, IMAGE_COLOR );
	
    // Draw background3 icon
	GRRLIB_DrawImg(190,95+yOffset, images.background3, 0, 1.3, 1.3, 0xFFFFFF00 | alfa );

	// Draw Credits icon
	GRRLIB_DrawImg(ICON_X,ICON_Y+yOffset, images.info, 0, ICON_ZOOM, ICON_ZOOM, IMAGE_COLOR );
		
    // Show Content
	drawText(0, ypos, fontParagraph, "GAME LOGIC");
	ypos+=15;
	drawText(0, ypos, fontNormal, "wplaat");

	ypos+=25;
	drawText(0, ypos, fontParagraph, "GAME GRAPHICS");
  	ypos+=15;
	drawText(0, ypos, fontNormal, "wplaat");
  	ypos+=15;
	drawText(0, ypos, fontNormal, "DrTwox");
	
	ypos+=25;
	drawText(0, ypos, fontParagraph, "MUSIC & SOUND EFFECTS");
	ypos+=15;
	drawText(0, ypos, fontNormal, "wplaat");
  
  	ypos+=25;
	drawText(0, ypos, fontParagraph, "TESTERS");
	ypos+=15;
	drawText(0, ypos, fontNormal, "wplaat");	  
	ypos+=15;
	drawText(0, ypos, fontNormal, "zouzzz");
		  		  	  
	ypos+=25;
	drawText(0, ypos, fontParagraph, "CONTENT PROVIDERS");
	ypos+=15;
	drawText(0, ypos, fontNormal, "wplaat");	 
	ypos+=15;
	drawText(0, ypos, fontNormal, "Rhoderik, Flark");
	ypos+=15;
	drawText(0, ypos, fontNormal, "Ezio Soma (Italiano translation & questions)");
	ypos+=15;
	drawText(0, ypos, fontNormal, "www.biblequizzes.com");
	
	ypos+=25;
	drawText(0, ypos, fontNormal,"Greetings to everybody in the Wii homebrew scene");
	
	sprintf(tmp,"%d fps", CalculateFrameRate());
	drawText(20, 395, fontSpecial, tmp);
}		 

void drawHighScoreScreen(void)
{
	int  ypos=yOffset+130;
	int  i;
	char tmp[MAX_LEN];
	struct tm *local;
	struct tm *level;

    // Draw panel
    GRRLIB_DrawImg(10,60, images.panel2, 0, 1, 1, IMAGE_COLOR );
 	
    // Draw background2 icon
	GRRLIB_DrawImg(180,90+yOffset, images.background2, 0, 1.4, 1.2, 0x88888888 );
	
	// Draw Info icon
	GRRLIB_DrawImg(ICON_X,ICON_Y+yOffset, images.info, 0, ICON_ZOOM, ICON_ZOOM, IMAGE_COLOR );
		
	// Draw title
	drawText(0, ypos, fontTitle, translation.labelHighScore);	

    // Show Content
    ypos+=30;
	drawText(30, ypos, fontParagraph, translation.labelDate);
	drawText(210, ypos, fontParagraph, translation.labelPlayTime);
	drawText(345, ypos, fontParagraph, translation.labelScore);
	drawText(420, ypos, fontParagraph, translation.labelHints);
	drawText(495, ypos, fontParagraph, translation.labelTopic);

    for (i=0; i<maxHighScores; i++)
	{
	   // Show only highscores from the seleceted language
       if ( languages[selectedLanguage].id==highscores[i].languageId )
	   {
	     ypos+=15;  
	   
	     local = localtime(&highscores[i].startTime);
	     sprintf(tmp,"%02d-%02d-%04d %02d:%02d:%02d", 
			  local->tm_mday, local->tm_mon+1, local->tm_year+1900, 
			  local->tm_hour, local->tm_min, local->tm_sec);
		 drawText(30, ypos, fontNormal, tmp);
	   
	     level = localtime(&highscores[i].playTime);
	     sprintf(tmp,"%02d:%02d:%02d", level->tm_hour, level->tm_min, level->tm_sec);
		 drawText(210, ypos, fontNormal, tmp);
 
         sprintf(tmp,"%d / %d", highscores[i].score,highscores[i].questions);
         drawText(345, ypos, fontNormal, tmp);
		 
		 sprintf(tmp,"%d", highscores[i].hint);
         drawText(420, ypos, fontNormal, tmp );
		 
         drawText(495, ypos, fontNormal, highscores[i].topic);
       }	
	}	
	
	sprintf(tmp,"%d fps", CalculateFrameRate());
	drawText(20, 395, fontSpecial, tmp);
}

void drawHelpScreen(void) {

	int  ypos=yOffset+80;
	char tmp[MAX_LEN];

    // Draw panel
    GRRLIB_DrawImg(10,60, images.panel2, 0, 1, 1, IMAGE_COLOR );
 		
    // Draw Help icon
    GRRLIB_DrawImg(ICON_X,ICON_Y+yOffset, images.question, 0, ICON_ZOOM, ICON_ZOOM, IMAGE_COLOR );
	
	// Draw Image
	ypos+=25;
	GRRLIB_DrawImg(80,ypos, images.help, 0, 1, 1, IMAGE_COLOR );
	
	ypos+=250;
	drawText(0, ypos, fontNormal, "Please visit http://www.plaatsoft.nl for more information");
	
	sprintf(tmp,"%d fps", CalculateFrameRate());
	drawText(20, 395, fontSpecial, tmp);
}

void drawReleaseNotes(void) {

   int  ypos=yOffset+60;
   int  i=0;
   int  len=0;
   int  lineCount=0;
   int  maxLines=0;
   char *buffer=NULL;
   char text[MAX_BUFFER_SIZE];
   char tmp[MAX_LEN];
		
   // Draw panel
   GRRLIB_DrawImg(10,60, images.panel2, 0, 1, 1, IMAGE_COLOR );
 
   // Draw Info icon
   GRRLIB_DrawImg(ICON_X,ICON_Y+yOffset, images.info, 0, ICON_ZOOM, ICON_ZOOM, IMAGE_COLOR );
		 	      
   // Draw content	
   LAN( buffer=tcp_get_releasenote();)
   if (buffer!=NULL) 
   {
	  strncpy(text,buffer,MAX_BUFFER_SIZE);
	  len=strlen(text);
	  for (i=0;i<len;i++) if (text[i]=='\n') maxLines++;
   }
	
   if (len!=0)
   {		  
	   int startpos=0;
  	   for (i=0; i<len; i++)
	   {
	      if (text[i]=='\n') 
		  {
		     text[i]=0x00;
		     if ((lineCount++)>notesStartLine+17) break;
		     if (lineCount>notesStartLine) 
			 {				   
		        ypos+=15;
			    sprintf(tmp,"%s",text+startpos);
		        drawText(40, ypos, fontNormal, tmp);	
			 }
			 
			 if (strcmp(text+startpos,"last update")==0) break;
			  
			 startpos=i+1;
						
			 if (noteDelay++>400)
		     {
			    if (notesStartLine++>maxLines) notesStartLine=4;
			    noteDelay=0;
			 }
		  }
	   }
	}
	else
	{
	   ypos+=60;
	   drawText(0, ypos, fontNormal, "No release notes information available" );	
	   ypos+=20;
	   drawText(0, ypos, fontNormal, "on this moment!" );		  
    }
	
	sprintf(tmp,"%d fps", CalculateFrameRate());
	drawText(20, 395, fontSpecial, tmp);
}

void drawIntro1(void) { 	   

	// Draw background
	GRRLIB_DrawImg(0,0, images.logo1, 0, 1, 1, IMAGE_COLOR );
		  		  		  	  
	// Draw text layer on top of background 
   GRRLIB_DrawImg2(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, 255);
}


void drawIntro2(void) { 	
	
	char tmp[MAX_LEN];			     
   int  ypos=yOffset+320;
	int  j;
		  
   // Draw background
	GRRLIB_DrawImg(0,0, images.background4, 0, 1, 1, IMAGE_COLOR );

	// Draw Plaatsoft logo		 
   for(j=0;j<images.logo.h;j++) {
      GRRLIB_DrawTile(((640-images.logo2.w)/2)+
		sin(wave1)*50, 
		(((480-images.logo2.h)/2)-50)+j, 
		images.logo, 0, 1, 1, IMAGE_COLOR,j );
      wave1+=0.02;
   }
	wave2+=0.02;
   wave1=wave2;
		  
	drawText(0, ypos, fontSubTitle, "Please visit my website for more information.");
	ypos+=40;
	drawText(0, ypos, fontSubTitle,  "http://www.plaatsoft.nl"  );
			  
	sprintf(tmp,"%d fps", CalculateFrameRate());
	drawText(20, 460, fontSpecial, tmp);
}

void drawIntro3(void) { 
	
	char tmp[MAX_LEN];
	int  ypos=yOffset+390;

	// Draw background
	GRRLIB_DrawImg(0,0, images.logo3, 0, 0.95, 0.98, IMAGE_COLOR );
	GRRLIB_DrawImg(310,0, images.logo4, 0, 0.95, 0.98, IMAGE_COLOR );
	GRRLIB_DrawImg(0,240, images.logo5, 0, 0.95, 0.98, IMAGE_COLOR );
	GRRLIB_DrawImg(310,240, images.logo6, 0, 0.95, 0.98, IMAGE_COLOR );
		  
   GRRLIB_DrawImg(350, 240, images.logo2, 0, 0.5, 0.5, IMAGE_COLOR );
		  
	drawText(350, ypos, fontNormal,  "Some more Wii games developed"  );
	ypos+=20;
	drawText(400, ypos, fontNormal,  "by www.plaatsoft.nl"  );
			 
	sprintf(tmp,"%d fps", CalculateFrameRate()); 
	drawText(580, 460, fontSpecial, tmp); 
}

void drawBannerInfo() {

	int max;
   int select;   
   char tmp[MAX_LEN];
	
   // Select Next Question
   if (maxQuestions<0) { 
		max=0;
	} else {
		max=maxQuestions;
	}
	
   if (selectedQuestion<max) { 
		select=selectedQuestion+1;
	} else  {
		select=max;
   }
   
   GRRLIB_DrawImg(10,0, images.banner, 0, 1, 1, IMAGE_COLOR );

   sprintf(tmp,"%s %02d/%02d",translation.labelQuestion, select, max);
   drawText(120-((strlen(tmp)*14)/2), yOffset, fontHead, tmp);
   
   sprintf(tmp,"%s v%s",PROGRAM_NAME,PROGRAM_VERSION);
   drawText(240, yOffset, fontHead, tmp);
   	  
   sprintf(tmp,"%s %02d", translation.labelScore, score);
   drawText(445+(115-((strlen(tmp)*14)/2)), yOffset, fontHead, tmp);
}

void drawGameboard() { 
     
   // Init text layer	  
   GRRLIB_initTexture();
      
   switch (stateMachine) {
 
		case stateIntro1:
			drawIntro1();
			break;

		case stateIntro2:
			drawIntro2();
			break;

		case stateIntro3:
			drawIntro3();
			break;
		 
      case stateMenu:
			drawBannerInfo();
	   	drawWelcomeScreen();  
			drawButtons(); 
	     	break;
	   
      case stateQuestion:	   
			drawBannerInfo();
	  		drawQuestionScreen();
			drawButtons(); 
         break;

      case stateAnswer:
			drawBannerInfo();
	   	drawAnswerScreen();
			drawButtons(); 
	      break;
	   
      case stateResult:
			drawBannerInfo();
      	drawResultScreen();
			drawButtons(); 
	      break;	
   	   
	   case stateHighScore:  
			drawBannerInfo();
	      drawHighScoreScreen();
			drawButtons(); 
			break;
				
	   case stateSound:
			drawBannerInfo();
			drawSoundScreen();
			drawButtons(); 
			break;
	   
	   case stateCredits:  
			drawBannerInfo();
	   	drawCreditsScreen();		   
			drawButtons(); 
			break;
				
	   case stateGoodbye:
			drawBannerInfo();
			drawGoodbyeScreen();
			drawButtons(); 
			break;
				
	   case stateHelp:
			drawBannerInfo();
			drawHelpScreen();
			drawButtons(); 
			break;
				
	   case stateReleaseNotes:
			drawBannerInfo();
			drawReleaseNotes();
			drawButtons(); 
			break;
	}  
		
   // Draw text layer on top of panels and buttons
   GRRLIB_DrawImg2(0, 0, GRRLIB_GetTexture(), 0, 1.0, 1.0, 255);
}

// -----------------------------------------------------------
// MAIN
// -----------------------------------------------------------

int main() {
	char *s_fn="main";
	traceEvent(s_fn,0,"enter");
	
   int i;
		
   VIDEO_Init();
	
   WPAD_Init();
	
	// Wiimote is shutdown after 300 seconds of innactivity.
   WPAD_SetIdleTimeout(300); 
	
	// enable accelerometers and IR
	WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);	
 
  	// Set Shutdown Callbacks.
	SYS_SetPowerCallback( doPowerOff );
	WPAD_SetPowerButtonCallback( doPadPowerOff );
	
   // Init Sound engine			
	SND_Init(INIT_RATE_48000); 
	MODPlay_Init(&snd1);
   SND_Pause(0);

   // Obtain the preferred video mode from the system
	// This will correspond to the settings in the Wii menu
	rmode = VIDEO_GetPreferredMode(NULL);
		
	if (rmode->xfbHeight==528) {
	   // TV mode PAL 50Hz
	   yOffset = 25;  
		yjpegOffset = 25;
	} else {      
	   // TV mode PAL 60Hz
	   yOffset = 25;
		yjpegOffset = 0;
	}

   // Init Fat
   fatInitDefault();
	
	// Open trace module
	traceOpen(TRACE_FILENAME);

	traceEvent(s_fn, 0,"%s %s Started", PROGRAM_NAME, PROGRAM_VERSION);
	
  	// Init game variables    
	initGame();
	
   // Init music track
   initMusicTrack();
			
	// Init Freetype font library
	GRRLIB_InitFreetype();

    // Init threads	
	initThreads();
			
	// Load global language content file
	initLanguages( FILENAME_LANGUAGES );
	
	// Load Translation file
	initTranslation( languages[selectedLanguage].translation );
	
	// Load global Topic file
	initTopics( languages[selectedLanguage].topics );
	
	// Load question file.
	initQuestions( topics[selectedTopic].filename);
	
	// Load images
	initImages();
	
	// Init pointers
	initPointer();
	
	// Load highscore xml file
	initHighScore(HIGHSCORE_FILENAME);

   // Init GRRLib graphics library
   GRRLIB_Init();
    
	// Make screen black
	GRRLIB_FillScreen(0x000000FF);
   GRRLIB_Render();
			
	// Repeat forever
   while(!bPowerOff)
	{
	   // icon angle 
	   if (++angle>=MAX_ANGLE) angle=0;
		
		// icon alfa 
		if (alfa_direction)
		{
		   ++alfa;
		   if (++alfa>=MAX_ALFA) alfa_direction=false;
		}
		else
		{
		   --alfa;
		   if (--alfa<=0) alfa_direction=true;
		}
		
	   // Init (Update) state Machine
	   initStateMachine();
		
		// Scan for button events
		WPAD_SetVRes(0, 640, 480);
      WPAD_ScanPads();
		
	   // Draw game board and other items
      drawGameboard();

		// Process four WiiMote pointers
      for (i=0; i<MAX_POINTERS; i++)
		{
			u32 wpaddown = WPAD_ButtonsDown(i);
			u32 wpadheld = WPAD_ButtonsHeld(i);
		
         // Scan for ir events (WiiMote's)
			WPAD_SetVRes(i, MAX_HORZ_PIXELS, MAX_VERT_PIXELS);
			WPAD_IR(i, &pointers[i].ir); 
			pointers[i].x=pointers[i].ir.sx-WSP_POINTER_X;
			pointers[i].xOffset=pointers[i].x+IR_X_OFFSET;
			pointers[i].y=pointers[i].ir.sy-WSP_POINTER_Y;
			pointers[i].yOffset=pointers[i].y+IR_Y_OFFSET;
			pointers[i].angle=pointers[i].ir.angle;
					
			// handle button events
         if (wpaddown & BUTTON_A) {
				buttonA(pointers[i].xOffset,pointers[i].yOffset);		
			}
			
			if (wpaddown & BUTTON_MINUS ) {
				buttonMinus();
			}
			
			if (wpaddown & BUTTON_1 ) {
				button1x();				
			}
			
			if (wpaddown & BUTTON_2 ) {
				button2y();		
			}
			
			if (wpaddown & BUTTON_HOME) {
				buttonHome();
			}
			
		   // Make screenshot 
			if (wpadheld & BUTTON_PLUS) {
		      char filename[MAX_LEN];
      	   struct tm *level;	   
		      time_t dt=time(NULL);
		      level = localtime(&dt);
		      sprintf(filename,"%sbiblequiz-%04d%02d%02d%02d%02d%02d.png", GAME_DIRECTORY, level->tm_year+1900,level->tm_mon+1, level->tm_mday,  level->tm_hour, level->tm_min, level->tm_sec);		  
            GRRLIB_ScrShot(filename);			   
			}

			// Draw wiiremote ir pointer
			GRRLIB_DrawImg( 
				pointers[i].x, 
				pointers[i].y, 
				pointers[i].image, 
				0, //pointers[i].angle, 
				1, 1, IMAGE_COLOR );
		}
		GRRLIB_Render();
	}
	
	GRRLIB_Exit();
	
	// Shut the system down.
	if ( bPowerOff ) {
		traceEvent(s_fn, 0,"Shut the system down");
		traceEvent(s_fn, 0,"%s %s Stopped", PROGRAM_NAME, PROGRAM_VERSION);
		traceClose();

		SYS_ResetSystem( SYS_POWEROFF, 0, 0 );
   }

   return 0;
}

// -----------------------------------------------------------
// THE END
// -----------------------------------------------------------
