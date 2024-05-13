#pragma once
#include "Cocoader.g.h"
#include "winrt/Windows.Graphics.Imaging.h"
#include <winrt/Windows.Foundation.h>

using namespace winrt;
using namespace Windows::Foundation;

namespace winrt::CocoaderWRC::implementation
{
    struct Cocoader : CocoaderT<Cocoader>
    {
        Cocoader() = default;

        /// <summary>
        /// Initializes Cocoader for media encoding/decoding.
        /// </summary>
        /// <param name="url">URL of stream to decode</param>
        void InitializeCocoader(winrt::hstring url);

        /// <summary>
        /// Start receiving stream and feed into Media Foundation pipeline.
        /// </summary>
        /// <returns></returns>
        IAsyncAction StartStreamingAsync();

        IAsyncOperation<Collections::IVector<Windows::Graphics::Imaging::SoftwareBitmap>> GetNextFrameAsync();

        void Decode();
    };
}

namespace winrt::CocoaderWRC::factory_implementation
{
    struct Cocoader : CocoaderT<Cocoader, implementation::Cocoader>
    {
    };
}
