/* This file is part of the the dci project. Copyright (C) 2013-2023 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "pch.hpp"

namespace dci::module::ppn::topology::lis::space
{
    //regular ppn identifier
    using Id = node::link::Id;

    using SmallNum = uint64;

    //small identifier - Id tip
    enum Sid : SmallNum {};

    //local centered small identifier - Sid normalized by local node id
    enum Csid : SmallNum {};

    //tip little endian
    Sid& sid_l(Id& id);
    const Sid& sid_l(const Id& id);

    //tip native endian
    Sid sid(const Id& id);

    void setSid(Id& id, Sid sid);
    Id id(Sid sid);

    Csid csid(Sid sidBase, Sid sidTarget);
    Csid csid(const Id& idBase, const Id& idTarget);

    struct Range
    {
        SmallNum _min {};
        SmallNum _max {};
    };

    std::vector<Range> ranges(Sid sidBase, Csid csidTargetMin, Csid csidTargetMax);
    std::vector<Range> ranges(const Id& idBase, Csid csidTargetMin, Csid csidTargetMax);

    SmallNum dist(const Id& id1, const Id& id2);
}
