#pragma once

#include "MainPage.g.h"

namespace winrt::Notepad::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        static hstring const& FileName() { return fileName; }
        static Windows::Storage::StorageFile const& CurrentFileFile() { return currentFile; }

        int32_t MyProperty();
        void MyProperty(int32_t value);
        void PreparePage();
        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        void FileSaveButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void FileExit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void FileOpenButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        Windows::Foundation::IAsyncAction SaveFile();
        Windows::Foundation::IAsyncAction OpenFileAsync();
        void UpdateTitleText(hstring title);
        static hstring fileName;
        static Windows::Storage::StorageFile currentFile;
       
    };
}

namespace winrt::Notepad::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
