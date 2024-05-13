#pragma once
#include "Cocoader.g.h"
#include "winrt/Windows.Graphics.Imaging.h"
#include <winrt/Windows.Foundation.h>

using namespace winrt;
using namespace winrt::Windows::Foundation;

namespace winrt::CocoaderWRC::implementation
{
    struct Cocoader : CocoaderT<Cocoader>
    {
        Cocoader() = default;

    public:
        MediaPlayer player;

        /// <summary>
        /// Initializes Cocoader for media encoding/decoding.
        /// </summary>
        /// <param name="url">URL of stream to decode</param>
        void InitializeCocoader(winrt::hstring url);

        /// <summary>
        /// Start receiving stream and feed into Media Foundation pipeline.
        /// </summary>
        void StartStreaming();

        /// <summary>
        /// Stop stream
        /// </summary>
        void StopStreaming();

        /// <summary>
        /// Event for when frames are available from member property MediaPlayer player. Will take frame from player and convert to SoftwareBitmap and pass to ProcessFrame()
        /// </summary>
        void OnVideoFrameAvailable();

        /// <summary>
        /// Converts frames from SoftwareBitmap into Rgba8 for use in Unity
        /// </summary>
        void ProcessFrame(SoftwareBitmap const& bitmap);
    };
}

namespace winrt::CocoaderWRC::factory_implementation
{
    struct Cocoader : CocoaderT<Cocoader, implementation::Cocoader>
    {
    };
}
