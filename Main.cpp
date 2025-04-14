#include <wx/wx.h>
#include "User.h"
#include "PartsManagerFrames.h"

class App : public wxApp {
public:
    bool OnInit() override {
        wxFrame* loginWindow = new wxFrame(NULL, wxID_ANY, "Login Box", wxDefaultPosition, wxSize(400, 300));
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* usernameLabel = new wxStaticText(loginWindow, wxID_ANY, "Username:");
        sizer->Add(usernameLabel, 0, wxALIGN_LEFT | wxTOP, 20);

        wxTextCtrl* usernameCtrl = new wxTextCtrl(loginWindow, wxID_ANY);
        sizer->Add(usernameCtrl, 0, wxEXPAND | wxTOP, 5);

        wxStaticText* passwordLabel = new wxStaticText(loginWindow, wxID_ANY, "Password:");
        sizer->Add(passwordLabel, 0, wxALIGN_LEFT | wxTOP, 20);

        wxTextCtrl* passwordCtrl = new wxTextCtrl(loginWindow, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
        sizer->Add(passwordCtrl, 0, wxEXPAND | wxTOP, 5);

        wxButton* loginButton = new wxButton(loginWindow, wxID_OK, "Login");
        sizer->Add(loginButton, 0, wxALIGN_CENTER | wxTOP, 20);

        loginButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
            if (usernameCtrl->GetValue() == "admin" && passwordCtrl->GetValue() == "1234") {
                loginWindow->Destroy();
                PartsManagerFrames* partsFrame = new PartsManagerFrames();
                partsFrame->Show();
            }
            else {
                wxMessageBox("Invalid credentials", "Error", wxOK | wxICON_ERROR);
            }
            });

        loginWindow->SetSizerAndFit(sizer);
        loginWindow->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);
