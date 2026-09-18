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

#include "part.h"

namespace mu::engraving {
// Map from origin track to shared track
using SharedTrackMap = std::map<track_idx_t, track_idx_t>;
std::string dump(const SharedTrackMap& map);

struct SharedTrackMapByTickEntry {
    SharedTrackMapByTickEntry() {}
    SharedTrackMapByTickEntry(SharedTrackMap trackMap, bool isUserModified = false)
        : m_sharedTrackMap(trackMap), m_isUserModified(isUserModified) {}

    const SharedTrackMap& sharedTrackMap() const { return m_sharedTrackMap; }
    void setSharedTrackMap(SharedTrackMap map) { m_sharedTrackMap = map; }

    void setIsUserModified(bool val) { m_isUserModified = val; }
    bool isUserModified() const { return m_isUserModified; }

    void setIsReset(bool val) { m_isReset = val; }
    bool isReset() const { return m_isReset; }

    bool operator==(const SharedTrackMapByTickEntry& other) const
    {
        return m_sharedTrackMap == other.m_sharedTrackMap && m_isUserModified == other.m_isUserModified;
    }

    bool operator!=(const SharedTrackMapByTickEntry& other) const { return !(*this == other); }

private:
    SharedTrackMap m_sharedTrackMap;
    bool m_isUserModified = false;
    bool m_isReset = false;
};

class SharedPart final : public Part
{
    OBJECT_ALLOCATOR(engraving, SharedPart)
    DECLARE_CLASSOF(ElementType::SHARED_PART)

public:
    SharedPart(Score* score);

    void addOriginPart(Part* p);
    void removeOriginPart(Part* p);
    const std::vector<Part*>& originParts() const { return m_originParts; }

    String partName() const override;

    PropertyValue getProperty(Pid pid) const override;
    PropertyValue propertyDefault(Pid pid) const override;
    bool setProperty(Pid pid, const PropertyValue& v) override;

    bool enabled() const;
    bool show() const override;

    const SharedTrackMapByTickEntry& trackMapAtTick(const Fraction& tick) const;
    void setTrackMapAtTick(const SharedTrackMapByTickEntry& map, const Fraction& tick);
    void removeMapAtTick(const Fraction& tick);
    void removeMapsBetweenTicks(const Fraction& startTick, const Fraction& endTick, bool removeUserChanges);
    std::map<Fraction, SharedTrackMapByTickEntry> trackMapsBetweenTicks(const Fraction& startTick, const Fraction& endTick) const;

    bool isSameInstrumentsAtTick(const Fraction& tick);

    bool isSameInstruments() const { return m_isSameInstruments; }

private:
    void computeIsSameInstruments();
    bool m_isSameInstruments = true;

    bool m_enabled = true;
    std::vector<Part*> m_originParts;
    std::map<Fraction, SharedTrackMapByTickEntry> m_trackMapsByTick { { Fraction(0, 1), SharedTrackMapByTickEntry() } };
};
}
