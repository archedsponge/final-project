#ifndef PARTSMANAGERFRAMES_H
#define PARTSMANAGERFRAMES_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include <string>
#include "Part.h" // Use Part.h for Part class
#include <fstream>
#include <sstream>

class PartsManagerFrames : public wxFrame {
public:
    PartsManagerFrames();
    PartsManagerFrames(const wxString& title);
    void SortList(wxListEvent& event);
    void OnSortDescription(wxListEvent& event);
    void OnSortColumn(wxListEvent& event);
    void OnSortCost(wxListEvent& event);
    void OnSortRetail(wxListEvent& event);
    void OnSortManufacturer(wxListEvent& event);
    void OnSortQuantity(wxListEvent& event);
    void OnSortPartNumber(wxListEvent& event);
    void OnAddPart(wxCommandEvent& event);
    void OnEditPart(wxCommandEvent& event);
    void OnDeletePart(wxCommandEvent& event);
    void OnSaveChanges(wxCommandEvent& event);
    void OnSearch(wxCommandEvent& event);
    void OnItemSelected(wxListEvent& event);
    void OnItemDeselected(wxListEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnShowAll(wxCommandEvent& event);

private:
    wxListCtrl* partList;
    wxButton* addButton;
    wxButton* editButton;
    wxButton* deleteButton;
    wxButton* saveButton;
    wxButton* searchButton;
    wxButton* showAllButton;
    wxStaticText* totalCostLabel; // New label for total cost

    std::vector<Part> inventory;
    int selectedPartIndex = -1;

    void save_to_file(const std::string& filename);
    void load_from_file(const std::string& filename);
    void UpdateTotalCost(); // New method to update total cost display

    wxDECLARE_EVENT_TABLE();
};

#endif // PARTSMANAGERFRAMES_H
