/* This file is part of the the dci project. Copyright (C) 2013-2022 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "pch.hpp"
#include "../space.hpp"

namespace dci::module::ppn::topology::lis
{
    class Io;
}

namespace dci::module::ppn::topology::lis::io
{
    class Online
    {
    public:
        Online(Io* io, const space::Id& id);
        ~Online();

        const space::Id& id() const;

        void joined(const node::link::Remote<>& r);
        void disjoined(const node::link::Remote<>& r);

        void state(real64 rating, List<transport::Address>&& addresses);

        bool empty() const;

    public:
        bool charged() const;
        const List<transport::Address>& addresses() const;

    private:
        Io *                        _io;
        space::Id                   _id;
        Set<node::link::Remote<>>   _remotes;
        real64                      _rating{};
        List<transport::Address>    _addresses;
    };
}
