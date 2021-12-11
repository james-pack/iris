#pragma once

#include <memory>
#include <string>

#include "catalog/catalog_reader.h"

namespace pack::iris::catalog {

std::unique_ptr<CatalogReader> readBrightStarCatalog(const std::string& location);

}  // namespace pack::iris::catalog
