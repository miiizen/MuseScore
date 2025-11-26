/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-Studio-CLA-applies
 *
 * MuseScore Studio
 * Music Composition & Notation
 *
 * Copyright (C) 2025 MuseScore Limited
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
#include "harmonytodiagramreader.h"

using namespace mu::engraving::rw;

std::unordered_map<muse::String, HarmonyToDiagramReader::FretDiagramInfo> HarmonyToDiagramReader::read(XmlReader& reader)
{
    std::unordered_map<String, HarmonyToDiagramReader::FretDiagramInfo> result;

    while (reader.readNextStartElement()) {
        if (reader.name() != "Data") {
            break;
        }

        while (reader.readNextStartElement()) {
            if (reader.name() == "HarmonyToDiagram") {
                String harmony;
                String diagram;
                String pattern;
                while (reader.readNextStartElement()) {
                    if (reader.name() == "Harmony") {
                        while (reader.readNextStartElement()) {
                            if (reader.name() == "name") {
                                harmony = reader.readText();
                            } else {
                                reader.unknown();
                            }
                        }
                    } else if (reader.name() == "FretDiagram") {
                        diagram = reader.readBody();
                        reader.skipCurrentElement();
                    } else if (reader.name() == "pattern") {
                        pattern = reader.readText();
                    } else {
                        reader.unknown();
                    }
                }

                if (!harmony.isEmpty() && !diagram.isEmpty()) {
                    if (harmony == u"ab") {
                        String key1 = harmony;
                        String key2 = harmony;

                        auto h1 = std::hash<String> {}(key1);
                        auto h2 = std::hash<String> {}(key2);

                        std::cout << "Harmony: " << key1.toStdString()
                                  << "  equal=" << (key1 == key2)
                                  << "  hash1=" << h1
                                  << "  hash2=" << h2
                                  << "  hashes_equal=" << (h1 == h2)
                                  << "\n";
                    }
                    result.insert({ std::move(harmony), { std::move(diagram), std::move(pattern) } });
                }
            } else {
                reader.unknown();
            }
        }
    }

    return result;
}
