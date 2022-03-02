#include <analysis.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Spring.h"

void draw(); 
void calculate(); 

static int panelHandle;
int springBMP_1,springBMP_2, top,left,width,height, i=1,counter=0,secondMass=0;
double g=9.81, REAL[10000];
double dt=0.00001,CALC=2000;    

typedef struct
{
double y, vy, ay, as,mass,k;
}SPRING;

SPRING  spring_1,spring_2;


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Spring.uir", PANEL)) < 0)
		return -1;

	void initielize();
	{
		//LOAD SPRING BMP
		GetBitmapFromFile ("Spring.png", &springBMP_1);
		springBMP_2=springBMP_1;
		top=15;
		left=15;
		width=50;
		height=240;
		
		spring_1.vy=0;
		spring_1.as=0;
		spring_1.mass=10;
		spring_1.k=30;
		
		spring_2.vy=0;
		spring_2.as=0;
		spring_2.mass=30;
		spring_2.k=50;
		
		GetCtrlVal (panelHandle, PANEL_Y_OFFSET, &spring_1.y);
		
		SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_DK_RED);
		SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, MakeColor(200,100,100));
		
		calculate();
		draw();  
	}
	
	DisplayPanel (panelHandle);
	RunUserInterface ();
	
	void terminate();
	{
		//release BMP 
		DiscardBitmap (springBMP_1);
		
	}
	
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK exitFunc (int panel, int event, void *callbackData,
						  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

void calculate()
{
	for(int j=0; j<CALC;j++){
		if(secondMass)
		spring_1.as=spring_2.k*(spring_2.y-spring_1.y)/spring_1.mass-spring_1.k*spring_1.y/spring_1.mass;
		  else spring_1.as=-spring_1.k*spring_1.y/spring_1.mass;
	
	spring_1.ay=spring_1.as+g;

	if(secondMass){
	spring_2.as=-spring_2.k*(spring_2.y-spring_1.y)/spring_2.mass;
	spring_2.ay=spring_2.as+g;
	spring_2.y=spring_2.y+spring_2.vy*dt+spring_2.ay*pow(dt,2)/2;
	spring_2.vy=spring_2.vy+spring_2.ay*dt;	
	}
	spring_1.y=spring_1.y+spring_1.vy*dt+spring_1.ay*pow(dt,2)/2;
	spring_1.vy=spring_1.vy+spring_1.ay*dt;
	}
}


void draw()
{
double SecSpringStart;	
	//first spring   
	CanvasStartBatchDraw (panelHandle, PANEL_CANVAS);
	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
	
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, springBMP_1, VAL_ENTIRE_OBJECT,MakeRect(top,left,height-spring_1.y,width) );
	CanvasDrawRect (panelHandle, PANEL_CANVAS,MakeRect (top+height-spring_1.y, left, width, width) , VAL_DRAW_FRAME_AND_INTERIOR);
	
	//second spring
	if(secondMass){
		SecSpringStart=top+height-spring_1.y+width;
		CanvasDrawBitmap (panelHandle, PANEL_CANVAS, springBMP_1, VAL_ENTIRE_OBJECT,MakeRect(SecSpringStart,left
						  																			,height/2-spring_2.y,width) );
		
		CanvasDrawRect (panelHandle, PANEL_CANVAS,MakeRect (SecSpringStart+height/2-spring_2.y, left, width, width) 
																									,VAL_DRAW_FRAME_AND_INTERIOR);
	}
	
	CanvasEndBatchDraw (panelHandle, PANEL_CANVAS);    
	
	//STRIPCHART
	
	PlotStripChartPoint (panelHandle, PANEL_STRIPCHART, spring_1.y);

	//DATA Acquisition
	
	REAL[counter]=-spring_1.y;
	counter++;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~START
int CVICALLBACK Start (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	double IMG[10000],H[10000],data[10000];
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			//reset all
			if(i%2){
			DeleteGraphPlot (panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			counter=0;
			for(int k=0;k<counter;k++){
			H[k]=0;
			REAL[k]=0;
			IMG[k]=0;
			}
			}
			
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, i%2);
			//dimme all bottons
			SetCtrlAttribute (panelHandle, PANEL_NUMOFMASS, ATTR_DIMMED, i%2); 
			
			SetCtrlAttribute (panelHandle, PANEL_Y_OFFSET, ATTR_DIMMED, i%2);
			SetCtrlAttribute (panelHandle, PANEL_K, ATTR_DIMMED, i%2);
			SetCtrlAttribute (panelHandle, PANEL_MASS, ATTR_DIMMED, i%2);
			if(secondMass){
			SetCtrlAttribute (panelHandle, PANEL_Y_OFFSET_2, ATTR_DIMMED, i%2);
			SetCtrlAttribute (panelHandle, PANEL_K_2, ATTR_DIMMED, i%2);
			SetCtrlAttribute (panelHandle, PANEL_MASS_2, ATTR_DIMMED, i%2);
				}
			//-- 
			i++;
			
			//FUORIER
			if(counter){
			
			ReFFT (REAL, IMG,counter );
			
			for(int k=0;k<counter;k++){
				H[k]= pow( pow( REAL[k],2)+pow( IMG[k],2) ,0.5);
				data[k]=k/(counter*dt*CALC);	
				}
			
				PlotXY (panelHandle, PANEL_GRAPH, data, H, counter, VAL_DOUBLE, VAL_DOUBLE, VAL_CONNECTED_POINTS, VAL_SOLID_CIRCLE, VAL_SOLID, 1, VAL_RED);
			}
			
			counter=0;
			break;
	}
	return 0;
}

int CVICALLBACK Change (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			//1st spring val
			GetCtrlVal (panelHandle, PANEL_Y_OFFSET, &spring_1.y);   
			GetCtrlVal (panelHandle, PANEL_K, &spring_1.k);
			GetCtrlVal (panelHandle, PANEL_MASS, &spring_1.mass);
			//2nd spring val
			GetCtrlVal (panelHandle, PANEL_Y_OFFSET_2, &spring_2.y);   
			GetCtrlVal (panelHandle, PANEL_K_2, &spring_2.k);
			GetCtrlVal (panelHandle, PANEL_MASS_2, &spring_2.mass);
			break;
	}
	return 0;
}

int CVICALLBACK Tick (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			calculate();
			draw(); 
			break;
	}
	return 0;
}

int CVICALLBACK numOfMass (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_NUMOFMASS, &secondMass);
			SetCtrlAttribute (panelHandle, PANEL_Y_OFFSET_2, ATTR_DIMMED, 1-secondMass);
			SetCtrlAttribute (panelHandle, PANEL_K_2, ATTR_DIMMED, 1-secondMass);
			SetCtrlAttribute (panelHandle, PANEL_MASS_2, ATTR_DIMMED, 1-secondMass);
			draw();
			break;
	}
	return 0;
}
