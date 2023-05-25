# Access Infrared Camera using Media Foundation Platform APIs  (C++/ WinRT) non-UWP
## Pre Requirements
-  Windows 10/11 
-  have a compatible infrared camera (IR Camera)
-  Visual Studio 2019/2022
-  WinRT
-  C++ 17/20
-  OpenCV

## Test Environment
- OS: Windows 11 Home 22H2
- IR Camera: NexiGo HelloCam N930W Camera
- IDE:  Visual Studio 2022 
- programming lenguaje: C++ 20
- Windows SDK: 10.0.22621.0
- Platform Toolset: Visual Studio 2019(v142)

## Objective
The objective was to develop an application that could get access and control of a IR Camera in Windows. Doing a short investigation, I found that the easy way to get access to the IR Camera is using the Media Foundation API that is available using `C++/WinRT`or `C++/CX` . This application uses `C++/WinRT` and `Xaml` framework  without been a Universal Windows plaform App( you don’t have the problems of a Universal Windows App 🙂 ).To achieve this the application is based on the following Microsoft tutorial: https://learn.microsoft.com/en-us/windows/apps/desktop/modernize/host-standard-control-with-xaml-islands-cpp.

WARNING: This project is only an example of how to access the IR Camera in the most simpler way which is not optimized, don't have error handling in most cases and you will have to modify it to your needs.

# How To Run
To Build and run this project you would need to meet the pre requirement and for opencv you would need to modify the paths of where you have the opencv folder installed.

![ir_display](https://github.com/andresbeltranc/ir_camera_sample_win32/assets/89097527/6727d2ae-c8e2-447e-bb39-f7d9fb08d882)
