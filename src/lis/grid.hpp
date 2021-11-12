/* This file is part of the the dci project. Copyright (C) 2013-2021 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "pch.hpp"
#include "grid/kernel.hpp"
#include "grid/bar.hpp"
#include "space.hpp"

namespace dci::module::ppn::topology
{
    class Lis;
}

namespace dci::module::ppn::topology::lis
{
    class Grid
    {
    public:
        Grid(Lis* lis);
        ~Grid();

        void start();
        void stop();

    public:
        void setup(uint8 bits, uint16 size);
        const grid::Kernel& kernel() const;
        bool fillRequest(List<api::GridFillingStep>& filling);

    public:
        void joined(const space::Id& id, const node::link::Remote<>& r);
        void disjoined(const space::Id& id, const node::link::Remote<>& r);

        void state(const space::Id& id, real64 rating);

        void demand(const space::Id& id, real64 weight, demand::NeedHolder<>&& d);

    private:
        grid::Bar& bar(space::Csid csid);

    public://for bars
        void requestRatings(space::Csid csidStart, space::Csid csidStop);
        void requestDemand(const space::Id& id, real64 weight);

    private:
        void reindex();

    private:
        Lis *                       _lis;
        grid::Kernel                _kernel;
        std::deque<grid::BarPtr>    _bars;
    };
}
