#pragma once

#include "MainPage.g.h"

namespace winrt::Notepad::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        static hstring const& FileName() { return fileName; }

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
        Windows::Foundation::IAsyncAction SaveFileAs();
        void UpdateTitleText(hstring title);
        
    public:
        void FileSaveAsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void inputText_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
    };
}

namespace winrt::Notepad::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
