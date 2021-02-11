#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"


using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::Notepad::implementation
{
    // Global Variables:
    Windows::Storage::StorageFile m_file{ nullptr };

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
        ExitApp();   
    }

    IAsyncAction MainPage::ExitApp()
    {
        // Check wheather the textbox contain string and not saved!
        hstring userText = inputText().Text();
        if (inputText().Text().c_str() != L"" && nullptr == m_file)
        {
            auto dialog = ContentDialog();
            dialog.Content(box_value(L"Do you want to save changes to Untitled?"));
            dialog.Title(box_value(L"Notepad"));
            dialog.CloseButtonText(L"Cancel");
            dialog.PrimaryButtonText(L"Save");
            dialog.SecondaryButtonText(L"Don't save");
            ContentDialogResult result = co_await dialog.ShowAsync();
            if (result == ContentDialogResult::Primary)
            {
                SaveFile();
            }
            else if (result == ContentDialogResult::None)
            {
                co_return;
            }
            else
            {
                Application::Current().Exit();
            }
        }
        else
        {
            Application::Current().Exit();
        }
    }

    // SaveAs

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
            UpdateTitleText(file.Name());
            // Prevent remote access to file until saving is done
            CachedFileManager::DeferUpdates(file);
            
            hstring userInput = inputText().Text();

            // Write the stuff to the file
            co_await FileIO::WriteTextAsync(file, userInput);

            // Let Windows know stuff is done
            co_await Windows::Storage::CachedFileManager::CompleteUpdatesAsync(file);

            m_file = file;
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
            /*currentFile = file;*/
            UpdateTitleText(file.Name());
            // Clear previous returned file text & file.
            m_file = nullptr;
            m_file = file;
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

    void MainPage::FileAboutButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {

    }

    void MainPage::UpdateTitleText(hstring title) 
    {
        titleBarText().Text(title + L" - Notepad");
    }

    void MainPage::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e) 
    {
        auto content = e.Parameter();
        auto args = content.try_as<winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs>();
        if (args != nullptr)
        {
            if (args.Kind() == winrt::Windows::ApplicationModel::Activation::ActivationKind::File)
            {
                auto fileArgs = args.try_as<winrt::Windows::ApplicationModel::Activation::FileActivatedEventArgs>();
                auto file = fileArgs.Files().GetAt(0);
                LoadFile(file.try_as<winrt::Windows::Storage::StorageFile>());
            }
        }
    }

    IAsyncAction MainPage::LoadFile(winrt::Windows::Storage::StorageFile const& file)
    {
        if (file != nullptr)
        {
            /*currentFile = file;*/
            UpdateTitleText(file.Name());
            // Clear previous returned file text & file.
            m_file = nullptr;
            m_file = file;
            inputText().Text(L"");
            hstring fileContent = co_await FileIO::ReadTextAsync(file);
            inputText().Text(fileContent);  
        }
    }
}









