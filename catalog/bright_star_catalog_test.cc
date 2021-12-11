#include "catalog/bright_star_catalog.h"

#include <memory>

#include "gtest/gtest.h"

namespace pack::iris::catalog {

TEST(BrightStarCatalogReader, ContainsCatalogId) {
  std::unique_ptr<CatalogReader> reader{readBrightStarCatalog("bright_star_catalog_sample.dat")};
  Catalog catalog{reader->read()};
  EXPECT_NE("", catalog.catalog_id());
}

}  // namespace pack::iris::catalog
