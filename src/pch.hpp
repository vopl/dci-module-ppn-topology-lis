/* This file is part of the the dci project. Copyright (C) 2013-2021 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <dci/host.hpp>
#include <dci/logger.hpp>
#include <dci/utils/atScopeExit.hpp>
#include <dci/utils/b2h.hpp>
#include <dci/utils/h2b.hpp>
#include <dci/utils/endian.hpp>
#include <dci/utils/net/url.hpp>
#include <dci/poll/timer.hpp>
#include <dci/stiac.hpp>
#include <dci/config.hpp>
#include <dci/mm/heap/allocable.hpp>
#include <dci/poll/timer.hpp>
#include <cmath>
#include "ppn/topology/lis.hpp"

namespace dci::module::ppn::topology
{
    using namespace dci;

    namespace transport     = idl::ppn::transport;
    namespace node          = idl::ppn::node;
    namespace rdb           = idl::ppn::node::rdb;
    namespace pql           = idl::ppn::node::rdb::pql;
    namespace api           = idl::ppn::topology::lis;
    namespace connectivity  = idl::ppn::connectivity;
    namespace demand        = idl::ppn::connectivity::demand;
}
