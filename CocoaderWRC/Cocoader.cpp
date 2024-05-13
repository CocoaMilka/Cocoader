#include "pch.h"
#include "Cocoader.h"
#include "Cocoader.g.cpp"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Core.h>
#include <winrt/Windows.Media.Playback.h>
#include "winrt/Windows.Graphics.Imaging.h"

#include <d3d11_4.h>
#include <Windows.Graphics.DirectX.Direct3D11.interop.h>
#include <unknwn.h>



#include "winrt/Windows.Graphics.DirectX.Direct3D11.h";

using namespace winrt::Windows::Media::Playback;
using namespace winrt::Windows::Media::Core;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Graphics::Imaging;
using namespace winrt::Windows::Graphics::DirectX::Direct3D11;

namespace winrt::CocoaderWRC::implementation
{

    void Cocoader::InitializeCocoader(winrt::hstring url)
    {
        // Create a MediaSource from the URL
        MediaSource mediaSource = MediaSource::CreateFromUri(Uri(url));

        // Pass MediaSource to MediaPlaybackItem
        MediaPlaybackItem mediaPlaybackItem = MediaPlaybackItem(mediaSource);

        // Set MediaPlaybackItem as source for media player. Player is a public member variable of Cocoader.
        player.Source(mediaPlaybackItem);

        // Subscribe to the video frame output
        player.VideoFrameAvailable({ this, &Cocoader::OnVideoFrameAvailable });
        player.IsVideoFrameServerEnabled(true);
    }

    void Cocoader::OnVideoFrameAvailable()
    {
        // Assuming DirectX interop, get frame as Direct3D surface
        IDirect3DSurface frameTexture;
        player.CopyFrameToVideoSurface(frameTexture);

        // Asynchronously convert Direct3D surface to SoftwareBitmap
        IAsyncOperation createBitmapTask = SoftwareBitmap::CreateCopyFromSurfaceAsync(frameTexture);

        createBitmapTask.Completed([this](IAsyncOperation<SoftwareBitmap> const& operation, AsyncStatus const status)
        {
            if (status == AsyncStatus::Completed)
            {
                // Retrieve the SoftwareBitmap result
                SoftwareBitmap frameBitmap = operation.GetResults();

                // Process and store the frame for Unity to access
                ProcessFrame(frameBitmap);
            }
            else
            {
                // Handle errors or cancellation
            }
        });
    }

    void Cocoader::ProcessFrame(SoftwareBitmap const& bitmap)
    {
        // Process the software bitmap, e.g., convert to a specific format, serialize, send to Unity
        SoftwareBitmap converted = SoftwareBitmap::Convert(bitmap, BitmapPixelFormat::Rgba8);
    }

    void Cocoader::StartStreaming()
    {
        player.Play();
    }

    void Cocoader::StopStreaming()
    {
        player.Pause();
    }
}
