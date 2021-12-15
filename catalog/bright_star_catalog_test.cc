#include "catalog/bright_star_catalog.h"

#include <memory>
#include <string>

#include "catalog/catalog.pb.h"
#include "gtest/gtest.h"

namespace pack::iris::catalog {

const ObjectSummary* Lookup(const Catalog& catalog, const std::string& id) {
  for (const auto& object : catalog.objects()) {
    if (id == object.object_id()) {
      return &object;
    }
  }
  return nullptr;
}

::testing::AssertionResult ContainsObjectWithId(const Catalog& catalog, const std::string& id) {
  const ObjectSummary* object{Lookup(catalog, id)};
  if (object != nullptr) {
    return ::testing::AssertionSuccess();
  }
  return ::testing::AssertionFailure() << "No object with id '" << id << "' found.";
}

std::unique_ptr<CatalogReader> CreateReader() {
  return ReadBrightStarCatalog("catalog/bright_star_catalog_sample.dat");
}

TEST(BrightStarCatalogReader, ContainsCatalogId) {
  std::unique_ptr<CatalogReader> reader{CreateReader()};
  Catalog catalog{reader->Read()};
  EXPECT_NE("", catalog.catalog_id());
}

TEST(BrightStarCatalogReader, ContainsRightNumberOfObjects) {
  // Gamma Geminorum is the first star in the sample data. It has the id HR 2421. This test verifies that we can read
  // the sample and interpret at least the first line.
  std::unique_ptr<CatalogReader> reader{CreateReader()};
  Catalog catalog{reader->Read()};
  // 100 lines in sample data, but includes 2 non-stars.
  EXPECT_EQ(98, catalog.objects_size());
}

TEST(BrightStarCatalogReader, AllObjectsHaveId) {
  std::unique_ptr<CatalogReader> reader{CreateReader()};
  Catalog catalog{reader->Read()};
  for (const auto& object : catalog.objects()) {
    EXPECT_NE(object.object_id(), "");
  }
}

TEST(BrightStarCatalogReader, AllObjectsHaveRaDecLocation) {
  std::unique_ptr<CatalogReader> reader{CreateReader()};
  Catalog catalog{reader->Read()};
  for (const auto& object : catalog.objects()) {
    bool found_ra_dec{false};
    for (const auto& location : object.locations()) {
      if (location.has_ra_dec()) {
        found_ra_dec = true;
        break;
      }
    }
    EXPECT_TRUE(found_ra_dec);
  }
}

TEST(BrightStarCatalogReader, AllObjectsHaveGalacticCoords) {
  std::unique_ptr<CatalogReader> reader{CreateReader()};
  Catalog catalog{reader->Read()};
  for (const auto& object : catalog.objects()) {
    bool found_coords{false};
    for (const auto& location : object.locations()) {
      if (location.has_galactic_coords()) {
        found_coords = true;
        break;
      }
    }
    EXPECT_TRUE(found_coords);
  }
}

TEST(BrightStarCatalogReader, AllObjectsHaveMagnitude) {
  std::unique_ptr<CatalogReader> reader{CreateReader()};
  Catalog catalog{reader->Read()};
  for (const auto& object : catalog.objects()) {
    EXPECT_NE(object.magnitude(), 0.F);
  }
}

TEST(BrightStarCatalogReader, ContainsGammaGeminorum) {
  // Gamma Geminorum is the first star in the sample data. It has the id HR 2421. This test verifies that we can read
  // the sample and interpret at least the first line.
  std::unique_ptr<CatalogReader> reader{CreateReader()};
  Catalog catalog{reader->Read()};
  EXPECT_TRUE(ContainsObjectWithId(catalog, "2421"));
}

TEST(BrightStarCatalogReader, ContainsSirius) {
  std::unique_ptr<CatalogReader> reader{CreateReader()};
  Catalog catalog{reader->Read()};
  const ObjectSummary* sirius{Lookup(catalog, "2491")};
  ASSERT_NE(sirius, nullptr);
  EXPECT_NEAR(-1.47, sirius->magnitude(), 0.02);
}

}  // namespace pack::iris::catalog
