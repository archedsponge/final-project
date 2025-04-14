#ifndef PART_H
#define PART_H

#include <string>

class Part {
public:
    Part() = default; // Default constructor
    Part(const std::string& part_number, const std::string& part_description, double part_cost, double part_retail, const std::string& part_manufacturer, int part_quantity, const std::string& part_location);

    std::string getPartNumber() const;
    std::string getPartDescription() const;
    double getPartCost() const;
    double getPartRetail() const;
    std::string getPartManufacturer() const;
    int getPartQuantity() const;
    std::string getPartLocation() const;

    void setPartNumber(const std::string& part_number);
    void setPartDescription(const std::string& part_description);
    void setPartCost(double part_cost);
    void setPartRetail(double part_retail);
    void setPartManufacturer(const std::string& part_manufacturer);
    void setPartQuantity(int part_quantity);
    void setPartLocation(const std::string& part_location);
    std::string part_number;
    std::string part_description;
    double part_cost;
    double part_retail;
    std::string part_manufacturer;
    int part_quantity;
    std::string part_location;
private:

};

#endif // PART_H
