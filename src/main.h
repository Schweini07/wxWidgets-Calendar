#ifndef _MAIN_
#define _MAIN_

#include "wx/wx.h"
#include "clock.h"

static bool is_running = true;

class CalendarApp : public wxApp
{
    public:
        virtual bool OnInit();
};

class CalendarFrame : public wxFrame
{
    public:
        CalendarFrame(const wxString &title);

        void OnClose(wxCloseEvent &event);
        void OnDayButton(wxCommandEvent &event);
        void OnNewEventButton(wxCommandEvent &event);
        static void UpdateTimeText();
    
    private:
        Clock clock;
        // TODO: Change map to struct
        std::map<char, std::string> date_as_strings_map = clock.getDateAsStrings();
        tm *time_struct = clock.getTimeStruct();
};

class EventDialog : public wxDialog
{
    public:
        EventDialog(const wxString &title);

        void OnCancelButton(wxCommandEvent &event);
        void OnOkButton(wxCommandEvent &event);
};

class TextCtrlWithText : public wxBoxSizer
{
    public:
        TextCtrlWithText(wxWindow *parent, const wxString &text);
};

#endif