#define WIN32_LEAN_AND_MEAN // Disables inclusion of many large headers
#define _WIN32_WINNT 0x0601 // Defines the version of Windows for <windows.h>

// clang-format off
#include <windows.h>
#include <shlobj.h>
#include <shellapi.h>
#include <string>
#include <iostream>
// clang-format on

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Shell32.lib")

/**
 * This class is used to keep the program running while showing the Properties
 * dialog. Without it the dialog closes as soon as the `showProperties()`
 * function returns. See https://devblogs.microsoft.com/oldnewthing/?p=22163.
 */
class ProcessReference : public IUnknown {
public:
  STDMETHODIMP QueryInterface(REFIID riid, void **ppv) {
    if (riid == IID_IUnknown) {
      *ppv = static_cast<IUnknown *>(this);
      AddRef();
      return S_OK;
    }

    *ppv = NULL;

    return E_NOINTERFACE;
  }

  STDMETHODIMP_(ULONG) AddRef() { return InterlockedIncrement(&m_cRef); }

  STDMETHODIMP_(ULONG) Release() {
    LONG lRef = InterlockedDecrement(&m_cRef);

    if (lRef == 0) {
      PostThreadMessage(m_dwThread, WM_NULL, 0, 0);
    }

    return lRef;
  }

  ProcessReference() : m_cRef(1), m_dwThread(GetCurrentThreadId()) {
    SHSetInstanceExplorer(this);
  }

  ~ProcessReference() {
    SHSetInstanceExplorer(NULL);
    Release();

    MSG msg;
    while (m_cRef && GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

private:
  LONG m_cRef;
  DWORD m_dwThread;
};

void showProperties(char *path) {
  // Keeps the executable alive until the dialog is closed
  ProcessReference ref;

  // Create the info struct and fill it
  SHELLEXECUTEINFO info = {sizeof(info)};
  info.fMask = SEE_MASK_INVOKEIDLIST;
  info.nShow = SW_SHOWNORMAL;
  info.lpVerb = "properties";
  info.lpFile = path;

  // Show the properties by executing with the info struct
  ShellExecuteEx(&info);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "file or directory path is required to show properties"
              << std::endl;
    std::cout << "usage: show-properties.exe <path to file or directory>";
    return 1;
  }

  showProperties(argv[1]);

  return 0;
}
