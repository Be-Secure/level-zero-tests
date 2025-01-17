/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "test_harness/test_harness.hpp"
#include "logging/logging.hpp"

namespace lzt = level_zero_tests;

namespace {

void check_image_properties(ze_image_properties_t imageprop) {

  EXPECT_TRUE((static_cast<uint32_t>(imageprop.samplerFilterFlags) == 0) ||
              ((static_cast<uint32_t>(imageprop.samplerFilterFlags) &
                static_cast<uint32_t>(ZE_IMAGE_SAMPLER_FILTER_FLAG_POINT)) ==
               static_cast<uint32_t>(ZE_IMAGE_SAMPLER_FILTER_FLAG_POINT)) ||
              ((static_cast<uint32_t>(imageprop.samplerFilterFlags) &
                static_cast<uint32_t>(ZE_IMAGE_SAMPLER_FILTER_FLAG_LINEAR)) ==
               static_cast<uint32_t>(ZE_IMAGE_SAMPLER_FILTER_FLAG_LINEAR)));
}

void image_create_test_1d(ze_image_format_type_t format_type,
                          ze_image_format_layout_t layout, bool useArrayImage,
                          bool properties_only) {

  for (auto image_rw_flag : lzt::image_rw_flags) {
    for (auto image_cache_flag : lzt::image_cache_flags) {
      for (auto image_width : lzt::image_widths) {

        ze_image_type_t image_type;
        uint32_t array_levels;
        if (useArrayImage) {
          image_type = ZE_IMAGE_TYPE_1DARRAY;
          array_levels = 1;
        } else {
          image_type = ZE_IMAGE_TYPE_1D;
          array_levels = 0;
        }

        ze_image_handle_t image;
        ze_image_format_t format_descriptor = {
            layout,                    // layout
            format_type,               // type
            ZE_IMAGE_FORMAT_SWIZZLE_R, // x
            ZE_IMAGE_FORMAT_SWIZZLE_G, // y
            ZE_IMAGE_FORMAT_SWIZZLE_B, // z
            ZE_IMAGE_FORMAT_SWIZZLE_A  // w
        };
        ze_image_flag_t flags =
            (ze_image_flag_t)(image_rw_flag | image_cache_flag);
        ze_image_desc_t image_descriptor = {};
        image_descriptor.stype = ZE_STRUCTURE_TYPE_IMAGE_DESC;
        image_descriptor.flags = flags;
        image_descriptor.type = image_type;
        image_descriptor.format = format_descriptor;
        image_descriptor.width = image_width;
        image_descriptor.height = 1;
        image_descriptor.depth = 1;
        image_descriptor.arraylevels = array_levels;
        image_descriptor.miplevels = 0;

        lzt::print_image_descriptor(image_descriptor);
        if (properties_only) {
          check_image_properties(
              lzt::get_ze_image_properties(image_descriptor));
        } else {
          image = lzt::create_ze_image(image_descriptor);
          if (image) {
            lzt::destroy_ze_image(image);
          }
        }
      }
    }
  }
}

void image_create_test_2d(ze_image_format_type_t format_type,
                          ze_image_format_layout_t layout, bool useArrayImage,
                          bool properties_only) {

  for (auto image_rw_flag : lzt::image_rw_flags) {
    for (auto image_cache_flag : lzt::image_cache_flags) {
      for (auto image_width : lzt::image_widths) {
        for (auto image_height : lzt::image_heights) {

          ze_image_type_t image_type;
          uint32_t array_levels;
          if (useArrayImage) {
            image_type = ZE_IMAGE_TYPE_2DARRAY;
            array_levels = 2;
          } else {
            image_type = ZE_IMAGE_TYPE_2D;
            array_levels = 0;
          }

          ze_image_handle_t image;
          ze_image_format_t format_descriptor = {
              layout,                    // layout
              format_type,               // type
              ZE_IMAGE_FORMAT_SWIZZLE_R, // x
              ZE_IMAGE_FORMAT_SWIZZLE_G, // y
              ZE_IMAGE_FORMAT_SWIZZLE_B, // z
              ZE_IMAGE_FORMAT_SWIZZLE_A  // w
          };
          ze_image_flag_t flags =
              (ze_image_flag_t)(image_rw_flag | image_cache_flag);
          ze_image_desc_t image_descriptor = {};
          image_descriptor.stype = ZE_STRUCTURE_TYPE_IMAGE_DESC;
          image_descriptor.flags = flags;
          image_descriptor.type = image_type;
          image_descriptor.format = format_descriptor;
          image_descriptor.width = image_width;
          image_descriptor.height = image_height;
          image_descriptor.depth = 1;
          image_descriptor.arraylevels = array_levels;
          image_descriptor.miplevels = 0;

          lzt::print_image_descriptor(image_descriptor);
          if (properties_only) {
            check_image_properties(
                lzt::get_ze_image_properties(image_descriptor));
          } else {
            image = lzt::create_ze_image(image_descriptor);
            if (image) {
              lzt::destroy_ze_image(image);
            }
          }
        }
      }
    }
  }
}

void image_create_test_3d(ze_image_format_type_t format_type,
                          ze_image_format_layout_t layout,
                          bool properties_only) {

  for (auto image_rw_flag : lzt::image_rw_flags) {
    for (auto image_cache_flag : lzt::image_cache_flags) {
      for (auto image_width : lzt::image_widths) {
        for (auto image_height : lzt::image_heights) {
          for (auto image_depth : lzt::image_depths) {

            ze_image_type_t image_type = ZE_IMAGE_TYPE_3D;
            ze_image_handle_t image;
            ze_image_format_t format_descriptor = {
                layout,                    // layout
                format_type,               // type
                ZE_IMAGE_FORMAT_SWIZZLE_R, // x
                ZE_IMAGE_FORMAT_SWIZZLE_G, // y
                ZE_IMAGE_FORMAT_SWIZZLE_B, // z
                ZE_IMAGE_FORMAT_SWIZZLE_A  // w
            };
            ze_image_flag_t flags =
                (ze_image_flag_t)(image_rw_flag | image_cache_flag);
            ze_image_desc_t image_descriptor = {};
            image_descriptor.stype = ZE_STRUCTURE_TYPE_IMAGE_DESC;
            image_descriptor.flags = flags;
            image_descriptor.type = image_type;
            image_descriptor.format = format_descriptor;
            image_descriptor.width = image_width;
            image_descriptor.height = image_height;
            image_descriptor.depth = image_depth;
            image_descriptor.arraylevels = 0;
            image_descriptor.miplevels = 0;

            lzt::print_image_descriptor(image_descriptor);
            if (properties_only) {
              check_image_properties(
                  lzt::get_ze_image_properties(image_descriptor));
            } else {
              image = lzt::create_ze_image(image_descriptor);
              if (image) {
                lzt::destroy_ze_image(image);
              }
            }
          }
        }
      }
    }
  }
}

class zeImageCreateTests : public ::testing::Test {};

TEST(zeImageCreateTests,
     GivenValidDescriptorWhenCreatingUINTImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = false;

  for (auto layout : lzt::image_format_layout_uint) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_UINT, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_UINT, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_UINT, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_UINT, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_UINT, layout, properties_only);
  }
}

TEST(zeImageCreateTests,
     GivenValidDescriptorWhenCreatingSINTImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = false;

  for (auto layout : lzt::image_format_layout_sint) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_SINT, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_SINT, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_SINT, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_SINT, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_SINT, layout, properties_only);
  }
}

TEST(zeImageCreateTests,
     GivenValidDescriptorWhenCreatingUNORMImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = false;

  for (auto layout : lzt::image_format_layout_unorm) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_UNORM, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_UNORM, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_UNORM, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_UNORM, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_UNORM, layout, properties_only);
  }
}

TEST(zeImageCreateTests,
     GivenValidDescriptorWhenCreatingSNORMImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = false;

  for (auto layout : lzt::image_format_layout_snorm) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_SNORM, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_SNORM, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_SNORM, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_SNORM, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_SNORM, layout, properties_only);
  }
}

TEST(zeImageCreateTests,
     GivenValidDescriptorWhenCreatingFLOATImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = false;

  for (auto layout : lzt::image_format_layout_float) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, properties_only);
  }
}

TEST(zeImageCreateTests,
     GivenValidDescriptorWhenCreatingMediaImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = false;

  for (auto layout : lzt::image_format_media_layouts) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, properties_only);
  }
}

class zeImageGetPropertiesTests : public ::testing::Test {};

TEST(zeImageGetPropertiesTests,
     GivenValidDescriptorWhenCreatingUINTImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = true;

  for (auto layout : lzt::image_format_layout_uint) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_UINT, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_UINT, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_UINT, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_UINT, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_UINT, layout, properties_only);
  }
}

TEST(zeImageGetPropertiesTests,
     GivenValidDescriptorWhenCreatingSINTImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = true;

  for (auto layout : lzt::image_format_layout_sint) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_SINT, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_SINT, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_SINT, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_SINT, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_SINT, layout, properties_only);
  }
}

TEST(zeImageGetPropertiesTests,
     GivenValidDescriptorWhenCreatingUNORMImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = true;

  for (auto layout : lzt::image_format_layout_unorm) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_UNORM, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_UNORM, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_UNORM, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_UNORM, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_UNORM, layout, properties_only);
  }
}

TEST(zeImageGetPropertiesTests,
     GivenValidDescriptorWhenCreatingSNORMImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = true;

  for (auto layout : lzt::image_format_layout_snorm) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_SNORM, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_SNORM, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_SNORM, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_SNORM, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_SNORM, layout, properties_only);
  }
}

TEST(zeImageGetPropertiesTests,
     GivenValidDescriptorWhenCreatingFLOATImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = true;

  for (auto layout : lzt::image_format_layout_float) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, properties_only);
  }
}

TEST(zeImageGetPropertiesTests,
     GivenValidDescriptorWhenCreatingMediaImageThenNotNullPointerIsReturned) {
  if (!(lzt::image_support())) {
    LOG_INFO << "device does not support images, cannot run test";
    SUCCEED();
    return;
  }
  bool properties_only = true;

  for (auto layout : lzt::image_format_media_layouts) {
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, true,
                         properties_only);
    image_create_test_1d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, false,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, true,
                         properties_only);
    image_create_test_2d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, false,
                         properties_only);
    image_create_test_3d(ZE_IMAGE_FORMAT_TYPE_FLOAT, layout, properties_only);
  }
}

} // namespace
