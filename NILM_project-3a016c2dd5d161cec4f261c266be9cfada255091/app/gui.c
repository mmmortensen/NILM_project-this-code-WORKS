#include "includes.h"
#include "gui.h"

// Application variables
char headLine[20] = "Monitoring";
bool mode = 0; // 0 = Monitoring mode, 1 = Learning mode
int devicesConnected = 1; // amount of devices registered
bool hasMeanValue = 0; // is the mean value measured
bool modeButtonState = 1; // enable / disable mode button
bool settingsButtonState = 1; // enable / disable settings button
bool backButtonState = 0; // enable / disable back button
bool addDeviceButtonState = 1; // enable / disable back button
int screen = 0;
 /* 0 = Monitor mode
  * 1 = Learning mode
  * 2 = Devices 
  * 3 = Web Server
  * 4 = Information
  * 5 = Settings
  * 9 = Main Menu
  */
// Get mode
bool gui_getMode(){return mode;}
/*************************************************************************
 * Function Name: gui_toggleMode
 * Parameters: none
 *
 * Return: none
 *
 * Description: Toggles between learning and monitoring mode
 *
 *************************************************************************/
void gui_toggleMode(pAlgoDevice_t pDevices,int devLamps[])
{
  mode=!mode;
  if(mode)
  {
    gui_learningScreen();
  }
  else
  {
    gui_monitoringScreen(pDevices,devLamps);
  }
}
/*************************************************************************
 * Function Name: gui_clearScreen
 * Parameters: none
 *
 * Return: none
 *
 * Description: clears the screen to all white
 *
 *************************************************************************/
void gui_clearScreen(void)
{
    // Clear background
    GLCD_SetFont(&Terminal_18_24_12,0x000000,0xffffffff);
    GLCD_SetWindow(0,0,319,239);
    GLCD_TextSetPos(0,0);
    GLCD_print("\f%s"," ");
}
/*************************************************************************
 * Function Name: gui_button
 * Parameters: xLeft, yUp, xRight, yDown, text, textPosX, textPosY, txtColor, backgroundColor
 *
 * Return: none
 *
 * Description: place button
 *
 *************************************************************************/
void gui_button(int xLeft, int yUp, int xRight, int yDown, pInt8U text, int textPosX, int textPosY, LdcPixel_t txtColor, LdcPixel_t backgroundColor)
{
    // Add Button
    GLCD_SetFont(&Terminal_18_24_12,txtColor,backgroundColor);
    GLCD_SetWindow(xLeft,yUp,xRight, yDown);
    GLCD_print("\f%s", " ");
    GLCD_SetWindow(xLeft+textPosX,yUp+textPosY,xRight,yDown);
    GLCD_TextSetPos(0,0);
    GLCD_print("\f%s", text);
}
/*************************************************************************
 * Function Name: gui_monitoringScreen
 * Parameters: None
 *
 * Return: none
 *
 * Description: GUI home screen (Monitoring mode)
 *
 *************************************************************************/
void gui_monitoringScreen(pAlgoDevice_t pDevices,int devLamps[])
{
  // Menu options
  settingsButtonState = 0; // Enable Settings
  modeButtonState = 0; // Enable Mode
  screen = 0; // Tracking screen, 0 = monitoring screen
  
  // Clear screen
  gui_clearScreen();
  
  // Entering MONITORING MODE
  strcpy(headLine, "Monitoring");
  
  // Set headline
  GLCD_SetFont(&Terminal_18_24_12,0x000000,0xffffffff);
  GLCD_SetWindow(95,0,225,23);
  GLCD_TextSetPos(0,0);
  GLCD_print("\f%s", headLine);
  
  // device img 1
  (devLamps[0]==1)? GLCD_LoadPic(28, 59, &lamp_onPic, 1):
        GLCD_LoadPic(28, 59, &lamp_offPic, 1);  
  GLCD_SetWindow(5,136,101,228);
  GLCD_TextSetPos(0,0);
  GLCD_print("\fDev 1\n\rP: %f\n\rQ: %f\n\rH: 46W",(*pDevices).dP, 
             (*pDevices).dQ);

  // device img 2  
  (devLamps[1]==1)? GLCD_LoadPic(134, 59, &lamp_onPic, 1):
     GLCD_LoadPic(134, 59, &lamp_offPic, 1);
  GLCD_SetWindow(111,136,207,228);
  GLCD_TextSetPos(0,0);
  GLCD_print("\fDev 2\n\rP: %f\n\rQ: %f\n\rH: 46W",(*(pDevices+1)).dP,
             (*(pDevices+1)).dQ);

  // device img 3
  (devLamps[2]==1)?  GLCD_LoadPic(240, 59, &lamp_onPic, 1):
     GLCD_LoadPic(240, 59, &lamp_offPic, 1);
  
  // Back button
  GLCD_LoadPic(0, 0, &button_backPic, 1);
 
  
  GLCD_SetWindow(219,136,313,228);
  GLCD_TextSetPos(0,0);

//    GLCD_print("\fDev 3\n\rP: %f\n\rQ: %f\n\rH: 46W",(*(pDevices+2)).dP,
//             (*(pDevices+2)).dQ);
  
}


/*************************************************************************
 * Function Name: gui_learningScreen
 * Parameters: None
 *
 * Return: none
 *
 * Description: GUI learning screen (Learning mode)
 *
 *************************************************************************/
void gui_learningScreen(void)
{
  // Menu options
  settingsButtonState = 0;
  modeButtonState = 0;
  screen = 1; // Tracking screen, 1 = learning screen
  
  // Clear screen
  gui_clearScreen();
  
  // Entering LEARNING MODE
  strcpy(headLine, "Learning Mode");
  
  // Set headline
  GLCD_SetFont(&Terminal_18_24_12,0x000000,0xffffffff);
  GLCD_SetWindow(85,0,235,23);
  GLCD_TextSetPos(0,0);
  GLCD_print("\f%s", headLine);
  
  
  // Add Device
  gui_button(80,70,240,120,"Add Device",23,13,0x000000,0x0066ff66);
  
  if(devicesConnected)
  {
    // Delete All Devices
    gui_button(80,130,240,180,"Delete All",23,13,0x000000,0x00ff9966);
  }
  
  // Back button
  GLCD_LoadPic(0, 0, &button_backPic, 1);
  
  gui_button(0,0,319,50,dataArray,0,0,0x000000,0x00ff9966);
}
/*************************************************************************
 * Function Name: gui_devicesScreen
 * Parameters: None
 *
 * Return: none
 *
 * Description: GUI add device (Learning mode)
 *
 *************************************************************************/
void gui_devicesScreen(void)
{
  // Menu options
  settingsButtonState = 0;
  modeButtonState = 0;
  backButtonState = 1;
  screen = 2; // 2 = Devies screen
  
  // Clear screen
  gui_clearScreen();
  
  // Entering Devices
  strcpy(headLine, "Devices");
  
  // Set headline
  GLCD_SetFont(&Terminal_18_24_12,0x000000,0xffffffff);
  GLCD_SetWindow(85,0,235,23);
  GLCD_TextSetPos(0,0);
  GLCD_print("\f%s", headLine);
  
    // Message
  GLCD_SetFont(&Terminal_18_24_12,0x000000,0xffffffff);
  GLCD_SetWindow(85,100,235,123);
  GLCD_TextSetPos(0,0);
  GLCD_print("\f%s", "Devices!!! :D");

  // Back button
  GLCD_LoadPic(0, 0, &button_backPic, 1);
}
/*************************************************************************
 * Function Name: gui_serverScreen
 * Parameters: None
 *
 * Return: none
 *
 * Description: GUI settings screen
 *
 *************************************************************************/
void gui_serverScreen(void)
{
 // Menu options
  settingsButtonState = 0;
  modeButtonState = 0;
  backButtonState = 1;
  screen = 3; // 3 = Server screen
  
  // Clear screen
  gui_clearScreen();
  
  // Entering Seb Server Screen
  strcpy(headLine, "Web Server");
  
  // Set headline
  GLCD_SetFont(&Terminal_18_24_12,0x000000,0xffffffff);
  GLCD_SetWindow(85,0,235,23);
  GLCD_TextSetPos(0,0);
  GLCD_print("\f%s", headLine);
  
  // Message
  GLCD_SetFont(&Terminal_18_24_12,0x000000,0xffffffff);
  GLCD_SetWindow(85,100,235,123);
  GLCD_TextSetPos(0,0);
  GLCD_print("\f%s", "Server info!!! :D");
  
  // Back button
  GLCD_LoadPic(0, 0, &button_backPic, 1);
}
/*************************************************************************
 * Function Name: gui_infoScreen
 * Parameters: None
 *
 * Return: none
 *
 * Description: GUI settings screen
 *
 *************************************************************************/
void gui_infoScreen(void)
{
 // Menu options
  settingsButtonState = 0;
  modeButtonState = 0;
  backButtonState = 1;
  screen = 4; // 4 = Info screen
  
  // Clear screen
  gui_clearScreen();
  
  // Entering Information Screen
  strcpy(headLine, "Information");
  
  // Set headline
  GLCD_SetFont(&Terminal_18_24_12,0x000000,0xffffffff);
  GLCD_SetWindow(85,0,235,23);
  GLCD_TextSetPos(0,0);
  GLCD_print("\f%s", headLine);
  
  // Message
  GLCD_SetFont(&Terminal_18_24_12,0x000000,0xffffffff);
  GLCD_SetWindow(85,100,235,123);
  GLCD_TextSetPos(0,0);
  GLCD_print("\f%s", "Info!!! :D");
  
  // Back button
  GLCD_LoadPic(0, 0, &button_backPic, 1);
}
/*************************************************************************
 * Function Name: gui_settingsScreen
 * Parameters: None
 *
 * Return: none
 *
 * Description: GUI settings screen
 *
 *************************************************************************/
void gui_settingsScreen(void)
{
  // Menu options
  settingsButtonState = 0;
  modeButtonState = 0;
  backButtonState = 1;
  screen = 5; // 5 = settings screen
  
  // Clear screen
  gui_clearScreen();
  
  // Entering Settings screen
  strcpy(headLine, "Settings");
  
  // Set headline
  GLCD_SetFont(&Terminal_18_24_12,0x000000,0xffffffff);
  GLCD_SetWindow(85,0,235,23);
  GLCD_TextSetPos(0,0);
  GLCD_print("\f%s", headLine);
  
  // Message
  GLCD_SetFont(&Terminal_18_24_12,0x000000,0xffffffff);
  GLCD_SetWindow(85,100,235,123);
  GLCD_TextSetPos(0,0);
  GLCD_print("\f%s", "Settings!!! :D");
  
  // Back button
  GLCD_LoadPic(0, 0, &button_backPic, 1);
}
/*************************************************************************
 * Function Name: gui_mainScreen
 * Parameters: None
 *
 * Return: none
 *
 * Description: GUI settings screen
 *
 *************************************************************************/
void gui_mainScreen(void)
{
  // Menu options
  settingsButtonState = 0;
  modeButtonState = 0;
  backButtonState = 1;
  screen = 9; // Main screen, 9 = settings screen
  
  // Clear screen
  gui_clearScreen();
  
  // Main Menu Buttons
  GLCD_LoadPic(59, 64, &button_monitorPic, 1); 
  GLCD_LoadPic(129, 64, &button_learnPic, 1);
  GLCD_LoadPic(199, 64, &button_devicesPic, 1); 
  GLCD_LoadPic(59, 134, &button_serverPic, 1); 
  GLCD_LoadPic(129, 134, &button_infoPic, 1); 
  GLCD_LoadPic(199, 134, &button_settingsPic, 1); 
}
