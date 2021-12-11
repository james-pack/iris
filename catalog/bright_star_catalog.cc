#include "catalog/bright_star_catalog.h"

#include <memory>
#include <string>

#include "catalog/catalog.pb.h"
#include "catalog/catalog_reader.h"

namespace pack::iris::catalog {

class BrightStarCatalogReader final : public CatalogReader {
 public:
  BrightStarCatalogReader(const std::string& location) : CatalogReader(location) {}

  Catalog read() const override {
    Catalog catalog{};
    catalog.set_catalog_id("Bright Star Catalog");
    return catalog;
  }
};

std::unique_ptr<CatalogReader> readBrightStarCatalog(const std::string& location) {
  return std::unique_ptr<CatalogReader>{new BrightStarCatalogReader{location}};
}

}  // namespace pack::iris::catalog
