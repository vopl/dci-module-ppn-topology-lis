/* This file is part of the the dci project. Copyright (C) 2013-2023 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "pch.hpp"
#include "bar/offline.hpp"
#include "bar/online.hpp"
#include "../space.hpp"

namespace dci::module::ppn::topology::lis
{
    class Grid;
}

namespace dci::module::ppn::topology::lis::grid
{
    class Bar
        : public mm::heap::Allocable<Bar>
        , private bar::Offline
        , private bar::Online
    {
    public:
        Bar(Grid* grid, space::Csid csidBegin, space::Csid csidEnd);
        ~Bar();

        void start();
        void stop();

        void joined     (space::Csid csid, const space::Id& id, const node::link::Remote<>& r);
        void disjoined  (space::Csid csid, const space::Id& id, const node::link::Remote<>& r);
        void rating     (space::Csid csid, const space::Id& id, real64 v);
        void demand     (space::Csid csid, const space::Id& id, real64 weight, demand::NeedHolder<>&& d);

        std::size_t onlineSize() const;

    private:
        void requestRatings();
        void requestDemand(const space::Id& id, real64 weight);

    private:
        friend class bar::Offline;
        friend class bar::Online;

    private:
        Grid *      _grid;
        space::Csid _csidBegin{};
        space::Csid _csidEnd{};
    };
    using BarPtr = std::unique_ptr<Bar>;
}
