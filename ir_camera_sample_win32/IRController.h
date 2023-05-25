#pragma once
#include <hstring.h>
#include <iostream>
//#include <robuffer.h>
#include <codecvt>
#include <robuffer.h>
#include <wrl.h>

#include <codecvt>
#include "winrt/Windows.System.Diagnostics.h"
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Foundation.Collections.h"
#include "winrt/Windows.Devices.Enumeration.h"
#include "winrt/Windows.Media.Devices.h"
#include "winrt/Windows.UI.Xaml.Controls.h";
#include "winrt/Windows.Media.MediaProperties.h"
#include "winrt/Windows.Media.Capture.h"
#include "winrt/Windows.Media.Capture.Frames.h"
#include "winrt/Windows.Media.Core.h"
#include "winrt/Windows.UI.Popups.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.System.h>
#include "winrt/Windows.storage.streams.h"
#include "winrt/Windows.Graphics.Imaging.h"
#include <winrt/Windows.System.Threading.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/highgui/highgui.hpp"

using namespace winrt;
using namespace winrt::Windows::Devices;
using namespace winrt::Windows::Devices::Enumeration;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Media;
using namespace winrt::Windows::Media::Capture;
using namespace winrt::Windows::Media::Capture::Frames;
using namespace winrt::Windows::Graphics::Imaging;
using namespace winrt::Windows::System::Threading;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Media;

using namespace Microsoft::WRL;
using namespace std;


class IRController
{
private:
	MediaCapture m_mediaCapture;
	MediaFrameReader m_frameReader;
	winrt::slim_mutex m_lock;
	CaptureElement capElement;
public:
	IRController()
		: m_frameReader(nullptr)
		, m_mediaCapture(nullptr)
	{

	}
	void InitIRCamera();
	void FrameArrivedHandler(const MediaFrameReader& FrameReader, const  MediaFrameArrivedEventArgs& args);
	void MediaCaptureErrorHandler(MediaCapture sender, MediaCaptureFailedEventArgs errorEventArgs);
	CaptureElement getCaptureElement();

};

