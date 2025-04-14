#include "AddPartDialogs.h"

AddPartDialogs::AddPartDialogs(wxWindow* parent, const wxString& partNumber, const wxString& description, const wxString& cost, const wxString& retail, const wxString& manufacturer, const wxString& quantity, const wxString& location)
    : wxDialog(parent, wxID_ANY, "Add/Edit Part", wxDefaultPosition, wxSize(400, 300))
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    partNumberCtrl = new wxTextCtrl(this, wxID_ANY, partNumber);
    descriptionCtrl = new wxTextCtrl(this, wxID_ANY, description);
    costCtrl = new wxTextCtrl(this, wxID_ANY, cost);
    retailCtrl = new wxTextCtrl(this, wxID_ANY, retail);
    manufacturerCtrl = new wxTextCtrl(this, wxID_ANY, manufacturer);
    quantityCtrl = new wxTextCtrl(this, wxID_ANY, quantity);
    locationCtrl = new wxTextCtrl(this, wxID_ANY, location);

    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Part Number"), 0, wxALL, 5);
    mainSizer->Add(partNumberCtrl, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Description"), 0, wxALL, 5);
    mainSizer->Add(descriptionCtrl, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Cost"), 0, wxALL, 5);
    mainSizer->Add(costCtrl, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Retail"), 0, wxALL, 5);
    mainSizer->Add(retailCtrl, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Manufacturer"), 0, wxALL, 5);
    mainSizer->Add(manufacturerCtrl, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Quantity"), 0, wxALL, 5);
    mainSizer->Add(quantityCtrl, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Location"), 0, wxALL, 5);
    mainSizer->Add(locationCtrl, 0, wxALL | wxEXPAND, 5);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL, 5);
    buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL, 5);

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);

    SetSizerAndFit(mainSizer);
}

wxString AddPartDialogs::GetPartNumber() const { return partNumberCtrl->GetValue(); }
wxString AddPartDialogs::GetDescription() const { return descriptionCtrl->GetValue(); }
wxString AddPartDialogs::GetCost() const { return costCtrl->GetValue(); }
wxString AddPartDialogs::GetRetail() const { return retailCtrl->GetValue(); }
wxString AddPartDialogs::GetManufacturer() const { return manufacturerCtrl->GetValue(); }
wxString AddPartDialogs::GetQuantity() const { return quantityCtrl->GetValue(); }
wxString AddPartDialogs::GetLocation() const { return locationCtrl->GetValue(); }
