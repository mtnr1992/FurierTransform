/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: exitFunc */
#define  PANEL_CANVAS                     2       /* control type: canvas, callback function: (none) */
#define  PANEL_MASS_2                     3       /* control type: numeric, callback function: Change */
#define  PANEL_K_2                        4       /* control type: numeric, callback function: Change */
#define  PANEL_Y_OFFSET_2                 5       /* control type: numeric, callback function: Change */
#define  PANEL_MASS                       6       /* control type: numeric, callback function: Change */
#define  PANEL_K                          7       /* control type: numeric, callback function: Change */
#define  PANEL_Y_OFFSET                   8       /* control type: numeric, callback function: Change */
#define  PANEL_STARTSTOP                  9       /* control type: textButton, callback function: Start */
#define  PANEL_NUMOFMASS                  10      /* control type: radioButton, callback function: numOfMass */
#define  PANEL_TEXTMSG                    11      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION                 12      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_2                  13      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_2               14      /* control type: deco, callback function: (none) */
#define  PANEL_STRIPCHART                 15      /* control type: strip, callback function: (none) */
#define  PANEL_GRAPH                      16      /* control type: graph, callback function: (none) */
#define  PANEL_DECORATION_3               17      /* control type: deco, callback function: (none) */
#define  PANEL_TIMER                      18      /* control type: timer, callback function: Tick */
#define  PANEL_TEXTMSG_3                  19      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exitFunc(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK numOfMass(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Start(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tick(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
