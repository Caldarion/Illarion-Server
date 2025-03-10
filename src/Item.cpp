//  illarionserver - server for the game Illarion
//  Copyright 2011 Illarion e.V.
//
//  This file is part of illarionserver.
//
//  illarionserver is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  illarionserver is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with illarionserver.  If not, see <http://www.gnu.org/licenses/>.


#include "Item.hpp"
#include "data/Data.hpp"
#include <sstream>
#include <boost/lexical_cast.hpp>

bool ItemLookAt::operator==(const ItemLookAt& rhs) const {
	bool equal = true;
	equal &= (name == rhs.name);
	equal &= (rareness == rhs.rareness);
	equal &= (description == rhs.description);
	equal &= (craftedBy == rhs.craftedBy);
	equal &= (weight == rhs.weight);
	equal &= (worth == rhs.worth);
	equal &= (qualityText == rhs.qualityText);
	equal &= (durabilityText == rhs.durabilityText);
	equal &= (durabilityValue == rhs.durabilityValue);
	equal &= (diamondLevel == rhs.diamondLevel);
	equal &= (emeraldLevel == rhs.emeraldLevel);
	equal &= (rubyLevel == rhs.rubyLevel);
	equal &= (sapphireLevel == rhs.sapphireLevel);
	equal &= (amethystLevel == rhs.amethystLevel);
	equal &= (obsidianLevel == rhs.obsidianLevel);
	equal &= (topazLevel == rhs.topazLevel);
	equal &= (bonus == rhs.bonus);

	return equal;
}

bool ScriptItem::operator==(const ScriptItem& rhs) const {
	bool equal = (static_cast<const Item&>(*this) == rhs);
	equal &= (type == rhs.type);
	equal &= (pos == rhs.pos);
	equal &= (itempos == rhs.itempos);
	equal &= (owner == rhs.owner);
	equal &= (inside == rhs.inside);

	return equal;
}

bool Item::operator==(const Item& rhs) const {
	bool equal = true;
	equal &= (id == rhs.id);
	equal &= (number == rhs.number);
	equal &= (wear == rhs.wear);
	equal &= (quality == rhs.quality);
	equal &= (datamap == rhs.datamap);

	return equal;
}

Item::Item(id_type id, number_type number, wear_type wear, quality_type quality, const script_data_exchangemap &datamap):
    id(id), number(number), wear(wear), quality(quality), datamap(1) {
    setData(&datamap);
}

auto Item::increaseNumberBy(Item::number_type count) -> number_type {
    const auto &common = Data::CommonItems[id];

    if (common.isValid()) {
        count += getNumber();

        if (count >= common.MaxStack) {
            setNumber(common.MaxStack);
            count -= common.MaxStack;
        } else {
            setNumber(count);
            count = 0;
        }
    }

    return count;
}

void Item::setMinQuality(const Item &item) {
    quality_type minQuality = (quality < item.quality) ? quality : item.quality;
    minQuality /= 100;
    quality_type minDurability = (getDurability() < item.getDurability()) ? getDurability() : item.getDurability();
    quality = minQuality * 100 + minDurability;
}

void Item::setData(script_data_exchangemap const *datamap) {
    if (datamap == nullptr) {
        this->datamap.clear();
        return;
    }

    for (const auto& item : *datamap) {
        setData(item.first, item.second);
    }
}


bool Item::hasData(const script_data_exchangemap &datamap) const {
    if (datamap.empty() && !hasNoData()) {
        return false;
    }

    for (const auto& item : datamap) {
        if (getData(item.first) != item.second) {
            return false;
        }
    }

    return true;
}

bool Item::hasNoData() const {
    return datamap.empty();
}

std::string Item::getData(const std::string &key) const {
    if (datamap.find(key) != datamap.end()) {
        return datamap.at(key);
    } else {
        return "";
    }
}


void Item::setData(const std::string &key, const std::string &value) {
    if (value.length() > 0) {
        datamap[key] = value;
    } else {
        datamap.erase(key);
    }
}


void Item::setData(const std::string &key, int32_t value) {
    std::stringstream ss;
    ss << value;
    setData(key, ss.str());
}

uint16_t Item::getDepot() {
    uint16_t depotId;

    try {
        depotId = boost::lexical_cast<uint16_t>(getData("depot"));
    } catch (boost::bad_lexical_cast) {
        depotId = 1;
    }

    return depotId;
}

void Item::reset() {
    id = 0;
    number = 0;
    wear = 0;
    quality = 333;
    datamap.clear();
}


void Item::resetWear() {
    const auto &common = Data::CommonItems[id];

    if (common.isValid()) {
        if (!common.rotsInInventory && common.AgeingSpeed > wear) {
            wear = common.AgeingSpeed;
        }
    }
}


void Item::save(std::ostream &obj) const {
    obj.write((char *) &id, sizeof(id_type));
    obj.write((char *) &number, sizeof(number_type));
    obj.write((char *) &wear, sizeof(wear_type));
    obj.write((char *) &quality, sizeof(quality_type));
    uint8_t mapsize = static_cast<uint8_t>(datamap.size());
    obj.write((char *) &mapsize, sizeof(uint8_t));

    for (auto it = datamap.begin(); it != datamap.end(); ++it) {
        uint8_t sz1 = static_cast<uint8_t>(it->first.size());
        uint8_t sz2 = static_cast<uint8_t>(it->second.size());
        obj.write((char *) &sz1 , sizeof(uint8_t));
        obj.write((char *) &sz2 , sizeof(uint8_t));
        obj.write((char *) it->first.data() , sz1);
        obj.write((char *) it->second.data() , sz2);
    }
}


void Item::load(std::istream &obj) {
    obj.read((char *) &id, sizeof(id_type));
    obj.read((char *) &number, sizeof(number_type));
    obj.read((char *) &wear, sizeof(wear_type));
    obj.read((char *) &quality, sizeof(quality_type));
    uint8_t tempsize;
    obj.read((char *) &tempsize, sizeof(uint8_t));
    char readStr[255];

    for (int i = 0; i < tempsize; ++i) {
        uint8_t sz1 = 0;
        uint8_t sz2 = 0;
        obj.read((char *) &sz1, sizeof(uint8_t));
        obj.read((char *) &sz2, sizeof(uint8_t));
        obj.read((char *) readStr, sz1);
        std::string key(readStr,sz1);
        obj.read((char *) readStr, sz2);
        std::string value(readStr,sz2);
        datamap[key] = value;
    }
}


bool Item::survivesAgeing() {
    if (wear != 255 && wear != 0) {
        --wear;
    }

    return wear > 0;
}

bool Item::isContainer() const {
    return Data::ContainerItems.exists(id);
}

TYPE_OF_VOLUME Item::getVolume() const {
    const auto &common = Data::CommonItems[id];

    if (common.isValid()) {
        return common.Volume;
    }

    return 0;
}

TYPE_OF_WEIGHT Item::getWeight() const {
    const auto &common = Data::CommonItems[id];

    if (common.isValid()) {
        return common.Weight * number;
    }

    return 0;
}

TYPE_OF_WORTH Item::getWorth() const {
    const auto &common = Data::CommonItems[id];

    if (common.isValid()) {
        return common.Worth * number;
    }

    return 0;
}

auto Item::getMaxStack() const -> number_type {
    const auto &common = Data::CommonItems[id];;

    if (common.isValid()) {
        return common.MaxStack;
    }

    return 0;
}

bool Item::isLarge() const {
    return getVolume() >= LARGE_ITEM_VOLUME;
}

bool Item::isStackable() const {
    return getMaxStack() > 1;
}

bool Item::isPermanent() const {
    return wear == PERMANENT_WEAR;
}

void Item::makePermanent() {
    wear = PERMANENT_WEAR;
}
