#include "PartsManagerFrames.h"
#include "AddPartDialogs.h"
#include "Part.h"
#include <fstream>
#include <sstream>
#include <wx/wx.h>
#include <iomanip>

wxBEGIN_EVENT_TABLE(PartsManagerFrames, wxFrame)
EVT_BUTTON(1001, PartsManagerFrames::OnAddPart)
EVT_BUTTON(1002, PartsManagerFrames::OnEditPart)
EVT_BUTTON(1003, PartsManagerFrames::OnDeletePart)
EVT_BUTTON(1004, PartsManagerFrames::OnSaveChanges)
EVT_BUTTON(1005, PartsManagerFrames::OnSearch)
EVT_BUTTON(1006, PartsManagerFrames::OnShowAll)
EVT_LIST_ITEM_SELECTED(wxID_ANY, PartsManagerFrames::OnItemSelected)
EVT_LIST_ITEM_DESELECTED(wxID_ANY, PartsManagerFrames::OnItemDeselected)
EVT_CLOSE(PartsManagerFrames::OnClose)
wxEND_EVENT_TABLE()

PartsManagerFrames::PartsManagerFrames()
    : wxFrame(nullptr, wxID_ANY, "Parts Manager", wxDefaultPosition, wxSize(600, 400)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    partList = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
    partList->InsertColumn(0, "Part Number", wxLIST_FORMAT_LEFT, 100);
    partList->InsertColumn(1, "Description", wxLIST_FORMAT_LEFT, 200);
    partList->InsertColumn(2, "Cost", wxLIST_FORMAT_LEFT, 100);
    partList->InsertColumn(3, "Retail Price", wxLIST_FORMAT_LEFT, 100);
    partList->InsertColumn(4, "Manufacturer", wxLIST_FORMAT_LEFT, 150);
    partList->InsertColumn(5, "Quantity", wxLIST_FORMAT_LEFT, 100);
    partList->InsertColumn(6, "Location", wxLIST_FORMAT_LEFT, 100);

    mainSizer->Add(partList, 1, wxEXPAND | wxALL, 10);
    partList->Bind(wxEVT_LIST_COL_CLICK, &PartsManagerFrames::OnSortColumn, this);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    addButton = new wxButton(panel, 1001, "Add Part");
    editButton = new wxButton(panel, 1002, "Edit Part");
    deleteButton = new wxButton(panel, 1003, "Delete Part");
    saveButton = new wxButton(panel, 1004, "Save Changes");
    searchButton = new wxButton(panel, 1005, "Search");
    showAllButton = new wxButton(panel, 1006, "Show All");

    buttonSizer->Add(addButton, 1, wxALL, 5);
    buttonSizer->Add(editButton, 1, wxALL, 5);
    buttonSizer->Add(deleteButton, 1, wxALL, 5);
    buttonSizer->Add(saveButton, 1, wxALL, 5);
    buttonSizer->Add(searchButton, 1, wxALL, 5);
    buttonSizer->Add(showAllButton, 1, wxALL, 5);

    editButton->Disable();
    deleteButton->Disable();

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    // Add total cost label
    totalCostLabel = new wxStaticText(panel, wxID_ANY, "Total Inventory Cost: $0.00");
    mainSizer->Add(totalCostLabel, 0, wxALIGN_LEFT | wxALL, 10);

    panel->SetSizer(mainSizer);
    mainSizer->Fit(panel);
    mainSizer->SetSizeHints(panel);
    panel->Layout();

    addButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnAddPart, this);
    editButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnEditPart, this);
    deleteButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnDeletePart, this);
    saveButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnSaveChanges, this);
    searchButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnSearch, this);
    showAllButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnShowAll, this);

    load_from_file("inventory.txt");
    UpdateTotalCost(); // Initialize total cost
}

// Constructor with title (similar setup, omitted for brevity but includes totalCostLabel)
PartsManagerFrames::PartsManagerFrames(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    partList = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
    partList->InsertColumn(0, "Part Number", wxLIST_FORMAT_LEFT, 100);
    partList->InsertColumn(1, "Description", wxLIST_FORMAT_LEFT, 200);
    partList->InsertColumn(2, "Cost", wxLIST_FORMAT_LEFT, 100);
    partList->InsertColumn(3, "Retail Price", wxLIST_FORMAT_LEFT, 100);
    partList->InsertColumn(4, "Manufacturer", wxLIST_FORMAT_LEFT, 150);
    partList->InsertColumn(5, "Quantity", wxLIST_FORMAT_LEFT, 100);
    partList->InsertColumn(6, "Location", wxLIST_FORMAT_LEFT, 100);

    mainSizer->Add(partList, 1, wxEXPAND | wxALL, 10);
    partList->Bind(wxEVT_LIST_COL_CLICK, &PartsManagerFrames::OnSortColumn, this);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    addButton = new wxButton(panel, 1001, "Add Part");
    editButton = new wxButton(panel, 1002, "Edit Part");
    deleteButton = new wxButton(panel, 1003, "Delete Part");
    saveButton = new wxButton(panel, 1004, "Save Changes");
    searchButton = new wxButton(panel, 1005, "Search");
    showAllButton = new wxButton(panel, 1006, "Show All");

    buttonSizer->Add(addButton, 1, wxALL, 5);
    buttonSizer->Add(editButton, 1, wxALL, 5);
    buttonSizer->Add(deleteButton, 1, wxALL, 5);
    buttonSizer->Add(saveButton, 1, wxALL, 5);
    buttonSizer->Add(searchButton, 1, wxALL, 5);
    buttonSizer->Add(showAllButton, 1, wxALL, 5);

    editButton->Disable();
    deleteButton->Disable();

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    totalCostLabel = new wxStaticText(panel, wxID_ANY, "Total Inventory Cost: $0.00");
    mainSizer->Add(totalCostLabel, 0, wxALIGN_LEFT | wxALL, 10);

    panel->SetSizer(mainSizer);
    mainSizer->Fit(panel);
    mainSizer->SetSizeHints(panel);
    panel->Layout();

    addButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnAddPart, this);
    editButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnEditPart, this);
    deleteButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnDeletePart, this);
    saveButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnSaveChanges, this);
    searchButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnSearch, this);
    showAllButton->Bind(wxEVT_BUTTON, &PartsManagerFrames::OnShowAll, this);

    load_from_file("inventory.txt");
    UpdateTotalCost();
}

void PartsManagerFrames::UpdateTotalCost() {
    double totalCost = 0.0;
    for (const auto& part : inventory) {
        totalCost += part.getPartCost() * part.getPartQuantity();
    }
    totalCostLabel->SetLabel(wxString::Format("Total Inventory Cost: $%.2f", totalCost));
}

void PartsManagerFrames::OnSortColumn(wxListEvent& event) {
    int col = event.GetColumn();
    wxLogMessage("Sorting column: %d", col);

    switch (col) {
    case 0: OnSortPartNumber(event); break;
    case 1: OnSortDescription(event); break;
    case 2: OnSortCost(event); break;
    case 3: OnSortRetail(event); break;
    case 4: OnSortManufacturer(event); break;
    case 5: OnSortQuantity(event); break;
    default: wxLogMessage("Unknown column clicked: %d", col); break;
    }
}

void PartsManagerFrames::OnSortDescription(wxListEvent& event) {
    wxLogMessage("Sorting by Description...");

    std::sort(inventory.begin(), inventory.end(), [](const Part& a, const Part& b) {
        return a.getPartDescription() < b.getPartDescription();
        });

    partList->DeleteAllItems();
    for (const auto& part : inventory) {
        long index = partList->GetItemCount();
        partList->InsertItem(index, part.getPartNumber());
        partList->SetItem(index, 1, part.getPartDescription());
        partList->SetItem(index, 2, std::to_string(part.getPartCost()));
        partList->SetItem(index, 3, std::to_string(part.getPartRetail()));
        partList->SetItem(index, 4, part.getPartManufacturer());
        partList->SetItem(index, 5, std::to_string(part.getPartQuantity()));
        partList->SetItem(index, 6, part.getPartLocation());
    }
}

void PartsManagerFrames::OnSortCost(wxListEvent& event) {
    wxLogMessage("Sorting by Cost...");

    std::sort(inventory.begin(), inventory.end(), [](const Part& a, const Part& b) {
        return a.getPartCost() < b.getPartCost();
        });

    partList->DeleteAllItems();
    for (const auto& part : inventory) {
        long index = partList->GetItemCount();
        partList->InsertItem(index, part.getPartNumber());
        partList->SetItem(index, 1, part.getPartDescription());
        partList->SetItem(index, 2, std::to_string(part.getPartCost()));
        partList->SetItem(index, 3, std::to_string(part.getPartRetail()));
        partList->SetItem(index, 4, part.getPartManufacturer());
        partList->SetItem(index, 5, std::to_string(part.getPartQuantity()));
        partList->SetItem(index, 6, part.getPartLocation());
    }
}

void PartsManagerFrames::OnSortRetail(wxListEvent& event) {
    wxLogMessage("Sorting by Retail Price...");

    std::sort(inventory.begin(), inventory.end(), [](const Part& a, const Part& b) {
        return a.getPartRetail() < b.getPartRetail();
        });

    partList->DeleteAllItems();
    for (const auto& part : inventory) {
        long index = partList->GetItemCount();
        partList->InsertItem(index, part.getPartNumber());
        partList->SetItem(index, 1, part.getPartDescription());
        partList->SetItem(index, 2, std::to_string(part.getPartCost()));
        partList->SetItem(index, 3, std::to_string(part.getPartRetail()));
        partList->SetItem(index, 4, part.getPartManufacturer());
        partList->SetItem(index, 5, std::to_string(part.getPartQuantity()));
        partList->SetItem(index, 6, part.getPartLocation());
    }
}

void PartsManagerFrames::OnSortManufacturer(wxListEvent& event) {
    wxLogMessage("Sorting by Manufacturer...");

    std::sort(inventory.begin(), inventory.end(), [](const Part& a, const Part& b) {
        return a.getPartManufacturer() < b.getPartManufacturer();
        });

    partList->DeleteAllItems();
    for (const auto& part : inventory) {
        long index = partList->GetItemCount();
        partList->InsertItem(index, part.getPartNumber());
        partList->SetItem(index, 1, part.getPartDescription());
        partList->SetItem(index, 2, std::to_string(part.getPartCost()));
        partList->SetItem(index, 3, std::to_string(part.getPartRetail()));
        partList->SetItem(index, 4, part.getPartManufacturer());
        partList->SetItem(index, 5, std::to_string(part.getPartQuantity()));
        partList->SetItem(index, 6, part.getPartLocation());
    }
}

void PartsManagerFrames::OnSortPartNumber(wxListEvent& event) {
    wxLogMessage("Sorting by Part Number...");

    std::sort(inventory.begin(), inventory.end(), [](const Part& a, const Part& b) {
        return a.getPartNumber() < b.getPartNumber(); // String comparison
        });

    partList->DeleteAllItems();
    for (const auto& part : inventory) {
        long index = partList->GetItemCount();
        partList->InsertItem(index, part.getPartNumber());
        partList->SetItem(index, 1, part.getPartDescription());
        partList->SetItem(index, 2, std::to_string(part.getPartCost()));
        partList->SetItem(index, 3, std::to_string(part.getPartRetail()));
        partList->SetItem(index, 4, part.getPartManufacturer());
        partList->SetItem(index, 5, std::to_string(part.getPartQuantity()));
        partList->SetItem(index, 6, part.getPartLocation());
    }
}

void PartsManagerFrames::OnSortQuantity(wxListEvent& event) {
    wxLogMessage("Sorting by Quantity...");

    std::sort(inventory.begin(), inventory.end(), [](const Part& a, const Part& b) {
        return a.getPartQuantity() < b.getPartQuantity();
        });

    partList->DeleteAllItems();
    for (const auto& part : inventory) {
        long index = partList->GetItemCount();
        partList->InsertItem(index, part.getPartNumber());
        partList->SetItem(index, 1, part.getPartDescription());
        partList->SetItem(index, 2, std::to_string(part.getPartCost()));
        partList->SetItem(index, 3, std::to_string(part.getPartRetail()));
        partList->SetItem(index, 4, part.getPartManufacturer());
        partList->SetItem(index, 5, std::to_string(part.getPartQuantity()));
        partList->SetItem(index, 6, part.getPartLocation());
    }
}

void PartsManagerFrames::save_to_file(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        wxMessageBox("Failed to open file for saving.", "Error", wxOK | wxICON_ERROR);
        wxLogMessage("Failed to open file for saving: %s", filename);
        return;
    }
    wxLogMessage("Saving inventory to file: %s", filename);
    wxLogMessage("Inventory size: %d", inventory.size());
    for (const auto& part : inventory) {
        wxLogMessage("Saving part: %s", part.getPartNumber());
        out << part.getPartNumber() << ","
            << part.getPartDescription() << ","
            << part.getPartCost() << ","
            << part.getPartRetail() << ","
            << part.getPartManufacturer() << ","
            << part.getPartQuantity() << ","
            << part.getPartLocation() << "\n";
    }
    out.close();
    wxLogMessage("Inventory saved to file: %s", filename);
}

void PartsManagerFrames::load_from_file(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        wxMessageBox("Failed to open file for loading.", "Error", wxOK | wxICON_ERROR);
        wxLogMessage("Failed to open file for loading: %s", filename);
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        Part part;
        std::string part_number, part_description, part_manufacturer, part_location;
        double part_cost, part_retail;
        int part_quantity;

        std::getline(iss, part_number, ',');
        std::getline(iss, part_description, ',');
        iss >> part_cost;
        iss.ignore(1, ',');
        iss >> part_retail;
        iss.ignore(1, ',');
        std::getline(iss, part_manufacturer, ',');
        iss >> part_quantity;
        iss.ignore(1, ',');
        std::getline(iss, part_location, ',');

        part.setPartNumber(part_number);
        part.setPartDescription(part_description);
        part.setPartCost(part_cost);
        part.setPartRetail(part_retail);
        part.setPartManufacturer(part_manufacturer);
        part.setPartQuantity(part_quantity);
        part.setPartLocation(part_location);

        inventory.push_back(part);

        long index = partList->GetItemCount();
        partList->InsertItem(index, part.getPartNumber());
        partList->SetItem(index, 1, part.getPartDescription());
        partList->SetItem(index, 2, std::to_string(part.getPartCost()));
        partList->SetItem(index, 3, std::to_string(part.getPartRetail()));
        partList->SetItem(index, 4, part.getPartManufacturer());
        partList->SetItem(index, 5, std::to_string(part.getPartQuantity()));
        partList->SetItem(index, 6, part.getPartLocation());
    }
    in.close();
    wxLogMessage("Inventory loaded from file: %s", filename);
    UpdateTotalCost(); // Update total cost after loading
}

void PartsManagerFrames::OnItemSelected(wxListEvent& event) {
    selectedPartIndex = event.GetIndex();
    editButton->Enable(selectedPartIndex != -1);
    deleteButton->Enable(selectedPartIndex != -1);
}

void PartsManagerFrames::OnItemDeselected(wxListEvent& event) {
    selectedPartIndex = -1;
    editButton->Disable();
    deleteButton->Disable();
}

void PartsManagerFrames::OnAddPart(wxCommandEvent& event) {
    AddPartDialogs dlg(this, "", "", "", "", "", "", "");
    if (dlg.ShowModal() == wxID_OK) {
        long index = partList->GetItemCount();
        partList->InsertItem(index, dlg.GetPartNumber());
        partList->SetItem(index, 1, dlg.GetDescription());
        partList->SetItem(index, 2, dlg.GetCost());
        partList->SetItem(index, 3, dlg.GetRetail());
        partList->SetItem(index, 4, dlg.GetManufacturer());
        partList->SetItem(index, 5, dlg.GetQuantity());
        partList->SetItem(index, 6, dlg.GetLocation());

        Part part;
        part.setPartNumber(dlg.GetPartNumber().ToStdString());
        part.setPartDescription(dlg.GetDescription().ToStdString());
        part.setPartCost(std::stod(dlg.GetCost().ToStdString()));
        part.setPartRetail(std::stod(dlg.GetRetail().ToStdString()));
        part.setPartManufacturer(dlg.GetManufacturer().ToStdString());
        part.setPartQuantity(std::stoi(dlg.GetQuantity().ToStdString()));
        part.setPartLocation(dlg.GetLocation().ToStdString());
        inventory.push_back(part);
        wxLogMessage("Part added: %s", part.getPartNumber());
        UpdateTotalCost(); // Update total cost after adding
    }
}

void PartsManagerFrames::OnEditPart(wxCommandEvent& event) {
    if (selectedPartIndex == -1) return;
    wxString partNumber = partList->GetItemText(selectedPartIndex);
    wxString description = partList->GetItemText(selectedPartIndex, 1);
    wxString cost = partList->GetItemText(selectedPartIndex, 2);
    wxString retail = partList->GetItemText(selectedPartIndex, 3);
    wxString manufacturer = partList->GetItemText(selectedPartIndex, 4);
    wxString quantity = partList->GetItemText(selectedPartIndex, 5);
    wxString location = partList->GetItemText(selectedPartIndex, 6);

    AddPartDialogs dlg(this, partNumber, description, cost, retail, manufacturer, quantity, location);
    if (dlg.ShowModal() == wxID_OK) {
        partList->SetItem(selectedPartIndex, 0, dlg.GetPartNumber());
        partList->SetItem(selectedPartIndex, 1, dlg.GetDescription());
        partList->SetItem(selectedPartIndex, 2, dlg.GetCost());
        partList->SetItem(selectedPartIndex, 3, dlg.GetRetail());
        partList->SetItem(selectedPartIndex, 4, dlg.GetManufacturer());
        partList->SetItem(selectedPartIndex, 5, dlg.GetQuantity());
        partList->SetItem(selectedPartIndex, 6, dlg.GetLocation());

        inventory[selectedPartIndex].setPartNumber(dlg.GetPartNumber().ToStdString());
        inventory[selectedPartIndex].setPartDescription(dlg.GetDescription().ToStdString());
        inventory[selectedPartIndex].setPartCost(std::stod(dlg.GetCost().ToStdString()));
        inventory[selectedPartIndex].setPartRetail(std::stod(dlg.GetRetail().ToStdString()));
        inventory[selectedPartIndex].setPartManufacturer(dlg.GetManufacturer().ToStdString());
        inventory[selectedPartIndex].setPartQuantity(std::stoi(dlg.GetQuantity().ToStdString()));
        inventory[selectedPartIndex].setPartLocation(dlg.GetLocation().ToStdString());
        wxLogMessage("Part edited: %s", inventory[selectedPartIndex].getPartNumber());
        UpdateTotalCost(); // Update total cost after editing
    }
}

void PartsManagerFrames::OnDeletePart(wxCommandEvent& event) {

    // Validate selectedPartIndex
    if (selectedPartIndex < 0 || selectedPartIndex >= static_cast<int>(inventory.size())) {
        return;
    }

    // Remove the part from the inventory
    inventory.erase(inventory.begin() + selectedPartIndex);

    // Remove the part from the list control
    partList->DeleteItem(selectedPartIndex);

    // Reset selectedPartIndex and disable buttons
    selectedPartIndex = -1;
    editButton->Disable();
    deleteButton->Disable();

    // Update total cost after deletion
    UpdateTotalCost();
}

void PartsManagerFrames::OnSaveChanges(wxCommandEvent& event) {
    wxLogMessage("OnSaveChanges called.");
    save_to_file("inventory.txt");
    wxMessageBox("Changes have been saved.", "Save", wxOK | wxICON_INFORMATION);
}

void PartsManagerFrames::OnClose(wxCloseEvent& event) {
    wxLogMessage("OnClose called.");
    save_to_file("inventory.txt");
    event.Skip();
}

void PartsManagerFrames::OnSearch(wxCommandEvent& event) {
    wxTextEntryDialog searchDialog(this, "Enter part number or description to search:", "Search Part");
    if (searchDialog.ShowModal() == wxID_OK) {
        wxString searchQuery = searchDialog.GetValue().Lower();
        partList->DeleteAllItems();

        for (const auto& part : inventory) {
            wxString partNumber = wxString(part.getPartNumber()).Lower();
            wxString description = wxString(part.getPartDescription()).Lower();
            wxString location = wxString(part.getPartLocation()).Lower();

            if (partNumber.Contains(searchQuery) || description.Contains(searchQuery) || location.Contains(searchQuery)) {
                long index = partList->GetItemCount();
                partList->InsertItem(index, part.getPartNumber());
                partList->SetItem(index, 1, part.getPartDescription());
                partList->SetItem(index, 2, std::to_string(part.getPartCost()));
                partList->SetItem(index, 3, std::to_string(part.getPartRetail()));
                partList->SetItem(index, 4, part.getPartManufacturer());
                partList->SetItem(index, 5, std::to_string(part.getPartQuantity()));
                partList->SetItem(index, 6, part.getPartLocation());
            }
        }

        if (partList->GetItemCount() == 0) {
            wxMessageBox("No parts found.", "Search Result", wxOK | wxICON_INFORMATION);
        }
        UpdateTotalCost(); // Update total cost after search (optional, as list may be filtered)
    }
}

void PartsManagerFrames::OnShowAll(wxCommandEvent& event) {
    partList->DeleteAllItems();

    for (const auto& part : inventory) {
        long index = partList->GetItemCount();
        partList->InsertItem(index, part.getPartNumber());
        partList->SetItem(index, 1, part.getPartDescription());
        partList->SetItem(index, 2, std::to_string(part.getPartCost()));
        partList->SetItem(index, 3, std::to_string(part.getPartRetail()));
        partList->SetItem(index, 4, part.getPartManufacturer());
        partList->SetItem(index, 5, std::to_string(part.getPartQuantity()));
        partList->SetItem(index, 6, part.getPartLocation());
    }
    UpdateTotalCost(); // Update total cost after showing all
}

// SortList not implemented; placeholder to avoid linker error
void PartsManagerFrames::SortList(wxListEvent& event) {
    OnSortColumn(event);
}
