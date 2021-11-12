/* This file is part of the the dci project. Copyright (C) 2013-2021 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#include "pch.hpp"
#include "kernel.hpp"

namespace dci::module::ppn::topology::lis::grid
{
    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    Kernel::Kernel()
    {
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    Kernel::Kernel(uint8 bits, uint16 size)
        : _bits{std::clamp(bits, _bitsMin, _bitsMax)}
        , _size{std::clamp(size, _sizeMin, _sizeMax)}
        , _stepMult{std::pow(0.5, static_cast<real64>(_bits)/_size)}
    {
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    Kernel::Kernel(const Kernel& another)
        : _bits{another._bits}
        , _size{another._size}
        , _stepMult{another._stepMult}
    {
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    Kernel::~Kernel()
    {
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    bool Kernel::change(uint8 bits, uint16 size)
    {
        bits = std::clamp(bits, _bitsMin, _bitsMax);
        size = std::clamp(size, _sizeMin, _sizeMax);

        if(_bits == bits && _size == size)
        {
            return false;
        }

        _bits = bits;
        _size = size;
        _stepMult = std::pow(0.5, static_cast<real64>(_bits)/_size);

        return true;
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    Kernel& Kernel::operator=(const Kernel& another)
    {
        _bits = another._bits;
        _size = another._size;
        _stepMult = another._stepMult;

        return *this;
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    bool Kernel::operator==(const Kernel& another) const
    {
        return std::tie(_bits, _size) == std::tie(another._bits, another._size);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    bool Kernel::operator!=(const Kernel& another) const
    {
        return !operator==(another);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    uint8 Kernel::bits() const
    {
        return _bits;
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    uint16 Kernel::size() const
    {
        return _size;
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    std::size_t Kernel::idx(space::Csid csid) const
    {
        real64 dist01 = static_cast<real64>(csid) / 0x1p64;

        dbgAssert(0 <= dist01);
        dbgAssert(1 >= dist01);

        if(dist01 <= std::numeric_limits<real64>::min())
        {
            return _size-1;
        }

        real64 r = log(dist01) / log(_stepMult);
        dbgAssert(std::isnormal(r));

        if(r >= _size-1)
        {
            return _size-1;
        }

        if(r <= 0)
        {
            return 0;
        }

        return static_cast<std::size_t>(r);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    space::Csid Kernel::csid(std::size_t idx) const
    {
        dbgAssert(idx <= _size);

        if(idx >= _size)
        {
            return {};
        }

        real64 dist01 = std::pow(_stepMult, idx);
        real64 dist64 = dist01 * 0x1p64;

        space::SmallNum res = static_cast<space::SmallNum>(dist64 + 0.5);

        if(res < static_cast<space::SmallNum>(dist64/2))
        {
            res = ~space::SmallNum{};
        }

        return static_cast<space::Csid>(res);
    }
}
