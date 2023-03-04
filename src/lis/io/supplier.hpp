/* This file is part of the the dci project. Copyright (C) 2013-2023 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "pch.hpp"
#include "../grid/kernel.hpp"

namespace dci::module::ppn::topology::lis
{
    class Io;
}

namespace dci::module::ppn::topology::lis::io
{
    class Supplier
    {
    public:
        Supplier(Io* io);
        ~Supplier();

        sbs::Owner& sbsOwner();

        void alloc(const api::Supplier<>& s, const node::link::Remote<>& r);
        void free(const api::Supplier<>& s);
        bool empty() const;

        const transport::Address& address() const;

        void gridRequest(const grid::Kernel& gridKernel, const List<api::GridFillingStep>& filling);

    private:
        Io *                _io;
        sbs::Owner          _sbsOwner;
        api::Supplier<>     _remote;
        transport::Address  _address;
        grid::Kernel        _gridKernel;
        bool                _gridKernelSent{false};
    };
}
