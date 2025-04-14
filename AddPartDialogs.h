#ifndef ADDPARTDIALOGS_H
#define ADDPARTDIALOGS_H

#include <wx/wx.h>

class AddPartDialogs : public wxDialog
{
public:
    AddPartDialogs(wxWindow* parent, const wxString& partNumber, const wxString& description, const wxString& cost, const wxString& retail, const wxString& manufacturer, const wxString& quantity, const wxString& location);

    wxString GetPartNumber() const;
    wxString GetDescription() const;
    wxString GetCost() const;
    wxString GetRetail() const;
    wxString GetManufacturer() const;
    wxString GetQuantity() const;
    wxString GetLocation() const;

private:
    wxTextCtrl* partNumberCtrl;
    wxTextCtrl* descriptionCtrl;
    wxTextCtrl* costCtrl;
    wxTextCtrl* retailCtrl;
    wxTextCtrl* manufacturerCtrl;
    wxTextCtrl* quantityCtrl;
    wxTextCtrl* locationCtrl;
};

#endif // ADDPARTDIALOGS_H
