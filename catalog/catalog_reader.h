#pragma once

#include <string>

#include "catalog/catalog.pb.h"

namespace pack::iris::catalog {

class CatalogReader {
 protected:
  const std::string location_;

 public:
  // Prepare to read the catalog from the given location. The location string may have different meaning for different
  // catalog readers, but will generally be either a directory or a file.
  CatalogReader(const std::string& location) : location_(location) {}
  virtual ~CatalogReader() = default;

  // Read the catalog.
  virtual Catalog read() const = 0;
};

}  // namespace pack::iris::catalog
