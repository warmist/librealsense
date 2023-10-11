// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2023 Intel Corporation. All Rights Reserved.

#pragma once

#include <memory>
#include <vector>
#include <functional>


struct rs2_device_info;


namespace librealsense {


class device_info;
class context;


// Interface for device factories, allowing for:
//      - notification callbacks for any device additions and removals
//      - querying of current devices in the system
// 
// A device factory is contained by a context, 1:1. I.e., multiple factory instances may exist at once, each for a
// different context.
//

class device_factory
{
protected:
    context & _context;

    device_factory( context & ctx )
        : _context( ctx )
    {
    }

public:
    // Callbacks take this form.
    //
    using callback = std::function< void( std::vector< rs2_device_info > & devices_removed,
                                          std::vector< rs2_device_info > & devices_added ) >;

    virtual ~device_factory() = default;

    // Query any subset of available devices and return them as device-info objects from which actual devices can be
    // created as needed.
    // 
    // Devices will match both the requested mask and the device-mask from the context settings. See
    // RS2_PRODUCT_LINE_... defines for possible values.
    //
    virtual std::vector< std::shared_ptr< device_info > > query_devices( unsigned mask ) const = 0;
};


}  // namespace librealsense