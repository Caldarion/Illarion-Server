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


#ifndef _CHARACTERCONTAINER_HPP_
#define _CHARACTERCONTAINER_HPP_

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <boost/lexical_cast.hpp>
#include "globals.hpp"
#include "utility.hpp"
#include "constants.hpp"


template <class T>
class CharacterContainer {
public:
    typedef T* pointer;

private:
    typedef std::function<void(pointer)> for_each_type;
    typedef void(T::*for_each_member_type)();
    typedef typename std::unordered_map<TYPE_OF_CHARACTER_ID, pointer> container_type;
    typedef typename std::multimap<position, TYPE_OF_CHARACTER_ID,PositionComparison> position_to_id_type;
    position_to_id_type position_to_id;
    container_type container;

    bool getPosition(TYPE_OF_CHARACTER_ID id,position& pos);
    iterator_range<position_to_id_type::const_iterator> projection_x_axis(const position& pos, int r) const;

public:
    bool empty() const {
        return container.empty();
    }

    auto size() const -> decltype(container.size()) {
        return container.size();
    }

    void insert(pointer p) {
        const auto id = p->getId();
        
        if (!find(id)) {
            container.emplace(id, p);
            position_to_id.insert(std::make_pair(p->getPosition(), id));
        }
    }

    pointer find(const std::string &name) const;
    pointer find(TYPE_OF_CHARACTER_ID id) const;
    pointer find(const position &pos) const;
    void update(pointer p, const position& newPosition);
    bool erase(TYPE_OF_CHARACTER_ID id);
    void clear() {
        container.clear();
        position_to_id.clear();
    }

    std::vector<pointer> findAllCharactersInRangeOf(const position &pos, const Range &range) const;
    std::vector<pointer> findAllCharactersInScreen(const position &pos) const;
    std::vector<pointer> findAllAliveCharactersInRangeOf(const position &pos, const Range &range) const;
    bool findAllCharactersWithXInRangeOf(short int startx, short int endx, std::vector<pointer> &ret) const;

    void for_each(const for_each_type &function) {
        for (const auto &key_value : container) {
            function(key_value.second);
        }
    }

    void for_each(const for_each_type &function) const {
        for (const auto &key_value : container) {
            function(key_value.second);
        }
    }

    void for_each(const for_each_member_type &function) {
        for (const auto &key_value : container) {
            (key_value.second->*function)();
        }
    }
};



#endif
