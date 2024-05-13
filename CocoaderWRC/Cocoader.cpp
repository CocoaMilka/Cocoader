#include "pch.h"
#include "Cocoader.h"
#include "Cocoader.g.cpp"

namespace winrt::CocoaderWRC::implementation
{
    void Cocoader::InitializeCocoader(winrt::hstring url)
    {
        throw hresult_not_implemented();
    }

    IAsyncAction Cocoader::StartStreamingAsync()
    {
        return IAsyncAction();
    }

    IAsyncOperation<Collections::IVector<Windows::Graphics::Imaging::SoftwareBitmap>> Cocoader::GetNextFrameAsync()
    {
        return IAsyncOperation<Collections::IVector<Windows::Graphics::Imaging::SoftwareBitmap>>();
    }

    void Cocoader::Decode()
    {
        throw hresult_not_implemented();
    }
}
