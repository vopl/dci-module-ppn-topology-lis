/* This file is part of the the dci project. Copyright (C) 2013-2023 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#include "pch.hpp"
#include "bar.hpp"
#include "../grid.hpp"

namespace dci::module::ppn::topology::lis::grid
{
    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    Bar::Bar(Grid* grid, space::Csid csidBegin, space::Csid csidEnd)
        : _grid{grid}
        , _csidBegin{csidBegin}
        , _csidEnd{csidEnd}
    {
        dbgAssert(csidBegin < csidEnd);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    Bar::~Bar()
    {
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void Bar::start()
    {
        if(bar::Online::empty())
        {
            bar::Offline::start();
        }
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void Bar::stop()
    {
        if(bar::Online::empty())
        {
            bar::Offline::stop();
        }
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void Bar::joined(space::Csid csid, const space::Id& id, const node::link::Remote<>& r)
    {
        bar::Offline::stop();
        bar::Online::joined(csid, id, r);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void Bar::disjoined(space::Csid csid, const space::Id& id, const node::link::Remote<>& r)
    {
        bar::Online::disjoined(csid, id, r);
        if(bar::Online::empty())
        {
            bar::Offline::start();
        }
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void Bar::rating(space::Csid csid, const space::Id& id, real64 v)
    {
        if(bar::Online::empty())
        {
            bar::Offline::rating(csid, id, v);
        }
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void Bar::demand(space::Csid csid, const space::Id& id, real64 weight, demand::NeedHolder<>&& d)
    {
        if(!bar::Online::empty())
        {
            bar::Online::demand(csid, id, weight, std::move(d));
        }
        else
        {
            bar::Offline::demand(csid, id, weight, std::move(d));
        }
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    std::size_t Bar::onlineSize() const
    {
        return Online::size();
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void Bar::requestRatings()
    {
        return _grid->requestRatings(_csidBegin, _csidEnd);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void Bar::requestDemand(const space::Id& id, real64 weight)
    {
        return _grid->requestDemand(id, weight);
    }
}
