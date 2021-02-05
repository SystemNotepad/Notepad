#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"


using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;

namespace winrt::Notepad::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
        titleBarText().Text(L"Untitled - Notepad");
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::FileSaveButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        SaveFile();
    }

    void MainPage::FileExit_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        // Check wheather the textbox contain string and not saved!
        Application::Current().Exit();
    }

    IAsyncAction MainPage::SaveFile()
    {
        // Setup the picker
        auto picker = FileSavePicker();
        picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
        picker.SuggestedFileName(L"Untitled");
        picker.FileTypeChoices().Insert(L"Text Documents", winrt::single_threaded_vector<hstring>({ L".txt" }));
        picker.FileTypeChoices().Insert(L"All files", winrt::single_threaded_vector<hstring>({ L"." }));
        picker.DefaultFileExtension(L".txt");

        if (auto file = co_await picker.PickSaveFileAsync())
        {
            // Prevent remote access to file until saving is done
            CachedFileManager::DeferUpdates(file);
            
            hstring userInput = inputText().Text();

            // Write the stuff to the file
            co_await FileIO::WriteTextAsync(file, userInput);

            // Let Windows know stuff is done
            co_await Windows::Storage::CachedFileManager::CompleteUpdatesAsync(file);
        }
    }

    void MainPage::FileOpenButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        OpenFileAsync();
    }

    IAsyncAction MainPage::OpenFileAsync() 
    {
        auto lifetime = get_strong();

        // Clear previous returned file name, if it exists, between iterations of this scenario

        FileOpenPicker openPicker;
        openPicker.ViewMode(PickerViewMode::Thumbnail);
        openPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
        openPicker.FileTypeFilter().ReplaceAll({ L".txt"/*, L".md"*/ });
        StorageFile file = co_await openPicker.PickSingleFileAsync();
        if (file != nullptr)
        {
            UpdateTitleText(file.Name());
            // Clear previous returned file text.
            inputText().Text(L""); 
            hstring fileContent = co_await FileIO::ReadTextAsync(file);
            inputText().Text(fileContent);// Application now has read/write access to the picked file  
            
        }
        else
        {
            // OutputTextBlock().Text(L"Operation cancelled.");
            // Operation Cancelled.
        }
    }

    void MainPage::UpdateTitleText(hstring title) 
    {
        titleBarText().Text(title + L" - Notepad");
    }
}






