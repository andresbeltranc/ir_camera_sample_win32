#include "IRController.h"

struct __declspec(uuid("5b0d3235-4dba-4d44-865e-8f1d0e4fd04d")) __declspec(novtable) IMemoryBufferByteAccess : ::IUnknown
{
    virtual HRESULT __stdcall GetBuffer(uint8_t** value, uint32_t* capacity) = 0;
};

void IRController::InitIRCamera()
{
    m_mediaCapture = MediaCapture();
    list<MediaFrameSourceGroup> irDevices;
    auto devices = MediaFrameSourceGroup::FindAllAsync().get();
    for (auto&& device : devices) {
        auto currentDevice = device.SourceInfos().First().Current();
        if (currentDevice.SourceKind() == MediaFrameSourceKind::Infrared) {
            irDevices.push_front(device);
        }
    }
    if (irDevices.empty()) {
        OutputDebugStringA("IR CAMERA DEVICES NOT FOUND\n");
    }
    MediaFrameSourceGroup device = irDevices.front();
    MediaCaptureInitializationSettings settings;
    settings.SourceGroup(device);
    settings.SharingMode(MediaCaptureSharingMode::SharedReadOnly);
    settings.StreamingCaptureMode(StreamingCaptureMode::Video);
    settings.MemoryPreference(MediaCaptureMemoryPreference::Cpu);
    m_mediaCapture.InitializeAsync(settings).get();
    m_mediaCapture.Failed([this](auto&& sender, auto&& args) {MediaCaptureErrorHandler(sender, args); });
    auto frameSource = m_mediaCapture.FrameSources().First().Current().Value();
    auto preferredFormat = frameSource.SupportedFormats().First().Current();
    frameSource.SetFormatAsync(preferredFormat).get();
    
    capElement.Stretch(Stretch::Fill);
    //capElement.Width(preferredFormat.VideoFormat().Width());
    //capElement.Height(preferredFormat.VideoFormat().Height());
    capElement.Source(m_mediaCapture);
    //capElement.Visibility(Visibility::Collapsed);
    //m_mediaCapture.StartPreviewAsync();
    //auto infraredTorchControl = m_mediaCapture.VideoDeviceController().InfraredTorchControl();
    //if (infraredTorchControl.IsSupported()) {
    //    infraredTorchControl.CurrentMode(winrt::Windows::Media::Devices::InfraredTorchMode::AlternatingFrameIllumination);
    //}
    //m_mediaCapture.StopPreviewAsync();
    m_frameReader = m_mediaCapture.CreateFrameReaderAsync(frameSource).get();
    m_frameReader.AcquisitionMode(MediaFrameReaderAcquisitionMode::Realtime);
    m_frameReader.FrameArrived([this](auto&& mfr, auto&& args) {FrameArrivedHandler(mfr, args); });
    MediaFrameReaderStartStatus status = m_frameReader.StartAsync().get();



}

void IRController::FrameArrivedHandler(const MediaFrameReader& FrameReader, const MediaFrameArrivedEventArgs& args)
{
    m_lock.lock();
    try
    {
        MediaFrameReference mediaFrame(nullptr);
        mediaFrame = FrameReader.TryAcquireLatestFrame();
        if (mediaFrame != nullptr) {
            auto vmFrame = mediaFrame.VideoMediaFrame();
            if (vmFrame != nullptr) {
                auto irFrame = vmFrame.InfraredMediaFrame();
                auto videoFrame = irFrame.VideoMediaFrame().DepthMediaFrame();                 
                SoftwareBitmap bitmap = videoFrame.VideoMediaFrame().SoftwareBitmap();
                bitmap = SoftwareBitmap::Convert(bitmap, BitmapPixelFormat::Bgra8);
                BitmapBuffer bitmapBuffer = bitmap.LockBuffer(BitmapBufferAccessMode::Read);
                IMemoryBufferReference ref = bitmapBuffer.CreateReference();
                auto interop = ref.as<IMemoryBufferByteAccess>();
                uint8_t* value{};
                uint32_t value_size{};
                check_hresult(interop->GetBuffer(&value, &value_size));
                cv::Mat formated_frame = cv::Mat(vmFrame.VideoFormat().Height(), vmFrame.VideoFormat().Width(), CV_8UC4, (void*)value);
                cv::imshow("IR Video Display", formated_frame);
                cv::waitKey(33);
                //if (irFrame.IsIlluminated()){}               
                bitmap.Close();
               

            }
            mediaFrame.Close();
        }
    }
    catch (winrt::hresult_error const& ex)
    {
        OutputDebugStringA("ERROR \n");
    }
    m_lock.unlock();

}

void IRController::MediaCaptureErrorHandler(MediaCapture sender, MediaCaptureFailedEventArgs errorEventArgs)
{
    OutputDebugStringA(winrt::to_string(errorEventArgs.Message()).c_str());

}

CaptureElement IRController::getCaptureElement()
{
    return capElement;
}
