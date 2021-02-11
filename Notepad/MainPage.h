#pragma once

#include "MainPage.g.h"

namespace winrt::Notepad::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        static hstring const& FileName() { return fileName; }
        // static Windows::Storage::StorageFile const& CurrentFile() { return currentFile; }

        int32_t MyProperty();
        void MyProperty(int32_t value);
        void PreparePage();
        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        void FileSaveButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void FileExit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void FileOpenButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void FileAboutButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        

    private:
        static hstring fileName;
        Windows::Foundation::IAsyncAction SaveFile();
        Windows::Foundation::IAsyncAction OpenFileAsync();
        Windows::Foundation::IAsyncAction ExitApp();
        Windows::Foundation::IAsyncAction LoadFile(winrt::Windows::Storage::StorageFile const& file);
        void UpdateTitleText(hstring title);
        
    };
}

namespace winrt::Notepad::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
