#include "main.h"

#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <time.h>
#include <string>
#include <map>
#include <iostream>
#include <thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

wxIMPLEMENT_APP(CalendarApp);

bool CalendarApp::OnInit()
{
    if ( !wxApp::OnInit() ) { return false; }

    CalendarFrame *frame = new CalendarFrame("Calendar");

    // TODO: Implement increasing time
    //std::thread time_increase(frame->UpdateTimeText);

    frame->SetMinSize(wxSize(400, 300));
    frame->Show(true);

    return true;
}


// FIXME: Incosistent use for the sizers `Add`function
CalendarFrame::CalendarFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title)
{
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxPanel *panel = new wxPanel(this);
    panel->SetSizer(sizer);

    sizer->Add(190, 5);

    wxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(topSizer, wxSizerFlags().Center());

    wxStaticText *time = new wxStaticText(panel, wxID_ANY, clock.getTimeString());
    topSizer->Add(time, wxSizerFlags().Left());

    topSizer->Add(150, 0);

    wxStaticText *date = new wxStaticText(panel, wxID_ANY, clock.getDateString());
    topSizer->Add(date, wxSizerFlags().Right());

    sizer->Add(0, 20);

    wxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(bottomSizer, wxSizerFlags().Center());

    wxSizer *monthSizer = new wxBoxSizer(wxVERTICAL);
    bottomSizer->Add(monthSizer);

    wxSizer *dayButtonsSizer = new wxGridSizer(7, 1, 1);
    monthSizer->Add(dayButtonsSizer);

    for (int i = 0; i < 31; i++)
    {
        wxButton *dayButton = new wxButton(panel, wxID_ANY, std::to_string(i+1).c_str(), wxDefaultPosition, wxSize(35, 35));
        dayButton->Bind(wxEVT_BUTTON, &CalendarFrame::OnDayButton, this);

        if (i == time_struct->tm_mday-1)
        {
            dayButton->SetForegroundColour(*wxCYAN);
        }

        dayButtonsSizer->Add(dayButton);
    }

    monthSizer->Add(0, 7);

    wxStaticText *month = new wxStaticText(panel, wxID_ANY, date_as_strings_map['m']);
    monthSizer->Add(month, wxSizerFlags().Center());

    bottomSizer->Add(20, 0);

    wxSizer *eventsSizer = new wxWrapSizer(wxVERTICAL);
    bottomSizer->Add(eventsSizer);

    wxButton *newEventButton = new wxButton(panel, wxID_ANY, "New Event");
    newEventButton->Bind(wxEVT_BUTTON, &CalendarFrame::OnNewEventButton, this);
    eventsSizer->Add(newEventButton, wxSizerFlags().Center());

    wxStaticText *event = new wxStaticText(panel, wxID_ANY, "Event");
    eventsSizer->Add(event, wxSizerFlags().Center());
}

void CalendarFrame::OnDayButton(wxCommandEvent &event)
{

}

void CalendarFrame::OnNewEventButton(wxCommandEvent &event)
{
    EventDialog *evtDialog = new EventDialog("New Event");
}

void CalendarFrame::UpdateTimeText()
{
    sleep(1);
    std::cout << "Hi" << std::endl;
}

EventDialog::EventDialog(const wxString &title) : wxDialog(NULL, wxID_ANY, title)
{
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxPanel *panel = new wxPanel(this);

    TextCtrlWithText *eventName = new TextCtrlWithText(this, "Event Name");
    sizer->Add(eventName);

    TextCtrlWithText *eventDescription = new TextCtrlWithText(this, "Event Description");
    sizer->Add(eventDescription);

    sizer->Add(panel, 1);

    wxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(bottomSizer, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    wxButton *cancelButton = new wxButton(this, wxID_ANY, "Cancel");
    cancelButton->Bind(wxEVT_BUTTON, &EventDialog::OnCancelButton, this);
    bottomSizer->Add(cancelButton, 1, wxLEFT, 5);

    wxButton *okButton = new wxButton(this, wxID_ANY, "OK");
    okButton->Bind(wxEVT_BUTTON, &EventDialog::OnOkButton, this);
    bottomSizer->Add(okButton, 1);

    SetSizer(sizer);

    ShowModal();
    Destroy();
}

void EventDialog::OnCancelButton(wxCommandEvent &event)
{
    Destroy();
}

void EventDialog::OnOkButton(wxCommandEvent &event)
{
    Destroy();
}

TextCtrlWithText::TextCtrlWithText(wxWindow *parent, const wxString &text) : wxBoxSizer(wxHORIZONTAL)
{
    wxStaticText *staticText = new wxStaticText(parent, wxID_ANY, text);
    this->Add(staticText, wxSizerFlags().Center());

    wxTextCtrl *textCtrl = new wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition);
    this->Add(textCtrl);
}