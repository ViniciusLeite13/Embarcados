/////////////////////////////////////////////////////////////////////////////
// Oak.h : header file
//
// Version 1.3
//
// Control for Toradex Oak USB Sensors
//
// Copyright (c) 2007-2011. All Rights Reserved.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <windows.h>

#define VENDOR_ID_TORADEX 0x1B67
#define MAX_NO_CHANNELS 11

#ifdef __cplusplus	// If used by C++ code, 
extern "C"			// we need to export the C interface
{          
#endif

//---------------------------------------------------------------------------
// differentiate between UNICODE and ASCII versions of the library
//---------------------------------------------------------------------------
#ifdef _UNICODE
	#define tOakString                  tOakString_w
	#define tDevicePathString           tDevicePathString_w
	#define tChannel                    tChannel_w
	#define tOakSensor                  tOakSensor_w
	#define PtOakSensor                 PtOakSensor_w
	#define OAK_HANDLE                  OAK_HANDLE_w
	#define tNotifyFct                  tNotifyFct_w

	#define Oak_Register_Callback       Oak_Register_Callback_w
	#define Oak_Hotplug_Enable          Oak_Hotplug_Enable_w
	#define Oak_NotifyConnectedDevices  Oak_NotifyConnectedDevices_w
	#define Oak_DestroyNotifications    Oak_DestroyNotifications_w
	#define Oak_Feature                 Oak_Feature_w
	#define Oak_Initialize              Oak_Initialize_w
	#define Oak_FindSensor              Oak_FindSensor_w
	#define Oak_GetCurrentInReport      Oak_GetCurrentInReport_w
	#define Oak_GetInReport             Oak_GetInReport_w
	#define Oak_SendOutReport           Oak_SendOutReport_w
   #define Oak_Cleanup                 Oak_Cleanup_w
#else	// ASCII
	#define tOakString                  tOakString_a
	#define tDevicePathString           tDevicePathString_a
	#define tChannel                    tChannel_a
	#define tOakSensor                  tOakSensor_a
	#define PtOakSensor                 PtOakSensor_a
	#define OAK_HANDLE                  OAK_HANDLE_a
	#define tNotifyFct                  tNotifyFct_a

	#define Oak_Register_Callback       Oak_Register_Callback_a
	#define Oak_Hotplug_Enable          Oak_Hotplug_Enable_a
	#define Oak_NotifyConnectedDevices  Oak_NotifyConnectedDevices_a
	#define Oak_DestroyNotifications    Oak_DestroyNotifications_a
	#define Oak_Feature                 Oak_Feature_a
	#define Oak_Initialize              Oak_Initialize_a
	#define Oak_FindSensor              Oak_FindSensor_a
	#define Oak_GetCurrentInReport      Oak_GetCurrentInReport_a
	#define Oak_GetInReport             Oak_GetInReport_a
	#define Oak_SendOutReport           Oak_SendOutReport_a
   #define Oak_Cleanup                 Oak_Cleanup_a
#endif


	//---------------------------------------------------------------------------
	// Type definitions
	//---------------------------------------------------------------------------
	typedef TCHAR	tOakString [24];
	typedef TCHAR	tDevicePathString[256];

	// Data that is available about each single data channel.
	// An array of this type is used as part of the tOakSensor struct below.
	typedef struct
	{
	   bool		IsSigned;
		BYTE		BitSize;
				
		signed char UnitExponent;
		ULONG		Unit;
		TCHAR		UnitStr[24];

		TCHAR		ChannelName[24];
		TCHAR		UserChannelName[24];
		TCHAR		UserChannelName_NV[24];

		BYTE		RFU[64]; // reserved for future use
	} tChannel;

	// Information that is available about a connected sensor
	typedef struct
	{
		TCHAR	DevicePath [256];

			WORD		VID;
			WORD		PID;
			WORD		REV;
			TCHAR		SN[24];

		  BYTE		RFU[64]; // reserved for future use

			TCHAR		DeviceName[24];
			TCHAR		UserDeviceName[24];
			TCHAR		UserDeviceName_NV[24];
		
			WORD		NumChannels;
			tChannel	Channel[MAX_NO_CHANNELS];
	} tOakSensor;
	typedef tOakSensor *PtOakSensor, *OAK_HANDLE;

	// The following line of code defines a type named tNotifyFct.
	// Functions of this type are needed as Callback functions (see "Oak_Register_Callback" below).
	// a variable of type tNotifyFct is a pointer to a function that takes a tOakSensor as an argument, and has no return value.
	// A Callback function must look e.g. like this:
	//
	//		void __stdcall SensorWasJustAttached(PtOakSensor Sensor, LPARAM UserParam)
	//		{
	//				/* do necessary actions when a sensor was attached / removed */
	//		}
	//
	//	IMPORTANT: it is strongly recommended to code the Callback function in a way, that it can be called 
	//             more than once for the same sensor!
	//			   Given you want to keep a list of connected sensors, verify in the "OnConnect"
	//			   function if the sensor is already in the list, before adding it.
	typedef void  (__stdcall * tNotifyFct)(PtOakSensor,LPARAM);

	//---------------------------------------------------------------------------
	// Functions to detect sensors
	//---------------------------------------------------------------------------
	// Register a Notify function that will be called, when a device is connected that matches all the filter parameters
	// to ignore a filter parameter, set it to 0 or NULL respectively
extern "C" __declspec(dllexport) void Oak_Register_Callback( tNotifyFct OnConnect, tNotifyFct OnDisconnect,
									  WORD PID, WORD REV, LPTSTR SN, 
									  LPTSTR DeviceName, LPTSTR ChannelName, 
									  LPTSTR UserDeviceName, LPTSTR UserChannelName,
									  LPARAM UserParam);

	// Call once to enable live notifications when a sensor is
	// inserted or removed
extern "C" __declspec(dllexport) void Oak_Hotplug_Enable(void);

	// Call notify function for all currently connected devices that match the registered filter criteria
	// (as if all sensors just has been plugged in)
extern "C" __declspec(dllexport) void Oak_NotifyConnectedDevices(void);

	// Clear all callback functions that are registered to be called on Connect/Disconnect of an Oak Sensor device
extern "C" __declspec(dllexport) void Oak_DestroyNotifications(void);

	//---------------------------------------------------------------------------
	// Functions to communicate with the sensors
	//---------------------------------------------------------------------------

	// Send and Receive a Feature Report to/from the sensor device
	//		- "RptBuf" will be sent to the sensor. 
	//		- The function then waits until the sensor has the result ready ( if there is any). 
	//		- "RptBuf" will finally be overwritten by the sensor's answer.
extern "C" __declspec(dllexport) bool Oak_Feature(LPCTSTR DevicePath, BYTE RptBuf[33], bool ExpectResult);

	//---------------------------------------------------------------------------
	// Functions to Read Sensor values
	//---------------------------------------------------------------------------
	// Toradex recommends to use standard windows functions: 
	//  DeviceHandle = Createfile (DevicePath, ...);
	//  ReadFile(DeviceHandle, ReadBuffer, ...);
	//  CloseHandle(DeviceHandle);

	//---------------------------------------------------------------------------
	// Functions only needed for debug purposes
	//---------------------------------------------------------------------------
	// initialize debug stuff
extern "C" __declspec(dllexport) void Oak_Initialize(void);


	//---------------------------------------------------------------------------
	// Blocking functions that return directly with a result
	//---------------------------------------------------------------------------
	// Search for a sensor and result a structure containing information about it.
	// if the provided filters fit for more than one sensor, only one (random) sensor is returned.
	// The function returns true, if a sensor matched the provided filters.
extern "C" __declspec(dllexport) bool Oak_FindSensor(
									  WORD PID, WORD REV, LPCTSTR SN,					// filters to be set
									  LPCTSTR DeviceName, LPCTSTR ChannelName,			// 0 or NULL acts as wildcard.
									  LPCTSTR UserDeviceName, LPCTSTR UserChannelName,
									  PtOakSensor SensorFound);						// this is the return value

	// Get current device state (USB communication using Control Endpoint)
	// - this function only works for Windows Versions XP and higher
	// - do not use this function to continuously read data from the sensor - as it always returns the last
	//   report received, reports may be lost.
extern "C" __declspec(dllexport) bool Oak_GetCurrentInReport (LPCTSTR DevicePath, BYTE RptBuf[33], BYTE InReportLength);

	// Wait for a report to be received and return it.
	// The function returns anyway, after "Timeout_ms" has elapsed.
	// - do not set the Timeout_ms close to the sensor's report rate. We found that reports may get lost if you do.
extern "C" __declspec(dllexport) bool Oak_GetInReport (LPCTSTR DevicePath, BYTE RptBuf[33], BYTE InReportLength, WORD Timeout_ms);

	// Waits for sending a report and sent it.
	// The function returns anyway, after "Timeout_ms" has elapsed.
	// - do not set the Timeout_ms close to the sensor's report rate. We found that reports may get lost if you do.
extern "C" __declspec(dllexport) bool Oak_SendOutReport (LPCTSTR DevicePath, BYTE RptBuf[33], BYTE OutReportLength, WORD Timeout_ms);

   // Operate a proper cleanup of the library internals.
   // Call this function whenever your done using the library (typically when your program is about to exit).
   // Not calling this function may result in memory leaks
extern "C" __declspec(dllexport) void Oak_Cleanup();


#ifdef __cplusplus
}
#endif
