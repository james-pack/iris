#include "catalog/bright_star_catalog.h"

#include <errno.h>

#include <charconv>
#include <exception>
#include <fstream>
#include <memory>
#include <string>
#include <string_view>
#include <system_error>

#include "catalog/catalog.pb.h"
#include "catalog/catalog_reader.h"

namespace pack::iris::catalog {

namespace {

template <typename T>
T ExtractValue(int& offset, int length, const std::string& buffer, T& value) {
  using std::to_string;
  std::string_view chars(buffer.data() + offset, length);
  // Remove leading space or '+' sign.
  chars.remove_prefix(std::min(chars.find_first_not_of(" +"), chars.size()));
  auto [ignored, error]{std::from_chars(chars.data(), chars.data() + chars.size(), value)};
  if (error == std::errc::invalid_argument) {
    throw std::system_error(std::make_error_code(error), "Format not matched on interval [" + to_string(offset) + "," +
                                                             to_string(length) + "] -- substring: '" +
                                                             std::string{chars} + "'");
  } else if (error == std::errc::result_out_of_range) {
    throw std::system_error(std::make_error_code(error), "Value out of range");
  }

  offset += length;
  return value;
}

template <>
float ExtractValue(int& offset, int length, const std::string& buffer, float& value) {
  using std::to_string;
  const char* begin{buffer.data() + offset};
  char* end;
  errno = 0;
  value = std::strtof(begin, &end);
  if (errno == ERANGE) {
    throw std::system_error(std::make_error_code(std::errc::result_out_of_range), "Value out of range");
  } else if (end - begin > length) {
    throw std::system_error(std::make_error_code(std::errc::invalid_argument),
                            "Format not matched on interval [" + to_string(offset) + "," + to_string(length) + "]");
  }

  offset += length;
  return value;
}

template <typename T>
T ExtractValue(int& offset, int length, const std::string& buffer) {
  T value{};
  return ExtractValue(offset, length, buffer, value);
}

std::string* ExtractNonEmptyValue(int& offset, int length, const std::string& buffer, std::string* value) {
  std::string_view chars(buffer.data() + offset, length);
  chars.remove_prefix(std::min(chars.find_first_not_of(" "), chars.size()));
  *value = chars;
  offset += length;
  return value;
}

void ExtractOptionalName(int& offset, int length, const std::string& buffer, ObjectSummary* object) {
  std::string name{};
  name.reserve(length);
  ExtractNonEmptyValue(offset, 11, buffer, &name);
  if (!name.empty()) {
    object->set_primary_name(name);
  }
}

void ExtractOptionalDesignation(int& offset, int length, const std::string& buffer, ObjectSummary* object) {
  std::string designation{};
  designation.reserve(length);
  ExtractNonEmptyValue(offset, 11, buffer, &designation);
  if (!designation.empty()) {
    *object->add_designations() = designation;
  }
}

}  // namespace

class BrightStarCatalogReader final : public CatalogReader {
 private:
  static void ParseObject(const std::string& line, ObjectSummary* object) {
    using std::to_string;
    int offset{0};

    int hr_id;
    ExtractValue(offset, 4, line, hr_id);
    object->set_object_id(to_string(hr_id));

    ExtractOptionalName(offset, 10, line, object);

    // Durchmusterung ID
    ExtractOptionalDesignation(offset, 11, line, object);
    // Henry Draper Catalog Number
    ExtractOptionalDesignation(offset, 6, line, object);
    // SAO Catalog Number
    ExtractOptionalDesignation(offset, 6, line, object);
    // FK5 star number
    ExtractOptionalDesignation(offset, 4, line, object);

    offset = 44;  // Skip some fields.

    // Aitken's Double Star Catalog (ADS) designation
    ExtractOptionalDesignation(offset, 5, line, object);

    offset = 51;  // Skip some fields.

    // Variable star identification
    ExtractOptionalDesignation(offset, 9, line, object);

    offset = 75;  // Skip some fields.

    RaDec* ra_dec_location = object->add_locations()->mutable_ra_dec();
    ra_dec_location->set_epoch("J2000");
    Time* ra = ra_dec_location->mutable_ra();
    Angle* dec = ra_dec_location->mutable_dec();
    ra->set_hour(ExtractValue<unsigned int>(offset, 2, line));
    ra->set_minute(ExtractValue<unsigned int>(offset, 2, line));
    ra->set_second(ExtractValue<float>(offset, 4, line));
    dec->set_degree(ExtractValue<int>(offset, 3, line));
    dec->set_minute(ExtractValue<unsigned int>(offset, 2, line));
    dec->set_second(ExtractValue<unsigned int>(offset, 2, line));

    LatLong* galactic_coords = object->add_locations()->mutable_galactic_coords();
    galactic_coords->set_latitude(ExtractValue<float>(offset, 6, line));
    galactic_coords->set_longitude(ExtractValue<float>(offset, 6, line));

    object->set_magnitude(ExtractValue<float>(offset, 5, line));
  }

 public:
  BrightStarCatalogReader(const std::string& location) : CatalogReader(location) {}

  Catalog Read() const override {
    Catalog catalog{};
    catalog.set_catalog_id("Bright Star Catalog");

    std::ifstream file{location_};
    if (!file) {
      throw std::runtime_error("Could not read file '" + location_ + "'");
    }

    std::string line{};
    while (std::getline(file, line)) {
      try {
        ParseObject(line, catalog.add_objects());
      } catch (const std::system_error& e) {
        catalog.mutable_objects()->RemoveLast();
      }
    }

    return catalog;
  }
};

std::unique_ptr<CatalogReader> ReadBrightStarCatalog(const std::string& location) {
  return std::unique_ptr<CatalogReader>{new BrightStarCatalogReader{location}};
}

}  // namespace pack::iris::catalog
