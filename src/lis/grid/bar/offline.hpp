/* This file is part of the the dci project. Copyright (C) 2013-2021 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "pch.hpp"
#include "../../space.hpp"

namespace dci::module::ppn::topology::lis::grid::bar
{
    class Offline
    {
    public:
        Offline();
        ~Offline();

        void start();
        void stop();

        void rating (space::Csid csid, const space::Id& id, real64 v);
        void demand (space::Csid csid, const space::Id& id, real64 weight, demand::NeedHolder<>&& d);

    private:
        bool _started {false};

    private:
        struct Record
        {
            real64 _rating          {};

            bool                    _demandRequested    {};
            demand::NeedHolder<>    _demand             {};
            real64                  _demandWeight       {};
        };

        std::map<space::Id, Record> _records;
    };
}
