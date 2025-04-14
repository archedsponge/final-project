#include "Part.h"

Part::Part(const std::string& part_number, const std::string& part_description, double part_cost, double part_retail, const std::string& part_manufacturer, int part_quantity, const std::string& part_location)
    : part_number(part_number), part_description(part_description), part_cost(part_cost), part_retail(part_retail), part_manufacturer(part_manufacturer), part_quantity(part_quantity), part_location(part_location) {
}

std::string Part::getPartNumber() const { return part_number; }
std::string Part::getPartDescription() const { return part_description; }
double Part::getPartCost() const { return part_cost; }
double Part::getPartRetail() const { return part_retail; }
std::string Part::getPartManufacturer() const { return part_manufacturer; }
int Part::getPartQuantity() const { return part_quantity; }
std::string Part::getPartLocation() const { return part_location; }

void Part::setPartNumber(const std::string& part_number) { this->part_number = part_number; }
void Part::setPartDescription(const std::string& part_description) { this->part_description = part_description; }
void Part::setPartCost(double part_cost) { this->part_cost = part_cost; }
void Part::setPartRetail(double part_retail) { this->part_retail = part_retail; }
void Part::setPartManufacturer(const std::string& part_manufacturer) { this->part_manufacturer = part_manufacturer; }
void Part::setPartQuantity(int part_quantity) { this->part_quantity = part_quantity; }
void Part::setPartLocation(const std::string& part_location) { this->part_location = part_location; }
