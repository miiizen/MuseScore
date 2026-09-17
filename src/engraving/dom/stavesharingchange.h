/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-Studio-CLA-applies
 *
 * MuseScore Studio
 * Music Composition & Notation
 *
 * Copyright (C) 2026 MuseScore Limited and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "indicatoricon.h"

namespace mu::engraving {
class StaveSharingChange final : public IndicatorIcon
{
    OBJECT_ALLOCATOR(engraving, StaveSharingChange)
    DECLARE_CLASSOF(ElementType::STAVE_SHARING_CHANGE)

public:
    StaveSharingChange(Segment* parent);
    StaveSharingChange* clone() const override { return new StaveSharingChange(*this); }

    // TODO: placeholder icon, to be replaced once the stave-sharing-change glyph is decided
    char16_t iconCode() const override { return 0xF4A0; }
};
}
